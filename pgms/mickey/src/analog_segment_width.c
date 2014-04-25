#ifndef lint
static char SccsId[] = "@(#)analog_segment_width.c	Yale Version 2.2 5/16/91";
#endif
/* -----------------------------------------------------------------

	FILE:		segment_width.c
	AUTHOR:		Dahe Chen
	DATE:		Tue Apr 24 17:09:05 EDT 1990
	CONTENTS:	segment_width()
			This function is actually supplied by the
			user of Mickey. It will return the width
			of a segment of a route given the current
			density on the segment and the lenght of
			the route.
			The sample function uses the Black's law.
	REVISION:
		Tue Oct  9 16:03:01 EDT 1990
		Scale the parameter width down to smaller values.

----------------------------------------------------------------- */

#include <stdio.h>
#include <math.h>

/***********************************************************
* Boltzmann's constant in electron volts
***********************************************************/
#define		Boltzmann	8.61423e-5

/***********************************************************
* For all precesses
***********************************************************/
#define		Beta		2.9e13

/***********************************************************
* 	0.5	Analog 16KA
* 	0.5	Analog 20KA
* 	0.3	Std SSIV
* 	-0.35	L7 2 Metal 1
* 	0.2	L7 2 Metal 2
* 	0.45	L7 5 Metal 1
* 	1.00	L7 5 Metal 2
***********************************************************/
#define		Wsigma		0.5

/***********************************************************
* 	330	Analog 16KA
* 	330	Analog 20KA
* 	330	Std SSIV
* 	200	L7 2 Metal 1
* 	500	L7 2 Metal 2
* 	350	L7 5 Metal 1
* 	500	L7 5 Metal 2
***********************************************************/
#define		Tsigma		330

/***********************************************************
* 	16000	Analog 16KA
* 	20000	Analog 20KA
* 	11000	Std SSIV
* 	7900	L7 2 Metal 1
* 	16000	L7 2 Metal 2
* 	7900	L7 5 Metal 1
* 	16000	L7 5 Metal 2
***********************************************************/
#define		T		16000.0

/***********************************************************
* For all precesses
***********************************************************/
#define		Ea		0.6

/***********************************************************
* For all precesses. NOTE: this number must be a FLOATING
* number.
***********************************************************/
#define		n		2.0

/***********************************************************
* For all precesses
***********************************************************/
#define		Sigma		0.41

/***********************************************************
* Median Time to Failur (MTF) of a metal line in years
***********************************************************/
#define		MTF		10.0

/***********************************************************
* Temperature in Celsius
***********************************************************/
#define		temperature	20.0

int
segment_width(dist, dens)
    int dist;
    int dens;
{

    int width;
    double temp;

    temp = Boltzmann * (temperature+273.15);
    temp = 100.0 * exp(temp);
    width = (int) (MTF * pow((double)dens, n) / temp);

    return(width);

}/* end of segment_width */
