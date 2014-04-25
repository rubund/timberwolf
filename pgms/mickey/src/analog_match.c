#ifndef lint
static char SccsId[] = "@(#)analog_match.c	Yale Version 2.6 5/16/91";
#endif
/* -----------------------------------------------------------------

	FILE:		analog_match.c
	AUTHOR:		Dahe Chen
	DATE:		Mon May 14 21:53:43 EDT 1990
	CONTENTS: This file contains functions reading a set of nets
		from the file ckt.mtch that are to be matched on
		either capacitance or resistance or both. Sort all
		the routes in the nets by corresponding paramter and
		find a sub-array with the maximum number of elements.
	REVISION:
		Wed Nov 28 18:51:51 EST 1990
	    Change the code reading data and add the code handling
	    errors.
		Fri Dec  7 12:55:42 EST 1990
	    Initialize the variable numtokens.
		Fri Dec  7 13:18:16 EST 1990
	    Rewrite the functions.
		Tue Feb  5 11:44:41 EST 1991
	    Change the keywords to net_cap_match, net_res_match and
	    net_mix_match.
		Tue Feb  5 11:53:33 EST 1991
	    Reformat error message output.

----------------------------------------------------------------- */

#include <yalecad/string.h>
#include <define.h>
#include <gg_router.h>
#include <macros.h>
#include <dgraph.h>
#include <analog.h>

typedef struct term_list {
    int net;
    int route;
    float key;
} TLIST,
*TLISTPTR ;

static int max;
static int min;
static int numterms;

static NLISTPTR Pnlist;
static NLISTPTR Pnew;
static TLISTPTR *Aterms;

void
analog_match()
{

    void analog_match_routes();

    char input[LRECL];
    char **tokens;
    INT numtokens;
    register int i;
    register int j;
    register int k;
    register int n;
    int length;
    int nummatch;
    int *Anarray;
    int *Astatus;

    ROUTPTR *Aroute;
    OFSETPTR Pelist;
    OFSETPTR Ptlist;

    CAP_MATCH = FALSE;
    MIX_MATCH = FALSE;
    RES_MATCH = FALSE;

    Anarray = (int *) Ysafe_calloc((numnets+1), sizeof(int));
    Astatus = (int *) Ysafe_malloc((NUMTREES+1) * sizeof(int));

    while (fgets(input, LRECL, fin))
    {
	tokens = Ystrparser(input, " \n\t", &numtokens);

	if (numtokens == 0)
	{
	    continue;
	}

	if (strncmp(tokens[0], "net_mix_match", 13) == STRINGEQ)
	{
	    MIX_MATCH = atoi(tokens[1]);
	}
	else if (strncmp(tokens[0], "net_cap_match", 13) == STRINGEQ)
	{
	    CAP_MATCH = atoi(tokens[1]);
	}
	else if (strncmp(tokens[0], "net_res_match", 13) == STRINGEQ)
	{
	    RES_MATCH = atoi(tokens[1]);
	}
	else
	{
	    ERROR3("\n\nUnknown keyword %s in file %s.mtch\n",
			tokens[0],
			cktName);
	    exit(GP_FAIL);
	}

	numterms = 0;
	nummatch = CAP_MATCH + MIX_MATCH + RES_MATCH;
	Pnlist = NIL(NLIST);

	if (!nummatch)
	{
	    ERROR1("\n\nNo matching type specified while reading");
	    ERROR1(" a set of nets to be matched\n\n");
	    exit(GP_FAIL);
	}

	for (i = 1; i <= nummatch; i++)
	{
	    if (!fgets(input, LRECL, fin))
	    {
		ERROR2("\n\nError while reading %s.mtch\n", cktName);
		exit(GP_FAIL);
	    }
	    tokens = Ystrparser(input, " \n\t", &numtokens);

	    if (numtokens != 2)
	    {
		ERROR2("\n\nThe number of tokens, %d, should", numtokens);
		ERROR1(" be 2\n");
		exit(GP_FAIL);
	    }

	    if (strncmp(tokens[0], "net", 3) != STRINGEQ)
	    {
		ERROR2("\n\nUnknown keyword %s", tokens[0]);
		ERROR2(" in the file %s.mtch\n\n", cktName);
		exit(GP_FAIL);
	    }

	    /***********************************************************
	    * Find the net from the net-list narray.
	    ***********************************************************/
	    n = 0; 
	    while (strcmp(narray[++n]->name, tokens[1]))
		;
	    if (Anarray[n])
	    {
		/*********************************************************
		* The net is already in a set of nets being matched.
		* Now it is in another set of nets to be matched,
		* that should be an error.
		*********************************************************/
		ERROR2("\n\nNet %s is in two different sets", tokens[1]);
		ERROR1(" of nets to be matched.\n");
		ERROR1("Mickey must quit\n\n");
		exit(GP_FAIL);
	    }
	    else
	    {
		Anarray[n] = TRUE;
		Pnew = (NLISTPTR) Ysafe_malloc(sizeof(NLIST));
		Pnew->net = n;
		Pnew->next = Pnlist;
		Pnlist = Pnew;
		numterms += narray[n]->num_of_routes;
	    }
	}

	Aterms = (TLISTPTR *) Ysafe_malloc(numterms
		    * sizeof(TLISTPTR));

	if (MIX_MATCH)
	{
	    /***********************************************************
	    * The set of nets requires that both capacitances and
	    * resistances be matched.
	    ***********************************************************/
	    i = 0;
	    for (Pnew = Pnlist; Pnew; Pnew = Pnew->next)
	    {
		Aroute = narray[Pnew->net]->Aroute;
		length = narray[Pnew->net]->num_of_routes;
		for (j = 1; j <= length; j++)
		{
		    Aterms[i] = (TLISTPTR)Ysafe_malloc(sizeof(TLIST));
		    Aterms[i]->net = Pnew->net;
		    Aterms[i]->route = j;
		    Aterms[i]->key = Aroute[j]->capacitance;
		    i++;
		}
	    }
	    analog_match_routes(C_TOLERANCE);

	    for (i = 0; i < numterms; i++)
	    {
		j = Aterms[i]->net;
		k = Aterms[i]->route;
		Aterms[i]->key = narray[j]->Aroute[k]->resistance;
	    }
	    analog_match_routes(R_TOLERANCE);
	}
	else if (CAP_MATCH)
	{
	    /***********************************************************
	    * The set of nets requires that only capacitances be
	    * matched.
	    ***********************************************************/
	    i = 0;
	    for (Pnew = Pnlist; Pnew; Pnew = Pnew->next)
	    {
		Aroute = narray[Pnew->net]->Aroute;
		length = narray[Pnew->net]->num_of_routes;
		for (j = 1; j <= length; j++)
		{
		    Aterms[i] = (TLISTPTR)Ysafe_malloc(sizeof(TLIST));
		    Aterms[i]->net = Pnew->net;
		    Aterms[i]->route = j;
		    Aterms[i]->key = Aroute[j]->capacitance;
		    i++;
		}
	    }
	    analog_match_routes(C_TOLERANCE);
	}
	else
	{
	    /***********************************************************
	    * The set of nets requires that only resistances be
	    * matched.
	    ***********************************************************/
	    i = 0;
	    for (Pnew = Pnlist; Pnew; Pnew = Pnew->next)
	    {
		Aroute = narray[Pnew->net]->Aroute;
		length = narray[Pnew->net]->num_of_routes;
		for (j = 1; j <= length; j++)
		{
		    Aterms[i] = (TLISTPTR)Ysafe_malloc(sizeof(TLIST));
		    Aterms[i]->net = Pnew->net;
		    Aterms[i]->route = j;
		    Aterms[i]->key = Aroute[j]->resistance;
		    i++;
		}
	    }
	    analog_match_routes(R_TOLERANCE);
	}

	/***********************************************************
	* Update the routes of the nets in the set to be matched.
	***********************************************************/
	if ((max - min + 1) != numterms)
	{
	    /***********************************************************
	    * There are routes discarded in the set of nets being
	    * matched. Update the route configuration.
	    ***********************************************************/
	    numterms = max - min + 1;

	    if (numterms == 0)
	    {
		/*********************************************************
		* No match can be found for the set of nets. Report
		* the status to the user and quit.
		*********************************************************/
		ERROR1("\n\nMatch for the set of nets:\n");
		for (Pnew = Pnlist; Pnew; Pnew = Pnew->next)
		{
		    ERROR2("\t\tnet %s\n", narray[Pnew->net]->name);
		}
		ERROR1("failed. Mickey must quit\n\n");
		exit(GP_FAIL);
	    }

	    for (Pnew = Pnlist; Pnew; Pnew = Pnew->next)
	    {
		n = Pnew->net;
		Aroute = narray[n]->Aroute;
		length = narray[n]->num_of_routes;
		for (i = 0; i <= NUMTREES; i++)
		{
		    Astatus[i] = FALSE;
		}
		for (i = 0; i < numterms; i++)
		{
		    if (Aterms[i]->net == n)
		    {
			j = Aterms[i]->route;
			Astatus[j] = TRUE;
		    }
		}
		for (i = 1; i <= NUMTREES; i++)
		{
		    if (!Astatus[i])
		    {
			Pelist = Aroute[i]->Pedge;
			while (Pelist)
			{
			    Ptlist = Pelist;
			    Pelist = Pelist->next;
			    Ysafe_free((char *) Ptlist);
			}
			Ysafe_free((char *) Aroute[i]);
			Aroute[i] = NIL(ROUT);
			length--;
		    }
		}
		j = 1;
		narray[n]->num_of_routes = length;
		for (i = 1; i <= NUMTREES; i++)
		{
		    if (Aroute[i])
		    {
			Aroute[j++] = Aroute[i];
		    }
		}
		narray[n]->Aroute = (ROUTPTR *) Ysafe_realloc(Aroute,
			    (length+1) * sizeof(ROUTPTR));
	    }
	}

	/***********************************************************
	* Initialize the parameters for next set of nets to be
	* matched.
	***********************************************************/
	CAP_MATCH = FALSE;
	MIX_MATCH = FALSE;
	RES_MATCH = FALSE;
	for (i = 0; i < numterms; i++)
	{
	    Ysafe_free((char *) Aterms[i]);
	}
	Ysafe_free((char *) Aterms);
    }

    Ysafe_free((char *) Anarray);

    return;

} /* end of analog_match */

/*=====================================================================
*   Return the difference of two keys.
=====================================================================*/
int
analog_comp(item1, item2)
    TLISTPTR *item1;
    TLISTPTR *item2;
{

    return((*item1)->key - (*item2)->key);

} /* end of analog_comp */

/*=====================================================================
*   The function finds the maximum number of entries in Aterms such
* that Aterms[max] - Aterms[min] <= tolerance and shifts the elements
* to the beginning of the array.
=====================================================================*/
void
analog_match_routes(tolerance)
    float tolerance;
{

    register int i;
    register int j;
    register int k;

    int analog_comp();

    Yquicksort((char *)Aterms, numterms, sizeof(TLISTPTR), analog_comp);

    i =
    j =
    min =
    max = 0;

    while (j < numterms && i < numterms)
    {
	/***********************************************************
	* Find a sub-array such that A[max] - A[min] < tolerance.
	***********************************************************/
	while (j < numterms && i < numterms
	   && (Aterms[j]->key - Aterms[i]->key) <= tolerance)
	{
	    j++;
	}
	if (j == numterms)
	{
	    j--;
	}

	/***********************************************************
	* Check if the new sub-array has more elements than the old
	* one. If so, check if the new sub-array contains routes
	* from all the nets in the set to be matched. If so, replace
	* the old sub-array with the new one.
	***********************************************************/
	if ((j - i) > (max - min))
	{
	    for (Pnew = Pnlist; Pnew; Pnew = Pnew->next)
	    {
		for (k = i; k <= j; k++)
		{
		    if (Aterms[k]->net == Pnew->net)
		    {
			break;
		    }
		}

		if (k > j)
		{
		    /*****************************************************
		    * The new sub-array does not contain routes from all
		    * the nets in the set to be matched.
		    *****************************************************/
		    break;
		}
	    }

	    if (k <= j)
	    {
		/*********************************************************
		* The new sub-array contains routes from all the nets to
		* be matched. Store the minimum and maximum index in min
		* and max.
		*********************************************************/
		min = i;
		max = j;
	    }
	}

	/***********************************************************
	* Increase the lower end of the indices by one.
	***********************************************************/
	i++;
    }

    if (min)
    {
	i = 0;
	for (j = min; j <= max; j++)
	{
	    Ysafe_free((char *) Aterms[i]);
	    Aterms[i++] = Aterms[j];
	}
    }
    else
    {
	i = max + 1;
    }

    /***********************************************************
    * Free the memory for discarded elements.
    ***********************************************************/
    for (; i < numterms; i++)
    {
	Ysafe_free((char *) Aterms[i]);
    }

    return;

} /* end of analog_match_routes */
