/* ======================================================================= *//**
 * @Component			OMAPCONF
 * @Filename			util.h
 * @Description			I2C helper functions
 * @Author			Jean Delvare <khali@linux-fr.org>
 * @Date			2006
 * @Copyright			GPL version 2
 *//*======================================================================== */
/*
    util - helper functions
    Copyright (C) 2006 Jean Delvare <khali@linux-fr.org>

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
    MA 02110-1301 USA.
*/

#ifndef _UTIL_H
#define _UTIL_H


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		user_ack
 * @BRIEF		Return 1 if we should continue, 0 if we should abort
 * @RETURNS		1 if we should continue, 0 if we should abort
 * @param[in]		def: default value
 * @DESCRIPTION		Return 1 if we should continue, 0 if we should abort
 *//*------------------------------------------------------------------------ */
extern int user_ack(int def);


#endif
