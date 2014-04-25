#ifndef lint
static char SccsId[] = "@(#)read_net.c	Yale Version 2.6 5/16/91";
#endif
/* -----------------------------------------------------------------

	FILE:		read_net.c
	AUTHOR:		Dahe Chen
	DATE:		Fri Feb 10 22:59:02 EDT 1989
	CONTENTS:	read_one_net()
	REVISION:
		Sun Oct 21 14:01:34 EDT 1990
	    Add the code checking if equivalent pins are on top one
	    another. If so, output an error message and stop Mickey.
		Tue Nov 27 18:17:04 EST 1990
	    Read net lists for both digital and analog circuits.
		Thu Nov 29 17:29:02 EST 1990
	    Remove the use of x/y locations.
		Fri Nov 30 13:21:38 EST 1990
	    Fix a bug on checking if equivalent pins are on top
	    each other.
		Tue Dec  4 21:44:33 EST 1990
	    Clean the field in parray if there are no equivalent
	    pins. Otherwise, this will cause problems for the code
	    handling analog circuits.
		Mon Jan 21 17:18:51 EST 1991
	    Change the input format for analog nets.
		Tue Jan 22 16:11:01 EST 1991
	    Add fields to store capacitance and resistance match
	    request for common points.
		Tue Jan 29 17:11:35 EST 1991
	    Check and set pins with mixed noisy and sensitive type.
		Mon Feb  4 16:15:23 EST 1991
	    Fix error message output.
		Tue Feb  5 10:21:54 EST 1991
	    Initialize the variable net_type.
		Tue Feb  5 12:11:26 EST 1991
	    Reformat error message output.
		Tue Feb  5 14:51:45 EST 1991
	    There is no default on net types of analog nets.
		Tue Feb  5 17:24:07 EST 1991
	    Initialize the variable max_volt_drop.

----------------------------------------------------------------- */

#include <string.h>
#include <yalecad/string.h>
#include <define.h>
#include <macros.h>
#include <gg_router.h>
#include <analog.h>

/***********************************************************
* Define ANALOG_PIN to be the number of fields on a line
* specifying a pin of a net. A deliminator is a tab, a sapce
* or a new line.
***********************************************************/
#define ANALOG_PIN 12

/*=====================================================================
*  In order to have this file work properly, there must be a blank line
* between the records of two consecutive nets and the very first line
* can not be a blank line. Also the name of nets can not be over 256
* characters.
=====================================================================*/
BOOLEAN
read_one_net()
{
    char input[LRECL];
    char **tokens;
    int i;
    int v1; /* Vertex index */
    int v2; /* Vertex index */
    int pin;
    int equiv;
    INT numtokens;

    C_LISTPTR Pnew;
    LISTPTR Pnode;
    PINPTR Pfirst; /* Header of the pin list */
    PINPTR Ppin;

    EQUIVAL = FALSE;
    SHIFTED = FALSE;
    CAP_MATCH = FALSE;
    MIX_MATCH = FALSE;
    RES_MATCH = FALSE;
    COMMON_POINT = FALSE;

    equiv = 0;
    numpins = 0;
    net_type = 0;
    numcomms = 0;
    max_volt_drop = 0;
    Pfirst = NIL(PIN);
    Plist = NIL(C_LIST);

    while (fgets(input, LRECL, fin))
    {
	tokens = Ystrparser(input, " \t\n", &numtokens);

	if (numtokens == 0)
	{
	    /***********************************************************
	    * An empty line is reached. A complete record is read in
	    * so quit reading the net.
	    ***********************************************************/
	    break;
	}

	if (strncmp(tokens[0], "net", 3) == STRINGEQ)
	{
	    /***********************************************************
	    * The beginning of a digital net is read in. Get the net
	    * name and set the net type to be noisy.
	    ***********************************************************/
	    (void) strcpy(netName, tokens[1]);
	    DIGITAL = TRUE;
	    net_type = NOISY;
	}
	else if (strncmp(tokens[0], "analog_net", 10) == STRINGEQ)
	{
	    /***********************************************************
	    * The beginning of an analog net is read in. Get the net
	    * name and read in the capacitance upper bound, resistance
	    * upper bound, maximum value of the voltage drop, plus the
	    * net type specification. Note that not all the  parameters
	    * have to be present.
	    ***********************************************************/
	    (void) strcpy(netName, tokens[1]);

	    if (numtokens < 3)
	    {
		ERROR1("\n\nThe entry line for an analog net must have ");
		ERROR1("at least 3 fields!\n");
		ERROR2("Net name: %s\n", netName);
		exit(GP_FAIL);
	    }

	    for (i = 2; i < numtokens; i += 2)
	    {
		if (strncmp(tokens[i], "cap", 3) == STRINGEQ)
		{
		    cap_upper_bound = atof(tokens[i+1]);
		}
		else if (strncmp(tokens[i], "res", 3) == STRINGEQ)
		{
		    res_upper_bound = atof(tokens[i+1]);
		}
		else if (strncmp(tokens[i], "max_drop", 8) == STRINGEQ)
		{
		    max_volt_drop = atof(tokens[i+1]);
		}
		else if (strncmp(tokens[i], "noisy", 5) == STRINGEQ)
		{
		    if (net_type == SENSITIVE)
		    {
			net_type = MIXED;
		    }
		    else if(net_type == SHIELD)
		    {
			ERROR1("\n\n");
			ERROR1("A net can not be NOISY and SHIELDING ");
			ERROR1("at the same time\n");
			ERROR2("Net name: %s\n", netName);
			exit(GP_FAIL);
		    }
		    else
		    {
			net_type = NOISY;
		    }
		    i--;
		}
		else if(strncmp(tokens[i], "sensitive", 9) == STRINGEQ)
		{
		    if (net_type == NOISY)
		    {
			net_type = MIXED;
		    }
		    else if(net_type == SHIELD)
		    {
			ERROR1("\n\nA net can not be SENSITIVE and ");
			ERROR1("SHIELDING at the same time\n");
			ERROR2("Net name: %s\n", netName);
			exit(GP_FAIL);
		    }
		    else
		    {
			net_type = SENSITIVE;
		    }
		    i--;
		}
		else if (strncmp(tokens[i], "shielding", 9) == STRINGEQ)
		{
		    if (net_type == NOISY || net_type == SENSITIVE)
		    {
			ERROR1("\n\nA net can not be SENSITIVE and ");
			ERROR1("SHIELDING or NOISY and\n");
			ERROR1("SHIELDING at the same time\n");
			ERROR2("Net name: %s\n", netName);
			exit(GP_FAIL);
		    }
		    else
		    {
			net_type = SHIELD;
		    }
		    i--;
		}
		else
		{
		    ERROR1("\n\n");
		    ERROR2("Unknown keyword \"%s\" for the ", tokens[i]);
		    ERROR2("net %s.\nNotice that the keywords", netName);
		    ERROR1(" are case-sensitive. DO NOT USE capital");
		    ERROR1(" letters in the keywords.\n");
		    exit(GP_FAIL);
		}
	    }
	    if (!net_type)
	    {
		ERROR1("\n\nNet type must be specified for analog nets");
		ERROR2(".\nNo net type is specified for net %s\n",
		    netName);
		exit(GP_FAIL);
	    }
	    DIGITAL = FALSE;
	}
	else if (strncmp(tokens[0], "common_point", 12) == STRINGEQ)
	{
	    numcomms++;
	    Pnew = (C_LISTPTR) Ysafe_malloc(sizeof(C_LIST));
	    Pnew->numpin = atoi(tokens[1]);
	    Pnew->cap_match = FALSE;
	    Pnew->res_match = FALSE;
	    Pnew->next = Plist;
	    Plist = Pnew;
	    COMMON_POINT = TRUE;
	}
	else if (strncmp(tokens[0], "pin", 3) == STRINGEQ
	      || strncmp(tokens[0], "equiv", 5) == STRINGEQ)
	{
	    Ppin = (PINPTR) Ysafe_malloc(sizeof(PIN));
	    if (tokens[0][0] == 'e')
	    {
		/*********************************************************
		* This pin is an equivalent pin of the previous pin(s).
		*********************************************************/
		EQUIVAL = TRUE;
		if (Pfirst->equiv)
		{
		    Ppin->equiv = Pfirst->equiv;
		}
		else
		{
		    Ppin->equiv = ++equiv;
		    Pfirst->equiv = equiv;
		}
	    }
	    else
	    {
		Ppin->equiv = FALSE;
	    }
	    Ppin->node[0] = v1 = atoi(tokens[5]);
	    Ppin->node[1] = v2 = atoi(tokens[6]);
	    Ppin->shifted = FALSE;
	    Ppin->vertex = ++numpins;
	    Ppin->pin[0] = Ppin->pin[1] = 0;
	    Ppin->dist[0] = atoi(tokens[8]);

	    if (numtokens == ANALOG_PIN)
	    {
		Ppin->density = atoi(tokens[11]);
	    }
	    else
	    {
		Ppin->density = 0;
	    }

	    /***********************************************************
	    * Find the edge index of the channel on which the pin is
	    * located. This is for removing the rectilinear restriction.
	    ***********************************************************/
	    Pnode = garray[v1]->first;
	    while (Pnode->t_vertex != v2)
	    {
		Pnode = Pnode->next;
	    }

	    Ppin->dist[1] = Pnode->length - Ppin->dist[0];

	    /*********************************************************
	    * Check if the pin overlaps with a vertex of the channel
	    * graph. If so, we have to shift the pin along the channel
	    * a bit due to the data structure. 
	    *********************************************************/
	    if (!(Ppin->dist[0]))
	    {
		/*****************************************************
		* The pin overlaps with vertex v1 of the channel
		* graph.
		*****************************************************/
		Ppin->dist[0]++;
		Ppin->dist[1]--;
		Ppin->shifted = 1;
		SHIFTED = TRUE;
	    }

	    if (!(Ppin->dist[1]))
	    {
		/*****************************************************
		* The pin overlaps with vertex v2 of the channel
		* graph.
		*****************************************************/
		Ppin->dist[0]--;
		Ppin->dist[1]++;
		Ppin->shifted = -1;
		SHIFTED = TRUE;
	    }

	    Ppin->next = Pfirst;
	    Pfirst = Ppin;
	}
	else if (strncmp(tokens[0], "cap_match", 9) == STRINGEQ)
	{
	    Pnew->cap_match = TRUE;
	}
	else if (strncmp(tokens[0], "res_match", 9) == STRINGEQ)
	{
	    Pnew->res_match = TRUE;
	}
	else
	{
	    ERROR1("\n\n");
	    ERROR2("Unknown keyword \"%s\" in the record ", tokens[0]);
	    ERROR2("for the net %s\n", netName);
	    exit(GP_FAIL);
	}
    }

    if (numpins)
    {
	/***********************************************************
	* Make an array for the list of pins.
	***********************************************************/
	pin = numpins;
	parray = (PINPTR *) Ysafe_malloc((numpins+1) * sizeof(PINPTR));
	while (Pfirst)
	{
	    parray[pin--] = Pfirst;
	    Pfirst = Pfirst->next;
	}
    }

    if (EQUIVAL == TRUE)
    {
	/***********************************************************
	* Make each group of equivalent pins a circular linked list
	* which will be used to construct the segment tree.
	***********************************************************/
	for (i = 1; i <= numpins ;)
	{
	    if (parray[i]->equiv)
	    {
		v1 = i;
		v2 = i + 1;
		pin = parray[i]->equiv;

		while (v2 <= numpins && parray[v2]->equiv == pin)
		{
		    parray[v1]->next = parray[v2];
		    v1++;
		    v2++;
		}

		parray[v1]->next = parray[i];
		i = v2;
	    }
	    else
	    {
		parray[i]->next = NIL(PIN);
		i++;
	    }
	}

	/***********************************************************
	* Check each set of equivalent pins on their geometric
	* positions and make sure that they are NOT on top each
	* other.
	***********************************************************/
	for (i = 1; i <= numpins; i++)
	{
	    if (parray[i]->next)
	    {
		/*********************************************************
		* A set of equivalent pins is found. Check each pair of
		* the equivalent pins in the set and make sure that none
		* of them are on top each other.
		*********************************************************/
		Pfirst = parray[i];
		while (Pfirst->next != parray[i])
		{
		    for (Ppin = Pfirst->next;
			 Ppin != Pfirst;
			 Ppin = Ppin->next)
		    {
			if (Pfirst->dist[0] == Ppin->dist[0]
			 && Pfirst->node[0] == Ppin->node[0]
			 && Pfirst->node[1] == Ppin->node[1])
			{
			    ERROR1("\n\n");
			    ERROR1("FATAL ERROR: Equivalent pins are ");
			    ERROR1("on top each other in the net ");
			    ERROR2("%s.\nMust exit. Sorry!\n\n", netName);
			    exit(GP_FAIL);
			}
		    }
		    Pfirst = Pfirst->next;
		}
	    }
	}
    }
    else
    {
	/***********************************************************
	* There are equivalent pins in this net. Clean the field
	* next in parray.
	***********************************************************/
	for (i = 1; i <= numpins; i++)
	{
	    parray[i]->next = NIL(PIN);
	}
    }

    if (COMMON_POINT != FALSE)
    {
	/***********************************************************
	* There exit common pins in this net. Make sure the common
	* pins have no equivalent pins to them. Mickey can not
	* handle common pins with equivalent pins.
	***********************************************************/
	v1 = 0;
	Pnew = Plist;
	while (Pnew)
	{
	    v2 = Pnew->numpin;
	    for (i = ++v1; i < v2; i++)
	    {
		if (parray[i]->next)
		{
		    ERROR1("\n\nMickey can not handle pins which are");
		    ERROR1(" equivalent pins\n and");
		    ERROR1(" are to be connected to a common point\n");
		    exit(GP_FAIL);
		}
		parray[i]->next = parray[i+1];
	    }
	    parray[i]->next = parray[v1];
	    v1 = i + 1;
	    Pnew = Pnew->next;
	}

	while (Plist)
	{
	    Pnew = Plist;
	    Plist = Plist->next;
	    Ysafe_free((char *) Pnew);
	}
    }

    return(numpins);
} /* end of read_one_net */
