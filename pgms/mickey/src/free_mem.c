#ifndef lint
static char SccsId[] = "@(#)free_mem.c	Yale Version 2.2 5/16/91";
#endif
/* -----------------------------------------------------------------

	FILE:		free_mem.c
	AUTHOR:		Dahe Chen
	DATE:		Wed Jul 12 17:36:42 EDT 1989
	CONTENTS:	free_mem()
	REVISION:	Wed Apr 25 17:45:12 EDT 1990:
		Save garray for the calculation of channel densities
		when there are special routes caused by empty rooms.
		
----------------------------------------------------------------- */

#include <define.h>
#include <gg_router.h>
#include <heap_func.h>
#include <steiner_tree.h>

void
free_mem()
{

    int i;
    int j;
    LISTPTR Pnode;
    TREEPTR *tarray;

    totnodes = numnodes + maxpins;
    totedges = numedges + maxpins;

    for (i = 1; i <= totnodes; i++)
    {
	tarray = garray[i]->tree;
	for (j = 0; j <= totnodes; j++)
	{
	    Ysafe_free((char *) tarray[j]);
	}
	Ysafe_free((char *) tarray);

	Pnode = garray[i]->first;
	while (Pnode)
	{
	    garray[i]->first = garray[i]->first->next;
	    Ysafe_free((char *) Pnode);
	    Pnode = garray[i]->first;
	}

	Ysafe_free((char *) garray[i]);
    }
    Ysafe_free((char *) garray);

    for (i = 1; i <= numnodes; i++)
    {
	tarray = sarray[i]->tree;
	for (j = 0; j <= numnodes; j++)
	{
	    Ysafe_free((char *) tarray[j]);
	}
	Ysafe_free((char *) tarray);
	sarray[i]->tree = NIL(TREEPTR);
    }
    garray = sarray;

    for (i = 1; i <= totedges; i++)
    {
	Ysafe_free((char *) earray[i]);
    }
    Ysafe_free((char *) earray);

    for (i = 1; i <= numedges; i++)
    {
	Ysafe_free((char *) carray[i]);
    }
    Ysafe_free((char *) carray);

} /* end of free_mem */
