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
*	Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
*	MA  02110-1301, USA.
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
*		A C-program for MT19937, with initialization improved
*		2002/2/10. Coded by Takuji Nishimura and Makoto Matsumoto.
*		This is a faster version by taking Shawn Cokus's
*		optimization, Matthe Bellew's simplification, Isaku Wada's
*		real version.
*
*		Before using, initialize the state by using
*		init_genrand(seed).
*
*		Modified for Ymer 11/11/2003.
*
*		Copyright (C) 1997 - 2002, Makoto Matsumoto and
*		Takuji Nishimura, all rights reserved.
*
*		Redistribution and use in source and binary forms, with
*		or without modification, are permitted provided that the
*		following conditions are met:
*
*		1. Redistributions of source code must retain the above
*			copyright notice, this list of conditions and
*			the following disclaimer.
*
*		2. Redistributions in binary form must reproduce the above
*			copyright notice, this list of conditions and the
*			following disclaimer in the documentation and/or
*			other materials provided with the distribution.
*
*		3. The names of its contributors may not be used to endorse
*			or promote products derived from this software
*			without specific prior written permission.
*
*		THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
*		"AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
*		LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
*		A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR
*		CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
*		EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
*		PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
*		PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
*		LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
*		NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
*		SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
*		Any feedback is very welcome.
*			http://www.math.keio.ac.jp/matumoto/emt.html
*		email: matumoto@math.keio.ac.jp
*/

#include "rng_ymer.h"

#include "macro.h"

#include <stdlib.h>

/* Period parameters */
#define N 624
#define M 397
#define MATRIX_A ((unsigned long) 0x9908b0dfL)   /* constant vector a */
#define UMASK ((unsigned long) 0x80000000L) /* most significant w-r bits */
#define LMASK ((unsigned long) 0x7fffffffL) /* least significant r bits */
#define MIXBITS(u,v) ( ((u) & UMASK) | ((v) & LMASK) )
#define TWIST(u,v) ((MIXBITS((u),(v)) >> 1) ^ \
                ((v) & ((unsigned long) 1L) ? MATRIX_A : ((unsigned long) 0L)))

static unsigned long state[N]; /* the array for the state vector  */
static int left = 1;
static int initf = 0;
static unsigned long *next;

/**
* Seeds the MT19937 random number generator.
* @param pRandGenerator the rand number generator structure, needed for GSL.
* @param s the value the stream of random numbers should start with
*/
void generateSeedYM(void * UNUSED(pRandGenerator), unsigned long s){
	int j;
        state[0]= s & (unsigned long) 0xffffffffL;
	for (j=1; j<N; j++) {
                state[j] = ((unsigned long) 1812433253L *
                                (state[j - 1] ^ (state[j - 1] >> 30)) + j);
		/* See Knuth TAOCP Vol2. 3rd Ed. P.106 for multiplier. */
		/* In the previous versions, MSBs of the seed affect   */
		/* only MSBs of the array state[].                     */
		/* 2002/01/09 modified by Makoto Matsumoto             */
                state[j] &= (unsigned long) 0xffffffffL;/*for >32 bit machines*/
	}
	left = 1; initf = 1;
}

static void next_state(void){
	unsigned long *p=state;
	int j;

	/* if init_genrand() has not been called, */
	/* a default initial seed is used         */
        if ( 0 == initf ) {
                generateSeedYM(NULL, (unsigned long) 5489L);
        }

	left = N;
	next = state;

	for (j=N-M+1; --j; p++){
		*p = p[M] ^ TWIST(p[0], p[1]);
	}

	for (j=M; --j; p++){
		*p = p[M-N] ^ TWIST(p[0], p[1]);
	}

	*p = p[M-N] ^ TWIST(p[0], state[0]);
}

/**
* Generates a random number in the interval (0,1).
* @param pRandGenerator the rand number generator structure, needed for GSL.
*/
double generateRandUnifYM(void * UNUSED(pRandGenerator)){
    unsigned long y;

    if (--left == 0) next_state();
    y = *next++;

    /* Tempering */
    y ^= (y >> 11);
    y ^= (y << 7) & (unsigned long) 0x9d2c5680L;
    y ^= (y << 15) & (unsigned long) 0xefc60000L;
    y ^= (y >> 18);

    return ((double)y + 0.5) * (1.0/4294967296.0);
    /* divided by 2^32 */
}

/* These real versions are due to Isaku Wada, 2002/01/09 added */
