#ifndef lint
static char SccsId[] = "@(#)checker.c	SDD Version 1.3 5/16/91" ;
#endif
/* -----------------------------------------------------------------

	FILE:		checker.c
	AUTHOR:		Dahe Chen
	DATE:		Mon Jan 28 17:25:21 EST 1991
	CONTENTS:	This file contains functions used to check
		various outputs of Mickey and to compare with the
		incremental outputs.
	REVISION:

----------------------------------------------------------------- */

#include <define.h>
#include <macros.h>
#include <dgraph.h>

/*=====================================================================
*   Compute the channel density of each channel from the given routing
* configuration and compare that with the given channel density.
=====================================================================*/
void
check_channel_density()
{
    register int i;
    register int j;
    int c_dens;
    int l_dens;
    int m_dens;
    int r_dens;
    int number;

    NLISTPTR Pnlist;

    for (i = 1; i <= numedges; i++)
    {
	c_dens = 0;
	m_dens = 0;
	r_dens = dearray[i]->density;

	if (dearray[i]->Pcnet)
	{
	    Pnlist = dearray[i]->Pcnet;
	    while (Pnlist)
	    {
		c_dens += dearray[i]->width;
		Pnlist = Pnlist->next;
	    }
	}

	if (dearray[i]->Adens)
	{
	    number = dearray[i]->numpin;
	    for (j = 0; j < number; j++)
	    {
		l_dens = 0;
		Pnlist = dearray[i]->Adens[j]->Pnlist;
		while (Pnlist)
		{
		    l_dens += dearray[i]->width;
		    Pnlist = Pnlist->next;
		}
		m_dens = MAX(m_dens, l_dens);
	    }
	    c_dens += m_dens;
	    r_dens += dearray[i]->Aindex[1]->key;
	}

	if (c_dens != r_dens)
	{
	    ERROR2("\nInconsistent channel densities in channel %d:\n",
		i);
	    ERROR3("\tMeasured: %d --- Recorded: %d\n", c_dens, r_dens);
	}
    }

    return;
} /* end of check_channel_density */
