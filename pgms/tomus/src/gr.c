/* ----------------------------------------------------------------- 
FILE:	    gr.c                                       
DESCRIPTION: To replace Mickey (YEAAH!!), writing my own global router
CONTENTS:    

DATE:	    March 17 1992 
REVISIONS:  
----------------------------------------------------------------- */
#ifndef VMS
#ifndef lint
static char SccsId[] = "@(#) newnetlist.c (Yale) version 1.15 2/23/91" ;
#endif
#endif

#include <yalecad/deck.h>
#include <yalecad/graph.h>
#include <yalecad/rbtree.h>
#include <yalecad/draw.h>
#include <yalecad/colors.h>
#include <standard.h>

#define GREATER 1
#define LESS -1
#define EQUAL 0
#define MAXIMPROVES 10
#define MAXCOLORS 14
#define ECOEF1 3
#define ECOEF2 1
/*
#define DRAWROUTE 1
*/

extern DOUBLE track_pitch;
extern int *grid_x, *grid_y;
extern BOOL doGraphicsG ;

typedef struct node{
	short int id;
	int tile;
	int x;
	int y;
}
*NODEPTR,NODE;
NODEPTR *nodelist;

typedef struct edge{
	short int node1;
	short int node2;
	BOOL InotO ;
	int length ;
	int capacity;
	int weight;
	int overflow;
}
*EDGEPTR, EDGE;
EDGEPTR *edgelist;

typedef struct route{
	int net ;
	YGRAPHPTR routeGraph ;
}
*ROUTEPTR, ROUTE ;

YGRAPHPTR GraphG ;
YTREEPTR Nodetree, Hor_edtree, Ver_edtree ;
YTREEPTR RouteTreeG ;
YDECKPTR overflowEdgeG ;
INT Coeff1G = ECOEF1 ;
DOUBLE Coeff2G = ECOEF2 ;
INT num_padsG ;
INT maxImproveG = MAXIMPROVES ;
BOOL label_flagG ;

INT current_netG;
static int padAlloc = 200;
static NODEPTR ndptr;
static EDGEPTR edptr ;
static PTILEPTR tptr1, tptr2, tptr3 , tptr4;
static int temp1,temp2,pad,padx,pady;
static int lx = 0;
static int rx = 0 ;
static int ty = 0 ;
static int by = 0 ;
static int gridx,gridy;
static int x1S,x2S,x3S,y1S,y2S,y3S;
static int capx,capy,line;
static int *Hcap,*Vcap;
static int numnodes,numedges;
extern int *line_x,*line_y;

extern INT get_length(YGRAPHPTR);
extern INT setEdgeWeight(int, int, BOOL);

/** ---------------------------------------------------
comparison function for the Routetree
------------------------------------------------------*/
INT GRcompNetRoute(r1,r2)
ROUTEPTR r1, r2 ;
{
    if ( r1->net > r2->net) return (GREATER);
    else if (r1->net < r2->net) return (LESS);
    else return (EQUAL);
}

/** ---------------------------------------------------
comparison function for the GraphG nodes
------------------------------------------------------*/
INT GRcomparenodes(node1,node2)
YNODEPTR node1, node2 ;
{
    NODEPTR n1,n2;

    n1 = (NODEPTR) Ygraph_nodeData( node1 );
    n2 = (NODEPTR) Ygraph_nodeData( node2 );

    if (n1->y == n2->y && n1->x == n2->x) return (EQUAL);
    else if (n1->y > n2->y) return (GREATER);
    else if (n1->x > n2->x && n1->y == n2->y) return (GREATER);
    else return (LESS);
} /* GRcomparenodes */

/** ---------------------------------------------------
comparison function for the GraphG edges
------------------------------------------------------*/
INT GRcompareedges(edge1,edge2)
YEDGEPTR edge1, edge2 ;
{
    EDGEPTR e1, e2 ;

    e1 = (EDGEPTR) Ygraph_edgeData(edge1 );
    e2 = (EDGEPTR) Ygraph_edgeData(edge2 );

    if ( e1->node1 > e2->node1) return (GREATER);
    else if (e1->node1 < e2->node1) return (LESS);
    else return (EQUAL);
} /* GRcompareedges */

INT comparenodes(n1,n2)
NODEPTR n1,n2;
{
if (n1->y == n2->y && n1->x == n2->x) return (EQUAL);
else if (n1->y > n2->y) return (GREATER);
else if (n1->x > n2->x && n1->y == n2->y) return (GREATER);
else return (LESS);
}

INT compareedges(e1,e2)
EDGEPTR e1,e2;
{
if ( e1->node1 > e2->node1) return (GREATER);
else if (e1->node1 < e2->node1) return (LESS);
else return (EQUAL);
}

/** ---------------------------------------------------
draw a node of a route of a net 
------------------------------------------------------*/
VOID drawRouteNode( net , node, color)
NODEPTR node ;
int color , net ;
{
static int xr,yr;
static char labelS[8] ;

    xr = node->x;
    yr = node->y;
    if (!label_flagG )sprintf ( labelS, "n%d", net ) ;
    TWdrawPin(0,xr-60,yr-60,xr+60,yr+60,color,labelS);

} /* drawRouteNode */

/** ---------------------------------------------------
draw a node of the main graph GraphG
------------------------------------------------------*/
VOID drawGraphNode(node)
YNODEPTR node ;
{
static int xr,yr;
NODEPTR n ;

n = (NODEPTR) Ygraph_nodeData (node) ;

    xr = n->x;
    yr = n->y;
    TWdrawPin(0,xr-20,yr-20,xr+20,yr+20,TWBLACK,NULL);

} /* drawGraphNode */

/** ---------------------------------------------------
draw the edges of a route of a net 
------------------------------------------------------*/
VOID drawRouteEdge(edge,color)
EDGEPTR edge ;
INT color ;
{
static int x1,y1,x2,y2;

    x1 = nodelist[edge->node1]->x ;
    x2 = nodelist[edge->node2]->x ;
    y1 = nodelist[edge->node1]->y ;
    y2 = nodelist[edge->node2]->y ;
    TWdrawLine(0,x1,y1,x2,y2,color,NULL);
} /* drawGraphEdge */

/** ---------------------------------------------------
draw a edge of the main graph GraphG
------------------------------------------------------*/
VOID drawGraphEdge(edge,color)
YEDGEPTR edge ;
INT color ;
{
static int x1,y1,x2,y2;
EDGEPTR e ;
static char labelS[8] ;

e = (EDGEPTR) Ygraph_edgeData (edge) ;

    x1 = nodelist[e->node1]->x ;
    x2 = nodelist[e->node2]->x ;
    y1 = nodelist[e->node1]->y ;
    y2 = nodelist[e->node2]->y ;
    sprintf(labelS, "%d",e->weight) ; 
    TWdrawLine(0,x1,y1,x2,y2,color,labelS);
} /* drawGraphEdge */

/** ---------------------------------------------------
draw the graph for a route of a net
------------------------------------------------------*/
drawRoute(r)
ROUTEPTR r ;
{

YNODEPTR node ;
NODEPTR n ;
YEDGEPTR edge ;
EDGEPTR e ;
int color ;

/* first draw the core and pads */

    TWstartFrame() ;
    drawLines();
    drawcore();
    drawPads();
    /*
    Ygraph_draw(GraphG) ;
    */

/* draw the route */

label_flagG = TRUE ;
	color = PICK_INT ( 1, MAXCOLORS ) ;
    for ( node = Ygraph_nodeEnumerate( r->routeGraph, TRUE) ; node ; 
	node = Ygraph_nodeEnumerate( r->routeGraph, FALSE ) ) {

	n = (NODEPTR) Ygraph_nodeData(node);
	drawRouteNode ( r->net, n , color ) ;
    }
    for ( edge = Ygraph_edgeEnumerate( r->routeGraph, TRUE) ; edge ; 
	edge = Ygraph_edgeEnumerate( r->routeGraph, FALSE ) ) {

	e = (EDGEPTR) Ygraph_edgeData(edge);
	drawRouteEdge ( e , color ) ;
    }
	TWflushFrame();

/* draw the net */
label_flagG = FALSE ;
	color = PICK_INT ( 1, MAXCOLORS ) ;
    for ( node = Ygraph_enumerateRequired( GraphG, TRUE) ; node ; 
	node = Ygraph_enumerateRequired( GraphG, FALSE ) ) {

	n = (NODEPTR) Ygraph_nodeData(node);
	drawRouteNode ( r->net, n , color ) ;
    }
	TWflushFrame();

} /* drawRoute */

/** ---------------------------------------------------
The main routine for the global router
------------------------------------------------------*/
global_route()
{
INT GRcomparenodes(), GRcompareedges() ;
INT net ;
INT cost, overflow , wire_length ;
NODEPTR node , n1, n2 ;
EDGEPTR edge , e ;
ROUTEPTR route ;
YGRAPHPTR graph ;
YEDGEPTR graphedge ;


    /* ---first make the graph ---*/

    GraphG = Ygraph_init ( GRcomparenodes, GRcompareedges, NULL, 0 ) ;
    if (doGraphicsG) Ygraph_drawFunctions(GraphG,drawGraphNode,drawGraphEdge);

    /* ---make the graph nodes and edges ---*/

    make_graph() ;

    /* ---insert the nodes and edges into the global graph---  */

    for ( edge = (EDGEPTR) Yrbtree_enumerate(Hor_edtree, TRUE) ; edge ; 
	edge = (EDGEPTR) Yrbtree_enumerate(Hor_edtree, FALSE ) ) {

	n1 = nodelist[edge->node1] ;
	n2 = nodelist[edge->node2] ;
	Ygraph_edgeInsert ( GraphG , edge, edge->weight , n1, n2 ) ;
    }
    for ( edge = (EDGEPTR) Yrbtree_enumerate(Ver_edtree, TRUE) ; edge ; 
	edge = (EDGEPTR) Yrbtree_enumerate(Ver_edtree, FALSE ) ) {

	n1 = nodelist[edge->node1] ;
	n2 = nodelist[edge->node2] ;
	Ygraph_edgeInsert ( GraphG , edge, edge->weight , n1, n2 ) ;
    }
#ifdef DRAWROUTE
    /* ---now draw the graph to check and 
    verify integrity of the graph --- */

    if (doGraphicsG) Ygraph_draw(GraphG) ;
    Ygraph_verify (GraphG) ;
#endif /* DRAWROUTE */
    /* ---now generate one route for each net--- */

    RouteTreeG = Yrbtree_init( GRcompNetRoute ) ;

    for ( net = 1  ; net <= numnetsG ; net++ ) {
      if ( GRerase_net( netarrayG[net] ) == TRUE ) continue ;
      if( !( netarrayG[net]->numpins ) ) continue ;
	    generateTreeForNet (net) ;
    }
    /* ---now calculate the overflow on every edge
    a) first add the sum of the routes on each edge --- */

    cost = wire_length = 0 ;
    for ( route= (ROUTEPTR) Yrbtree_enumerate(RouteTreeG, TRUE) ; route ; 
	route = (ROUTEPTR) Yrbtree_enumerate(RouteTreeG, FALSE ) ) {

	graph = route->routeGraph ;
	wire_length += get_length(graph) ;
	cost += Ygraph_size(graph) ;
	/*--- enumerate the edges of the graph and add the 
	      overflow to the egde overflow field ---*/

	for ( graphedge = Ygraph_edgeEnumerate( graph, TRUE) ; graphedge ; 
	    graphedge = Ygraph_edgeEnumerate( graph, FALSE ) ) {

	    e = (EDGEPTR) Ygraph_edgeData(graphedge);
	    e->overflow ++ ;
	    if (!e->InotO) num_padsG++ ;
	}
    }

    /*b) calculate the difference of the capacity 
	  and the sum of the routes on each edge and thus the overflow --- */

	overflowEdgeG = Ydeck_init () ;
	overflow = 0 ;
	for ( graphedge = Ygraph_edgeEnumerate( GraphG, TRUE) ; graphedge ; 
	    graphedge = Ygraph_edgeEnumerate( GraphG, FALSE ) ) {
	    e = (EDGEPTR) Ygraph_edgeData(graphedge);
	    e->overflow -= e->capacity ;
	    if ( e->overflow > 0 ) {
		Ydeck_push ( overflowEdgeG, e ) ;
		overflow += e->overflow ;
	    }
	}
	printf ("cost wirelength overflow pads \n") ;
	printf ("%ld %ld %ld %ld \n", cost, wire_length,overflow, num_padsG) ;
	generate_pseudopads() ;

Ygraph_empty (GraphG,0,0) ;
} /* end global_route () */


INT get_length(g)
YGRAPHPTR g ;
{
YEDGEPTR graphedge ;
EDGEPTR e ;
INT length = 0 ;

	for ( graphedge = Ygraph_edgeEnumerate( g, TRUE ) ; graphedge ; 
	    graphedge = Ygraph_edgeEnumerate( g, FALSE ) ) {

	    e = (EDGEPTR) Ygraph_edgeData(graphedge);
	    length += e->length ;
	}
	return (length ) ;
} /* get_length */

generateTreeForNet (n)
INT n ; 
{

INT GRcompNetRoute() ;
ROUTEPTR route ;
static int maxImproveS ;

    Ygraph_clearRequired( GraphG );

    findNodesForPins( n ) ;
    if ( Ygraph_nodeRequiredCount( GraphG ) > 2 ){
	maxImproveS = maxImproveG ;
    } else {
	maxImproveS = 0 ;
    }

    route = YMALLOC( 1 , ROUTE ) ;
    route->net = n ;
    route->routeGraph = Ygraph_steiner( GraphG, maxImproveS ) ; 
    Yrbtree_insert( RouteTreeG, (char*)route ) ;
#ifdef DRAWROUTE
    drawRoute (route) ;
#endif
} /* generateTreeForNet () */

make_graph()
{
static int num,edges,precap;
static PADBOXPTR padptr;
static CBOXPTR padcellptr;
EDGEPTR search_Vedges( P1(INT n1) ) ;
EDGEPTR search_Hedges( P1(INT n1) ) ;
INT comparenodes(), compareedges() ;
BOOL flag_l = FALSE;
BOOL flag_b = FALSE;
BOOL flag_t = FALSE;
BOOL flag_r = FALSE;
INT first_Xgrid, first_Ygrid, last_Xgrid, last_Ygrid ; 

 temp1 = vlineG * hlineG;
 temp2 = vlineG + hlineG;

 numnodes =  temp1 + temp2 + 1;
 numedges =  2*temp1 + temp2 ; 
/* numedges =  2*temp1 - temp2 + 8;  */

 nodelist = (NODEPTR*) Ysafe_calloc ( (numnodes+1) , sizeof(NODEPTR));
 edgelist = (EDGEPTR*) Ysafe_calloc ( (numedges+1) , sizeof(EDGEPTR));

 /**** project all the pins of the pads on the edges ********/
 /**** on the ring of the core                       *******/
 /**** Find the center line going thru the pads      ********/

for (pad = numcellsG + numMacroG + 1; pad <= numcellsG + numtermsG; pad++){

  padcellptr = carrayG[pad];
  padptr = padcellptr->padptr;
  if (padptr->padside == 1) {
     if (flag_l) continue;
     else {
        lx = padcellptr->cxcenter;
	flag_l = TRUE ;
     }
  } else if (padptr->padside == 3){
     if (flag_r) continue;
     else {
        rx = padcellptr->cxcenter;
	flag_r = TRUE ;
     }
  } else if (padptr->padside == 2){
     if (flag_t) continue;
     else {
        ty = padcellptr->cycenter;
	flag_t = TRUE ;
     }
  } else if (padptr->padside == 4){
     if (flag_b) continue;
     else {
        by = padcellptr->cycenter;
	flag_b = TRUE ;
     }
  } 
}

Hcap = (int*) Ysafe_calloc (vlineG+1 , sizeof(int));
Hcap[0] = (double) ( line_x[1] - lx ) / track_pitch; 

for (line = 1; line <vlineG; line++){
 precap = (double)(line_x[line+1] - line_x[line])/ track_pitch;
 if (precap == 0) precap = 1;
 Hcap[line] = precap;
}
Hcap[vlineG] = (double) ( rx - line_x[vlineG] ) / track_pitch; 

Vcap = (int*) Ysafe_calloc (hlineG+1 , sizeof(int));
Vcap[0] = (double) ( line_y[1] - by ) / track_pitch; 
for (line = 1; line <hlineG; line++){
 precap = (double)(line_y[line+1] - line_y[line])/ track_pitch;
 if (precap == 0) precap = 1;
 Vcap[line] = precap;
}
Vcap[hlineG] = (double) ( ty - line_y[hlineG] ) / track_pitch; 


Nodetree = Yrbtree_init( comparenodes ) ;
Hor_edtree = Yrbtree_init( compareedges ) ;
Ver_edtree = Yrbtree_init( compareedges ) ;


    if (flag_l) { /* that means flag was set */
	first_Xgrid = 1 ;
    } else {
	first_Xgrid = 2 ;
    }
    if (flag_r) { /* that means flag was set */
	last_Xgrid = vlineG +1 ;
    } else {
	last_Xgrid = vlineG ;
    }
    if (flag_b) { /* that means flag was set */
	first_Ygrid = 0 ;
	y2S = by; /* the initialisation true only for valid bottom pads */
    } else {
	first_Ygrid = 1 ;
	y2S = tarrayG[1]->center_y; /* the initialisation to first tile */
    }
    if (flag_r) { /* that means flag was set */
	last_Ygrid = hlineG ;
    } else {
	last_Ygrid = hlineG - 1;
    }
for (gridy = first_Ygrid ; gridy <= last_Ygrid ; gridy++){

	if ( gridy < hlineG-1 )
        	y3S = tarrayG[gridy*(vlineG-1)+1]->center_y;
	else y3S = ty;

    if (flag_l) { /* that means flag was set */
	x2S = lx; /* the initialisation true only for valid left pads */
    } else {
	x2S = tarrayG[1]->center_x; /* the initialisation to first tile */
    }
    for (gridx = first_Xgrid; gridx <= last_Xgrid ; gridx++){
        num++;
 	ndptr = nodelist[num] = (NODEPTR) Ysafe_calloc (1,sizeof(NODE)); 


/*****************CAPACITY calculations ***********************/

	capy = Hcap[gridx-1];

	capx = Vcap[gridy];

	if(gridx == 1 || gridx> vlineG || gridy == 0 || gridy > hlineG-1 ){
	  tptr2 = tarrayG[gridx];
	  tptr1 = tarrayG[gridx-1];
        } else {
	  tptr3 = tarrayG[(gridy-1)*(vlineG-1)+(gridx-1)];
	  ndptr->tile = tptr3->id;
	  tptr4 = tarrayG[(gridy)*(vlineG-1)+(gridx-1)];

/************ if the tiles belonged to same partition *********/
/************ and tiles belonged to same macro ****************/

	  tptr1 = tptr3 ;
	  tptr2 = tarrayG[(gridy-1)*(vlineG-1)+(gridx-1) + 1];
	  /*
	  tptr2 = tarrayG[gridx];
	  tptr1 = tarrayG[gridx-1];
	  */
        }

        if ( gridx < vlineG )
 	       x3S = tptr2->center_x;
        else x3S = rx;

	ndptr->id = num;
	ndptr->x = x2S;
	ndptr->y = y2S;

/**************valid top edges ***************************/

 	if ( gridy == 0 || ( gridy ==  hlineG-1 && flag_t ) ) { /*** top ***/

		edges ++;
 		edptr = edgelist[edges] = (EDGEPTR) 
			Ysafe_calloc (1,sizeof(EDGE));
 		edptr->node1 = num;
		edptr->node2 = num+ (last_Xgrid - first_Xgrid + 1 );
		edptr->InotO = FALSE ; /* these are the top vertical edges, so external */
		edptr->capacity = capy;
		edptr->length = y3S - y2S ;
		edptr->weight = 
			setEdgeWeight( edptr->length, capy, FALSE ) ;
	        edptr->overflow = 0 ;
	       	Yrbtree_insert(Ver_edtree, (char*)edptr);

        } else if (gridx >1 && gridx <= vlineG && gridy != last_Ygrid ){

		edges ++;
 		edptr = edgelist[edges] = (EDGEPTR) 
			Ysafe_calloc (1,sizeof(EDGE));
		edptr->InotO = FALSE ; /* all edges are external by default */

		if ((tptr4->partition_id && tptr3->partition_id )
		  && ( tptr4->partition_id == tptr3->partition_id )) {

		    edptr->InotO = TRUE ; /* these are internal edges inside a partition */
		} 
		if (tptr4->legal && tptr3->legal && tptr4->legal == tptr3->legal) {
		    edptr->InotO = TRUE ; /* these are internal edges inside a macro */
		}
 		edptr->node1 = num;
		edptr->node2 = num+(last_Xgrid - first_Xgrid + 1 );
       		edptr->capacity = capy;
		edptr->length = y3S - y2S ;
		edptr->weight = 
			setEdgeWeight( edptr->length, capy, edptr->InotO ) ;
	        edptr->overflow = 0 ;
		Yrbtree_insert(Ver_edtree, (char*)edptr);
	} 

/**************valid right edges ***************************/

 	if (  gridx == 1 || (gridx == vlineG  &&  flag_r )) { /**** right ***/
		edges ++;
 		edptr = edgelist[edges] = (EDGEPTR) 
			Ysafe_calloc (1,sizeof(EDGE));
 		edptr->node1 = num;
		edptr->node2 = num+1;
		edptr->InotO = FALSE ; /* these are the right hor. edges, so external */
       		edptr->capacity = capx;
		edptr->length = x3S - x2S ;
		edptr->weight = 
			setEdgeWeight( edptr->length, capx, FALSE ) ;
	        edptr->overflow = 0 ;
		Yrbtree_insert(Hor_edtree, (char*)edptr);
        } else if (gridy > 0 && gridy < hlineG && gridx!= last_Xgrid) {

		edges ++;
 		edptr = edgelist[edges] = (EDGEPTR) 
			Ysafe_calloc (1,sizeof(EDGE));
		edptr->InotO = FALSE ; /* all edges are external by default */

		if ((tptr2->partition_id && tptr1->partition_id )
		  && ( tptr2->partition_id == tptr1->partition_id )) {
		    edptr->InotO = TRUE ; /* these are internal edges inside a partition */
		} 
		if (tptr2->legal && tptr1->legal && tptr2->legal == tptr1->legal) {
		    edptr->InotO = TRUE ; /* these are internal edges inside a macro */
		} 
 		edptr->node1 = num;
		edptr->node2 = num+1;
       		edptr->capacity = capx;
		edptr->length = x3S - x2S ;
		edptr->weight = 
			setEdgeWeight( edptr->length, capx, edptr->InotO ) ;
	        edptr->overflow = 0 ;
       		Yrbtree_insert(Hor_edtree, (char*)edptr);
        } 
/***********************************************************/
	
	x1S = x2S;
	x2S = x3S;
	Yrbtree_insert(Nodetree, (char*)ndptr);
    }
    y1S = y2S;
    y2S = y3S;
}

} /* make_graph() */


INT setEdgeWeight(length, capacity, InotO)
int length , capacity ;
BOOL InotO ;
{
INT weight ;
DOUBLE edgecoeff ;
double  scale ;

    if (InotO) {
	edgecoeff = Coeff2G ;
    } else {
	edgecoeff = Coeff1G ;
    }
    scale = (length ) / 10 ;
    weight = length + (scale / capacity) * edgecoeff ;
    return (weight) ;

} /* setEdgeWeight */


findNodesForPins(net)
INT net ;
{

INT GRcomp_points();

static int node,x,y,cell,tile ;
static PINBOXPTR pinptr;
static CBOXPTR cptr;
static YTREEPTR xtree;
static CORNERS point, cor_ptr;
BOOL cont_flag ;


    xtree = Yrbtree_init( GRcomp_points ) ;

    x = y = 0;  

    for(pinptr = netarrayG[net]->pins ; pinptr ; pinptr = pinptr->next ) {

    /*** remember only one pad is allowed for each net on one side ****/

	point = (CORNERS) Ysafe_calloc( 1,sizeof(CORBOX));
	point->x_coord = grid_x[pinptr->xpos];
	cont_flag = FALSE;
	for (cor_ptr = (CORNERS) Yrbtree_interval(xtree,(char*)point,(char*)point,TRUE); cor_ptr;
	cor_ptr = (CORNERS) Yrbtree_interval(xtree,(char*)point,(char*)point,FALSE)){
		if (cor_ptr->y_coord == grid_y[pinptr->ypos]){
			Ysafe_free(point);
			cont_flag = TRUE;
			break;
		}
	}
	if (cont_flag) continue;

	x = grid_x[pinptr->xpos];
	y = point->y_coord = grid_y[pinptr->ypos];

	Yrbtree_insert(xtree, (char*)point);
	cell = pinptr->cell;

	if (cell <=numcellsG){
			node = GRsearch_nodes(x,y);
	} else {
		 if (cell <= numcellsG + numMacroG ){
			  /*** macro_case ***/

			   tile = search_macro_tile(x,y);
                           node =
			   GRsearch_nodes(tarrayG[tile]->center_x,
				tarrayG[tile]->center_y);
		  } else {
			  /*** pad_case **/
			node = GRsearch_nodes(x,y) ;
		  }
	}
	Ygraph_nodeRequired (GraphG, Ygraph_nodeFind(GraphG, nodelist[node]), (YNODEPTR) NULL ) ;
    }	
Yrbtree_empty(xtree, Ysafe_free);

}

INT GRcomp_points(a,b)
CORNERS a,b;
{
if (a->x_coord >b->x_coord ) return (GREATER);
else if (a->x_coord <b->x_coord ) return (LESS);
else return (EQUAL);
}

int GRsearch_nodes_for_pads( a, b, padside,dist)
int a, b, padside,*dist;
{
static int node,n , node2 ;

switch (padside){
	case 1:
	{
	 if (b < core_y2G) node = 1;
	 else if (b > core_y1G) node = 1 + hlineG * (vlineG + 1);
	 else {
		n = point_yloc(b);
		node = n*(vlineG + 1) + 1;
	 }
	 *dist = 0;
	}
	break;
	case 4:
	{
	 if (a < core_x1G) node = 1;
	 else if (a > core_x2G) node = (vlineG + 1);
	 else {
		n = point_xloc(a);
		node = n + 1;
	 }
	 *dist = 0;
	}
	break;
	case 3:
	{
	 if (b < core_y2G) node = vlineG + 1;
	 else if (b > core_y1G) node = numnodes;
	 else {
		n = point_yloc(b);
		node = n*(vlineG + 1) + (vlineG + 1);
	 }
	 node2 = node;
	 node -= 1;
	 *dist = nodelist[node2]->x - nodelist[node]->x;
	}
	break;
	case 2:
	{
	 if (a < core_x1G) node = 1 + hlineG * (vlineG + 1);
	 else if (a > core_x2G) node = numnodes;
	 else {
		n = point_yloc(a);
		node = n + 1 + hlineG *(vlineG + 1);
	 }
	 node2 = node ;
	 node -= (vlineG + 1);
	 *dist = nodelist[node2]->y - nodelist[node]->y;
	}
	break;
	default:
	printf("error code 1\n");
	break;
}
return (node);
}


BOOL GRerase_net(nptr)
DBOXPTR nptr;
{
BOOL func_val;
static PINBOXPTR pinptr;

	func_val = TRUE;
	for(pinptr = nptr->pins ; pinptr->next ; pinptr = pinptr->next ) {
		if (pinptr->xpos != pinptr->next->xpos ||
			pinptr->ypos != pinptr->next->ypos) {
		func_val = FALSE;
		break;
	}
	}
return (func_val);
}

int GRsearch_nodes(a,b)
int a,b;
{
static NODEPTR nodeptr,dumptr;

dumptr = (NODEPTR) Ysafe_calloc(1, sizeof(NODE));
dumptr->x = a;
dumptr->y = b;
nodeptr = (NODEPTR) Yrbtree_search(Nodetree, (char*)dumptr);
Ysafe_free(dumptr);
return(nodeptr->id);
}

generate_pseudopads()
{

ROUTEPTR route ;
YGRAPHPTR graph ;
YEDGEPTR graphedge ;
EDGEPTR e ;

    for ( route= (ROUTEPTR) Yrbtree_enumerate(RouteTreeG, TRUE) ; route ; 
	route = (ROUTEPTR) Yrbtree_enumerate(RouteTreeG, FALSE ) ) {

	graph = route->routeGraph ;
	/*--- enumerate the edges of the graph and add the 
	      overflow to the egde overflow field ---*/

	current_netG = route->net ;

	for ( graphedge = Ygraph_edgeEnumerate( graph, TRUE) ; graphedge ; 
	    graphedge = Ygraph_edgeEnumerate( graph, FALSE ) ) {

	    e = (EDGEPTR) Ygraph_edgeData(graphedge);
	    if (!e->InotO) {
		addPadtoPart( e ) ;
		num_padsG++ ;
	    }
	}
    }
} /* end generate_pseudopads() */

addPadtoPart( edgeptr )
EDGEPTR edgeptr;
{
 static NODEPTR ndptr1,ndptr2;
 static PTILEPTR tileptr1,tileptr2;
 INT temp;
 static INT node1, node2 ;
BOOL HnotV ;

node1 = edgeptr->node1;
node2 = edgeptr->node2;

 if (node1 >node2){
 temp = node1;
 node1 = node2;
 node2 = temp;
 }
 ndptr1 = nodelist[node1];
 ndptr2 = nodelist[node2];

 /* determine whether it is an horinzontal or Ver edge */

 if (ndptr1->x == ndptr2->x) {
     HnotV = FALSE ;
 } else if (ndptr1->y == ndptr2->y) {
     HnotV = TRUE ;
 }

 if (ndptr1->tile) {
 	tileptr1 = tarrayG[ndptr1->tile];
 }
 if (ndptr2->tile) {
	tileptr2 = tarrayG[ndptr2->tile];
 }

if (ndptr1->tile > 0 && ndptr2->tile > 0 ) { /**** check with bill*/
	if (HnotV) {
		padx = tileptr1->lower_right_x;
		pady = ndptr1->y;
               	GRgen_pads_pins(3,tileptr1);
               	GRgen_pads_pins(1,tileptr2);
	} else {
		pady = tileptr1->upper_left_y;
		padx = ndptr1->x;
               	GRgen_pads_pins(4,tileptr1);
               	GRgen_pads_pins(2,tileptr2);
	}
} else {
	if (HnotV) {
		pady = ndptr1->y;
		if (ndptr1->tile > 0) {
			padx = tileptr1->lower_right_x;
               		GRgen_pads_pins(3,tileptr1);
		}
		else if (ndptr2->tile > 0){
			padx = tileptr2->upper_left_x;
               		GRgen_pads_pins(1,tileptr2);
		}
	} else {
		padx = ndptr1->x;
		if (ndptr1->tile > 0) {
			pady = tileptr1->upper_left_y;
               		GRgen_pads_pins(4,tileptr1);
		}
		else if (ndptr2->tile > 0){
			pady = tileptr2->lower_right_y;
               		GRgen_pads_pins(2,tileptr2);
	        }
	}
}
}

GRgen_pads_pins(padside,tileptr)
int padside;
PTILEPTR tileptr;
{
/* add a pad to padlist of partition *
    name = pseudo1
    corners 1/4 (default)
    padx,pady
    restrict side R
    pin name pseudo1 signal netname layer 0 padx,pady 
*********/

static PADPTR padptr;
static PARTNPTR partptr;

    partptr = partarrayG[tileptr->partition_id];
    if (!partptr || !partptr->capacity) return;
    partptr->numpads++;
    if (!partptr->padlist) {
	partptr->padlist = (PADPTR*) Ysafe_calloc ((numnetsG +1) ,
						    sizeof(PADPTR));
    }

    padptr = partptr->padlist[partptr->numpads] = (PADPTR) Ysafe_calloc 
					    (1,sizeof(PDBOX));
    padptr->id = partptr->numpads;
    padptr->padside = padside;
    padptr->tileptr = tileptr;
    padptr->x = padx;
    padptr->y = pady;
    padptr->net = current_netG;
}

#ifdef OLDCODE

print_nodes()
{
static int i;
for (i=1; i<=numnodes; i++){
printf("node %d and tile %d\n ", i, nodelist[i]->tile);
}

EDGEPTR search_edges(n1,n2)
int n1,n2;
{
static int i;
static EDGEPTR edgeptr;
for (i = 1; i<=numedges; i++){
	edgeptr = edgelist[i];
	if (edgeptr->node1 != n1 || edgeptr->node2 != n2) continue;
	else return (edgeptr);
}
}

EDGEPTR search_Vedges(n1)
int n1;
{
static EDGEPTR edgeptr,dumptr;
dumptr = (EDGEPTR) Ysafe_calloc(1, sizeof(EDGE));
dumptr->node1 = n1;
edgeptr = (EDGEPTR) Yrbtree_search(Ver_edtree,(char*)dumptr);
Ysafe_free(dumptr);
return (edgeptr);
}


EDGEPTR search_Hedges(n1)
int n1;
{
static EDGEPTR edgeptr,dumptr;
dumptr = (EDGEPTR) Ysafe_calloc(1, sizeof(EDGE));
dumptr->node1 = n1;
edgeptr = (EDGEPTR) Yrbtree_search(Hor_edtree,(char*)dumptr);
Ysafe_free(dumptr);
return (edgeptr);
}


drawNode()
{
static int x1,y1,x2,y2,n,xr,yr;

for (n=1; n<=numnodes; n++){
    xr = nodelist[n]->x;
    yr = nodelist[n]->y;
    TWdrawPin(0,xr-20,yr-20,xr+20,yr+20,TWBROWN,NULL);
}

} /* drawNode */

drawEdge()
{
static int x1,y1,x2,y2,n,xr,yr;

for (n=1; n<=numedges; n++){
    x1 = edgelist[n]->x1;
    x2 = edgelist[n]->x2;
    y1 = edgelist[n]->y1;
    y2 = edgelist[n]->y2;
    if (edgelist[n]->HnotV)
    TWdrawLine(0,x1,y1,x2,y1,TWBLACK,NULL);
    else TWdrawLine(0,x1,y1,x1,y2,TWBLACK,NULL);
}
} /* drawEdge */


create_gpar_file()
{
FILE *fp;
char filename[LRECL] ;

sprintf( filename , "%s.gpar" , cktNameG ) ;
fp = TWOPEN( filename , "w",ABORT ) ;
fprintf(fp,"digital.circuit\n");
fprintf(fp,"objective 2\n");
fprintf(fp,"limit_iteration 0\n");
TWCLOSE(fp);
}

#endif /* OLDCODE */

