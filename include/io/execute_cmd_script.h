/**
*	WARNING: Do Not Remove This Section
*
*       $LastChangedRevision: 415 $
*       $LastChangedDate: 2016-03-23  $
*       $LastChangedBy: joleuger $
*
*	MRMC is a model checker for discrete-time and continuous-time Markov
*	reward models. It supports reward extensions of PCTL and CSL (PRCTL
*	and CSRL), and allows for the automated verification of properties
*	concerning long-run and instantaneous rewards as well as cumulative
*	rewards.
*
*	Copyright (C) The University of Twente, 2004-2008.
*	Copyright (C) RWTH Aachen, 2008-2009.
*	Copyright (C) University of Augsburg, 2016.
*	Authors: Maneesh Khattri, Ivan Zapreev, Johannes Leupolz
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
*	Source description: Read and execute Command (.cmd) script.
*/

#ifndef EXECUTE_CMD_SCRIPT_H
#define EXECUTE_CMD_SCRIPT_H

#include "label.h"

/*****************************************************************************
name		: execute_cmd_script
role		: reads and executes a .cmd file
@param		: char *filename: input .cmd file's name.
@return		: int: returns 0 if the program should exit after execution.
remark		:
******************************************************************************/
extern int execute_cmd_script(const char *);

#endif
