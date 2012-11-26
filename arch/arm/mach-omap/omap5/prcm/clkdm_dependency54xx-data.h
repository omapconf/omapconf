/******************************************************************************
 * TEXAS INSTRUMENTS CONFIDENTIAL                                             *
 ******************************************************************************
 *
 * clkdm_dependency54xx-data.h
 *
 * OMAP5 Clock Domain Dependencies Definitions
 *
 * Author: Patrick Titiano (p-titiano@ti.com)
 *
 * File automatically generated from reggen.py v0.8.
 *
 * [2012] TEXAS INSTRUMENTS Incorporated
 * All Rights Reserved.
 *
 * NOTICE: All information contained herein is, and remains the property
 * of TEXAS INSTRUMENTS Incorporated.
 * The intellectual and technical concepts contained
 * herein are proprietary to TEXAS INSTRUMENTS Incorporated and may be covered
 * by U.S. and Foreign Patents, patents in process, and are
 * protected by trade secret or copyright law.
 * Dissemination of this information or reproduction of this material
 * is strictly forbidden unless prior written permission is obtained
 * from TEXAS INSTRUMENTS Incorporated.
 *
 */

#ifndef __CLKDM_DEPENDENCY54XX_DATA_H__
#define __CLKDM_DEPENDENCY54XX_DATA_H__

#include <reg.h>
#include <clkdm54xx.h>
#include <clkdm_dependency.h>

extern const reg *clkdmdep54xx_reg_table[CLKDM54XX_ID_MAX][2];

extern const short int clkdmdep54xx_bit_pos_table[CLKDM54XX_ID_MAX];

extern const clkdmdep_ctrl_type *clkdmdep54xx_statdep_table[CLKDM54XX_ID_MAX];
extern const clkdmdep_ctrl_type *clkdmdep54xx_dyndep_table[CLKDM54XX_ID_MAX];


#endif