/**
*	WARNING: Do Not Remove This Section
*
*       $LastChangedRevision: 415 $
*       $LastChangedDate: 2010-12-18 17:21:05 +0100 (Sa, 18. Dez 2010) $
*       $LastChangedBy: davidjansen $
*
*	MRMC is a model checker for discrete-time and continuous-time Markov
*	reward models. It supports reward extensions of PCTL and CSL (PRCTL
*	and CSRL), and allows for the automated verification of properties
*	concerning long-run and instantaneous rewards as well as cumulative
*	rewards.
*
*	Copyright (C) The University of Twente, 2004-2008.
*	Copyright (C) RWTH Aachen, 2008-2009.
*	Authors: Ivan Zapreev, Christina Jansen
*
*	This program is free software; you can redistribute it and/or
*	modify it under the terms of the GNU General Public License
*	as published by the Free Software Foundation; either version 2
*	of the License, or (at your option) any later version.
*
*	This program is distributed in the hope that it will be useful,
*	but WITHOUT ANY WARRANTY; without even the implied warranty of
*	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*	GNU General Public License for more details.
*
*	You should have received a copy of the GNU General Public License
*	along with this program; if not, write to the Free Software
*	Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*
*	Main contact:
*		Lehrstuhl für Informatik 2, RWTH Aachen University
*		Ahornstrasse 55, 52074 Aachen, Germany
*		E-mail: info@mrmc-tool.org
*
*       Old contact:
*		Formal Methods and Tools Group, University of Twente,
*		P.O. Box 217, 7500 AE Enschede, The Netherlands,
*		Phone: +31 53 4893767, Fax: +31 53 4893247,
*		E-mail: mrmc@cs.utwente.nl
*
*	Source description:
*		A wrapper file for using different random number generators
*		from the GNU Scientific Library.
*
*		For more information see:
*			http://www.gnu.org/software/gsl/
*/

#ifndef RNG_GSL_H
#define RNG_GSL_H

/**
* Sets the method for computing non-uniformly distributed random numbers -
* all implementations taken from the GNU Scientific Library.
* @param _method one from {RNG_GSL_RANLUX_METHOD, RNG_GSL_LFG_METHOD, RNG_GSL_TAUS_METHOD}
* @return the pointer to the random number generator instance
*/
extern void * setGSLMethod(int _method);

/**
* This function seeds the chosen GSL random number
* generator.
* @param pRandGenerator the rand number generator structure, needed for GSL.
* @param s the value the stream of random numbers is started with
*/
extern inline void generateSeedGSL(void * pRandGenerator, unsigned long s);

/**
* Create uniformly distributed random number between 0 and 1
* @param pRandGenerator the rand number generator structure, needed for GSL.
* @return random number between 0 and 1
*/
extern inline double generateRandUnifGSL(void * pRandGenerator);

/**
* Creates an exponentially distributed random number using the
* chosen GSL random number generator.
* @param pRandGenerator the rand number generator structure, needed for GSL.
* @param lambda: inverse scale of exponential distribution
* @return the random number (exponentially distributed)
*/
extern inline double generateExpRandNumberGSL(void * pRandGenerator, double lambda);

/**
* This function frees the memory allocated for the chosen random number
* generator.
* @param pRandGenerator the rand number generator structure, needed for GSL.
*/
extern inline void freeRNGGSL(void * pRandGenerator);

#endif
