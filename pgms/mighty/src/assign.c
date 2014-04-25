#ifndef lint
static char SccsId[] = "@(#) assign.c version 6.1 6/19/90" ;
#endif

#include "mighty.h"
#include <yalecad/message.h>
extern int PREASSIGN;

int **costG = (int **)NULL;
static int *capS;
static int *rowS;
static int *colS;
static int *nextS;
static int *h1S;
static int *h2S;
static int *h3S;
static int *h4S;
static int *h5S;
static int *h6S;

/*
 *  Pseudo pins are made.
 *  This is to give guide in routing long channels
 *  or highly irregular shaped channels.
 */


int ** S_structure(m, n)
int m, /* number of rows( crossing nets ) */
    n; /* number of cols( tracks ) */
{
    int j;
    int *S_allocatevector();
    int ** S_allocatematrix();

    capS = S_allocatevector( n );
    for( j = 1; j <= n; j++ )
	capS[j] = 1;
    costG = S_allocatematrix( m, n );
    rowS = S_allocatevector( n );
    colS = S_allocatevector( m );
    nextS = S_allocatevector( m );
    h1S = S_allocatevector( m );
    h2S = S_allocatevector( n );
    h3S = S_allocatevector( m );
    h4S = S_allocatevector( n );
    h5S = S_allocatevector( n );
    h6S = S_allocatevector( n );
    return( costG );
}


void S_resetstructure(m, n)
int m, /* number of rows( crossing nets ) */
    n; /* number of cols( tracks ) */
/*
 *  reset to 0 all the entries, except capacities which are 1
 */
{
int i,
    j;
    for( j = 1; j <= n; j++ )
	capS[j] = 1;
    for( i = 1; i <= m; i++ )
        for( j = 1; j <= n; j++ )
	    costG[i][j] = 0;
    for( j = 1; j <= n; j++ )
	rowS[j] = 0;
    for( i = 1; i <= m; i++ )
	colS[i] = 0;
    for( i = 1; i <= m; i++ )
	nextS[i] = 0;
    for( i = 1; i <= m; i++ )
	h1S[i] = 0;
    for( j = 1; j <= n; j++ )
	h2S[j] = 0;
    for( i = 1; i <= m; i++ )
	h3S[i] = 0;
    for( j = 1; j <= n; j++ )
	h4S[j] = 0;
    for( j = 1; j <= n; j++ )
	h5S[j] = 0;
    for( j = 1; j <= n; j++ )
	h6S[j] = 0;
}


int * S_assign( m, n )
int m,
    n;
/*
 *  For bipatite graph with m source nodes ( i : rows )
 *  and n sink nodes ( j : cols ) connected by edges with costG[i][j] >=0
 *  an assignment of rows i to columns j is calculated which minimoizes
 *  the costG
 *
 *        z = sum costG[i][j] * x[i][j]
	      i,j
 *  subject to
 *
 *   sum x[i][j] <= capS[j];  sum x[i][j] = 1;  x[i][j] >= 0
 *    i                       j
 *
 *  INPUT :  The capacity vector capS[1..n]
 *	     costG matrix         costG[1..m][1..n]
 *     	     problem size m, n.  m <= sum capS[j]
 *				       i
 *  OUTPUT :  Two vectors rowS[1..n], colS[1..m] describing rows and
 *	     columns of the selected matrix entries.
 * 	     rowS[j] points to one of the rows assigned to col j.
 *	     Others may be accessed by nextS[rowS[j]] ...
 *  scratch : h1S[1..m], h2S[1..n], h3S[1..m], h4S[1..n], h5S[1..n], h6S[1..n]
 *
 *  method :  First an optimal assignment of a subset of rows and
 *	     columns is constructed heuristically.  Then shortest
 *	     augmenting paths are generated starting from unassigned
 *	     source nodes to sink nodes with free capacity, to determine
 *	     the solution of the complete problem.
 *	     REF : Lauther's class note; Burkhard & Derigs, "assignment
 *	     and matching problems, springer 1980
 *
 *	     Problems with m < n are handled as an n by n problem with
 *	     c[i][j] = INFINITY for i > m.
 *	     Sink nodes j with capS[j] > 1 are handled like a bunch of
 *	     capS[j] nodes with capacity 1 each.
 */
{
int i,
    j,
    k;
void S_initassign();
void S_shortestpath();
void S_augmentation();
void S_transformation();

    /*
     *  Initialize candidate list for shortest path
     */
    S_initassign(h1S, h2S, m, n);

    for( j = 2; j <= n; j++ )
	h6S[j] = j - 1;
    h6S[1] = n;

    for( i = 1; i <= m; i++ )
    {
	if( colS[i] == 0 )
	{
	    S_shortestpath( h1S, h2S, h3S, h4S, h5S, h6S, i, &j, &k, m, n );
	    S_augmentation( h5S, i, j );
	    S_transformation( h1S, h2S, h3S, h4S, k, m, n );
	}
    }
    return( colS );
}


S_initassign(ys, yt, m, n)
int ys[],
    yt[];
int m, n;
/*
 *  Initializes, checks feasibility and constructs an optimal assignment
 *  for a subset of rowSs and colSumns :
 *  First we calculate ys[i] = min costG[i][j];  yt[j] = min (costG[i][j] - ys[i])
 *				j			 i
 *
 *  Then admissible assignments (i,j) with c[i][j] = ys[i] + yt[j]
 *  are made.
 */
{
    int i,
	j,
	j0,
	ui,
	cij;
    int neff = 0;  /* total capacity */

    /*  initial assignment */
    for( j = 1; j <= n; j++ )
    {
	rowS[j] = 0;
	neff += capS[j];
    }
    if( neff < m )
    {
	M( ERRMSG, "initassign", "total capacity too small\n");
	fprintf(output_fileG, "failed\n");
	YexitPgm( 03 );
    }

    /*
     *  calculate ys and make trvial assignments
     */
    for( i = 1; i <= m; i++ )
    {
	colS[i] = 0;
	ui = INFINITY;
	for( j = 1; j <= n; j++ )
	{
	    if( costG[i][j] < ui )
	    {
		ui = costG[i][j];
		j0 = j;
	    }
	}
	ys[i] = ui;
	if( capS[j0] > 0 )
	{
	    capS[j0]--;
	    nextS[i] = rowS[j0];
	    rowS[j0] = i;
	    colS[i] = j0;
	    yt[j0] = 0;
	}
    }
    /*
     *  calculate yt
     */
    if( m < neff )
    {
	for( j = 1; j <= n; j++ )
	    yt[j] = 0;
    }
    else
    {
	for( j = 1; j <= n; j++ )
	{
	    if( rowS[j] == 0 )
	    {
		ui = INFINITY;
		for( i = 1; i <= m; i++ )
		{
		    if( (cij = costG[i][j] - ys[i]) < ui )
			ui = cij;
		}
		yt[j] = ui;
	    }
	}
    }
    /*
     *  make admissible assignments
     */
    for( i = 1; i <=m; i++ )
    {
	if( colS[i] == 0 )
	{
	    ui = ys[i];
	    for( j = 1; j <=n; j++ )
	    {
		if( capS[j] > 0 )
		{
		    if( costG[i][j] == ui + yt[j] )
		    {
			capS[j]--;
			nextS[i] = rowS[j];
			rowS[j] = i;
			colS[i] = j;
			goto DONE;
		    }
		}
	    }
	}
DONE :
	continue;
    }
}

     
S_shortestpath( ys, yt, dplus, dminus, back, next, i, indexp, dp, m, n )
int ys[],
    yt[],
    dplus[],
    dminus[],
    back[],
    next[];
int *indexp;
int *dp;
int i,
    m,
    n;
/*
 *  Finds a shortest path from starting node i to sink node index
 *  using dijkstra's algorithm and modified costGs.
 *  next is a cyclic list of all sink nodes.
 *  next[headcand..lastcand] are the active candidate nodes.
 *  back points back in the path.
 */
{
int lastcand,
    headcand,
    v,
    vgl,
    j,
    dalt,
    ysi;

    for( j = 1; j <= n; j++ )
	dminus[j] = INFINITY;
    for( j = 1; j <= m; j++ )
	dplus[j] = INFINITY;

    lastcand = headcand = n;
    *dp = 0;

    /* till sink node with free capacity is reached */
    for( ;; )
    {
	dplus[i] = dalt = *dp;
	*dp = INFINITY;
	v = headcand;
	ysi = ys[i];

	/* for all active and feasible sink nodes */
	for( ;; )
	{
	    j = next[v];
	    if( capS[j] > 0 || rowS[j] > 0 )
	    {
		/*  update distance  */
		vgl = dalt + costG[i][j] - ysi - yt[j];
		if( vgl < dminus[j] )
		{
		    dminus[j] = vgl;
		    back[j] = i;
		}
		if( dminus[j] < *dp )
		{
		    *dp = dminus[j];
		    *indexp = v;
		}
	    }
	    v = j;
	    if( v == lastcand ) break;
	}

	/*
	 *  remove next[v] from candidate set
	 */
	v = *indexp;
	*indexp = next[v];
	if( *indexp == lastcand )
	    lastcand = v;
	else
	{
	    next[v] = next[*indexp];
	    next[*indexp] = next[headcand];
	    next[headcand] = *indexp;
	    headcand = *indexp;
	}
	i = rowS[*indexp];
        if( capS[*indexp] > 0 ) break;
    }
}


S_augmentation( back, u, ind )
int back[];
int u,
    ind;
/*
 *  tracing back the augmenting path from index back to u,
 *  assignments are updated accordingly.
 */
{
int oldind;
int w = 0;

    (capS[ind])--;

    for( ; w != u; )
    {
	oldind = ind;

	w = back[ind];
	if( w != u )
	{
	    /* remove w, colS[w] from list associated with colS[w]  */
	    ind = colS[w];
	    rowS[ind] = nextS[w];
	}

	/*  add ede w, index to list associated with index  */
	nextS[w] = rowS[oldind];
	rowS[oldind] = w;
	colS[w] = oldind;
    }
}


S_transformation( ys, yt, dplus, dminus, d, m, n )
int ys[],
    yt[],
    dplus[],
    dminus[];
int d;
/*
 *  update ys and yt
 */
{
int i;
    
    for( i = 1; i <= m; i++ )
    {
	if( dplus[i] != INFINITY )
	    ys[i] = ys[i] + d - dplus[i];
    }
    for( i = 1; i <= n; i++ )
    {
	if( dminus[i] < d )
	    yt[i] = yt[i] - d + dminus[i];
    }
}


S_printresults( m, n )
int m,
    n;
{
int i,
    j,
    sum = 0,
    max = 0,
    cij;

    for( i = 1; i <= m; i++ )
    {
	if( (cij = costG[i][colS[i]]) > max )
	    max = cij;
	sum += cij;
    }
    /* if too high, exit */
    if( max >= PREASSIGN )
        printf("ERROR in pin-assignment\n");
    printf("sum = %d, max = %d\n", sum, max );
    for( j = 1; j <= n; j++ )
	printf("%d  %d\n", j, capS[j]);
    for( i = 1; i<= m; i++ )
    {
	for( j = 1; j <=n; j++ )
	{
	    if( colS[i] == j )
		printf("[%d]", costG[i][j]);
	    else
		printf(" %d ", costG[i][j]);
	}
	printf("\n");
    }
}
