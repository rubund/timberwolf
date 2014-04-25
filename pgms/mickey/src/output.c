#ifndef lint
static char SccsId[] = "@(#)output.c	Yale Version 2.2 5/16/91" ;
#endif
/* -----------------------------------------------------------------

	FILE:		output.c
	AUTHOR:		Dahe Chen
	DATE:		Fri Nov 4 13:51:48 EDT 1989
	CONTENTS:	output()
	REVISION:

----------------------------------------------------------------- */

#include	"define.h"
#include	"gg_router.h"
#include	"macros.h"

extern	int	mlen	;
extern	int	Mlen	;
extern	int	alen	;

void
output( routes , Apins )
int routes[] ;
int Apins[] ;
{

int i ;

OUT1(
"==================================================================\n" ) ;
OUT1(
"total nets                           t_m_len    t_M_len    t_a_len\n") ;
OUT1(
"==================================================================\n" ) ;
OUT5( "    %-13d                      %-8d  %-8d   %-d\n",
	   numnets, mlen, Mlen, alen ) ;
OUT1(
"==================================================================\n" ) ;
OUT1(
"total nets                         a_t_m_len  a_t_M_len  a_t_a_len\n") ;
OUT1(
"==================================================================\n" ) ;
OUT5( "    %-13d                      %-8d  %-8d   %-d\n\n\n",
	   numnets, mlen/numnets, Mlen/numnets,
	   alen/totroutes ) ;

PRINT(fdat,
"==================================================================\n" ) ;
PRINT(fdat,
"total nets                           t_m_len    t_M_len    t_a_len\n") ;
PRINT(fdat,
"==================================================================\n" ) ;
PRINT(fdat, "    %-13d                      %-8d  %-8d   %-d\n",
    numnets, mlen, Mlen, alen ) ;
PRINT(fdat,
"==================================================================\n" ) ;
PRINT(fdat,
"total nets                         a_t_m_len  a_t_M_len  a_t_a_len\n") ;
PRINT(fdat,
"==================================================================\n" ) ;
PRINT(fdat, "    %-13d                      %-8d  %-8d   %-d\n\n\n",
    numnets, mlen/numnets, Mlen/numnets,
    alen/totroutes ) ;

OUT1( "**************************************************\n" ) ;
OUT1( "Net distributions over pins on each net\n" ) ;
OUT1( "**************************************************\n" ) ;
PRINT(fdat, "**************************************************\n" ) ;
PRINT(fdat, "Net distributions over pins on each net\n" ) ;
PRINT(fdat, "**************************************************\n" ) ;
for ( i = 1 ; i < 50 ; i++ )
{
    if ( Apins[i] )
    {
	OUT3( "The number of nets with %-2d pin(s): %-d\n", i, Apins[i] );
	PRINT(fdat, "The number of nets with %-2d pin(s): %-d\n",
		i, Apins[i] ) ;
    }
}
if ( Apins[50] )
{
    OUT2( "The number of nets with 50 pins or more: %-d\n",
	    Apins[i] ) ;
    PRINT(fdat, "The number of nets with 50 pins or more: %-d\n",
	    Apins[i] ) ;
}
OUT1( "\n\n\n" ) ;
PRINT(fdat, "\n\n\n" ) ;
(void) fflush( stdout ) ;
(void) fflush( fdat ) ;

OUT1( "**************************************************\n" ) ;
OUT1( "Net distributions over routes on each net\n" ) ;
OUT1( "**************************************************\n" ) ;
PRINT(fdat, "**************************************************\n" ) ;
PRINT(fdat, "Net distributions over routes on each net\n" ) ;
PRINT(fdat, "**************************************************\n" ) ;
for ( i = 1 ; i <= NUMTREES ; i++ )
{
    if ( routes[i] )
    {
	OUT3( "The number of nets with %2d route(s): %-d\n",
		i, routes[i] ) ;
	PRINT(fdat, "The number of nets with %2d route(s): %-d\n",
		i, routes[i] ) ;
    }
}
(void) fflush( stdout ) ;
(void) fflush( fdat ) ;

} /* end of output */
