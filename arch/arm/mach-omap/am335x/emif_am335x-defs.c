/*
 *
 * @Component			OMAPCONF
 * @Filename			emif_am335x.c
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

#include <emif_am335x-defs.h>

reg am335x_emif4d_emif_mod_id_rev = {
	"EMIF4D_EMIF_MOD_ID_REV",
	AM335X_EMIF4D_EMIF_MOD_ID_REV,
	0xDEADBEEF,
	0};

reg am335x_emif4d_status = {
	"EMIF4D_STATUS",
	AM335X_EMIF4D_STATUS,
	0xDEADBEEF,
	0};

reg am335x_emif4d_sdram_config = {
	"EMIF4D_SDRAM_CONFIG",
	AM335X_EMIF4D_SDRAM_CONFIG,
	0xDEADBEEF,
	0};

reg am335x_emif4d_sdram_config_2 = {
	"EMIF4D_SDRAM_CONFIG_2",
	AM335X_EMIF4D_SDRAM_CONFIG_2,
	0xDEADBEEF,
	0};

reg am335x_emif4d_sdram_ref_ctrl = {
	"EMIF4D_SDRAM_REF_CTRL",
	AM335X_EMIF4D_SDRAM_REF_CTRL,
	0xDEADBEEF,
	0};

reg am335x_emif4d_sdram_ref_ctrl_shdw = {
	"EMIF4D_SDRAM_REF_CTRL_SHDW",
	AM335X_EMIF4D_SDRAM_REF_CTRL_SHDW,
	0xDEADBEEF,
	0};

reg am335x_emif4d_sdram_tim_1 = {
	"EMIF4D_SDRAM_TIM_1",
	AM335X_EMIF4D_SDRAM_TIM_1,
	0xDEADBEEF,
	0};

reg am335x_emif4d_sdram_tim_1_shdw = {
	"EMIF4D_SDRAM_TIM_1_SHDW",
	AM335X_EMIF4D_SDRAM_TIM_1_SHDW,
	0xDEADBEEF,
	0};

reg am335x_emif4d_sdram_tim_2 = {
	"EMIF4D_SDRAM_TIM_2",
	AM335X_EMIF4D_SDRAM_TIM_2,
	0xDEADBEEF,
	0};

reg am335x_emif4d_sdram_tim_2_shdw = {
	"EMIF4D_SDRAM_TIM_2_SHDW",
	AM335X_EMIF4D_SDRAM_TIM_2_SHDW,
	0xDEADBEEF,
	0};

reg am335x_emif4d_sdram_tim_3 = {
	"EMIF4D_SDRAM_TIM_3",
	AM335X_EMIF4D_SDRAM_TIM_3,
	0xDEADBEEF,
	0};

reg am335x_emif4d_sdram_tim_3_shdw = {
	"EMIF4D_SDRAM_TIM_3_SHDW",
	AM335X_EMIF4D_SDRAM_TIM_3_SHDW,
	0xDEADBEEF,
	0};

reg am335x_emif4d_pwr_mgmt_ctrl = {
	"EMIF4D_PWR_MGMT_CTRL",
	AM335X_EMIF4D_PWR_MGMT_CTRL,
	0xDEADBEEF,
	0};

reg am335x_emif4d_pwr_mgmt_ctrl_shdw = {
	"EMIF4D_PWR_MGMT_CTRL_SHDW",
	AM335X_EMIF4D_PWR_MGMT_CTRL_SHDW,
	0xDEADBEEF,
	0};

reg am335x_emif4d_int_config = {
	"EMIF4D_INT_CONFIG",
	AM335X_EMIF4D_INT_CONFIG,
	0xDEADBEEF,
	0};

reg am335x_emif4d_int_cfg_val_1 = {
	"EMIF4D_INT_CFG_VAL_1",
	AM335X_EMIF4D_INT_CFG_VAL_1,
	0xDEADBEEF,
	0};

reg am335x_emif4d_int_cfg_val_2 = {
	"EMIF4D_INT_CFG_VAL_2",
	AM335X_EMIF4D_INT_CFG_VAL_2,
	0xDEADBEEF,
	0};

reg am335x_emif4d_perf_cnt_1 = {
	"EMIF4D_PERF_CNT_1",
	AM335X_EMIF4D_PERF_CNT_1,
	0xDEADBEEF,
	0};

reg am335x_emif4d_perf_cnt_2 = {
	"EMIF4D_PERF_CNT_2",
	AM335X_EMIF4D_PERF_CNT_2,
	0xDEADBEEF,
	0};

reg am335x_emif4d_perf_cnt_cfg = {
	"EMIF4D_PERF_CNT_CFG",
	AM335X_EMIF4D_PERF_CNT_CFG,
	0xDEADBEEF,
	0};

reg am335x_emif4d_perf_cnt_sel = {
	"EMIF4D_PERF_CNT_SEL",
	AM335X_EMIF4D_PERF_CNT_SEL,
	0xDEADBEEF,
	0};

reg am335x_emif4d_perf_cnt_tim = {
	"EMIF4D_PERF_CNT_TIM",
	AM335X_EMIF4D_PERF_CNT_TIM,
	0xDEADBEEF,
	0};

reg am335x_emif4d_read_idle_ctrl = {
	"EMIF4D_READ_IDLE_CTRL",
	AM335X_EMIF4D_READ_IDLE_CTRL,
	0xDEADBEEF,
	0};

reg am335x_emif4d_read_idle_ctrl_shdw = {
	"EMIF4D_READ_IDLE_CTRL_SHDW",
	AM335X_EMIF4D_READ_IDLE_CTRL_SHDW,
	0xDEADBEEF,
	0};

reg am335x_emif4d_irqstatus_raw_sys = {
	"EMIF4D_IRQSTATUS_RAW_SYS",
	AM335X_EMIF4D_IRQSTATUS_RAW_SYS,
	0xDEADBEEF,
	0};

reg am335x_emif4d_irqstatus_sys = {
	"EMIF4D_IRQSTATUS_SYS",
	AM335X_EMIF4D_IRQSTATUS_SYS,
	0xDEADBEEF,
	0};

reg am335x_emif4d_irqenable_set_sys = {
	"EMIF4D_IRQENABLE_SET_SYS",
	AM335X_EMIF4D_IRQENABLE_SET_SYS,
	0xDEADBEEF,
	0};

reg am335x_emif4d_irqenable_clr_sys = {
	"EMIF4D_IRQENABLE_CLR_SYS",
	AM335X_EMIF4D_IRQENABLE_CLR_SYS,
	0xDEADBEEF,
	0};

reg am335x_emif4d_zq_config = {
	"EMIF4D_ZQ_CONFIG",
	AM335X_EMIF4D_ZQ_CONFIG,
	0xDEADBEEF,
	0};

reg am335x_emif4d_rdwr_lvl_rmp_win = {
	"EMIF4D_RDWR_LVL_RMP_WIN",
	AM335X_EMIF4D_RDWR_LVL_RMP_WIN,
	0xDEADBEEF,
	0};

reg am335x_emif4d_rdwr_lvl_rmp_ctrl = {
	"EMIF4D_RDWR_LVL_RMP_CTRL",
	AM335X_EMIF4D_RDWR_LVL_RMP_CTRL,
	0xDEADBEEF,
	0};

reg am335x_emif4d_rdwr_lvl_ctrl = {
	"EMIF4D_RDWR_LVL_CTRL",
	AM335X_EMIF4D_RDWR_LVL_CTRL,
	0xDEADBEEF,
	0};

reg am335x_emif4d_ddr_phy_ctrl_1 = {
	"EMIF4D_DDR_PHY_CTRL_1",
	AM335X_EMIF4D_DDR_PHY_CTRL_1,
	0xDEADBEEF,
	0};

reg am335x_emif4d_ddr_phy_ctrl_1_shdw = {
	"EMIF4D_DDR_PHY_CTRL_1_SHDW",
	AM335X_EMIF4D_DDR_PHY_CTRL_1_SHDW,
	0xDEADBEEF,
	0};

reg am335x_emif4d_pri_cos_map = {
	"EMIF4D_PRI_COS_MAP",
	AM335X_EMIF4D_PRI_COS_MAP,
	0xDEADBEEF,
	0};

reg am335x_emif4d_connid_cos_1_map = {
	"EMIF4D_CONNID_COS_1_MAP",
	AM335X_EMIF4D_CONNID_COS_1_MAP,
	0xDEADBEEF,
	0};

reg am335x_emif4d_connid_cos_2_map = {
	"EMIF4D_CONNID_COS_2_MAP",
	AM335X_EMIF4D_CONNID_COS_2_MAP,
	0xDEADBEEF,
	0};

reg am335x_emif4d_rd_wr_exec_thrsh = {
	"EMIF4D_RD_WR_EXEC_THRSH",
	AM335X_EMIF4D_RD_WR_EXEC_THRSH,
	0xDEADBEEF,
	0};

reg *am335x_emif4d_mod[AM335X_EMIF4D_MOD_REGCOUNT + 1] = {
	&am335x_emif4d_emif_mod_id_rev,
	&am335x_emif4d_status,
	&am335x_emif4d_sdram_config,
	&am335x_emif4d_sdram_config_2,
	&am335x_emif4d_sdram_ref_ctrl,
	&am335x_emif4d_sdram_ref_ctrl_shdw,
	&am335x_emif4d_sdram_tim_1,
	&am335x_emif4d_sdram_tim_1_shdw,
	&am335x_emif4d_sdram_tim_2,
	&am335x_emif4d_sdram_tim_2_shdw,
	&am335x_emif4d_sdram_tim_3,
	&am335x_emif4d_sdram_tim_3_shdw,
	&am335x_emif4d_pwr_mgmt_ctrl,
	&am335x_emif4d_pwr_mgmt_ctrl_shdw,
	&am335x_emif4d_int_config,
	&am335x_emif4d_int_cfg_val_1,
	&am335x_emif4d_int_cfg_val_2,
	&am335x_emif4d_perf_cnt_1,
	&am335x_emif4d_perf_cnt_2,
	&am335x_emif4d_perf_cnt_cfg,
	&am335x_emif4d_perf_cnt_sel,
	&am335x_emif4d_perf_cnt_tim,
	&am335x_emif4d_read_idle_ctrl,
	&am335x_emif4d_read_idle_ctrl_shdw,
	&am335x_emif4d_irqstatus_raw_sys,
	&am335x_emif4d_irqstatus_sys,
	&am335x_emif4d_irqenable_set_sys,
	&am335x_emif4d_irqenable_clr_sys,
	&am335x_emif4d_zq_config,
	&am335x_emif4d_rdwr_lvl_rmp_win,
	&am335x_emif4d_rdwr_lvl_rmp_ctrl,
	&am335x_emif4d_rdwr_lvl_ctrl,
	&am335x_emif4d_ddr_phy_ctrl_1,
	&am335x_emif4d_ddr_phy_ctrl_1_shdw,
	&am335x_emif4d_pri_cos_map,
	&am335x_emif4d_connid_cos_1_map,
	&am335x_emif4d_connid_cos_2_map,
	&am335x_emif4d_rd_wr_exec_thrsh,
	NULL};

reg **emif_am335x_mods[EMIF_AM335X_MODS_COUNT] = {
	(reg **) &am335x_emif4d_mod};

const char *emif_am335x_mods_name[EMIF_AM335X_MODS_COUNT] = {
	"EMIF4D"};
