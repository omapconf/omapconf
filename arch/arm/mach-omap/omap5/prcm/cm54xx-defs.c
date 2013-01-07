/*
 *
 * @Component			OMAPCONF
 * @Filename			cm54xx-defs.h
 * @Description			OMAP5 ES2 CM Registers Definitions & Functions
 * @Author			Patrick Titiano (p-titiano@ti.com)
 * @Date			2012
 * @Copyright			Texas Instruments Incorporated
 *
 *
 * Copyright (C) 2012 Texas Instruments Incorporated - http://www.ti.com/
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


#include <cm54xx-defs.h>


reg omap5430_cm_dss_clkstctrl = {
	"CM_DSS_CLKSTCTRL",
	OMAP5430_CM_DSS_CLKSTCTRL,
	0xDEADBEEF,
	0};

reg omap5430_cm_dss_staticdep = {
	"CM_DSS_STATICDEP",
	OMAP5430_CM_DSS_STATICDEP,
	0xDEADBEEF,
	0};

reg omap5430_cm_dss_dynamicdep = {
	"CM_DSS_DYNAMICDEP",
	OMAP5430_CM_DSS_DYNAMICDEP,
	0xDEADBEEF,
	0};

reg omap5430_cm_dss_dss_clkctrl = {
	"CM_DSS_DSS_CLKCTRL",
	OMAP5430_CM_DSS_DSS_CLKCTRL,
	0xDEADBEEF,
	0};

reg omap5430_cm_dss_bb2d_clkctrl = {
	"CM_DSS_BB2D_CLKCTRL",
	OMAP5430_CM_DSS_BB2D_CLKCTRL,
	0xDEADBEEF,
	0};

reg *omap5430_dss_cm_core_mod[OMAP5430_DSS_CM_CORE_MOD_REGCOUNT + 1] = {
	&omap5430_cm_dss_clkstctrl,
	&omap5430_cm_dss_staticdep,
	&omap5430_cm_dss_dynamicdep,
	&omap5430_cm_dss_dss_clkctrl,
	&omap5430_cm_dss_bb2d_clkctrl,
	NULL};

reg omap5430_cmi_identication = {
	"CMI_IDENTICATION",
	OMAP5430_CMI_IDENTICATION,
	0xDEADBEEF,
	0};

reg omap5430_cmi_sys_config = {
	"CMI_SYS_CONFIG",
	OMAP5430_CMI_SYS_CONFIG,
	0xDEADBEEF,
	0};

reg omap5430_cmi_status = {
	"CMI_STATUS",
	OMAP5430_CMI_STATUS,
	0xDEADBEEF,
	0};

reg omap5430_cmi_configuration = {
	"CMI_CONFIGURATION",
	OMAP5430_CMI_CONFIGURATION,
	0xDEADBEEF,
	0};

reg omap5430_cmi_class_filtering = {
	"CMI_CLASS_FILTERING",
	OMAP5430_CMI_CLASS_FILTERING,
	0xDEADBEEF,
	0};

reg omap5430_cmi_triggering = {
	"CMI_TRIGGERING",
	OMAP5430_CMI_TRIGGERING,
	0xDEADBEEF,
	0};

reg omap5430_cmi_sampling = {
	"CMI_SAMPLING",
	OMAP5430_CMI_SAMPLING,
	0xDEADBEEF,
	0};

reg *omap5430_instr_cm_core_mod[OMAP5430_INSTR_CM_CORE_MOD_REGCOUNT + 1] = {
	&omap5430_cmi_identication,
	&omap5430_cmi_sys_config,
	&omap5430_cmi_status,
	&omap5430_cmi_configuration,
	&omap5430_cmi_class_filtering,
	&omap5430_cmi_triggering,
	&omap5430_cmi_sampling,
	NULL};

reg omap5430_cm_l3main1_clkstctrl = {
	"CM_L3MAIN1_CLKSTCTRL",
	OMAP5430_CM_L3MAIN1_CLKSTCTRL,
	0xDEADBEEF,
	0};

reg omap5430_cm_l3main1_dynamicdep = {
	"CM_L3MAIN1_DYNAMICDEP",
	OMAP5430_CM_L3MAIN1_DYNAMICDEP,
	0xDEADBEEF,
	0};

reg omap5430_cm_l3main1_l3_main_1_clkctrl = {
	"CM_L3MAIN1_L3_MAIN_1_CLKCTRL",
	OMAP5430_CM_L3MAIN1_L3_MAIN_1_CLKCTRL,
	0xDEADBEEF,
	0};

reg omap5430_cm_l3main2_clkstctrl = {
	"CM_L3MAIN2_CLKSTCTRL",
	OMAP5430_CM_L3MAIN2_CLKSTCTRL,
	0xDEADBEEF,
	0};

reg omap5430_cm_l3main2_dynamicdep = {
	"CM_L3MAIN2_DYNAMICDEP",
	OMAP5430_CM_L3MAIN2_DYNAMICDEP,
	0xDEADBEEF,
	0};

reg omap5430_cm_l3main2_l3_main_2_clkctrl = {
	"CM_L3MAIN2_L3_MAIN_2_CLKCTRL",
	OMAP5430_CM_L3MAIN2_L3_MAIN_2_CLKCTRL,
	0xDEADBEEF,
	0};

reg omap5430_cm_l3main2_gpmc_clkctrl = {
	"CM_L3MAIN2_GPMC_CLKCTRL",
	OMAP5430_CM_L3MAIN2_GPMC_CLKCTRL,
	0xDEADBEEF,
	0};

reg omap5430_cm_l3main2_ocmc_ram_clkctrl = {
	"CM_L3MAIN2_OCMC_RAM_CLKCTRL",
	OMAP5430_CM_L3MAIN2_OCMC_RAM_CLKCTRL,
	0xDEADBEEF,
	0};

reg omap5430_cm_ipu_clkstctrl = {
	"CM_IPU_CLKSTCTRL",
	OMAP5430_CM_IPU_CLKSTCTRL,
	0xDEADBEEF,
	0};

reg omap5430_cm_ipu_staticdep = {
	"CM_IPU_STATICDEP",
	OMAP5430_CM_IPU_STATICDEP,
	0xDEADBEEF,
	0};

reg omap5430_cm_ipu_dynamicdep = {
	"CM_IPU_DYNAMICDEP",
	OMAP5430_CM_IPU_DYNAMICDEP,
	0xDEADBEEF,
	0};

reg omap5430_cm_ipu_ipu_clkctrl = {
	"CM_IPU_IPU_CLKCTRL",
	OMAP5430_CM_IPU_IPU_CLKCTRL,
	0xDEADBEEF,
	0};

reg omap5430_cm_dma_clkstctrl = {
	"CM_DMA_CLKSTCTRL",
	OMAP5430_CM_DMA_CLKSTCTRL,
	0xDEADBEEF,
	0};

reg omap5430_cm_dma_staticdep = {
	"CM_DMA_STATICDEP",
	OMAP5430_CM_DMA_STATICDEP,
	0xDEADBEEF,
	0};

reg omap5430_cm_dma_dynamicdep = {
	"CM_DMA_DYNAMICDEP",
	OMAP5430_CM_DMA_DYNAMICDEP,
	0xDEADBEEF,
	0};

reg omap5430_cm_dma_dma_system_clkctrl = {
	"CM_DMA_DMA_SYSTEM_CLKCTRL",
	OMAP5430_CM_DMA_DMA_SYSTEM_CLKCTRL,
	0xDEADBEEF,
	0};

reg omap5430_cm_emif_clkstctrl = {
	"CM_EMIF_CLKSTCTRL",
	OMAP5430_CM_EMIF_CLKSTCTRL,
	0xDEADBEEF,
	0};

reg omap5430_cm_emif_dmm_clkctrl = {
	"CM_EMIF_DMM_CLKCTRL",
	OMAP5430_CM_EMIF_DMM_CLKCTRL,
	0xDEADBEEF,
	0};

reg omap5430_cm_emif_emif_ocp_fw_clkctrl = {
	"CM_EMIF_EMIF_OCP_FW_CLKCTRL",
	OMAP5430_CM_EMIF_EMIF_OCP_FW_CLKCTRL,
	0xDEADBEEF,
	0};

reg omap5430_cm_emif_emif1_clkctrl = {
	"CM_EMIF_EMIF1_CLKCTRL",
	OMAP5430_CM_EMIF_EMIF1_CLKCTRL,
	0xDEADBEEF,
	0};

reg omap5430_cm_emif_emif2_clkctrl = {
	"CM_EMIF_EMIF2_CLKCTRL",
	OMAP5430_CM_EMIF_EMIF2_CLKCTRL,
	0xDEADBEEF,
	0};

reg omap5430_cm_emif_emif_dll_clkctrl = {
	"CM_EMIF_EMIF_DLL_CLKCTRL",
	OMAP5430_CM_EMIF_EMIF_DLL_CLKCTRL,
	0xDEADBEEF,
	0};

reg omap5430_cm_c2c_clkstctrl = {
	"CM_C2C_CLKSTCTRL",
	OMAP5430_CM_C2C_CLKSTCTRL,
	0xDEADBEEF,
	0};

reg omap5430_cm_c2c_staticdep = {
	"CM_C2C_STATICDEP",
	OMAP5430_CM_C2C_STATICDEP,
	0xDEADBEEF,
	0};

reg omap5430_cm_c2c_dynamicdep = {
	"CM_C2C_DYNAMICDEP",
	OMAP5430_CM_C2C_DYNAMICDEP,
	0xDEADBEEF,
	0};

reg omap5430_cm_c2c_c2c_clkctrl = {
	"CM_C2C_C2C_CLKCTRL",
	OMAP5430_CM_C2C_C2C_CLKCTRL,
	0xDEADBEEF,
	0};

reg omap5430_cm_c2c_modem_icr_clkctrl = {
	"CM_C2C_MODEM_ICR_CLKCTRL",
	OMAP5430_CM_C2C_MODEM_ICR_CLKCTRL,
	0xDEADBEEF,
	0};

reg omap5430_cm_c2c_c2c_ocp_fw_clkctrl = {
	"CM_C2C_C2C_OCP_FW_CLKCTRL",
	OMAP5430_CM_C2C_C2C_OCP_FW_CLKCTRL,
	0xDEADBEEF,
	0};

reg omap5430_cm_l4cfg_clkstctrl = {
	"CM_L4CFG_CLKSTCTRL",
	OMAP5430_CM_L4CFG_CLKSTCTRL,
	0xDEADBEEF,
	0};

reg omap5430_cm_l4cfg_dynamicdep = {
	"CM_L4CFG_DYNAMICDEP",
	OMAP5430_CM_L4CFG_DYNAMICDEP,
	0xDEADBEEF,
	0};

reg omap5430_cm_l4cfg_l4_cfg_clkctrl = {
	"CM_L4CFG_L4_CFG_CLKCTRL",
	OMAP5430_CM_L4CFG_L4_CFG_CLKCTRL,
	0xDEADBEEF,
	0};

reg omap5430_cm_l4cfg_spinlock_clkctrl = {
	"CM_L4CFG_SPINLOCK_CLKCTRL",
	OMAP5430_CM_L4CFG_SPINLOCK_CLKCTRL,
	0xDEADBEEF,
	0};

reg omap5430_cm_l4cfg_mailbox_clkctrl = {
	"CM_L4CFG_MAILBOX_CLKCTRL",
	OMAP5430_CM_L4CFG_MAILBOX_CLKCTRL,
	0xDEADBEEF,
	0};

reg omap5430_cm_l4cfg_sar_rom_clkctrl = {
	"CM_L4CFG_SAR_ROM_CLKCTRL",
	OMAP5430_CM_L4CFG_SAR_ROM_CLKCTRL,
	0xDEADBEEF,
	0};

reg omap5430_cm_l4cfg_ocp2scp2_clkctrl = {
	"CM_L4CFG_OCP2SCP2_CLKCTRL",
	OMAP5430_CM_L4CFG_OCP2SCP2_CLKCTRL,
	0xDEADBEEF,
	0};

reg omap5430_cm_l3instr_clkstctrl = {
	"CM_L3INSTR_CLKSTCTRL",
	OMAP5430_CM_L3INSTR_CLKSTCTRL,
	0xDEADBEEF,
	0};

reg omap5430_cm_l3instr_l3_main_3_clkctrl = {
	"CM_L3INSTR_L3_MAIN_3_CLKCTRL",
	OMAP5430_CM_L3INSTR_L3_MAIN_3_CLKCTRL,
	0xDEADBEEF,
	0};

reg omap5430_cm_l3instr_l3_instr_clkctrl = {
	"CM_L3INSTR_L3_INSTR_CLKCTRL",
	OMAP5430_CM_L3INSTR_L3_INSTR_CLKCTRL,
	0xDEADBEEF,
	0};

reg omap5430_cm_l3instr_ocp_wp_noc_clkctrl = {
	"CM_L3INSTR_OCP_WP_NOC_CLKCTRL",
	OMAP5430_CM_L3INSTR_OCP_WP_NOC_CLKCTRL,
	0xDEADBEEF,
	0};

reg omap5430_cm_l3instr_dll_aging_clkctrl = {
	"CM_L3INSTR_DLL_AGING_CLKCTRL",
	OMAP5430_CM_L3INSTR_DLL_AGING_CLKCTRL,
	0xDEADBEEF,
	0};

reg omap5430_cm_l3instr_ctrl_module_bandgap_clkctrl = {
	"CM_L3INSTR_CTRL_MODULE_BANDGAP_CLKCTRL",
	OMAP5430_CM_L3INSTR_CTRL_MODULE_BANDGAP_CLKCTRL,
	0xDEADBEEF,
	0};

reg omap5430_cm_mipiext_clkstctrl = {
	"CM_MIPIEXT_CLKSTCTRL",
	OMAP5430_CM_MIPIEXT_CLKSTCTRL,
	0xDEADBEEF,
	0};

reg omap5430_cm_mipiext_staticdep = {
	"CM_MIPIEXT_STATICDEP",
	OMAP5430_CM_MIPIEXT_STATICDEP,
	0xDEADBEEF,
	0};

reg omap5430_cm_mipiext_dynamicdep = {
	"CM_MIPIEXT_DYNAMICDEP",
	OMAP5430_CM_MIPIEXT_DYNAMICDEP,
	0xDEADBEEF,
	0};

reg omap5430_cm_mipiext_lli_clkctrl = {
	"CM_MIPIEXT_LLI_CLKCTRL",
	OMAP5430_CM_MIPIEXT_LLI_CLKCTRL,
	0xDEADBEEF,
	0};

reg omap5430_cm_mipiext_lli_ocp_fw_clkctrl = {
	"CM_MIPIEXT_LLI_OCP_FW_CLKCTRL",
	OMAP5430_CM_MIPIEXT_LLI_OCP_FW_CLKCTRL,
	0xDEADBEEF,
	0};

reg omap5430_cm_mipiext_mphy_clkctrl = {
	"CM_MIPIEXT_MPHY_CLKCTRL",
	OMAP5430_CM_MIPIEXT_MPHY_CLKCTRL,
	0xDEADBEEF,
	0};

reg omap5430_cm_l4per_clkstctrl = {
	"CM_L4PER_CLKSTCTRL",
	OMAP5430_CM_L4PER_CLKSTCTRL,
	0xDEADBEEF,
	0};

reg omap5430_cm_l4per_dynamicdep = {
	"CM_L4PER_DYNAMICDEP",
	OMAP5430_CM_L4PER_DYNAMICDEP,
	0xDEADBEEF,
	0};

reg omap5430_cm_l4per_timer10_clkctrl = {
	"CM_L4PER_TIMER10_CLKCTRL",
	OMAP5430_CM_L4PER_TIMER10_CLKCTRL,
	0xDEADBEEF,
	0};

reg omap5430_cm_l4per_timer11_clkctrl = {
	"CM_L4PER_TIMER11_CLKCTRL",
	OMAP5430_CM_L4PER_TIMER11_CLKCTRL,
	0xDEADBEEF,
	0};

reg omap5430_cm_l4per_timer2_clkctrl = {
	"CM_L4PER_TIMER2_CLKCTRL",
	OMAP5430_CM_L4PER_TIMER2_CLKCTRL,
	0xDEADBEEF,
	0};

reg omap5430_cm_l4per_timer3_clkctrl = {
	"CM_L4PER_TIMER3_CLKCTRL",
	OMAP5430_CM_L4PER_TIMER3_CLKCTRL,
	0xDEADBEEF,
	0};

reg omap5430_cm_l4per_timer4_clkctrl = {
	"CM_L4PER_TIMER4_CLKCTRL",
	OMAP5430_CM_L4PER_TIMER4_CLKCTRL,
	0xDEADBEEF,
	0};

reg omap5430_cm_l4per_timer9_clkctrl = {
	"CM_L4PER_TIMER9_CLKCTRL",
	OMAP5430_CM_L4PER_TIMER9_CLKCTRL,
	0xDEADBEEF,
	0};

reg omap5430_cm_l4per_elm_clkctrl = {
	"CM_L4PER_ELM_CLKCTRL",
	OMAP5430_CM_L4PER_ELM_CLKCTRL,
	0xDEADBEEF,
	0};

reg omap5430_cm_l4per_gpio2_clkctrl = {
	"CM_L4PER_GPIO2_CLKCTRL",
	OMAP5430_CM_L4PER_GPIO2_CLKCTRL,
	0xDEADBEEF,
	0};

reg omap5430_cm_l4per_gpio3_clkctrl = {
	"CM_L4PER_GPIO3_CLKCTRL",
	OMAP5430_CM_L4PER_GPIO3_CLKCTRL,
	0xDEADBEEF,
	0};

reg omap5430_cm_l4per_gpio4_clkctrl = {
	"CM_L4PER_GPIO4_CLKCTRL",
	OMAP5430_CM_L4PER_GPIO4_CLKCTRL,
	0xDEADBEEF,
	0};

reg omap5430_cm_l4per_gpio5_clkctrl = {
	"CM_L4PER_GPIO5_CLKCTRL",
	OMAP5430_CM_L4PER_GPIO5_CLKCTRL,
	0xDEADBEEF,
	0};

reg omap5430_cm_l4per_gpio6_clkctrl = {
	"CM_L4PER_GPIO6_CLKCTRL",
	OMAP5430_CM_L4PER_GPIO6_CLKCTRL,
	0xDEADBEEF,
	0};

reg omap5430_cm_l4per_hdq1w_clkctrl = {
	"CM_L4PER_HDQ1W_CLKCTRL",
	OMAP5430_CM_L4PER_HDQ1W_CLKCTRL,
	0xDEADBEEF,
	0};

reg omap5430_cm_l4per_i2c1_clkctrl = {
	"CM_L4PER_I2C1_CLKCTRL",
	OMAP5430_CM_L4PER_I2C1_CLKCTRL,
	0xDEADBEEF,
	0};

reg omap5430_cm_l4per_i2c2_clkctrl = {
	"CM_L4PER_I2C2_CLKCTRL",
	OMAP5430_CM_L4PER_I2C2_CLKCTRL,
	0xDEADBEEF,
	0};

reg omap5430_cm_l4per_i2c3_clkctrl = {
	"CM_L4PER_I2C3_CLKCTRL",
	OMAP5430_CM_L4PER_I2C3_CLKCTRL,
	0xDEADBEEF,
	0};

reg omap5430_cm_l4per_i2c4_clkctrl = {
	"CM_L4PER_I2C4_CLKCTRL",
	OMAP5430_CM_L4PER_I2C4_CLKCTRL,
	0xDEADBEEF,
	0};

reg omap5430_cm_l4per_l4_per_clkctrl = {
	"CM_L4PER_L4_PER_CLKCTRL",
	OMAP5430_CM_L4PER_L4_PER_CLKCTRL,
	0xDEADBEEF,
	0};

reg omap5430_cm_l4per_mcspi1_clkctrl = {
	"CM_L4PER_MCSPI1_CLKCTRL",
	OMAP5430_CM_L4PER_MCSPI1_CLKCTRL,
	0xDEADBEEF,
	0};

reg omap5430_cm_l4per_mcspi2_clkctrl = {
	"CM_L4PER_MCSPI2_CLKCTRL",
	OMAP5430_CM_L4PER_MCSPI2_CLKCTRL,
	0xDEADBEEF,
	0};

reg omap5430_cm_l4per_mcspi3_clkctrl = {
	"CM_L4PER_MCSPI3_CLKCTRL",
	OMAP5430_CM_L4PER_MCSPI3_CLKCTRL,
	0xDEADBEEF,
	0};

reg omap5430_cm_l4per_mcspi4_clkctrl = {
	"CM_L4PER_MCSPI4_CLKCTRL",
	OMAP5430_CM_L4PER_MCSPI4_CLKCTRL,
	0xDEADBEEF,
	0};

reg omap5430_cm_l4per_gpio7_clkctrl = {
	"CM_L4PER_GPIO7_CLKCTRL",
	OMAP5430_CM_L4PER_GPIO7_CLKCTRL,
	0xDEADBEEF,
	0};

reg omap5430_cm_l4per_gpio8_clkctrl = {
	"CM_L4PER_GPIO8_CLKCTRL",
	OMAP5430_CM_L4PER_GPIO8_CLKCTRL,
	0xDEADBEEF,
	0};

reg omap5430_cm_l4per_mmc3_clkctrl = {
	"CM_L4PER_MMC3_CLKCTRL",
	OMAP5430_CM_L4PER_MMC3_CLKCTRL,
	0xDEADBEEF,
	0};

reg omap5430_cm_l4per_mmc4_clkctrl = {
	"CM_L4PER_MMC4_CLKCTRL",
	OMAP5430_CM_L4PER_MMC4_CLKCTRL,
	0xDEADBEEF,
	0};

reg omap5430_cm_l4per_uart1_clkctrl = {
	"CM_L4PER_UART1_CLKCTRL",
	OMAP5430_CM_L4PER_UART1_CLKCTRL,
	0xDEADBEEF,
	0};

reg omap5430_cm_l4per_uart2_clkctrl = {
	"CM_L4PER_UART2_CLKCTRL",
	OMAP5430_CM_L4PER_UART2_CLKCTRL,
	0xDEADBEEF,
	0};

reg omap5430_cm_l4per_uart3_clkctrl = {
	"CM_L4PER_UART3_CLKCTRL",
	OMAP5430_CM_L4PER_UART3_CLKCTRL,
	0xDEADBEEF,
	0};

reg omap5430_cm_l4per_uart4_clkctrl = {
	"CM_L4PER_UART4_CLKCTRL",
	OMAP5430_CM_L4PER_UART4_CLKCTRL,
	0xDEADBEEF,
	0};

reg omap5430_cm_l4per_mmc5_clkctrl = {
	"CM_L4PER_MMC5_CLKCTRL",
	OMAP5430_CM_L4PER_MMC5_CLKCTRL,
	0xDEADBEEF,
	0};

reg omap5430_cm_l4per_i2c5_clkctrl = {
	"CM_L4PER_I2C5_CLKCTRL",
	OMAP5430_CM_L4PER_I2C5_CLKCTRL,
	0xDEADBEEF,
	0};

reg omap5430_cm_l4per_uart5_clkctrl = {
	"CM_L4PER_UART5_CLKCTRL",
	OMAP5430_CM_L4PER_UART5_CLKCTRL,
	0xDEADBEEF,
	0};

reg omap5430_cm_l4per_uart6_clkctrl = {
	"CM_L4PER_UART6_CLKCTRL",
	OMAP5430_CM_L4PER_UART6_CLKCTRL,
	0xDEADBEEF,
	0};

reg omap5430_cm_l4sec_clkstctrl = {
	"CM_L4SEC_CLKSTCTRL",
	OMAP5430_CM_L4SEC_CLKSTCTRL,
	0xDEADBEEF,
	0};

reg omap5430_cm_l4sec_staticdep = {
	"CM_L4SEC_STATICDEP",
	OMAP5430_CM_L4SEC_STATICDEP,
	0xDEADBEEF,
	0};

reg omap5430_cm_l4sec_dynamicdep = {
	"CM_L4SEC_DYNAMICDEP",
	OMAP5430_CM_L4SEC_DYNAMICDEP,
	0xDEADBEEF,
	0};

reg omap5430_cm_l4sec_aes1_clkctrl = {
	"CM_L4SEC_AES1_CLKCTRL",
	OMAP5430_CM_L4SEC_AES1_CLKCTRL,
	0xDEADBEEF,
	0};

reg omap5430_cm_l4sec_aes2_clkctrl = {
	"CM_L4SEC_AES2_CLKCTRL",
	OMAP5430_CM_L4SEC_AES2_CLKCTRL,
	0xDEADBEEF,
	0};

reg omap5430_cm_l4sec_des3des_clkctrl = {
	"CM_L4SEC_DES3DES_CLKCTRL",
	OMAP5430_CM_L4SEC_DES3DES_CLKCTRL,
	0xDEADBEEF,
	0};

reg omap5430_cm_l4sec_fpka_clkctrl = {
	"CM_L4SEC_FPKA_CLKCTRL",
	OMAP5430_CM_L4SEC_FPKA_CLKCTRL,
	0xDEADBEEF,
	0};

reg omap5430_cm_l4sec_rng_clkctrl = {
	"CM_L4SEC_RNG_CLKCTRL",
	OMAP5430_CM_L4SEC_RNG_CLKCTRL,
	0xDEADBEEF,
	0};

reg omap5430_cm_l4sec_sha2md5_clkctrl = {
	"CM_L4SEC_SHA2MD5_CLKCTRL",
	OMAP5430_CM_L4SEC_SHA2MD5_CLKCTRL,
	0xDEADBEEF,
	0};

reg omap5430_cm_l4sec_dma_crypto_clkctrl = {
	"CM_L4SEC_DMA_CRYPTO_CLKCTRL",
	OMAP5430_CM_L4SEC_DMA_CRYPTO_CLKCTRL,
	0xDEADBEEF,
	0};

reg *omap5430_core_cm_core_mod[OMAP5430_CORE_CM_CORE_MOD_REGCOUNT + 1] = {
	&omap5430_cm_l3main1_clkstctrl,
	&omap5430_cm_l3main1_dynamicdep,
	&omap5430_cm_l3main1_l3_main_1_clkctrl,
	&omap5430_cm_l3main2_clkstctrl,
	&omap5430_cm_l3main2_dynamicdep,
	&omap5430_cm_l3main2_l3_main_2_clkctrl,
	&omap5430_cm_l3main2_gpmc_clkctrl,
	&omap5430_cm_l3main2_ocmc_ram_clkctrl,
	&omap5430_cm_ipu_clkstctrl,
	&omap5430_cm_ipu_staticdep,
	&omap5430_cm_ipu_dynamicdep,
	&omap5430_cm_ipu_ipu_clkctrl,
	&omap5430_cm_dma_clkstctrl,
	&omap5430_cm_dma_staticdep,
	&omap5430_cm_dma_dynamicdep,
	&omap5430_cm_dma_dma_system_clkctrl,
	&omap5430_cm_emif_clkstctrl,
	&omap5430_cm_emif_dmm_clkctrl,
	&omap5430_cm_emif_emif_ocp_fw_clkctrl,
	&omap5430_cm_emif_emif1_clkctrl,
	&omap5430_cm_emif_emif2_clkctrl,
	&omap5430_cm_emif_emif_dll_clkctrl,
	&omap5430_cm_c2c_clkstctrl,
	&omap5430_cm_c2c_staticdep,
	&omap5430_cm_c2c_dynamicdep,
	&omap5430_cm_c2c_c2c_clkctrl,
	&omap5430_cm_c2c_modem_icr_clkctrl,
	&omap5430_cm_c2c_c2c_ocp_fw_clkctrl,
	&omap5430_cm_l4cfg_clkstctrl,
	&omap5430_cm_l4cfg_dynamicdep,
	&omap5430_cm_l4cfg_l4_cfg_clkctrl,
	&omap5430_cm_l4cfg_spinlock_clkctrl,
	&omap5430_cm_l4cfg_mailbox_clkctrl,
	&omap5430_cm_l4cfg_sar_rom_clkctrl,
	&omap5430_cm_l4cfg_ocp2scp2_clkctrl,
	&omap5430_cm_l3instr_clkstctrl,
	&omap5430_cm_l3instr_l3_main_3_clkctrl,
	&omap5430_cm_l3instr_l3_instr_clkctrl,
	&omap5430_cm_l3instr_ocp_wp_noc_clkctrl,
	&omap5430_cm_l3instr_dll_aging_clkctrl,
	&omap5430_cm_l3instr_ctrl_module_bandgap_clkctrl,
	&omap5430_cm_mipiext_clkstctrl,
	&omap5430_cm_mipiext_staticdep,
	&omap5430_cm_mipiext_dynamicdep,
	&omap5430_cm_mipiext_lli_clkctrl,
	&omap5430_cm_mipiext_lli_ocp_fw_clkctrl,
	&omap5430_cm_mipiext_mphy_clkctrl,
	&omap5430_cm_l4per_clkstctrl,
	&omap5430_cm_l4per_dynamicdep,
	&omap5430_cm_l4per_timer10_clkctrl,
	&omap5430_cm_l4per_timer11_clkctrl,
	&omap5430_cm_l4per_timer2_clkctrl,
	&omap5430_cm_l4per_timer3_clkctrl,
	&omap5430_cm_l4per_timer4_clkctrl,
	&omap5430_cm_l4per_timer9_clkctrl,
	&omap5430_cm_l4per_elm_clkctrl,
	&omap5430_cm_l4per_gpio2_clkctrl,
	&omap5430_cm_l4per_gpio3_clkctrl,
	&omap5430_cm_l4per_gpio4_clkctrl,
	&omap5430_cm_l4per_gpio5_clkctrl,
	&omap5430_cm_l4per_gpio6_clkctrl,
	&omap5430_cm_l4per_hdq1w_clkctrl,
	&omap5430_cm_l4per_i2c1_clkctrl,
	&omap5430_cm_l4per_i2c2_clkctrl,
	&omap5430_cm_l4per_i2c3_clkctrl,
	&omap5430_cm_l4per_i2c4_clkctrl,
	&omap5430_cm_l4per_l4_per_clkctrl,
	&omap5430_cm_l4per_mcspi1_clkctrl,
	&omap5430_cm_l4per_mcspi2_clkctrl,
	&omap5430_cm_l4per_mcspi3_clkctrl,
	&omap5430_cm_l4per_mcspi4_clkctrl,
	&omap5430_cm_l4per_gpio7_clkctrl,
	&omap5430_cm_l4per_gpio8_clkctrl,
	&omap5430_cm_l4per_mmc3_clkctrl,
	&omap5430_cm_l4per_mmc4_clkctrl,
	&omap5430_cm_l4per_uart1_clkctrl,
	&omap5430_cm_l4per_uart2_clkctrl,
	&omap5430_cm_l4per_uart3_clkctrl,
	&omap5430_cm_l4per_uart4_clkctrl,
	&omap5430_cm_l4per_mmc5_clkctrl,
	&omap5430_cm_l4per_i2c5_clkctrl,
	&omap5430_cm_l4per_uart5_clkctrl,
	&omap5430_cm_l4per_uart6_clkctrl,
	&omap5430_cm_l4sec_clkstctrl,
	&omap5430_cm_l4sec_staticdep,
	&omap5430_cm_l4sec_dynamicdep,
	&omap5430_cm_l4sec_aes1_clkctrl,
	&omap5430_cm_l4sec_aes2_clkctrl,
	&omap5430_cm_l4sec_des3des_clkctrl,
	&omap5430_cm_l4sec_fpka_clkctrl,
	&omap5430_cm_l4sec_rng_clkctrl,
	&omap5430_cm_l4sec_sha2md5_clkctrl,
	&omap5430_cm_l4sec_dma_crypto_clkctrl,
	NULL};

reg omap5430_cm_custefuse_clkstctrl = {
	"CM_CUSTEFUSE_CLKSTCTRL",
	OMAP5430_CM_CUSTEFUSE_CLKSTCTRL,
	0xDEADBEEF,
	0};

reg omap5430_cm_custefuse_efuse_ctrl_cust_clkctrl = {
	"CM_CUSTEFUSE_EFUSE_CTRL_CUST_CLKCTRL",
	OMAP5430_CM_CUSTEFUSE_EFUSE_CTRL_CUST_CLKCTRL,
	0xDEADBEEF,
	0};

reg *omap5430_custefuse_cm_core_mod[OMAP5430_CUSTEFUSE_CM_CORE_MOD_REGCOUNT + 1] = {
	&omap5430_cm_custefuse_clkstctrl,
	&omap5430_cm_custefuse_efuse_ctrl_cust_clkctrl,
	NULL};

reg omap5430_cm_abe_clkstctrl = {
	"CM_ABE_CLKSTCTRL",
	OMAP5430_CM_ABE_CLKSTCTRL,
	0xDEADBEEF,
	0};

reg omap5430_cm_abe_l4_abe_clkctrl = {
	"CM_ABE_L4_ABE_CLKCTRL",
	OMAP5430_CM_ABE_L4_ABE_CLKCTRL,
	0xDEADBEEF,
	0};

reg omap5430_cm_abe_aess_clkctrl = {
	"CM_ABE_AESS_CLKCTRL",
	OMAP5430_CM_ABE_AESS_CLKCTRL,
	0xDEADBEEF,
	0};

reg omap5430_cm_abe_mcpdm_clkctrl = {
	"CM_ABE_MCPDM_CLKCTRL",
	OMAP5430_CM_ABE_MCPDM_CLKCTRL,
	0xDEADBEEF,
	0};

reg omap5430_cm_abe_dmic_clkctrl = {
	"CM_ABE_DMIC_CLKCTRL",
	OMAP5430_CM_ABE_DMIC_CLKCTRL,
	0xDEADBEEF,
	0};

reg omap5430_cm_abe_mcasp_clkctrl = {
	"CM_ABE_MCASP_CLKCTRL",
	OMAP5430_CM_ABE_MCASP_CLKCTRL,
	0xDEADBEEF,
	0};

reg omap5430_cm_abe_mcbsp1_clkctrl = {
	"CM_ABE_MCBSP1_CLKCTRL",
	OMAP5430_CM_ABE_MCBSP1_CLKCTRL,
	0xDEADBEEF,
	0};

reg omap5430_cm_abe_mcbsp2_clkctrl = {
	"CM_ABE_MCBSP2_CLKCTRL",
	OMAP5430_CM_ABE_MCBSP2_CLKCTRL,
	0xDEADBEEF,
	0};

reg omap5430_cm_abe_mcbsp3_clkctrl = {
	"CM_ABE_MCBSP3_CLKCTRL",
	OMAP5430_CM_ABE_MCBSP3_CLKCTRL,
	0xDEADBEEF,
	0};

reg omap5430_cm_abe_slimbus1_clkctrl = {
	"CM_ABE_SLIMBUS1_CLKCTRL",
	OMAP5430_CM_ABE_SLIMBUS1_CLKCTRL,
	0xDEADBEEF,
	0};

reg omap5430_cm_abe_timer5_clkctrl = {
	"CM_ABE_TIMER5_CLKCTRL",
	OMAP5430_CM_ABE_TIMER5_CLKCTRL,
	0xDEADBEEF,
	0};

reg omap5430_cm_abe_timer6_clkctrl = {
	"CM_ABE_TIMER6_CLKCTRL",
	OMAP5430_CM_ABE_TIMER6_CLKCTRL,
	0xDEADBEEF,
	0};

reg omap5430_cm_abe_timer7_clkctrl = {
	"CM_ABE_TIMER7_CLKCTRL",
	OMAP5430_CM_ABE_TIMER7_CLKCTRL,
	0xDEADBEEF,
	0};

reg omap5430_cm_abe_timer8_clkctrl = {
	"CM_ABE_TIMER8_CLKCTRL",
	OMAP5430_CM_ABE_TIMER8_CLKCTRL,
	0xDEADBEEF,
	0};

reg omap5430_cm_abe_wd_timer3_clkctrl = {
	"CM_ABE_WD_TIMER3_CLKCTRL",
	OMAP5430_CM_ABE_WD_TIMER3_CLKCTRL,
	0xDEADBEEF,
	0};

reg *omap5430_abe_cm_core_aon_mod[OMAP5430_ABE_CM_CORE_AON_MOD_REGCOUNT + 1] = {
	&omap5430_cm_abe_clkstctrl,
	&omap5430_cm_abe_l4_abe_clkctrl,
	&omap5430_cm_abe_aess_clkctrl,
	&omap5430_cm_abe_mcpdm_clkctrl,
	&omap5430_cm_abe_dmic_clkctrl,
	&omap5430_cm_abe_mcasp_clkctrl,
	&omap5430_cm_abe_mcbsp1_clkctrl,
	&omap5430_cm_abe_mcbsp2_clkctrl,
	&omap5430_cm_abe_mcbsp3_clkctrl,
	&omap5430_cm_abe_slimbus1_clkctrl,
	&omap5430_cm_abe_timer5_clkctrl,
	&omap5430_cm_abe_timer6_clkctrl,
	&omap5430_cm_abe_timer7_clkctrl,
	&omap5430_cm_abe_timer8_clkctrl,
	&omap5430_cm_abe_wd_timer3_clkctrl,
	NULL};

reg omap5430_cm_gpu_clkstctrl = {
	"CM_GPU_CLKSTCTRL",
	OMAP5430_CM_GPU_CLKSTCTRL,
	0xDEADBEEF,
	0};

reg omap5430_cm_gpu_staticdep = {
	"CM_GPU_STATICDEP",
	OMAP5430_CM_GPU_STATICDEP,
	0xDEADBEEF,
	0};

reg omap5430_cm_gpu_dynamicdep = {
	"CM_GPU_DYNAMICDEP",
	OMAP5430_CM_GPU_DYNAMICDEP,
	0xDEADBEEF,
	0};

reg omap5430_cm_gpu_gpu_clkctrl = {
	"CM_GPU_GPU_CLKCTRL",
	OMAP5430_CM_GPU_GPU_CLKCTRL,
	0xDEADBEEF,
	0};

reg *omap5430_gpu_cm_core_mod[OMAP5430_GPU_CM_CORE_MOD_REGCOUNT + 1] = {
	&omap5430_cm_gpu_clkstctrl,
	&omap5430_cm_gpu_staticdep,
	&omap5430_cm_gpu_dynamicdep,
	&omap5430_cm_gpu_gpu_clkctrl,
	NULL};

reg omap5430_cm_emu_clkstctrl = {
	"CM_EMU_CLKSTCTRL",
	OMAP5430_CM_EMU_CLKSTCTRL,
	0xDEADBEEF,
	0};

reg omap5430_cm_emu_dynamicdep = {
	"CM_EMU_DYNAMICDEP",
	OMAP5430_CM_EMU_DYNAMICDEP,
	0xDEADBEEF,
	0};

reg omap5430_cm_emu_debugss_clkctrl = {
	"CM_EMU_DEBUGSS_CLKCTRL",
	OMAP5430_CM_EMU_DEBUGSS_CLKCTRL,
	0xDEADBEEF,
	0};

reg omap5430_cm_emu_mpu_emu_dbg_clkctrl = {
	"CM_EMU_MPU_EMU_DBG_CLKCTRL",
	OMAP5430_CM_EMU_MPU_EMU_DBG_CLKCTRL,
	0xDEADBEEF,
	0};

reg *omap5430_emu_cm_mod[OMAP5430_EMU_CM_MOD_REGCOUNT + 1] = {
	&omap5430_cm_emu_clkstctrl,
	&omap5430_cm_emu_dynamicdep,
	&omap5430_cm_emu_debugss_clkctrl,
	&omap5430_cm_emu_mpu_emu_dbg_clkctrl,
	NULL};

reg omap5430_revision_cm_core = {
	"REVISION_CM_CORE",
	OMAP5430_REVISION_CM_CORE,
	0xDEADBEEF,
	0};

reg omap5430_cm_cm_core_profiling_clkctrl = {
	"CM_CM_CORE_PROFILING_CLKCTRL",
	OMAP5430_CM_CM_CORE_PROFILING_CLKCTRL,
	0xDEADBEEF,
	0};

reg omap5430_cm_core_debug_cfg = {
	"CM_CORE_DEBUG_CFG",
	OMAP5430_CM_CORE_DEBUG_CFG,
	0xDEADBEEF,
	0};

reg *omap5430_intrconn_socket_cm_core_mod[OMAP5430_INTRCONN_SOCKET_CM_CORE_MOD_REGCOUNT + 1] = {
	&omap5430_revision_cm_core,
	&omap5430_cm_cm_core_profiling_clkctrl,
	&omap5430_cm_core_debug_cfg,
	NULL};

reg omap5430_cmi_identication_aon = {
	"CMI_IDENTICATION_AON",
	OMAP5430_CMI_IDENTICATION_AON,
	0xDEADBEEF,
	0};

reg omap5430_cmi_sys_config_aon = {
	"CMI_SYS_CONFIG_AON",
	OMAP5430_CMI_SYS_CONFIG_AON,
	0xDEADBEEF,
	0};

reg omap5430_cmi_status_aon = {
	"CMI_STATUS_AON",
	OMAP5430_CMI_STATUS_AON,
	0xDEADBEEF,
	0};

reg omap5430_cmi_configuration_aon = {
	"CMI_CONFIGURATION_AON",
	OMAP5430_CMI_CONFIGURATION_AON,
	0xDEADBEEF,
	0};

reg omap5430_cmi_class_filtering_aon = {
	"CMI_CLASS_FILTERING_AON",
	OMAP5430_CMI_CLASS_FILTERING_AON,
	0xDEADBEEF,
	0};

reg omap5430_cmi_triggering_aon = {
	"CMI_TRIGGERING_AON",
	OMAP5430_CMI_TRIGGERING_AON,
	0xDEADBEEF,
	0};

reg omap5430_cmi_sampling_aon = {
	"CMI_SAMPLING_AON",
	OMAP5430_CMI_SAMPLING_AON,
	0xDEADBEEF,
	0};

reg *omap5430_instr_cm_core_aon_mod[OMAP5430_INSTR_CM_CORE_AON_MOD_REGCOUNT + 1] = {
	&omap5430_cmi_identication_aon,
	&omap5430_cmi_sys_config_aon,
	&omap5430_cmi_status_aon,
	&omap5430_cmi_configuration_aon,
	&omap5430_cmi_class_filtering_aon,
	&omap5430_cmi_triggering_aon,
	&omap5430_cmi_sampling_aon,
	NULL};

reg omap5430_cm_clksel_core = {
	"CM_CLKSEL_CORE",
	OMAP5430_CM_CLKSEL_CORE,
	0xDEADBEEF,
	0};

reg omap5430_cm_clksel_abe = {
	"CM_CLKSEL_ABE",
	OMAP5430_CM_CLKSEL_ABE,
	0xDEADBEEF,
	0};

reg omap5430_cm_dll_ctrl = {
	"CM_DLL_CTRL",
	OMAP5430_CM_DLL_CTRL,
	0xDEADBEEF,
	0};

reg omap5430_cm_clkmode_dpll_core = {
	"CM_CLKMODE_DPLL_CORE",
	OMAP5430_CM_CLKMODE_DPLL_CORE,
	0xDEADBEEF,
	0};

reg omap5430_cm_idlest_dpll_core = {
	"CM_IDLEST_DPLL_CORE",
	OMAP5430_CM_IDLEST_DPLL_CORE,
	0xDEADBEEF,
	0};

reg omap5430_cm_autoidle_dpll_core = {
	"CM_AUTOIDLE_DPLL_CORE",
	OMAP5430_CM_AUTOIDLE_DPLL_CORE,
	0xDEADBEEF,
	0};

reg omap5430_cm_clksel_dpll_core = {
	"CM_CLKSEL_DPLL_CORE",
	OMAP5430_CM_CLKSEL_DPLL_CORE,
	0xDEADBEEF,
	0};

reg omap5430_cm_div_m2_dpll_core = {
	"CM_DIV_M2_DPLL_CORE",
	OMAP5430_CM_DIV_M2_DPLL_CORE,
	0xDEADBEEF,
	0};

reg omap5430_cm_div_m3_dpll_core = {
	"CM_DIV_M3_DPLL_CORE",
	OMAP5430_CM_DIV_M3_DPLL_CORE,
	0xDEADBEEF,
	0};

reg omap5430_cm_div_h11_dpll_core = {
	"CM_DIV_H11_DPLL_CORE",
	OMAP5430_CM_DIV_H11_DPLL_CORE,
	0xDEADBEEF,
	0};

reg omap5430_cm_div_h12_dpll_core = {
	"CM_DIV_H12_DPLL_CORE",
	OMAP5430_CM_DIV_H12_DPLL_CORE,
	0xDEADBEEF,
	0};

reg omap5430_cm_div_h13_dpll_core = {
	"CM_DIV_H13_DPLL_CORE",
	OMAP5430_CM_DIV_H13_DPLL_CORE,
	0xDEADBEEF,
	0};

reg omap5430_cm_div_h14_dpll_core = {
	"CM_DIV_H14_DPLL_CORE",
	OMAP5430_CM_DIV_H14_DPLL_CORE,
	0xDEADBEEF,
	0};

reg omap5430_cm_ssc_deltamstep_dpll_core = {
	"CM_SSC_DELTAMSTEP_DPLL_CORE",
	OMAP5430_CM_SSC_DELTAMSTEP_DPLL_CORE,
	0xDEADBEEF,
	0};

reg omap5430_cm_ssc_modfreqdiv_dpll_core = {
	"CM_SSC_MODFREQDIV_DPLL_CORE",
	OMAP5430_CM_SSC_MODFREQDIV_DPLL_CORE,
	0xDEADBEEF,
	0};

reg omap5430_cm_div_h21_dpll_core = {
	"CM_DIV_H21_DPLL_CORE",
	OMAP5430_CM_DIV_H21_DPLL_CORE,
	0xDEADBEEF,
	0};

reg omap5430_cm_div_h22_dpll_core = {
	"CM_DIV_H22_DPLL_CORE",
	OMAP5430_CM_DIV_H22_DPLL_CORE,
	0xDEADBEEF,
	0};

reg omap5430_cm_div_h23_dpll_core = {
	"CM_DIV_H23_DPLL_CORE",
	OMAP5430_CM_DIV_H23_DPLL_CORE,
	0xDEADBEEF,
	0};

reg omap5430_cm_div_h24_dpll_core = {
	"CM_DIV_H24_DPLL_CORE",
	OMAP5430_CM_DIV_H24_DPLL_CORE,
	0xDEADBEEF,
	0};

reg omap5430_cm_clkmode_dpll_mpu = {
	"CM_CLKMODE_DPLL_MPU",
	OMAP5430_CM_CLKMODE_DPLL_MPU,
	0xDEADBEEF,
	0};

reg omap5430_cm_idlest_dpll_mpu = {
	"CM_IDLEST_DPLL_MPU",
	OMAP5430_CM_IDLEST_DPLL_MPU,
	0xDEADBEEF,
	0};

reg omap5430_cm_autoidle_dpll_mpu = {
	"CM_AUTOIDLE_DPLL_MPU",
	OMAP5430_CM_AUTOIDLE_DPLL_MPU,
	0xDEADBEEF,
	0};

reg omap5430_cm_clksel_dpll_mpu = {
	"CM_CLKSEL_DPLL_MPU",
	OMAP5430_CM_CLKSEL_DPLL_MPU,
	0xDEADBEEF,
	0};

reg omap5430_cm_div_m2_dpll_mpu = {
	"CM_DIV_M2_DPLL_MPU",
	OMAP5430_CM_DIV_M2_DPLL_MPU,
	0xDEADBEEF,
	0};

reg omap5430_cm_ssc_deltamstep_dpll_mpu = {
	"CM_SSC_DELTAMSTEP_DPLL_MPU",
	OMAP5430_CM_SSC_DELTAMSTEP_DPLL_MPU,
	0xDEADBEEF,
	0};

reg omap5430_cm_ssc_modfreqdiv_dpll_mpu = {
	"CM_SSC_MODFREQDIV_DPLL_MPU",
	OMAP5430_CM_SSC_MODFREQDIV_DPLL_MPU,
	0xDEADBEEF,
	0};

reg omap5430_cm_bypclk_dpll_mpu = {
	"CM_BYPCLK_DPLL_MPU",
	OMAP5430_CM_BYPCLK_DPLL_MPU,
	0xDEADBEEF,
	0};

reg omap5430_cm_clkmode_dpll_iva = {
	"CM_CLKMODE_DPLL_IVA",
	OMAP5430_CM_CLKMODE_DPLL_IVA,
	0xDEADBEEF,
	0};

reg omap5430_cm_idlest_dpll_iva = {
	"CM_IDLEST_DPLL_IVA",
	OMAP5430_CM_IDLEST_DPLL_IVA,
	0xDEADBEEF,
	0};

reg omap5430_cm_autoidle_dpll_iva = {
	"CM_AUTOIDLE_DPLL_IVA",
	OMAP5430_CM_AUTOIDLE_DPLL_IVA,
	0xDEADBEEF,
	0};

reg omap5430_cm_clksel_dpll_iva = {
	"CM_CLKSEL_DPLL_IVA",
	OMAP5430_CM_CLKSEL_DPLL_IVA,
	0xDEADBEEF,
	0};

reg omap5430_cm_div_h11_dpll_iva = {
	"CM_DIV_H11_DPLL_IVA",
	OMAP5430_CM_DIV_H11_DPLL_IVA,
	0xDEADBEEF,
	0};

reg omap5430_cm_div_h12_dpll_iva = {
	"CM_DIV_H12_DPLL_IVA",
	OMAP5430_CM_DIV_H12_DPLL_IVA,
	0xDEADBEEF,
	0};

reg omap5430_cm_ssc_deltamstep_dpll_iva = {
	"CM_SSC_DELTAMSTEP_DPLL_IVA",
	OMAP5430_CM_SSC_DELTAMSTEP_DPLL_IVA,
	0xDEADBEEF,
	0};

reg omap5430_cm_ssc_modfreqdiv_dpll_iva = {
	"CM_SSC_MODFREQDIV_DPLL_IVA",
	OMAP5430_CM_SSC_MODFREQDIV_DPLL_IVA,
	0xDEADBEEF,
	0};

reg omap5430_cm_bypclk_dpll_iva = {
	"CM_BYPCLK_DPLL_IVA",
	OMAP5430_CM_BYPCLK_DPLL_IVA,
	0xDEADBEEF,
	0};

reg omap5430_cm_clkmode_dpll_abe = {
	"CM_CLKMODE_DPLL_ABE",
	OMAP5430_CM_CLKMODE_DPLL_ABE,
	0xDEADBEEF,
	0};

reg omap5430_cm_idlest_dpll_abe = {
	"CM_IDLEST_DPLL_ABE",
	OMAP5430_CM_IDLEST_DPLL_ABE,
	0xDEADBEEF,
	0};

reg omap5430_cm_autoidle_dpll_abe = {
	"CM_AUTOIDLE_DPLL_ABE",
	OMAP5430_CM_AUTOIDLE_DPLL_ABE,
	0xDEADBEEF,
	0};

reg omap5430_cm_clksel_dpll_abe = {
	"CM_CLKSEL_DPLL_ABE",
	OMAP5430_CM_CLKSEL_DPLL_ABE,
	0xDEADBEEF,
	0};

reg omap5430_cm_div_m2_dpll_abe = {
	"CM_DIV_M2_DPLL_ABE",
	OMAP5430_CM_DIV_M2_DPLL_ABE,
	0xDEADBEEF,
	0};

reg omap5430_cm_div_m3_dpll_abe = {
	"CM_DIV_M3_DPLL_ABE",
	OMAP5430_CM_DIV_M3_DPLL_ABE,
	0xDEADBEEF,
	0};

reg omap5430_cm_ssc_deltamstep_dpll_abe = {
	"CM_SSC_DELTAMSTEP_DPLL_ABE",
	OMAP5430_CM_SSC_DELTAMSTEP_DPLL_ABE,
	0xDEADBEEF,
	0};

reg omap5430_cm_ssc_modfreqdiv_dpll_abe = {
	"CM_SSC_MODFREQDIV_DPLL_ABE",
	OMAP5430_CM_SSC_MODFREQDIV_DPLL_ABE,
	0xDEADBEEF,
	0};

reg omap5430_cm_shadow_freq_config1 = {
	"CM_SHADOW_FREQ_CONFIG1",
	OMAP5430_CM_SHADOW_FREQ_CONFIG1,
	0xDEADBEEF,
	0};

reg omap5430_cm_shadow_freq_config2 = {
	"CM_SHADOW_FREQ_CONFIG2",
	OMAP5430_CM_SHADOW_FREQ_CONFIG2,
	0xDEADBEEF,
	0};

reg omap5430_cm_dyn_dep_prescal = {
	"CM_DYN_DEP_PRESCAL",
	OMAP5430_CM_DYN_DEP_PRESCAL,
	0xDEADBEEF,
	0};

reg omap5430_cm_restore_st = {
	"CM_RESTORE_ST",
	OMAP5430_CM_RESTORE_ST,
	0xDEADBEEF,
	0};

reg *omap5430_ckgen_cm_core_aon_mod[OMAP5430_CKGEN_CM_CORE_AON_MOD_REGCOUNT + 1] = {
	&omap5430_cm_clksel_core,
	&omap5430_cm_clksel_abe,
	&omap5430_cm_dll_ctrl,
	&omap5430_cm_clkmode_dpll_core,
	&omap5430_cm_idlest_dpll_core,
	&omap5430_cm_autoidle_dpll_core,
	&omap5430_cm_clksel_dpll_core,
	&omap5430_cm_div_m2_dpll_core,
	&omap5430_cm_div_m3_dpll_core,
	&omap5430_cm_div_h11_dpll_core,
	&omap5430_cm_div_h12_dpll_core,
	&omap5430_cm_div_h13_dpll_core,
	&omap5430_cm_div_h14_dpll_core,
	&omap5430_cm_ssc_deltamstep_dpll_core,
	&omap5430_cm_ssc_modfreqdiv_dpll_core,
	&omap5430_cm_div_h21_dpll_core,
	&omap5430_cm_div_h22_dpll_core,
	&omap5430_cm_div_h23_dpll_core,
	&omap5430_cm_div_h24_dpll_core,
	&omap5430_cm_clkmode_dpll_mpu,
	&omap5430_cm_idlest_dpll_mpu,
	&omap5430_cm_autoidle_dpll_mpu,
	&omap5430_cm_clksel_dpll_mpu,
	&omap5430_cm_div_m2_dpll_mpu,
	&omap5430_cm_ssc_deltamstep_dpll_mpu,
	&omap5430_cm_ssc_modfreqdiv_dpll_mpu,
	&omap5430_cm_bypclk_dpll_mpu,
	&omap5430_cm_clkmode_dpll_iva,
	&omap5430_cm_idlest_dpll_iva,
	&omap5430_cm_autoidle_dpll_iva,
	&omap5430_cm_clksel_dpll_iva,
	&omap5430_cm_div_h11_dpll_iva,
	&omap5430_cm_div_h12_dpll_iva,
	&omap5430_cm_ssc_deltamstep_dpll_iva,
	&omap5430_cm_ssc_modfreqdiv_dpll_iva,
	&omap5430_cm_bypclk_dpll_iva,
	&omap5430_cm_clkmode_dpll_abe,
	&omap5430_cm_idlest_dpll_abe,
	&omap5430_cm_autoidle_dpll_abe,
	&omap5430_cm_clksel_dpll_abe,
	&omap5430_cm_div_m2_dpll_abe,
	&omap5430_cm_div_m3_dpll_abe,
	&omap5430_cm_ssc_deltamstep_dpll_abe,
	&omap5430_cm_ssc_modfreqdiv_dpll_abe,
	&omap5430_cm_shadow_freq_config1,
	&omap5430_cm_shadow_freq_config2,
	&omap5430_cm_dyn_dep_prescal,
	&omap5430_cm_restore_st,
	NULL};

reg omap5430_cm_clksel_usb_60mhz = {
	"CM_CLKSEL_USB_60MHZ",
	OMAP5430_CM_CLKSEL_USB_60MHZ,
	0xDEADBEEF,
	0};

reg omap5430_cm_clkmode_dpll_per = {
	"CM_CLKMODE_DPLL_PER",
	OMAP5430_CM_CLKMODE_DPLL_PER,
	0xDEADBEEF,
	0};

reg omap5430_cm_idlest_dpll_per = {
	"CM_IDLEST_DPLL_PER",
	OMAP5430_CM_IDLEST_DPLL_PER,
	0xDEADBEEF,
	0};

reg omap5430_cm_autoidle_dpll_per = {
	"CM_AUTOIDLE_DPLL_PER",
	OMAP5430_CM_AUTOIDLE_DPLL_PER,
	0xDEADBEEF,
	0};

reg omap5430_cm_clksel_dpll_per = {
	"CM_CLKSEL_DPLL_PER",
	OMAP5430_CM_CLKSEL_DPLL_PER,
	0xDEADBEEF,
	0};

reg omap5430_cm_div_m2_dpll_per = {
	"CM_DIV_M2_DPLL_PER",
	OMAP5430_CM_DIV_M2_DPLL_PER,
	0xDEADBEEF,
	0};

reg omap5430_cm_div_m3_dpll_per = {
	"CM_DIV_M3_DPLL_PER",
	OMAP5430_CM_DIV_M3_DPLL_PER,
	0xDEADBEEF,
	0};

reg omap5430_cm_div_h11_dpll_per = {
	"CM_DIV_H11_DPLL_PER",
	OMAP5430_CM_DIV_H11_DPLL_PER,
	0xDEADBEEF,
	0};

reg omap5430_cm_div_h12_dpll_per = {
	"CM_DIV_H12_DPLL_PER",
	OMAP5430_CM_DIV_H12_DPLL_PER,
	0xDEADBEEF,
	0};

reg omap5430_cm_div_h14_dpll_per = {
	"CM_DIV_H14_DPLL_PER",
	OMAP5430_CM_DIV_H14_DPLL_PER,
	0xDEADBEEF,
	0};

reg omap5430_cm_ssc_deltamstep_dpll_per = {
	"CM_SSC_DELTAMSTEP_DPLL_PER",
	OMAP5430_CM_SSC_DELTAMSTEP_DPLL_PER,
	0xDEADBEEF,
	0};

reg omap5430_cm_ssc_modfreqdiv_dpll_per = {
	"CM_SSC_MODFREQDIV_DPLL_PER",
	OMAP5430_CM_SSC_MODFREQDIV_DPLL_PER,
	0xDEADBEEF,
	0};

reg omap5430_cm_clkmode_dpll_usb = {
	"CM_CLKMODE_DPLL_USB",
	OMAP5430_CM_CLKMODE_DPLL_USB,
	0xDEADBEEF,
	0};

reg omap5430_cm_idlest_dpll_usb = {
	"CM_IDLEST_DPLL_USB",
	OMAP5430_CM_IDLEST_DPLL_USB,
	0xDEADBEEF,
	0};

reg omap5430_cm_autoidle_dpll_usb = {
	"CM_AUTOIDLE_DPLL_USB",
	OMAP5430_CM_AUTOIDLE_DPLL_USB,
	0xDEADBEEF,
	0};

reg omap5430_cm_clksel_dpll_usb = {
	"CM_CLKSEL_DPLL_USB",
	OMAP5430_CM_CLKSEL_DPLL_USB,
	0xDEADBEEF,
	0};

reg omap5430_cm_div_m2_dpll_usb = {
	"CM_DIV_M2_DPLL_USB",
	OMAP5430_CM_DIV_M2_DPLL_USB,
	0xDEADBEEF,
	0};

reg omap5430_cm_ssc_deltamstep_dpll_usb = {
	"CM_SSC_DELTAMSTEP_DPLL_USB",
	OMAP5430_CM_SSC_DELTAMSTEP_DPLL_USB,
	0xDEADBEEF,
	0};

reg omap5430_cm_ssc_modfreqdiv_dpll_usb = {
	"CM_SSC_MODFREQDIV_DPLL_USB",
	OMAP5430_CM_SSC_MODFREQDIV_DPLL_USB,
	0xDEADBEEF,
	0};

reg omap5430_cm_clkdcoldo_dpll_usb = {
	"CM_CLKDCOLDO_DPLL_USB",
	OMAP5430_CM_CLKDCOLDO_DPLL_USB,
	0xDEADBEEF,
	0};

reg omap5430_cm_clkmode_dpll_unipro2 = {
	"CM_CLKMODE_DPLL_UNIPRO2",
	OMAP5430_CM_CLKMODE_DPLL_UNIPRO2,
	0xDEADBEEF,
	0};

reg omap5430_cm_idlest_dpll_unipro2 = {
	"CM_IDLEST_DPLL_UNIPRO2",
	OMAP5430_CM_IDLEST_DPLL_UNIPRO2,
	0xDEADBEEF,
	0};

reg omap5430_cm_autoidle_dpll_unipro2 = {
	"CM_AUTOIDLE_DPLL_UNIPRO2",
	OMAP5430_CM_AUTOIDLE_DPLL_UNIPRO2,
	0xDEADBEEF,
	0};

reg omap5430_cm_clksel_dpll_unipro2 = {
	"CM_CLKSEL_DPLL_UNIPRO2",
	OMAP5430_CM_CLKSEL_DPLL_UNIPRO2,
	0xDEADBEEF,
	0};

reg omap5430_cm_div_m2_dpll_unipro2 = {
	"CM_DIV_M2_DPLL_UNIPRO2",
	OMAP5430_CM_DIV_M2_DPLL_UNIPRO2,
	0xDEADBEEF,
	0};

reg omap5430_cm_ssc_deltamstep_dpll_unipro2 = {
	"CM_SSC_DELTAMSTEP_DPLL_UNIPRO2",
	OMAP5430_CM_SSC_DELTAMSTEP_DPLL_UNIPRO2,
	0xDEADBEEF,
	0};

reg omap5430_cm_ssc_modfreqdiv_dpll_unipro2 = {
	"CM_SSC_MODFREQDIV_DPLL_UNIPRO2",
	OMAP5430_CM_SSC_MODFREQDIV_DPLL_UNIPRO2,
	0xDEADBEEF,
	0};

reg omap5430_cm_clkdcoldo_dpll_unipro2 = {
	"CM_CLKDCOLDO_DPLL_UNIPRO2",
	OMAP5430_CM_CLKDCOLDO_DPLL_UNIPRO2,
	0xDEADBEEF,
	0};

reg omap5430_cm_clkmode_dpll_unipro1 = {
	"CM_CLKMODE_DPLL_UNIPRO1",
	OMAP5430_CM_CLKMODE_DPLL_UNIPRO1,
	0xDEADBEEF,
	0};

reg omap5430_cm_idlest_dpll_unipro1 = {
	"CM_IDLEST_DPLL_UNIPRO1",
	OMAP5430_CM_IDLEST_DPLL_UNIPRO1,
	0xDEADBEEF,
	0};

reg omap5430_cm_autoidle_dpll_unipro1 = {
	"CM_AUTOIDLE_DPLL_UNIPRO1",
	OMAP5430_CM_AUTOIDLE_DPLL_UNIPRO1,
	0xDEADBEEF,
	0};

reg omap5430_cm_clksel_dpll_unipro1 = {
	"CM_CLKSEL_DPLL_UNIPRO1",
	OMAP5430_CM_CLKSEL_DPLL_UNIPRO1,
	0xDEADBEEF,
	0};

reg omap5430_cm_div_m2_dpll_unipro1 = {
	"CM_DIV_M2_DPLL_UNIPRO1",
	OMAP5430_CM_DIV_M2_DPLL_UNIPRO1,
	0xDEADBEEF,
	0};

reg omap5430_cm_ssc_deltamstep_dpll_unipro1 = {
	"CM_SSC_DELTAMSTEP_DPLL_UNIPRO1",
	OMAP5430_CM_SSC_DELTAMSTEP_DPLL_UNIPRO1,
	0xDEADBEEF,
	0};

reg omap5430_cm_ssc_modfreqdiv_dpll_unipro1 = {
	"CM_SSC_MODFREQDIV_DPLL_UNIPRO1",
	OMAP5430_CM_SSC_MODFREQDIV_DPLL_UNIPRO1,
	0xDEADBEEF,
	0};

reg omap5430_cm_clkdcoldo_dpll_unipro1 = {
	"CM_CLKDCOLDO_DPLL_UNIPRO1",
	OMAP5430_CM_CLKDCOLDO_DPLL_UNIPRO1,
	0xDEADBEEF,
	0};

reg *omap5430_ckgen_cm_core_mod[OMAP5430_CKGEN_CM_CORE_MOD_REGCOUNT + 1] = {
	&omap5430_cm_clksel_usb_60mhz,
	&omap5430_cm_clkmode_dpll_per,
	&omap5430_cm_idlest_dpll_per,
	&omap5430_cm_autoidle_dpll_per,
	&omap5430_cm_clksel_dpll_per,
	&omap5430_cm_div_m2_dpll_per,
	&omap5430_cm_div_m3_dpll_per,
	&omap5430_cm_div_h11_dpll_per,
	&omap5430_cm_div_h12_dpll_per,
	&omap5430_cm_div_h14_dpll_per,
	&omap5430_cm_ssc_deltamstep_dpll_per,
	&omap5430_cm_ssc_modfreqdiv_dpll_per,
	&omap5430_cm_clkmode_dpll_usb,
	&omap5430_cm_idlest_dpll_usb,
	&omap5430_cm_autoidle_dpll_usb,
	&omap5430_cm_clksel_dpll_usb,
	&omap5430_cm_div_m2_dpll_usb,
	&omap5430_cm_ssc_deltamstep_dpll_usb,
	&omap5430_cm_ssc_modfreqdiv_dpll_usb,
	&omap5430_cm_clkdcoldo_dpll_usb,
	&omap5430_cm_clkmode_dpll_unipro2,
	&omap5430_cm_idlest_dpll_unipro2,
	&omap5430_cm_autoidle_dpll_unipro2,
	&omap5430_cm_clksel_dpll_unipro2,
	&omap5430_cm_div_m2_dpll_unipro2,
	&omap5430_cm_ssc_deltamstep_dpll_unipro2,
	&omap5430_cm_ssc_modfreqdiv_dpll_unipro2,
	&omap5430_cm_clkdcoldo_dpll_unipro2,
	&omap5430_cm_clkmode_dpll_unipro1,
	&omap5430_cm_idlest_dpll_unipro1,
	&omap5430_cm_autoidle_dpll_unipro1,
	&omap5430_cm_clksel_dpll_unipro1,
	&omap5430_cm_div_m2_dpll_unipro1,
	&omap5430_cm_ssc_deltamstep_dpll_unipro1,
	&omap5430_cm_ssc_modfreqdiv_dpll_unipro1,
	&omap5430_cm_clkdcoldo_dpll_unipro1,
	NULL};

reg omap5430_cm_l3init_clkstctrl = {
	"CM_L3INIT_CLKSTCTRL",
	OMAP5430_CM_L3INIT_CLKSTCTRL,
	0xDEADBEEF,
	0};

reg omap5430_cm_l3init_staticdep = {
	"CM_L3INIT_STATICDEP",
	OMAP5430_CM_L3INIT_STATICDEP,
	0xDEADBEEF,
	0};

reg omap5430_cm_l3init_dynamicdep = {
	"CM_L3INIT_DYNAMICDEP",
	OMAP5430_CM_L3INIT_DYNAMICDEP,
	0xDEADBEEF,
	0};

reg omap5430_cm_l3init_mmc1_clkctrl = {
	"CM_L3INIT_MMC1_CLKCTRL",
	OMAP5430_CM_L3INIT_MMC1_CLKCTRL,
	0xDEADBEEF,
	0};

reg omap5430_cm_l3init_mmc2_clkctrl = {
	"CM_L3INIT_MMC2_CLKCTRL",
	OMAP5430_CM_L3INIT_MMC2_CLKCTRL,
	0xDEADBEEF,
	0};

reg omap5430_cm_l3init_hsi_clkctrl = {
	"CM_L3INIT_HSI_CLKCTRL",
	OMAP5430_CM_L3INIT_HSI_CLKCTRL,
	0xDEADBEEF,
	0};

reg omap5430_cm_l3init_unipro2_clkctrl = {
	"CM_L3INIT_UNIPRO2_CLKCTRL",
	OMAP5430_CM_L3INIT_UNIPRO2_CLKCTRL,
	0xDEADBEEF,
	0};

reg omap5430_cm_l3init_mphy_unipro2_clkctrl = {
	"CM_L3INIT_MPHY_UNIPRO2_CLKCTRL",
	OMAP5430_CM_L3INIT_MPHY_UNIPRO2_CLKCTRL,
	0xDEADBEEF,
	0};

reg omap5430_cm_l3init_usb_host_hs_clkctrl = {
	"CM_L3INIT_USB_HOST_HS_CLKCTRL",
	OMAP5430_CM_L3INIT_USB_HOST_HS_CLKCTRL,
	0xDEADBEEF,
	0};

reg omap5430_cm_l3init_usb_tll_hs_clkctrl = {
	"CM_L3INIT_USB_TLL_HS_CLKCTRL",
	OMAP5430_CM_L3INIT_USB_TLL_HS_CLKCTRL,
	0xDEADBEEF,
	0};

reg omap5430_cm_l3init_ieee1500_2_ocp_clkctrl = {
	"CM_L3INIT_IEEE1500_2_OCP_CLKCTRL",
	OMAP5430_CM_L3INIT_IEEE1500_2_OCP_CLKCTRL,
	0xDEADBEEF,
	0};

reg omap5430_cm_l3init_sata_clkctrl = {
	"CM_L3INIT_SATA_CLKCTRL",
	OMAP5430_CM_L3INIT_SATA_CLKCTRL,
	0xDEADBEEF,
	0};

reg omap5430_cm_l3init_ocp2scp1_clkctrl = {
	"CM_L3INIT_OCP2SCP1_CLKCTRL",
	OMAP5430_CM_L3INIT_OCP2SCP1_CLKCTRL,
	0xDEADBEEF,
	0};

reg omap5430_cm_l3init_ocp2scp3_clkctrl = {
	"CM_L3INIT_OCP2SCP3_CLKCTRL",
	OMAP5430_CM_L3INIT_OCP2SCP3_CLKCTRL,
	0xDEADBEEF,
	0};

reg omap5430_cm_l3init_usb_otg_ss_clkctrl = {
	"CM_L3INIT_USB_OTG_SS_CLKCTRL",
	OMAP5430_CM_L3INIT_USB_OTG_SS_CLKCTRL,
	0xDEADBEEF,
	0};

reg *omap5430_l3init_cm_core_mod[OMAP5430_L3INIT_CM_CORE_MOD_REGCOUNT + 1] = {
	&omap5430_cm_l3init_clkstctrl,
	&omap5430_cm_l3init_staticdep,
	&omap5430_cm_l3init_dynamicdep,
	&omap5430_cm_l3init_mmc1_clkctrl,
	&omap5430_cm_l3init_mmc2_clkctrl,
	&omap5430_cm_l3init_hsi_clkctrl,
	&omap5430_cm_l3init_unipro2_clkctrl,
	&omap5430_cm_l3init_mphy_unipro2_clkctrl,
	&omap5430_cm_l3init_usb_host_hs_clkctrl,
	&omap5430_cm_l3init_usb_tll_hs_clkctrl,
	&omap5430_cm_l3init_ieee1500_2_ocp_clkctrl,
	&omap5430_cm_l3init_sata_clkctrl,
	&omap5430_cm_l3init_ocp2scp1_clkctrl,
	&omap5430_cm_l3init_ocp2scp3_clkctrl,
	&omap5430_cm_l3init_usb_otg_ss_clkctrl,
	NULL};

reg omap5430_revision_cm_core_aon = {
	"REVISION_CM_CORE_AON",
	OMAP5430_REVISION_CM_CORE_AON,
	0xDEADBEEF,
	0};

reg omap5430_cm_cm_core_aon_profiling_clkctrl = {
	"CM_CM_CORE_AON_PROFILING_CLKCTRL",
	OMAP5430_CM_CM_CORE_AON_PROFILING_CLKCTRL,
	0xDEADBEEF,
	0};

reg omap5430_cm_core_aon_debug_cfg = {
	"CM_CORE_AON_DEBUG_CFG",
	OMAP5430_CM_CORE_AON_DEBUG_CFG,
	0xDEADBEEF,
	0};

reg *omap5430_intrconn_socket_cm_core_aon_mod[OMAP5430_INTRCONN_SOCKET_CM_CORE_AON_MOD_REGCOUNT + 1] = {
	&omap5430_revision_cm_core_aon,
	&omap5430_cm_cm_core_aon_profiling_clkctrl,
	&omap5430_cm_core_aon_debug_cfg,
	NULL};

reg omap5430_cm_iva_clkstctrl = {
	"CM_IVA_CLKSTCTRL",
	OMAP5430_CM_IVA_CLKSTCTRL,
	0xDEADBEEF,
	0};

reg omap5430_cm_iva_staticdep = {
	"CM_IVA_STATICDEP",
	OMAP5430_CM_IVA_STATICDEP,
	0xDEADBEEF,
	0};

reg omap5430_cm_iva_dynamicdep = {
	"CM_IVA_DYNAMICDEP",
	OMAP5430_CM_IVA_DYNAMICDEP,
	0xDEADBEEF,
	0};

reg omap5430_cm_iva_iva_clkctrl = {
	"CM_IVA_IVA_CLKCTRL",
	OMAP5430_CM_IVA_IVA_CLKCTRL,
	0xDEADBEEF,
	0};

reg omap5430_cm_iva_sl2_clkctrl = {
	"CM_IVA_SL2_CLKCTRL",
	OMAP5430_CM_IVA_SL2_CLKCTRL,
	0xDEADBEEF,
	0};

reg *omap5430_iva_cm_core_mod[OMAP5430_IVA_CM_CORE_MOD_REGCOUNT + 1] = {
	&omap5430_cm_iva_clkstctrl,
	&omap5430_cm_iva_staticdep,
	&omap5430_cm_iva_dynamicdep,
	&omap5430_cm_iva_iva_clkctrl,
	&omap5430_cm_iva_sl2_clkctrl,
	NULL};

reg omap5430_cm_coreaon_clkstctrl = {
	"CM_COREAON_CLKSTCTRL",
	OMAP5430_CM_COREAON_CLKSTCTRL,
	0xDEADBEEF,
	0};

reg omap5430_cm_coreaon_smartreflex_mpu_clkctrl = {
	"CM_COREAON_SMARTREFLEX_MPU_CLKCTRL",
	OMAP5430_CM_COREAON_SMARTREFLEX_MPU_CLKCTRL,
	0xDEADBEEF,
	0};

reg omap5430_cm_coreaon_smartreflex_mm_clkctrl = {
	"CM_COREAON_SMARTREFLEX_MM_CLKCTRL",
	OMAP5430_CM_COREAON_SMARTREFLEX_MM_CLKCTRL,
	0xDEADBEEF,
	0};

reg omap5430_cm_coreaon_smartreflex_core_clkctrl = {
	"CM_COREAON_SMARTREFLEX_CORE_CLKCTRL",
	OMAP5430_CM_COREAON_SMARTREFLEX_CORE_CLKCTRL,
	0xDEADBEEF,
	0};

reg omap5430_cm_coreaon_usb_phy_core_clkctrl = {
	"CM_COREAON_USB_PHY_CORE_CLKCTRL",
	OMAP5430_CM_COREAON_USB_PHY_CORE_CLKCTRL,
	0xDEADBEEF,
	0};

reg omap5430_cm_coreaon_io_srcomp_clkctrl = {
	"CM_COREAON_IO_SRCOMP_CLKCTRL",
	OMAP5430_CM_COREAON_IO_SRCOMP_CLKCTRL,
	0xDEADBEEF,
	0};

reg *omap5430_coreaon_cm_core_mod[OMAP5430_COREAON_CM_CORE_MOD_REGCOUNT + 1] = {
	&omap5430_cm_coreaon_clkstctrl,
	&omap5430_cm_coreaon_smartreflex_mpu_clkctrl,
	&omap5430_cm_coreaon_smartreflex_mm_clkctrl,
	&omap5430_cm_coreaon_smartreflex_core_clkctrl,
	&omap5430_cm_coreaon_usb_phy_core_clkctrl,
	&omap5430_cm_coreaon_io_srcomp_clkctrl,
	NULL};

reg omap5430_cm_wkupaon_clkstctrl = {
	"CM_WKUPAON_CLKSTCTRL",
	OMAP5430_CM_WKUPAON_CLKSTCTRL,
	0xDEADBEEF,
	0};

reg omap5430_cm_wkupaon_l4_wkup_clkctrl = {
	"CM_WKUPAON_L4_WKUP_CLKCTRL",
	OMAP5430_CM_WKUPAON_L4_WKUP_CLKCTRL,
	0xDEADBEEF,
	0};

reg omap5430_cm_wkupaon_wd_timer2_clkctrl = {
	"CM_WKUPAON_WD_TIMER2_CLKCTRL",
	OMAP5430_CM_WKUPAON_WD_TIMER2_CLKCTRL,
	0xDEADBEEF,
	0};

reg omap5430_cm_wkupaon_gpio1_clkctrl = {
	"CM_WKUPAON_GPIO1_CLKCTRL",
	OMAP5430_CM_WKUPAON_GPIO1_CLKCTRL,
	0xDEADBEEF,
	0};

reg omap5430_cm_wkupaon_timer1_clkctrl = {
	"CM_WKUPAON_TIMER1_CLKCTRL",
	OMAP5430_CM_WKUPAON_TIMER1_CLKCTRL,
	0xDEADBEEF,
	0};

reg omap5430_cm_wkupaon_counter_32k_clkctrl = {
	"CM_WKUPAON_COUNTER_32K_CLKCTRL",
	OMAP5430_CM_WKUPAON_COUNTER_32K_CLKCTRL,
	0xDEADBEEF,
	0};

reg omap5430_cm_wkupaon_sar_ram_clkctrl = {
	"CM_WKUPAON_SAR_RAM_CLKCTRL",
	OMAP5430_CM_WKUPAON_SAR_RAM_CLKCTRL,
	0xDEADBEEF,
	0};

reg omap5430_cm_wkupaon_kbd_clkctrl = {
	"CM_WKUPAON_KBD_CLKCTRL",
	OMAP5430_CM_WKUPAON_KBD_CLKCTRL,
	0xDEADBEEF,
	0};

reg omap5430_cm_wkupaon_scrm_clkctrl = {
	"CM_WKUPAON_SCRM_CLKCTRL",
	OMAP5430_CM_WKUPAON_SCRM_CLKCTRL,
	0xDEADBEEF,
	0};

reg omap5430_cm_wkupaon_io_srcomp_clkctrl = {
	"CM_WKUPAON_IO_SRCOMP_CLKCTRL",
	OMAP5430_CM_WKUPAON_IO_SRCOMP_CLKCTRL,
	0xDEADBEEF,
	0};

reg *omap5430_wkupaon_cm_mod[OMAP5430_WKUPAON_CM_MOD_REGCOUNT + 1] = {
	&omap5430_cm_wkupaon_clkstctrl,
	&omap5430_cm_wkupaon_l4_wkup_clkctrl,
	&omap5430_cm_wkupaon_wd_timer2_clkctrl,
	&omap5430_cm_wkupaon_gpio1_clkctrl,
	&omap5430_cm_wkupaon_timer1_clkctrl,
	&omap5430_cm_wkupaon_counter_32k_clkctrl,
	&omap5430_cm_wkupaon_sar_ram_clkctrl,
	&omap5430_cm_wkupaon_kbd_clkctrl,
	&omap5430_cm_wkupaon_scrm_clkctrl,
	&omap5430_cm_wkupaon_io_srcomp_clkctrl,
	NULL};

reg omap5430_cm_mpu_clkstctrl = {
	"CM_MPU_CLKSTCTRL",
	OMAP5430_CM_MPU_CLKSTCTRL,
	0xDEADBEEF,
	0};

reg omap5430_cm_mpu_staticdep = {
	"CM_MPU_STATICDEP",
	OMAP5430_CM_MPU_STATICDEP,
	0xDEADBEEF,
	0};

reg omap5430_cm_mpu_dynamicdep = {
	"CM_MPU_DYNAMICDEP",
	OMAP5430_CM_MPU_DYNAMICDEP,
	0xDEADBEEF,
	0};

reg omap5430_cm_mpu_mpu_clkctrl = {
	"CM_MPU_MPU_CLKCTRL",
	OMAP5430_CM_MPU_MPU_CLKCTRL,
	0xDEADBEEF,
	0};

reg omap5430_cm_mpu_mpu_mpu_dbg_clkctrl = {
	"CM_MPU_MPU_MPU_DBG_CLKCTRL",
	OMAP5430_CM_MPU_MPU_MPU_DBG_CLKCTRL,
	0xDEADBEEF,
	0};

reg *omap5430_mpu_cm_core_aon_mod[OMAP5430_MPU_CM_CORE_AON_MOD_REGCOUNT + 1] = {
	&omap5430_cm_mpu_clkstctrl,
	&omap5430_cm_mpu_staticdep,
	&omap5430_cm_mpu_dynamicdep,
	&omap5430_cm_mpu_mpu_clkctrl,
	&omap5430_cm_mpu_mpu_mpu_dbg_clkctrl,
	NULL};

reg omap5430_cm_cam_clkstctrl = {
	"CM_CAM_CLKSTCTRL",
	OMAP5430_CM_CAM_CLKSTCTRL,
	0xDEADBEEF,
	0};

reg omap5430_cm_cam_staticdep = {
	"CM_CAM_STATICDEP",
	OMAP5430_CM_CAM_STATICDEP,
	0xDEADBEEF,
	0};

reg omap5430_cm_cam_dynamicdep = {
	"CM_CAM_DYNAMICDEP",
	OMAP5430_CM_CAM_DYNAMICDEP,
	0xDEADBEEF,
	0};

reg omap5430_cm_cam_iss_clkctrl = {
	"CM_CAM_ISS_CLKCTRL",
	OMAP5430_CM_CAM_ISS_CLKCTRL,
	0xDEADBEEF,
	0};

reg omap5430_cm_cam_fdif_clkctrl = {
	"CM_CAM_FDIF_CLKCTRL",
	OMAP5430_CM_CAM_FDIF_CLKCTRL,
	0xDEADBEEF,
	0};

reg omap5430_cm_cam_cal_clkctrl = {
	"CM_CAM_CAL_CLKCTRL",
	OMAP5430_CM_CAM_CAL_CLKCTRL,
	0xDEADBEEF,
	0};

reg *omap5430_cam_cm_core_mod[OMAP5430_CAM_CM_CORE_MOD_REGCOUNT + 1] = {
	&omap5430_cm_cam_clkstctrl,
	&omap5430_cm_cam_staticdep,
	&omap5430_cm_cam_dynamicdep,
	&omap5430_cm_cam_iss_clkctrl,
	&omap5430_cm_cam_fdif_clkctrl,
	&omap5430_cm_cam_cal_clkctrl,
	NULL};

reg omap5430_cm_dsp_clkstctrl = {
	"CM_DSP_CLKSTCTRL",
	OMAP5430_CM_DSP_CLKSTCTRL,
	0xDEADBEEF,
	0};

reg omap5430_cm_dsp_staticdep = {
	"CM_DSP_STATICDEP",
	OMAP5430_CM_DSP_STATICDEP,
	0xDEADBEEF,
	0};

reg omap5430_cm_dsp_dynamicdep = {
	"CM_DSP_DYNAMICDEP",
	OMAP5430_CM_DSP_DYNAMICDEP,
	0xDEADBEEF,
	0};

reg omap5430_cm_dsp_dsp_clkctrl = {
	"CM_DSP_DSP_CLKCTRL",
	OMAP5430_CM_DSP_DSP_CLKCTRL,
	0xDEADBEEF,
	0};

reg *omap5430_dsp_cm_core_aon_mod[OMAP5430_DSP_CM_CORE_AON_MOD_REGCOUNT + 1] = {
	&omap5430_cm_dsp_clkstctrl,
	&omap5430_cm_dsp_staticdep,
	&omap5430_cm_dsp_dynamicdep,
	&omap5430_cm_dsp_dsp_clkctrl,
	NULL};

reg **cm54xx_mods[CM54XX_MODS_COUNT + 1] = {
	(reg **) &omap5430_dss_cm_core_mod,
	(reg **) &omap5430_instr_cm_core_mod,
	(reg **) &omap5430_core_cm_core_mod,
	(reg **) &omap5430_custefuse_cm_core_mod,
	(reg **) &omap5430_abe_cm_core_aon_mod,
	(reg **) &omap5430_gpu_cm_core_mod,
	(reg **) &omap5430_emu_cm_mod,
	(reg **) &omap5430_intrconn_socket_cm_core_mod,
	(reg **) &omap5430_instr_cm_core_aon_mod,
	(reg **) &omap5430_ckgen_cm_core_aon_mod,
	(reg **) &omap5430_ckgen_cm_core_mod,
	NULL,
	(reg **) &omap5430_l3init_cm_core_mod,
	(reg **) &omap5430_wkupaon_cm_mod,
	(reg **) &omap5430_intrconn_socket_cm_core_aon_mod,
	(reg **) &omap5430_iva_cm_core_mod,
	(reg **) &omap5430_coreaon_cm_core_mod,
	(reg **) &omap5430_mpu_cm_core_aon_mod,
	(reg **) &omap5430_cam_cm_core_mod,
	(reg **) &omap5430_dsp_cm_core_aon_mod,
	NULL};


const dpll_settings_regs dpll54xx_regs[DPLL54XX_ID_MAX] = {
	{&omap5430_cm_clkmode_dpll_mpu,
		&omap5430_cm_idlest_dpll_mpu,
		&omap5430_cm_autoidle_dpll_mpu,
		&omap5430_cm_clksel_dpll_mpu,
		&omap5430_cm_bypclk_dpll_mpu,
		&omap5430_cm_div_m2_dpll_mpu,
		NULL,
		&omap5430_cm_ssc_deltamstep_dpll_mpu,
		&omap5430_cm_ssc_modfreqdiv_dpll_mpu,
		NULL},
	{&omap5430_cm_clkmode_dpll_iva,
		&omap5430_cm_idlest_dpll_iva,
		&omap5430_cm_autoidle_dpll_iva,
		&omap5430_cm_clksel_dpll_iva,
		&omap5430_cm_bypclk_dpll_iva,
		NULL,
		NULL,
		&omap5430_cm_ssc_deltamstep_dpll_iva,
		&omap5430_cm_ssc_modfreqdiv_dpll_iva,
		NULL},
	{&omap5430_cm_clkmode_dpll_core,
		&omap5430_cm_idlest_dpll_core,
		&omap5430_cm_autoidle_dpll_core,
		&omap5430_cm_clksel_dpll_core,
		NULL,
		&omap5430_cm_div_m2_dpll_core,
		&omap5430_cm_div_m3_dpll_core,
		&omap5430_cm_ssc_deltamstep_dpll_core,
		&omap5430_cm_ssc_modfreqdiv_dpll_core,
		NULL},
	{&omap5430_cm_clkmode_dpll_per,
		&omap5430_cm_idlest_dpll_per,
		&omap5430_cm_autoidle_dpll_per,
		&omap5430_cm_clksel_dpll_per,
		NULL,
		&omap5430_cm_div_m2_dpll_per,
		&omap5430_cm_div_m3_dpll_per,
		&omap5430_cm_ssc_deltamstep_dpll_per,
		&omap5430_cm_ssc_modfreqdiv_dpll_per,
		NULL},
	{&omap5430_cm_clkmode_dpll_abe,
		&omap5430_cm_idlest_dpll_abe,
		&omap5430_cm_autoidle_dpll_abe,
		&omap5430_cm_clksel_dpll_abe,
		NULL,
		&omap5430_cm_div_m2_dpll_abe,
		&omap5430_cm_div_m3_dpll_abe,
		&omap5430_cm_ssc_deltamstep_dpll_abe,
		&omap5430_cm_ssc_modfreqdiv_dpll_abe,
		NULL},
	{&omap5430_cm_clkmode_dpll_usb,
		&omap5430_cm_idlest_dpll_usb,
		&omap5430_cm_autoidle_dpll_usb,
		&omap5430_cm_clksel_dpll_usb,
		NULL,
		&omap5430_cm_div_m2_dpll_usb,
		NULL,
		&omap5430_cm_ssc_deltamstep_dpll_usb,
		&omap5430_cm_ssc_modfreqdiv_dpll_usb,
		&omap5430_cm_clkdcoldo_dpll_usb},
	{&omap5430_cm_clkmode_dpll_unipro1,
		&omap5430_cm_idlest_dpll_unipro1,
		&omap5430_cm_autoidle_dpll_unipro1,
		&omap5430_cm_clksel_dpll_unipro1,
		NULL,
		&omap5430_cm_div_m2_dpll_unipro1,
		NULL,
		&omap5430_cm_ssc_deltamstep_dpll_unipro1,
		&omap5430_cm_ssc_modfreqdiv_dpll_unipro1,
		&omap5430_cm_clkdcoldo_dpll_unipro1},
	{&omap5430_cm_clkmode_dpll_unipro2,
		&omap5430_cm_idlest_dpll_unipro2,
		&omap5430_cm_autoidle_dpll_unipro2,
		&omap5430_cm_clksel_dpll_unipro2,
		NULL,
		&omap5430_cm_div_m2_dpll_unipro2,
		NULL,
		&omap5430_cm_ssc_deltamstep_dpll_unipro2,
		&omap5430_cm_ssc_modfreqdiv_dpll_unipro2,
		&omap5430_cm_clkdcoldo_dpll_unipro2} };


const reg *dpll54xx_hsdiv_regs[DPLL54XX_ID_MAX][HSDIV54XX_ID_MAX] = {
	{NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL},
	{&omap5430_cm_div_h11_dpll_iva, &omap5430_cm_div_h12_dpll_iva,
		NULL, NULL, NULL, NULL, NULL, NULL},
	{&omap5430_cm_div_h11_dpll_core, &omap5430_cm_div_h12_dpll_core,
		&omap5430_cm_div_h13_dpll_core, &omap5430_cm_div_h14_dpll_core,
		&omap5430_cm_div_h21_dpll_core, &omap5430_cm_div_h22_dpll_core,
		&omap5430_cm_div_h23_dpll_core, &omap5430_cm_div_h24_dpll_core},
	{&omap5430_cm_div_h11_dpll_per, &omap5430_cm_div_h12_dpll_per, NULL,
		&omap5430_cm_div_h14_dpll_per, NULL, NULL, NULL, NULL},
	{NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL},
	{NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL},
	{NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL},
	{NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL} };
