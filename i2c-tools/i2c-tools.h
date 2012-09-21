/*
 *
 * @Component			OMAPCONF
 * @Filename			i2c-tools.h
 * @Description			i2c-tools Function Headers
 * @Author			Patrick Titiano (p-titiano@ti.com)
 * @Date			2011
 * @Copyright			Texas Instruments Incorporated
 *
 *
 * Copyright (C) 2011 Texas Instruments Incorporated - http://www.ti.com/
 *
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *    Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 *    Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the
 *    distribution.
 *
 *    Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */


#ifndef __I2C_TOOLS_H__
#define __I2C_TOOLS_H__


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		i2cget
 * @BRIEF		read given data from given address of given device of
 *			given I2C bus
 * @RETURNS		0 in case of success
 *			-1 in case of incorrect argument
 *			-8 in case of i2c dev cannot be opened
 *			-4 in case of I2C read error
 * @param[in]		i2cbus: I2C bus number
 * @param[in]		address: I2C device address
 * @param[in]		daddress: I2C device register address
 * @param[in,out]	data: I2C device register content (returned)
 * @DESCRIPTION		read given data from given address of given device of
 *			given I2C bus
 *//*------------------------------------------------------------------------ */
int i2cget(
	unsigned int i2cbus, unsigned int address, unsigned int daddress,
	unsigned int *data);


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		i2cset
 * @BRIEF		write given data at given address of given device of
 *			given I2C bus
 * @RETURNS		0 in case of success
 *			-1 in case of incorrect argument
 *			-8 in case of i2c dev cannot be opened
 *			-4 in case of I2C read error
 * @param[in]		i2cbus: I2C bus number
 * @param[in]		address: I2C device address
 * @param[in]		daddress: I2C device register address
 * @param[in]		data: data to be written
 * @DESCRIPTION		write given data at given address of given device of
 *			given I2C bus
 *//*------------------------------------------------------------------------ */
int i2cset(
	unsigned int i2cbus, unsigned int address, unsigned int daddress,
	unsigned int data);


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		i2cget_word
 * @BRIEF		read given data from given address of given device of
 *			given I2C bus
 * @RETURNS		0 in case of success
 *			-1 in case of incorrect argument
 *			-8 in case of i2c dev cannot be opened
 *			-4 in case of I2C read error
 * @param[in]		i2cbus: I2C bus number
 * @param[in]		address: I2C device address
 * @param[in]		daddress: I2C device register address
 * @param[in,out]	data: I2C device register content (returned)
 * @DESCRIPTION		read given data from given address of given device of
 *			given I2C bus
 *//*------------------------------------------------------------------------ */
int i2cget_word(
	unsigned int i2cbus, unsigned int address, unsigned int daddress,
	unsigned int *data);


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		i2cset_word
 * @BRIEF		write given data at given address of given device of
 *			given I2C bus
 * @RETURNS		0 in case of success
 *			-1 in case of incorrect argument
 *			-8 in case of i2c dev cannot be opened
 *			-4 in case of I2C read error
 * @param[in]		i2cbus: I2C bus number
 * @param[in]		address: I2C device address
 * @param[in]		daddress: I2C device register address
 * @param[in]		data: data to be written
 * @DESCRIPTION		write given data at given address of given device of
 *			given I2C bus
 *//*------------------------------------------------------------------------ */
int i2cset_word(
	unsigned int i2cbus, unsigned int address, unsigned int daddress,
	unsigned int data);


#endif
