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
*	Authors: Maneesh Khattri
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
*	Source description: Manage Storage for Labelling.
*/

#ifndef LABEL_H
#define LABEL_H

#include "bitset.h"

/*****************************************************************************
			STRUCTURE
name		: labelling
@member n	: The number of labels.
@member temp_n	: The actual number of labels in label (required when reading the .lab file).
@member ns	: The number of states.
@member label	: The ascendingly sorted list of labels.
@member b	: A list of bitsets.
remark		: There is a one-one relation between label and bitset. Each bitset
		  indicates the states in which a certain label is valid. For instance
		  bitset[0] indicates the states in which label[0] is valid.
******************************************************************************/
typedef struct labelling
{
	int n;
	int ns;
	int temp_n;
	char **label;
        /*@only@*/ bitset_ptr * b;
}labelling;

/*****************************************************************************
name		: get_new_label
role		: get a new labelling structure.
@param		: int n: the number of labels.
@param		: int ns: the number of states.
@return		: labelling *: returns a pointer to a new labelling structure.
remark		:
******************************************************************************/
extern labelling * get_new_label(int, int);

/*****************************************************************************
name		: add_label
role		: add a new label in ascending lexicographic order to the given
		  labelling structure.
@param		: labelling *labellin: the labelling structure.
@param		: char *label: the label to be added.
@return         : BOOL: FALSE-fail TRUE-success. Fails when labellin->n number
                  of labels
		  are already added.
remark		: This method also initializes the appropriate bitset with a new
		  bitset.
******************************************************************************/
extern BOOL add_label(labelling *, const char *);

/*****************************************************************************
name		: add_label_bitset
role		: set the bitset of the given labelling structure indexed by the
		  given label to a desired value.
@param		: labelling *labellin: the labelling structure.
@param		: char *label: the label whose bitset is to be changed.
@param		: bitset *b: the new bitset.
@return         : BOOL: FALSE-fail TRUE-success.
remark		: Fails when the given label cannot be found in the given labelling
		  structure.
******************************************************************************/
extern BOOL add_label_bitset(labelling *, const char *, bitset *);

/**
* Set the bit of the given labelling structure indexed by the given
* label and position to 1. Fails when the given label cannot be found
* in the given labelling structure.
* @param labellin the labelling structure.
* @param label the label whose bitset is to be changed.
* @param pos the position of the bit.
*/
extern void set_label_bit(labelling * labellin, const char * label, int pos);

/**
* Get the bitset of the given labelling structure indexed by the
* given label.
* @param labellin: the labelling structure.
* @param label: the label whose bitset is to be changed.
* @return the bitset of states labelled with 'label', if label is
*         not known returns NULL.
*/
extern bitset * get_label_bitset( const labelling *, const char *);

/*****************************************************************************
name		: print_labelling
role		: prints the given labelling structure.
@param		: labelling *labellin: the labelling structure to be printed.
@return		:
remark		:
******************************************************************************/
extern void print_labelling(const labelling *);

/**
* Writes the given labelling structure to a file
* @param labellin the labelling structure to be printed.
* @param fname the name of the output file
* @return FALSE if writing failed, TRUE otherwise.
* NOTE: This function returns FALSE if labelling is not valid, or the file could
*       not
*	be opened for writing. This is also indicated via a printf statement.
*/
extern BOOL write_lab_file(const labelling * a, const char * fname);

/*****************************************************************************
name		: free_labelling
role		: frees the given labelling structure.
@param		: labelling *labellin: the labelling structure to be freed.
@return		:
remark		:
******************************************************************************/
extern void free_labelling(labelling *);

#endif
