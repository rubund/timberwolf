#ifndef lint
static char SccsId[] = "@(#)output_route.c	Yale Version 3.3 5/28/91" ;
#endif
/* -----------------------------------------------------------------

	FILE:		output_route.c
	AUTHOR:		Dahe Chen
	DATE:		Tue Oct 10 10:53:10 EDT 1989
	CONTENTS:	output_route()
	REVISION:
		Thu May 17 15:14:13 EDT 1990
	    Add code of the calculation of channel densities for
	    channels adjacent one or more empty rooms.
		Fri Nov 16 19:04:56 EST 1990
	    Modify the code for analog circuits.
		Wed Dec  5 13:16:42 EST 1990
	    Remove h_width and v_width and use width in dearray.
		Sun Jan 27 17:17:06 EST 1991
	    Change the read-in of cktName.mtwf.
		Tue Mar  5 11:22:28 EST 1991
	    Change fclose to TWCLOSE.
		Tue May 28 16:28:17 EDT 1991
	    Output corrected offsets for the routes adjacent to
	    empty rooms.

----------------------------------------------------------------- */

#include <yalecad/string.h>
#include <define.h>
#include <gg_router.h>
#include <dgraph.h>
#include <macros.h>

void
output_route()
{

    char input[LRECL];
    char **tokens;

    register int i;
    register int j;
    register int r;
    register int l_node;
    register int r_node;

    int cell;
    int length;
    int density;
    int channel;
    INT numtokens;

    FILE *fp;
    FILE *fpyt;
    FILE *ftwf;
    OFSETPTR Pelist;

    ftwf = FOPEN("mtwf","r");
    fpyt = FOPEN("gpyt","w");

    for (i = numnets; i >= 1; i--)
    {
	r = narray[i]->route;
	length = narray[i]->Aroute[r]->length;
	fprintf(fpyt, "net %s	length %d\n", narray[i]->name, length);
	fprintf(fpyt, "pins %d\n", narray[i]->numpins);

	while (fgets(input, LRECL, ftwf))
	{
	    tokens = Ystrparser(input, " \t\n", &numtokens);
	    if (!numtokens)
	    {
		break;
	    }
	    else if (strncmp(tokens[0], "net", 3) == STRINGEQ
		  || strncmp(tokens[0], "analog_net", 10) == STRINGEQ)
	    {
		continue;
	    }
	    else if (strncmp(tokens[0], "common_point", 12) == STRINGEQ)
	    {
		cell = atoi(tokens[1]);
		for (j = 0; j < cell; j++)
		{
		    fgets(input, LRECL, ftwf);
		}
	    }
	    else if (strncmp(tokens[0], "cap_match", 9) == STRINGEQ)
	    {
		continue;
	    }
	    else if (strncmp(tokens[0], "res_match", 9) == STRINGEQ)
	    {
		continue;
	    }
	    else
	    {
		fprintf(fpyt,"\t");
		for (j = 0; j < numtokens; j++)
		{
		    fprintf(fpyt, "%s ", tokens[j]);
		}
		fprintf(fpyt,"\n");
	    }
	}

	channel = 0;
	Pelist = narray[i]->Aroute[r]->Pedge;
	while (Pelist)
	{
	    channel++;
	    Pelist = Pelist->next;
	}
	fprintf(fpyt, "channels %d\n", channel);

	Pelist = narray[i]->Aroute[r]->Pedge;
	while (Pelist)
	{
	    l_node = (int) dearray[Pelist->edge]->f_vertex;
	    r_node = (int) dearray[Pelist->edge]->t_vertex;
	    if (Pelist->back)
	    {
	        fprintf(fpyt, "\t%d %d %d ", l_node, r_node, Pelist->back[0]);
		fprintf(fpyt, "%d %d\n", Pelist->back[1], Pelist->width);
	    }
	    else
	    {
		fprintf(fpyt, "\t%d %d %d ", l_node, r_node, Pelist->l_off);
		fprintf(fpyt, "%d %d\n", Pelist->r_off, Pelist->width);
	    }
	    Pelist = Pelist->next;
	}
	fprintf(fpyt, "\n");
	fflush(fpyt);
    }
    TWCLOSE(fpyt);
    TWCLOSE(ftwf);

    fp = FOPEN("dens","w");

    for (i = 1; i <= numedges; i++)
    {
	if (dearray[i]->numpin && dearray[i]->capacity != -1)
	{
	    density = dearray[i]->density + dearray[i]->Aindex[1]->key;
	}
	else
	{
	    density = dearray[i]->density;
	}

	fprintf(fp, "channel: %d %d density: %d\n",
	    dearray[i]->f_vertex,
	    dearray[i]->t_vertex,
	    density);
	fflush(fp);
    }
    TWCLOSE(fp);

} /* end of output_route */
