/****************************************************************************
*                   POLYSOLV.h
*
*  This module contains all defines, typedefs, and prototypes for MATH.C.
*
*  from Persistence of Vision(tm) Ray Tracer
*  Copyright 1996,1999 Persistence of Vision Team
*---------------------------------------------------------------------------
*
*
* This program is based on the popular DKB raytracer version 2.12.
* DKBTrace was originally written by David K. Buck.
* DKBTrace Ver 2.0-2.12 were written by David K. Buck & Aaron A. Collins.
*
*****************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif


#ifndef POLYSOLV_H
#define POLYSOLV_H



/*****************************************************************************
* Global preprocessor defines
******************************************************************************/

#define MAX_ORDER 15


/*****************************************************************************
* Global typedefs
******************************************************************************/




/*****************************************************************************
* Global variables
******************************************************************************/



/*****************************************************************************
* Global functions
******************************************************************************/

int Solve_Polynomial (int n, double *c, double *r, int sturm, double epsilon);



#endif

#ifdef __cplusplus
}
#endif
