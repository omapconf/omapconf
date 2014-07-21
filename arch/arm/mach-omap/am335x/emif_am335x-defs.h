/*
 *
 * @Component			OMAPCONF
 * @Filename			emif_am335x-defs.h
 * @Description			AM335X EMIF Register Address Definitions
 * @Author			Gilberto Rodriguez <gilrod@ti.com>
 * @Date			2014
 * @Copyright			Texas Instruments Incorporated
 *
 *
 * Copyright (C) 2014 Texas Instruments Incorporated - http://www.ti.com/
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


#ifndef __EMIF_AM335X_DEFS_H__
#define __EMIF_AM335X_DEFS_H__


#include <reg.h>
#include <stdio.h>


#define AM335X_EMIF4D_EMIF_MOD_ID_REV			0x4c000000
extern reg am335x_emif4d_emif_mod_id_rev;
#define AM335X_EMIF4D_STATUS				0x4c000004
extern reg am335x_emif4d_status;
#define AM335X_EMIF4D_SDRAM_CONFIG			0x4c000008
extern reg am335x_emif4d_sdram_config;
#define AM335X_EMIF4D_SDRAM_CONFIG_2			0x4c00000c
extern reg am335x_emif4d_sdram_config_2;
#define AM335X_EMIF4D_SDRAM_REF_CTRL			0x4c000010
extern reg am335x_emif4d_sdram_ref_ctrl;
#define AM335X_EMIF4D_SDRAM_REF_CTRL_SHDW		0x4c000014
extern reg am335x_emif4d_sdram_ref_ctrl_shdw;
#define AM335X_EMIF4D_SDRAM_TIM_1			0x4c000018
extern reg am335x_emif4d_sdram_tim_1;
#define AM335X_EMIF4D_SDRAM_TIM_1_SHDW			0x4c00001c
extern reg am335x_emif4d_sdram_tim_1_shdw;
#define AM335X_EMIF4D_SDRAM_TIM_2			0x4c000020
extern reg am335x_emif4d_sdram_tim_2;
#define AM335X_EMIF4D_SDRAM_TIM_2_SHDW			0x4c000024
extern reg am335x_emif4d_sdram_tim_2_shdw;
#define AM335X_EMIF4D_SDRAM_TIM_3			0x4c000028
extern reg am335x_emif4d_sdram_tim_3;
#define AM335X_EMIF4D_SDRAM_TIM_3_SHDW			0x4c00002c
extern reg am335x_emif4d_sdram_tim_3_shdw;
#define AM335X_EMIF4D_PWR_MGMT_CTRL			0x4c000038
extern reg am335x_emif4d_pwr_mgmt_ctrl;
#define AM335X_EMIF4D_PWR_MGMT_CTRL_SHDW		0x4c00003c
extern reg am335x_emif4d_pwr_mgmt_ctrl_shdw;
#define AM335X_EMIF4D_INT_CONFIG			0x4c000054
extern reg am335x_emif4d_int_config;
#define AM335X_EMIF4D_INT_CFG_VAL_1			0x4c000058
extern reg am335x_emif4d_int_cfg_val_1;
#define AM335X_EMIF4D_INT_CFG_VAL_2			0x4c00005c
extern reg am335x_emif4d_int_cfg_val_2;
#define AM335X_EMIF4D_PERF_CNT_1			0x4c000080
extern reg am335x_emif4d_perf_cnt_1;
#define AM335X_EMIF4D_PERF_CNT_2			0x4c000084
extern reg am335x_emif4d_perf_cnt_2;
#define AM335X_EMIF4D_PERF_CNT_CFG			0x4c000088
extern reg am335x_emif4d_perf_cnt_cfg;
#define AM335X_EMIF4D_PERF_CNT_SEL			0x4c00008c
extern reg am335x_emif4d_perf_cnt_sel;
#define AM335X_EMIF4D_PERF_CNT_TIM			0x4c000090
extern reg am335x_emif4d_perf_cnt_tim;
#define AM335X_EMIF4D_READ_IDLE_CTRL			0x4c000098
extern reg am335x_emif4d_read_idle_ctrl;
#define AM335X_EMIF4D_READ_IDLE_CTRL_SHDW		0x4c00009c
extern reg am335x_emif4d_read_idle_ctrl_shdw;
#define AM335X_EMIF4D_IRQSTATUS_RAW_SYS			0x4c0000a4
extern reg am335x_emif4d_irqstatus_raw_sys;
#define AM335X_EMIF4D_IRQSTATUS_SYS			0x4c0000ac
extern reg am335x_emif4d_irqstatus_sys;
#define AM335X_EMIF4D_IRQENABLE_SET_SYS			0x4c0000b4
extern reg am335x_emif4d_irqenable_set_sys;
#define AM335X_EMIF4D_IRQENABLE_CLR_SYS			0x4c0000bc
extern reg am335x_emif4d_irqenable_clr_sys;
#define AM335X_EMIF4D_ZQ_CONFIG				0x4c0000c8
extern reg am335x_emif4d_zq_config;
#define AM335X_EMIF4D_RDWR_LVL_RMP_WIN			0x4c0000d4
extern reg am335x_emif4d_rdwr_lvl_rmp_win;
#define AM335X_EMIF4D_RDWR_LVL_RMP_CTRL			0x4c0000d8
extern reg am335x_emif4d_rdwr_lvl_rmp_ctrl;
#define AM335X_EMIF4D_RDWR_LVL_CTRL			0x4c0000dc
extern reg am335x_emif4d_rdwr_lvl_ctrl;
#define AM335X_EMIF4D_DDR_PHY_CTRL_1			0x4c0000e4
extern reg am335x_emif4d_ddr_phy_ctrl_1;
#define AM335X_EMIF4D_DDR_PHY_CTRL_1_SHDW		0x4c0000e8
extern reg am335x_emif4d_ddr_phy_ctrl_1_shdw;
#define AM335X_EMIF4D_PRI_COS_MAP			0x4c000100
extern reg am335x_emif4d_pri_cos_map;
#define AM335X_EMIF4D_CONNID_COS_1_MAP			0x4c000104
extern reg am335x_emif4d_connid_cos_1_map;
#define AM335X_EMIF4D_CONNID_COS_2_MAP			0x4c000108
extern reg am335x_emif4d_connid_cos_2_map;
#define AM335X_EMIF4D_RD_WR_EXEC_THRSH			0x4c000120
extern reg am335x_emif4d_rd_wr_exec_thrsh;
#define AM335X_EMIF4D_MOD_REGCOUNT			38
extern reg *am335x_emif4d_mod[AM335X_EMIF4D_MOD_REGCOUNT + 1];

typedef enum {
	EMIF_AM335X_EMIF4D,
	EMIF_AM335X_MODS_COUNT = 1
} emif_am335x_mod_id;


extern reg **emif_am335x_mods[EMIF_AM335X_MODS_COUNT];

extern const char *emif_am335x_mods_name[EMIF_AM335X_MODS_COUNT];


#endif
