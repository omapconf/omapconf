/*
 *
 * @Component			OMAPCONF
 * @Filename			ctrlmod_core_pad54xx-defs.c
 * @Description			OMAP5 CONTROL MODULE Registers Definitions
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


#include <ctrlmod_core_pad54xx-defs.h>

reg omap5430_control_core_pad_revision = {
	"CONTROL_CORE_PAD_REVISION",
	OMAP5430_CONTROL_CORE_PAD_REVISION,
	0xDEADBEEF,
	0};

reg omap5430_control_core_pad_hwinfo = {
	"CONTROL_CORE_PAD_HWINFO",
	OMAP5430_CONTROL_CORE_PAD_HWINFO,
	0xDEADBEEF,
	0};

reg omap5430_control_core_pad_sysconfig = {
	"CONTROL_CORE_PAD_SYSCONFIG",
	OMAP5430_CONTROL_CORE_PAD_SYSCONFIG,
	0xDEADBEEF,
	0};

reg omap5430_control_core_pad0_emmc_clk_pad1_emmc_cmd = {
	"CONTROL_CORE_PAD0_EMMC_CLK_PAD1_EMMC_CMD",
	OMAP5430_CONTROL_CORE_PAD0_EMMC_CLK_PAD1_EMMC_CMD,
	0xDEADBEEF,
	0};

reg omap5430_control_core_pad0_emmc_data0_pad1_emmc_data1 = {
	"CONTROL_CORE_PAD0_EMMC_DATA0_PAD1_EMMC_DATA1",
	OMAP5430_CONTROL_CORE_PAD0_EMMC_DATA0_PAD1_EMMC_DATA1,
	0xDEADBEEF,
	0};

reg omap5430_control_core_pad0_emmc_data2_pad1_emmc_data3 = {
	"CONTROL_CORE_PAD0_EMMC_DATA2_PAD1_EMMC_DATA3",
	OMAP5430_CONTROL_CORE_PAD0_EMMC_DATA2_PAD1_EMMC_DATA3,
	0xDEADBEEF,
	0};

reg omap5430_control_core_pad0_emmc_data4_pad1_emmc_data5 = {
	"CONTROL_CORE_PAD0_EMMC_DATA4_PAD1_EMMC_DATA5",
	OMAP5430_CONTROL_CORE_PAD0_EMMC_DATA4_PAD1_EMMC_DATA5,
	0xDEADBEEF,
	0};

reg omap5430_control_core_pad0_emmc_data6_pad1_emmc_data7 = {
	"CONTROL_CORE_PAD0_EMMC_DATA6_PAD1_EMMC_DATA7",
	OMAP5430_CONTROL_CORE_PAD0_EMMC_DATA6_PAD1_EMMC_DATA7,
	0xDEADBEEF,
	0};

reg omap5430_control_core_pad0_c2c_clkout0_pad1_c2c_clkout1 = {
	"CONTROL_CORE_PAD0_C2C_CLKOUT0_PAD1_C2C_CLKOUT1",
	OMAP5430_CONTROL_CORE_PAD0_C2C_CLKOUT0_PAD1_C2C_CLKOUT1,
	0xDEADBEEF,
	0};

reg omap5430_control_core_pad0_c2c_clkin0_pad1_c2c_clkin1 = {
	"CONTROL_CORE_PAD0_C2C_CLKIN0_PAD1_C2C_CLKIN1",
	OMAP5430_CONTROL_CORE_PAD0_C2C_CLKIN0_PAD1_C2C_CLKIN1,
	0xDEADBEEF,
	0};

reg omap5430_control_core_pad0_c2c_datain0_pad1_c2c_datain1 = {
	"CONTROL_CORE_PAD0_C2C_DATAIN0_PAD1_C2C_DATAIN1",
	OMAP5430_CONTROL_CORE_PAD0_C2C_DATAIN0_PAD1_C2C_DATAIN1,
	0xDEADBEEF,
	0};

reg omap5430_control_core_pad0_c2c_datain2_pad1_c2c_datain3 = {
	"CONTROL_CORE_PAD0_C2C_DATAIN2_PAD1_C2C_DATAIN3",
	OMAP5430_CONTROL_CORE_PAD0_C2C_DATAIN2_PAD1_C2C_DATAIN3,
	0xDEADBEEF,
	0};

reg omap5430_control_core_pad0_c2c_datain4_pad1_c2c_datain5 = {
	"CONTROL_CORE_PAD0_C2C_DATAIN4_PAD1_C2C_DATAIN5",
	OMAP5430_CONTROL_CORE_PAD0_C2C_DATAIN4_PAD1_C2C_DATAIN5,
	0xDEADBEEF,
	0};

reg omap5430_control_core_pad0_c2c_datain6_pad1_c2c_datain7 = {
	"CONTROL_CORE_PAD0_C2C_DATAIN6_PAD1_C2C_DATAIN7",
	OMAP5430_CONTROL_CORE_PAD0_C2C_DATAIN6_PAD1_C2C_DATAIN7,
	0xDEADBEEF,
	0};

reg omap5430_control_core_pad0_c2c_dataout0_pad1_c2c_dataout1 = {
	"CONTROL_CORE_PAD0_C2C_DATAOUT0_PAD1_C2C_DATAOUT1",
	OMAP5430_CONTROL_CORE_PAD0_C2C_DATAOUT0_PAD1_C2C_DATAOUT1,
	0xDEADBEEF,
	0};

reg omap5430_control_core_pad0_c2c_dataout2_pad1_c2c_dataout3 = {
	"CONTROL_CORE_PAD0_C2C_DATAOUT2_PAD1_C2C_DATAOUT3",
	OMAP5430_CONTROL_CORE_PAD0_C2C_DATAOUT2_PAD1_C2C_DATAOUT3,
	0xDEADBEEF,
	0};

reg omap5430_control_core_pad0_c2c_dataout4_pad1_c2c_dataout5 = {
	"CONTROL_CORE_PAD0_C2C_DATAOUT4_PAD1_C2C_DATAOUT5",
	OMAP5430_CONTROL_CORE_PAD0_C2C_DATAOUT4_PAD1_C2C_DATAOUT5,
	0xDEADBEEF,
	0};

reg omap5430_control_core_pad0_c2c_dataout6_pad1_c2c_dataout7 = {
	"CONTROL_CORE_PAD0_C2C_DATAOUT6_PAD1_C2C_DATAOUT7",
	OMAP5430_CONTROL_CORE_PAD0_C2C_DATAOUT6_PAD1_C2C_DATAOUT7,
	0xDEADBEEF,
	0};

reg omap5430_control_core_pad0_c2c_data8_pad1_c2c_data9 = {
	"CONTROL_CORE_PAD0_C2C_DATA8_PAD1_C2C_DATA9",
	OMAP5430_CONTROL_CORE_PAD0_C2C_DATA8_PAD1_C2C_DATA9,
	0xDEADBEEF,
	0};

reg omap5430_control_core_pad0_c2c_data10_pad1_c2c_data11 = {
	"CONTROL_CORE_PAD0_C2C_DATA10_PAD1_C2C_DATA11",
	OMAP5430_CONTROL_CORE_PAD0_C2C_DATA10_PAD1_C2C_DATA11,
	0xDEADBEEF,
	0};

reg omap5430_control_core_pad0_c2c_data12_pad1_c2c_data13 = {
	"CONTROL_CORE_PAD0_C2C_DATA12_PAD1_C2C_DATA13",
	OMAP5430_CONTROL_CORE_PAD0_C2C_DATA12_PAD1_C2C_DATA13,
	0xDEADBEEF,
	0};

reg omap5430_control_core_pad0_c2c_data14_pad1_c2c_data15 = {
	"CONTROL_CORE_PAD0_C2C_DATA14_PAD1_C2C_DATA15",
	OMAP5430_CONTROL_CORE_PAD0_C2C_DATA14_PAD1_C2C_DATA15,
	0xDEADBEEF,
	0};

reg omap5430_control_core_pad0_llia_wakereqout_pad1_llib_wakereqout = {
	"CONTROL_CORE_PAD0_LLIA_WAKEREQOUT_PAD1_LLIB_WAKEREQOUT",
	OMAP5430_CONTROL_CORE_PAD0_LLIA_WAKEREQOUT_PAD1_LLIB_WAKEREQOUT,
	0xDEADBEEF,
	0};

reg omap5430_control_core_pad0_hsi1_acready_pad1_hsi1_caready = {
	"CONTROL_CORE_PAD0_HSI1_ACREADY_PAD1_HSI1_CAREADY",
	OMAP5430_CONTROL_CORE_PAD0_HSI1_ACREADY_PAD1_HSI1_CAREADY,
	0xDEADBEEF,
	0};

reg omap5430_control_core_pad0_hsi1_acwake_pad1_hsi1_cawake = {
	"CONTROL_CORE_PAD0_HSI1_ACWAKE_PAD1_HSI1_CAWAKE",
	OMAP5430_CONTROL_CORE_PAD0_HSI1_ACWAKE_PAD1_HSI1_CAWAKE,
	0xDEADBEEF,
	0};

reg omap5430_control_core_pad0_hsi1_acflag_pad1_hsi1_acdata = {
	"CONTROL_CORE_PAD0_HSI1_ACFLAG_PAD1_HSI1_ACDATA",
	OMAP5430_CONTROL_CORE_PAD0_HSI1_ACFLAG_PAD1_HSI1_ACDATA,
	0xDEADBEEF,
	0};

reg omap5430_control_core_pad0_hsi1_caflag_pad1_hsi1_cadata = {
	"CONTROL_CORE_PAD0_HSI1_CAFLAG_PAD1_HSI1_CADATA",
	OMAP5430_CONTROL_CORE_PAD0_HSI1_CAFLAG_PAD1_HSI1_CADATA,
	0xDEADBEEF,
	0};

reg omap5430_control_core_pad0_uart1_tx_pad1_uart1_cts = {
	"CONTROL_CORE_PAD0_UART1_TX_PAD1_UART1_CTS",
	OMAP5430_CONTROL_CORE_PAD0_UART1_TX_PAD1_UART1_CTS,
	0xDEADBEEF,
	0};

reg omap5430_control_core_pad0_uart1_rx_pad1_uart1_rts = {
	"CONTROL_CORE_PAD0_UART1_RX_PAD1_UART1_RTS",
	OMAP5430_CONTROL_CORE_PAD0_UART1_RX_PAD1_UART1_RTS,
	0xDEADBEEF,
	0};

reg omap5430_control_core_pad0_hsi2_caready_pad1_hsi2_acready = {
	"CONTROL_CORE_PAD0_HSI2_CAREADY_PAD1_HSI2_ACREADY",
	OMAP5430_CONTROL_CORE_PAD0_HSI2_CAREADY_PAD1_HSI2_ACREADY,
	0xDEADBEEF,
	0};

reg omap5430_control_core_pad0_hsi2_cawake_pad1_hsi2_acwake = {
	"CONTROL_CORE_PAD0_HSI2_CAWAKE_PAD1_HSI2_ACWAKE",
	OMAP5430_CONTROL_CORE_PAD0_HSI2_CAWAKE_PAD1_HSI2_ACWAKE,
	0xDEADBEEF,
	0};

reg omap5430_control_core_pad0_hsi2_caflag_pad1_hsi2_cadata = {
	"CONTROL_CORE_PAD0_HSI2_CAFLAG_PAD1_HSI2_CADATA",
	OMAP5430_CONTROL_CORE_PAD0_HSI2_CAFLAG_PAD1_HSI2_CADATA,
	0xDEADBEEF,
	0};

reg omap5430_control_core_pad0_hsi2_acflag_pad1_hsi2_acdata = {
	"CONTROL_CORE_PAD0_HSI2_ACFLAG_PAD1_HSI2_ACDATA",
	OMAP5430_CONTROL_CORE_PAD0_HSI2_ACFLAG_PAD1_HSI2_ACDATA,
	0xDEADBEEF,
	0};

reg omap5430_control_core_pad0_uart2_rts_pad1_uart2_cts = {
	"CONTROL_CORE_PAD0_UART2_RTS_PAD1_UART2_CTS",
	OMAP5430_CONTROL_CORE_PAD0_UART2_RTS_PAD1_UART2_CTS,
	0xDEADBEEF,
	0};

reg omap5430_control_core_pad0_uart2_rx_pad1_uart2_tx = {
	"CONTROL_CORE_PAD0_UART2_RX_PAD1_UART2_TX",
	OMAP5430_CONTROL_CORE_PAD0_UART2_RX_PAD1_UART2_TX,
	0xDEADBEEF,
	0};

reg omap5430_control_core_pad0_usbb1_hsic_strobe_pad1_usbb1_hsic_data = {
	"CONTROL_CORE_PAD0_USBB1_HSIC_STROBE_PAD1_USBB1_HSIC_DATA",
	OMAP5430_CONTROL_CORE_PAD0_USBB1_HSIC_STROBE_PAD1_USBB1_HSIC_DATA,
	0xDEADBEEF,
	0};

reg omap5430_control_core_pad0_usbb2_hsic_strobe_pad1_usbb2_hsic_data = {
	"CONTROL_CORE_PAD0_USBB2_HSIC_STROBE_PAD1_USBB2_HSIC_DATA",
	OMAP5430_CONTROL_CORE_PAD0_USBB2_HSIC_STROBE_PAD1_USBB2_HSIC_DATA,
	0xDEADBEEF,
	0};

reg omap5430_control_core_pad0_timer10_pwm_evt_pad1_dsiporta_te0 = {
	"CONTROL_CORE_PAD0_TIMER10_PWM_EVT_PAD1_DSIPORTA_TE0",
	OMAP5430_CONTROL_CORE_PAD0_TIMER10_PWM_EVT_PAD1_DSIPORTA_TE0,
	0xDEADBEEF,
	0};

reg omap5430_control_core_pad0_dsiporta_lane0x_pad1_dsiporta_lane0y = {
	"CONTROL_CORE_PAD0_DSIPORTA_LANE0X_PAD1_DSIPORTA_LANE0Y",
	OMAP5430_CONTROL_CORE_PAD0_DSIPORTA_LANE0X_PAD1_DSIPORTA_LANE0Y,
	0xDEADBEEF,
	0};

reg omap5430_control_core_pad0_dsiporta_lane1x_pad1_dsiporta_lane1y = {
	"CONTROL_CORE_PAD0_DSIPORTA_LANE1X_PAD1_DSIPORTA_LANE1Y",
	OMAP5430_CONTROL_CORE_PAD0_DSIPORTA_LANE1X_PAD1_DSIPORTA_LANE1Y,
	0xDEADBEEF,
	0};

reg omap5430_control_core_pad0_dsiporta_lane2x_pad1_dsiporta_lane2y = {
	"CONTROL_CORE_PAD0_DSIPORTA_LANE2X_PAD1_DSIPORTA_LANE2Y",
	OMAP5430_CONTROL_CORE_PAD0_DSIPORTA_LANE2X_PAD1_DSIPORTA_LANE2Y,
	0xDEADBEEF,
	0};

reg omap5430_control_core_pad0_dsiporta_lane3x_pad1_dsiporta_lane3y = {
	"CONTROL_CORE_PAD0_DSIPORTA_LANE3X_PAD1_DSIPORTA_LANE3Y",
	OMAP5430_CONTROL_CORE_PAD0_DSIPORTA_LANE3X_PAD1_DSIPORTA_LANE3Y,
	0xDEADBEEF,
	0};

reg omap5430_control_core_pad0_dsiporta_lane4x_pad1_dsiporta_lane4y = {
	"CONTROL_CORE_PAD0_DSIPORTA_LANE4X_PAD1_DSIPORTA_LANE4Y",
	OMAP5430_CONTROL_CORE_PAD0_DSIPORTA_LANE4X_PAD1_DSIPORTA_LANE4Y,
	0xDEADBEEF,
	0};

reg omap5430_control_core_pad0_dsiportc_lane0x_pad1_dsiportc_lane0y = {
	"CONTROL_CORE_PAD0_DSIPORTC_LANE0X_PAD1_DSIPORTC_LANE0Y",
	OMAP5430_CONTROL_CORE_PAD0_DSIPORTC_LANE0X_PAD1_DSIPORTC_LANE0Y,
	0xDEADBEEF,
	0};

reg omap5430_control_core_pad0_dsiportc_lane1x_pad1_dsiportc_lane1y = {
	"CONTROL_CORE_PAD0_DSIPORTC_LANE1X_PAD1_DSIPORTC_LANE1Y",
	OMAP5430_CONTROL_CORE_PAD0_DSIPORTC_LANE1X_PAD1_DSIPORTC_LANE1Y,
	0xDEADBEEF,
	0};

reg omap5430_control_core_pad0_dsiportc_lane2x_pad1_dsiportc_lane2y = {
	"CONTROL_CORE_PAD0_DSIPORTC_LANE2X_PAD1_DSIPORTC_LANE2Y",
	OMAP5430_CONTROL_CORE_PAD0_DSIPORTC_LANE2X_PAD1_DSIPORTC_LANE2Y,
	0xDEADBEEF,
	0};

reg omap5430_control_core_pad0_dsiportc_lane3x_pad1_dsiportc_lane3y = {
	"CONTROL_CORE_PAD0_DSIPORTC_LANE3X_PAD1_DSIPORTC_LANE3Y",
	OMAP5430_CONTROL_CORE_PAD0_DSIPORTC_LANE3X_PAD1_DSIPORTC_LANE3Y,
	0xDEADBEEF,
	0};

reg omap5430_control_core_pad0_dsiportc_lane4x_pad1_dsiportc_lane4y = {
	"CONTROL_CORE_PAD0_DSIPORTC_LANE4X_PAD1_DSIPORTC_LANE4Y",
	OMAP5430_CONTROL_CORE_PAD0_DSIPORTC_LANE4X_PAD1_DSIPORTC_LANE4Y,
	0xDEADBEEF,
	0};

reg omap5430_control_core_pad0_dsiportc_te0_pad1_timer9_pwm_evt = {
	"CONTROL_CORE_PAD0_DSIPORTC_TE0_PAD1_TIMER9_PWM_EVT",
	OMAP5430_CONTROL_CORE_PAD0_DSIPORTC_TE0_PAD1_TIMER9_PWM_EVT,
	0xDEADBEEF,
	0};

reg omap5430_control_core_pad0_i2c4_scl_pad1_i2c4_sda = {
	"CONTROL_CORE_PAD0_I2C4_SCL_PAD1_I2C4_SDA",
	OMAP5430_CONTROL_CORE_PAD0_I2C4_SCL_PAD1_I2C4_SDA,
	0xDEADBEEF,
	0};

reg omap5430_control_core_pad0_mcspi2_clk_pad1_mcspi2_simo = {
	"CONTROL_CORE_PAD0_MCSPI2_CLK_PAD1_MCSPI2_SIMO",
	OMAP5430_CONTROL_CORE_PAD0_MCSPI2_CLK_PAD1_MCSPI2_SIMO,
	0xDEADBEEF,
	0};

reg omap5430_control_core_pad0_mcspi2_somi_pad1_mcspi2_cs0 = {
	"CONTROL_CORE_PAD0_MCSPI2_SOMI_PAD1_MCSPI2_CS0",
	OMAP5430_CONTROL_CORE_PAD0_MCSPI2_SOMI_PAD1_MCSPI2_CS0,
	0xDEADBEEF,
	0};

reg omap5430_control_core_pad0_rfbi_data15_pad1_rfbi_data14 = {
	"CONTROL_CORE_PAD0_RFBI_DATA15_PAD1_RFBI_DATA14",
	OMAP5430_CONTROL_CORE_PAD0_RFBI_DATA15_PAD1_RFBI_DATA14,
	0xDEADBEEF,
	0};

reg omap5430_control_core_pad0_rfbi_data13_pad1_rfbi_data12 = {
	"CONTROL_CORE_PAD0_RFBI_DATA13_PAD1_RFBI_DATA12",
	OMAP5430_CONTROL_CORE_PAD0_RFBI_DATA13_PAD1_RFBI_DATA12,
	0xDEADBEEF,
	0};

reg omap5430_control_core_pad0_rfbi_data11_pad1_rfbi_data10 = {
	"CONTROL_CORE_PAD0_RFBI_DATA11_PAD1_RFBI_DATA10",
	OMAP5430_CONTROL_CORE_PAD0_RFBI_DATA11_PAD1_RFBI_DATA10,
	0xDEADBEEF,
	0};

reg omap5430_control_core_pad0_rfbi_data9_pad1_rfbi_data8 = {
	"CONTROL_CORE_PAD0_RFBI_DATA9_PAD1_RFBI_DATA8",
	OMAP5430_CONTROL_CORE_PAD0_RFBI_DATA9_PAD1_RFBI_DATA8,
	0xDEADBEEF,
	0};

reg omap5430_control_core_pad0_rfbi_data7_pad1_rfbi_data6 = {
	"CONTROL_CORE_PAD0_RFBI_DATA7_PAD1_RFBI_DATA6",
	OMAP5430_CONTROL_CORE_PAD0_RFBI_DATA7_PAD1_RFBI_DATA6,
	0xDEADBEEF,
	0};

reg omap5430_control_core_pad0_rfbi_data5_pad1_rfbi_data4 = {
	"CONTROL_CORE_PAD0_RFBI_DATA5_PAD1_RFBI_DATA4",
	OMAP5430_CONTROL_CORE_PAD0_RFBI_DATA5_PAD1_RFBI_DATA4,
	0xDEADBEEF,
	0};

reg omap5430_control_core_pad0_rfbi_data3_pad1_rfbi_data2 = {
	"CONTROL_CORE_PAD0_RFBI_DATA3_PAD1_RFBI_DATA2",
	OMAP5430_CONTROL_CORE_PAD0_RFBI_DATA3_PAD1_RFBI_DATA2,
	0xDEADBEEF,
	0};

reg omap5430_control_core_pad0_rfbi_data1_pad1_rfbi_data0 = {
	"CONTROL_CORE_PAD0_RFBI_DATA1_PAD1_RFBI_DATA0",
	OMAP5430_CONTROL_CORE_PAD0_RFBI_DATA1_PAD1_RFBI_DATA0,
	0xDEADBEEF,
	0};

reg omap5430_control_core_pad0_rfbi_we_pad1_rfbi_cs0 = {
	"CONTROL_CORE_PAD0_RFBI_WE_PAD1_RFBI_CS0",
	OMAP5430_CONTROL_CORE_PAD0_RFBI_WE_PAD1_RFBI_CS0,
	0xDEADBEEF,
	0};

reg omap5430_control_core_pad0_rfbi_a0_pad1_rfbi_re = {
	"CONTROL_CORE_PAD0_RFBI_A0_PAD1_RFBI_RE",
	OMAP5430_CONTROL_CORE_PAD0_RFBI_A0_PAD1_RFBI_RE,
	0xDEADBEEF,
	0};

reg omap5430_control_core_pad0_rfbi_hsync0_pad1_rfbi_te_vsync0 = {
	"CONTROL_CORE_PAD0_RFBI_HSYNC0_PAD1_RFBI_TE_VSYNC0",
	OMAP5430_CONTROL_CORE_PAD0_RFBI_HSYNC0_PAD1_RFBI_TE_VSYNC0,
	0xDEADBEEF,
	0};

reg omap5430_control_core_pad0_gpio6_182_pad1_gpio6_183 = {
	"CONTROL_CORE_PAD0_GPIO6_182_PAD1_GPIO6_183",
	OMAP5430_CONTROL_CORE_PAD0_GPIO6_182_PAD1_GPIO6_183,
	0xDEADBEEF,
	0};

reg omap5430_control_core_pad0_gpio6_184_pad1_gpio6_185 = {
	"CONTROL_CORE_PAD0_GPIO6_184_PAD1_GPIO6_185",
	OMAP5430_CONTROL_CORE_PAD0_GPIO6_184_PAD1_GPIO6_185,
	0xDEADBEEF,
	0};

reg omap5430_control_core_pad0_gpio6_186_pad1_gpio6_187 = {
	"CONTROL_CORE_PAD0_GPIO6_186_PAD1_GPIO6_187",
	OMAP5430_CONTROL_CORE_PAD0_GPIO6_186_PAD1_GPIO6_187,
	0xDEADBEEF,
	0};

reg omap5430_control_core_pad0_hdmi_cec_pad1_hdmi_hpd = {
	"CONTROL_CORE_PAD0_HDMI_CEC_PAD1_HDMI_HPD",
	OMAP5430_CONTROL_CORE_PAD0_HDMI_CEC_PAD1_HDMI_HPD,
	0xDEADBEEF,
	0};

reg omap5430_control_core_pad0_hdmi_ddc_scl_pad1_hdmi_ddc_sda = {
	"CONTROL_CORE_PAD0_HDMI_DDC_SCL_PAD1_HDMI_DDC_SDA",
	OMAP5430_CONTROL_CORE_PAD0_HDMI_DDC_SCL_PAD1_HDMI_DDC_SDA,
	0xDEADBEEF,
	0};

reg omap5430_control_core_pad0_csiportc_lane0x_pad1_csiportc_lane0y = {
	"CONTROL_CORE_PAD0_CSIPORTC_LANE0X_PAD1_CSIPORTC_LANE0Y",
	OMAP5430_CONTROL_CORE_PAD0_CSIPORTC_LANE0X_PAD1_CSIPORTC_LANE0Y,
	0xDEADBEEF,
	0};

reg omap5430_control_core_pad0_csiportc_lane1x_pad1_csiportc_lane1y = {
	"CONTROL_CORE_PAD0_CSIPORTC_LANE1X_PAD1_CSIPORTC_LANE1Y",
	OMAP5430_CONTROL_CORE_PAD0_CSIPORTC_LANE1X_PAD1_CSIPORTC_LANE1Y,
	0xDEADBEEF,
	0};

reg omap5430_control_core_pad0_csiportb_lane0x_pad1_csiportb_lane0y = {
	"CONTROL_CORE_PAD0_CSIPORTB_LANE0X_PAD1_CSIPORTB_LANE0Y",
	OMAP5430_CONTROL_CORE_PAD0_CSIPORTB_LANE0X_PAD1_CSIPORTB_LANE0Y,
	0xDEADBEEF,
	0};

reg omap5430_control_core_pad0_csiportb_lane1x_pad1_csiportb_lane1y = {
	"CONTROL_CORE_PAD0_CSIPORTB_LANE1X_PAD1_CSIPORTB_LANE1Y",
	OMAP5430_CONTROL_CORE_PAD0_CSIPORTB_LANE1X_PAD1_CSIPORTB_LANE1Y,
	0xDEADBEEF,
	0};

reg omap5430_control_core_pad0_csiportb_lane2x_pad1_csiportb_lane2y = {
	"CONTROL_CORE_PAD0_CSIPORTB_LANE2X_PAD1_CSIPORTB_LANE2Y",
	OMAP5430_CONTROL_CORE_PAD0_CSIPORTB_LANE2X_PAD1_CSIPORTB_LANE2Y,
	0xDEADBEEF,
	0};

reg omap5430_control_core_pad0_csiporta_lane0x_pad1_csiporta_lane0y = {
	"CONTROL_CORE_PAD0_CSIPORTA_LANE0X_PAD1_CSIPORTA_LANE0Y",
	OMAP5430_CONTROL_CORE_PAD0_CSIPORTA_LANE0X_PAD1_CSIPORTA_LANE0Y,
	0xDEADBEEF,
	0};

reg omap5430_control_core_pad0_csiporta_lane1x_pad1_csiporta_lane1y = {
	"CONTROL_CORE_PAD0_CSIPORTA_LANE1X_PAD1_CSIPORTA_LANE1Y",
	OMAP5430_CONTROL_CORE_PAD0_CSIPORTA_LANE1X_PAD1_CSIPORTA_LANE1Y,
	0xDEADBEEF,
	0};

reg omap5430_control_core_pad0_csiporta_lane2x_pad1_csiporta_lane2y = {
	"CONTROL_CORE_PAD0_CSIPORTA_LANE2X_PAD1_CSIPORTA_LANE2Y",
	OMAP5430_CONTROL_CORE_PAD0_CSIPORTA_LANE2X_PAD1_CSIPORTA_LANE2Y,
	0xDEADBEEF,
	0};

reg omap5430_control_core_pad0_csiporta_lane3x_pad1_csiporta_lane3y = {
	"CONTROL_CORE_PAD0_CSIPORTA_LANE3X_PAD1_CSIPORTA_LANE3Y",
	OMAP5430_CONTROL_CORE_PAD0_CSIPORTA_LANE3X_PAD1_CSIPORTA_LANE3Y,
	0xDEADBEEF,
	0};

reg omap5430_control_core_pad0_csiporta_lane4x_pad1_csiporta_lane4y = {
	"CONTROL_CORE_PAD0_CSIPORTA_LANE4X_PAD1_CSIPORTA_LANE4Y",
	OMAP5430_CONTROL_CORE_PAD0_CSIPORTA_LANE4X_PAD1_CSIPORTA_LANE4Y,
	0xDEADBEEF,
	0};

reg omap5430_control_core_pad0_cam_shutter_pad1_cam_strobe = {
	"CONTROL_CORE_PAD0_CAM_SHUTTER_PAD1_CAM_STROBE",
	OMAP5430_CONTROL_CORE_PAD0_CAM_SHUTTER_PAD1_CAM_STROBE,
	0xDEADBEEF,
	0};

reg omap5430_control_core_pad0_cam_globalreset_pad1_timer11_pwm_evt = {
	"CONTROL_CORE_PAD0_CAM_GLOBALRESET_PAD1_TIMER11_PWM_EVT",
	OMAP5430_CONTROL_CORE_PAD0_CAM_GLOBALRESET_PAD1_TIMER11_PWM_EVT,
	0xDEADBEEF,
	0};

reg omap5430_control_core_pad0_timer5_pwm_evt_pad1_timer6_pwm_evt = {
	"CONTROL_CORE_PAD0_TIMER5_PWM_EVT_PAD1_TIMER6_PWM_EVT",
	OMAP5430_CONTROL_CORE_PAD0_TIMER5_PWM_EVT_PAD1_TIMER6_PWM_EVT,
	0xDEADBEEF,
	0};

reg omap5430_control_core_pad0_timer8_pwm_evt_pad1_i2c3_scl = {
	"CONTROL_CORE_PAD0_TIMER8_PWM_EVT_PAD1_I2C3_SCL",
	OMAP5430_CONTROL_CORE_PAD0_TIMER8_PWM_EVT_PAD1_I2C3_SCL,
	0xDEADBEEF,
	0};

reg omap5430_control_core_pad0_i2c3_sda_pad1_gpio8_233 = {
	"CONTROL_CORE_PAD0_I2C3_SDA_PAD1_GPIO8_233",
	OMAP5430_CONTROL_CORE_PAD0_I2C3_SDA_PAD1_GPIO8_233,
	0xDEADBEEF,
	0};

reg omap5430_control_core_pad0_gpio8_234_pad1_abe_clks = {
	"CONTROL_CORE_PAD0_GPIO8_234_PAD1_ABE_CLKS",
	OMAP5430_CONTROL_CORE_PAD0_GPIO8_234_PAD1_ABE_CLKS,
	0xDEADBEEF,
	0};

reg omap5430_control_core_pad0_abedmic_din1_pad1_abedmic_din2 = {
	"CONTROL_CORE_PAD0_ABEDMIC_DIN1_PAD1_ABEDMIC_DIN2",
	OMAP5430_CONTROL_CORE_PAD0_ABEDMIC_DIN1_PAD1_ABEDMIC_DIN2,
	0xDEADBEEF,
	0};

reg omap5430_control_core_pad0_abedmic_din3_pad1_abedmic_clk1 = {
	"CONTROL_CORE_PAD0_ABEDMIC_DIN3_PAD1_ABEDMIC_CLK1",
	OMAP5430_CONTROL_CORE_PAD0_ABEDMIC_DIN3_PAD1_ABEDMIC_CLK1,
	0xDEADBEEF,
	0};

reg omap5430_control_core_pad0_abedmic_clk2_pad1_abedmic_clk3 = {
	"CONTROL_CORE_PAD0_ABEDMIC_CLK2_PAD1_ABEDMIC_CLK3",
	OMAP5430_CONTROL_CORE_PAD0_ABEDMIC_CLK2_PAD1_ABEDMIC_CLK3,
	0xDEADBEEF,
	0};

reg omap5430_control_core_pad0_abeslimbus1_clock_pad1_abeslimbus1_data = {
	"CONTROL_CORE_PAD0_ABESLIMBUS1_CLOCK_PAD1_ABESLIMBUS1_DATA",
	OMAP5430_CONTROL_CORE_PAD0_ABESLIMBUS1_CLOCK_PAD1_ABESLIMBUS1_DATA,
	0xDEADBEEF,
	0};

reg omap5430_control_core_pad0_abemcbsp2_dr_pad1_abemcbsp2_dx = {
	"CONTROL_CORE_PAD0_ABEMCBSP2_DR_PAD1_ABEMCBSP2_DX",
	OMAP5430_CONTROL_CORE_PAD0_ABEMCBSP2_DR_PAD1_ABEMCBSP2_DX,
	0xDEADBEEF,
	0};

reg omap5430_control_core_pad0_abemcbsp2_fsx_pad1_abemcbsp2_clkx = {
	"CONTROL_CORE_PAD0_ABEMCBSP2_FSX_PAD1_ABEMCBSP2_CLKX",
	OMAP5430_CONTROL_CORE_PAD0_ABEMCBSP2_FSX_PAD1_ABEMCBSP2_CLKX,
	0xDEADBEEF,
	0};

reg omap5430_control_core_pad0_abemcpdm_ul_data_pad1_abemcpdm_dl_data = {
	"CONTROL_CORE_PAD0_ABEMCPDM_UL_DATA_PAD1_ABEMCPDM_DL_DATA",
	OMAP5430_CONTROL_CORE_PAD0_ABEMCPDM_UL_DATA_PAD1_ABEMCPDM_DL_DATA,
	0xDEADBEEF,
	0};

reg omap5430_control_core_pad0_abemcpdm_frame_pad1_abemcpdm_lb_clk = {
	"CONTROL_CORE_PAD0_ABEMCPDM_FRAME_PAD1_ABEMCPDM_LB_CLK",
	OMAP5430_CONTROL_CORE_PAD0_ABEMCPDM_FRAME_PAD1_ABEMCPDM_LB_CLK,
	0xDEADBEEF,
	0};

reg omap5430_control_core_pad0_wlsdio_clk_pad1_wlsdio_cmd = {
	"CONTROL_CORE_PAD0_WLSDIO_CLK_PAD1_WLSDIO_CMD",
	OMAP5430_CONTROL_CORE_PAD0_WLSDIO_CLK_PAD1_WLSDIO_CMD,
	0xDEADBEEF,
	0};

reg omap5430_control_core_pad0_wlsdio_data0_pad1_wlsdio_data1 = {
	"CONTROL_CORE_PAD0_WLSDIO_DATA0_PAD1_WLSDIO_DATA1",
	OMAP5430_CONTROL_CORE_PAD0_WLSDIO_DATA0_PAD1_WLSDIO_DATA1,
	0xDEADBEEF,
	0};

reg omap5430_control_core_pad0_wlsdio_data2_pad1_wlsdio_data3 = {
	"CONTROL_CORE_PAD0_WLSDIO_DATA2_PAD1_WLSDIO_DATA3",
	OMAP5430_CONTROL_CORE_PAD0_WLSDIO_DATA2_PAD1_WLSDIO_DATA3,
	0xDEADBEEF,
	0};

reg omap5430_control_core_pad0_uart5_rx_pad1_uart5_tx = {
	"CONTROL_CORE_PAD0_UART5_RX_PAD1_UART5_TX",
	OMAP5430_CONTROL_CORE_PAD0_UART5_RX_PAD1_UART5_TX,
	0xDEADBEEF,
	0};

reg omap5430_control_core_pad0_uart5_cts_pad1_uart5_rts = {
	"CONTROL_CORE_PAD0_UART5_CTS_PAD1_UART5_RTS",
	OMAP5430_CONTROL_CORE_PAD0_UART5_CTS_PAD1_UART5_RTS,
	0xDEADBEEF,
	0};

reg omap5430_control_core_pad0_i2c2_scl_pad1_i2c2_sda = {
	"CONTROL_CORE_PAD0_I2C2_SCL_PAD1_I2C2_SDA",
	OMAP5430_CONTROL_CORE_PAD0_I2C2_SCL_PAD1_I2C2_SDA,
	0xDEADBEEF,
	0};

reg omap5430_control_core_pad0_mcspi1_clk_pad1_mcspi1_somi = {
	"CONTROL_CORE_PAD0_MCSPI1_CLK_PAD1_MCSPI1_SOMI",
	OMAP5430_CONTROL_CORE_PAD0_MCSPI1_CLK_PAD1_MCSPI1_SOMI,
	0xDEADBEEF,
	0};

reg omap5430_control_core_pad0_mcspi1_simo_pad1_mcspi1_cs0 = {
	"CONTROL_CORE_PAD0_MCSPI1_SIMO_PAD1_MCSPI1_CS0",
	OMAP5430_CONTROL_CORE_PAD0_MCSPI1_SIMO_PAD1_MCSPI1_CS0,
	0xDEADBEEF,
	0};

reg omap5430_control_core_pad0_mcspi1_cs1_pad1_i2c5_scl = {
	"CONTROL_CORE_PAD0_MCSPI1_CS1_PAD1_I2C5_SCL",
	OMAP5430_CONTROL_CORE_PAD0_MCSPI1_CS1_PAD1_I2C5_SCL,
	0xDEADBEEF,
	0};

reg omap5430_control_core_pad0_i2c5_sda_pad1_perslimbus2_clock = {
	"CONTROL_CORE_PAD0_I2C5_SDA_PAD1_PERSLIMBUS2_CLOCK",
	OMAP5430_CONTROL_CORE_PAD0_I2C5_SDA_PAD1_PERSLIMBUS2_CLOCK,
	0xDEADBEEF,
	0};

reg omap5430_control_core_pad0_perslimbus2_data_pad1_uart6_tx = {
	"CONTROL_CORE_PAD0_PERSLIMBUS2_DATA_PAD1_UART6_TX",
	OMAP5430_CONTROL_CORE_PAD0_PERSLIMBUS2_DATA_PAD1_UART6_TX,
	0xDEADBEEF,
	0};

reg omap5430_control_core_pad0_i2c5_sda_pad1_gpio5_145 = {
	"CONTROL_CORE_PAD0_I2C5_SDA_PAD1_GPIO5_145",
	OMAP5430_CONTROL_CORE_PAD0_I2C5_SDA_PAD1_GPIO5_145,
	0xDEADBEEF,
	0};

reg omap5430_control_core_pad0_gpio5_146_pad1_uart6_tx = {
	"CONTROL_CORE_PAD0_GPIO5_146_PAD1_UART6_TX",
	OMAP5430_CONTROL_CORE_PAD0_GPIO5_146_PAD1_UART6_TX,
	0xDEADBEEF,
	0};

reg omap5430_control_core_pad0_uart6_rx_pad1_uart6_cts = {
	"CONTROL_CORE_PAD0_UART6_RX_PAD1_UART6_CTS",
	OMAP5430_CONTROL_CORE_PAD0_UART6_RX_PAD1_UART6_CTS,
	0xDEADBEEF,
	0};

reg omap5430_control_core_pad0_uart6_rts_pad1_uart3_cts_rctx = {
	"CONTROL_CORE_PAD0_UART6_RTS_PAD1_UART3_CTS_RCTX",
	OMAP5430_CONTROL_CORE_PAD0_UART6_RTS_PAD1_UART3_CTS_RCTX,
	0xDEADBEEF,
	0};

reg omap5430_control_core_pad0_uart3_rts_irsd_pad1_uart3_tx_irtx = {
	"CONTROL_CORE_PAD0_UART3_RTS_IRSD_PAD1_UART3_TX_IRTX",
	OMAP5430_CONTROL_CORE_PAD0_UART3_RTS_IRSD_PAD1_UART3_TX_IRTX,
	0xDEADBEEF,
	0};

reg omap5430_control_core_pad0_uart3_rx_irrx_pad1_usbb3_hsic_strobe = {
	"CONTROL_CORE_PAD0_UART3_RX_IRRX_PAD1_USBB3_HSIC_STROBE",
	OMAP5430_CONTROL_CORE_PAD0_UART3_RX_IRRX_PAD1_USBB3_HSIC_STROBE,
	0xDEADBEEF,
	0};

reg omap5430_control_core_pad0_usbb3_hsic_data_pad1_sdcard_clk = {
	"CONTROL_CORE_PAD0_USBB3_HSIC_DATA_PAD1_SDCARD_CLK",
	OMAP5430_CONTROL_CORE_PAD0_USBB3_HSIC_DATA_PAD1_SDCARD_CLK,
	0xDEADBEEF,
	0};

reg omap5430_control_core_pad0_sdcard_cmd_pad1_sdcard_data2 = {
	"CONTROL_CORE_PAD0_SDCARD_CMD_PAD1_SDCARD_DATA2",
	OMAP5430_CONTROL_CORE_PAD0_SDCARD_CMD_PAD1_SDCARD_DATA2,
	0xDEADBEEF,
	0};

reg omap5430_control_core_pad0_sdcard_data3_pad1_sdcard_data0 = {
	"CONTROL_CORE_PAD0_SDCARD_DATA3_PAD1_SDCARD_DATA0",
	OMAP5430_CONTROL_CORE_PAD0_SDCARD_DATA3_PAD1_SDCARD_DATA0,
	0xDEADBEEF,
	0};

reg omap5430_control_core_pad0_sdcard_data1_pad1_usbd0_hs_dp = {
	"CONTROL_CORE_PAD0_SDCARD_DATA1_PAD1_USBD0_HS_DP",
	OMAP5430_CONTROL_CORE_PAD0_SDCARD_DATA1_PAD1_USBD0_HS_DP,
	0xDEADBEEF,
	0};

reg omap5430_control_core_pad0_usbd0_hs_dm_pad1_i2c1_pmic_scl = {
	"CONTROL_CORE_PAD0_USBD0_HS_DM_PAD1_I2C1_PMIC_SCL",
	OMAP5430_CONTROL_CORE_PAD0_USBD0_HS_DM_PAD1_I2C1_PMIC_SCL,
	0xDEADBEEF,
	0};

reg omap5430_control_core_pad0_i2c1_pmic_sda_pad1_usbd0_ss_rx = {
	"CONTROL_CORE_PAD0_I2C1_PMIC_SDA_PAD1_USBD0_SS_RX",
	OMAP5430_CONTROL_CORE_PAD0_I2C1_PMIC_SDA_PAD1_USBD0_SS_RX,
	0xDEADBEEF,
	0};

reg omap5430_control_padconf_wakeupevent_0 = {
	"CONTROL_PADCONF_WAKEUPEVENT_0",
	OMAP5430_CONTROL_PADCONF_WAKEUPEVENT_0,
	0xDEADBEEF,
	0};

reg omap5430_control_padconf_wakeupevent_1 = {
	"CONTROL_PADCONF_WAKEUPEVENT_1",
	OMAP5430_CONTROL_PADCONF_WAKEUPEVENT_1,
	0xDEADBEEF,
	0};

reg omap5430_control_padconf_wakeupevent_2 = {
	"CONTROL_PADCONF_WAKEUPEVENT_2",
	OMAP5430_CONTROL_PADCONF_WAKEUPEVENT_2,
	0xDEADBEEF,
	0};

reg omap5430_control_padconf_wakeupevent_3 = {
	"CONTROL_PADCONF_WAKEUPEVENT_3",
	OMAP5430_CONTROL_PADCONF_WAKEUPEVENT_3,
	0xDEADBEEF,
	0};

reg omap5430_control_padconf_wakeupevent_4 = {
	"CONTROL_PADCONF_WAKEUPEVENT_4",
	OMAP5430_CONTROL_PADCONF_WAKEUPEVENT_4,
	0xDEADBEEF,
	0};

reg omap5430_control_padconf_wakeupevent_5 = {
	"CONTROL_PADCONF_WAKEUPEVENT_5",
	OMAP5430_CONTROL_PADCONF_WAKEUPEVENT_5,
	0xDEADBEEF,
	0};

reg omap5430_control_padconf_wakeupevent_6 = {
	"CONTROL_PADCONF_WAKEUPEVENT_6",
	OMAP5430_CONTROL_PADCONF_WAKEUPEVENT_6,
	0xDEADBEEF,
	0};

reg omap5430_control_padconf_global = {
	"CONTROL_PADCONF_GLOBAL",
	OMAP5430_CONTROL_PADCONF_GLOBAL,
	0xDEADBEEF,
	0};

reg omap5430_control_padconf_mode = {
	"CONTROL_PADCONF_MODE",
	OMAP5430_CONTROL_PADCONF_MODE,
	0xDEADBEEF,
	0};

reg omap5430_control_smart1io_padconf_0 = {
	"CONTROL_SMART1IO_PADCONF_0",
	OMAP5430_CONTROL_SMART1IO_PADCONF_0,
	0xDEADBEEF,
	0};

reg omap5430_control_smart1io_padconf_1 = {
	"CONTROL_SMART1IO_PADCONF_1",
	OMAP5430_CONTROL_SMART1IO_PADCONF_1,
	0xDEADBEEF,
	0};

reg omap5430_control_smart1io_padconf_2 = {
	"CONTROL_SMART1IO_PADCONF_2",
	OMAP5430_CONTROL_SMART1IO_PADCONF_2,
	0xDEADBEEF,
	0};

reg omap5430_control_smart2io_padconf_0 = {
	"CONTROL_SMART2IO_PADCONF_0",
	OMAP5430_CONTROL_SMART2IO_PADCONF_0,
	0xDEADBEEF,
	0};

reg omap5430_control_smart2io_padconf_1 = {
	"CONTROL_SMART2IO_PADCONF_1",
	OMAP5430_CONTROL_SMART2IO_PADCONF_1,
	0xDEADBEEF,
	0};

reg omap5430_control_smart2io_padconf_2 = {
	"CONTROL_SMART2IO_PADCONF_2",
	OMAP5430_CONTROL_SMART2IO_PADCONF_2,
	0xDEADBEEF,
	0};

reg omap5430_control_smart3io_padconf_0 = {
	"CONTROL_SMART3IO_PADCONF_0",
	OMAP5430_CONTROL_SMART3IO_PADCONF_0,
	0xDEADBEEF,
	0};

reg omap5430_control_smart3io_padconf_1 = {
	"CONTROL_SMART3IO_PADCONF_1",
	OMAP5430_CONTROL_SMART3IO_PADCONF_1,
	0xDEADBEEF,
	0};

reg omap5430_control_pbias = {
	"CONTROL_PBIAS",
	OMAP5430_CONTROL_PBIAS,
	0xDEADBEEF,
	0};

reg omap5430_control_i2c_0 = {
	"CONTROL_I2C_0",
	OMAP5430_CONTROL_I2C_0,
	0xDEADBEEF,
	0};

reg omap5430_control_camera_rx = {
	"CONTROL_CAMERA_RX",
	OMAP5430_CONTROL_CAMERA_RX,
	0xDEADBEEF,
	0};

reg omap5430_control_hdmi_tx_phy = {
	"CONTROL_HDMI_TX_PHY",
	OMAP5430_CONTROL_HDMI_TX_PHY,
	0xDEADBEEF,
	0};

reg omap5430_control_uniportm = {
	"CONTROL_UNIPORTM",
	OMAP5430_CONTROL_UNIPORTM,
	0xDEADBEEF,
	0};

reg omap5430_control_dsiphy = {
	"CONTROL_DSIPHY",
	OMAP5430_CONTROL_DSIPHY,
	0xDEADBEEF,
	0};

reg omap5430_control_mcbsplp = {
	"CONTROL_MCBSPLP",
	OMAP5430_CONTROL_MCBSPLP,
	0xDEADBEEF,
	0};

reg omap5430_control_usb2phycore = {
	"CONTROL_USB2PHYCORE",
	OMAP5430_CONTROL_USB2PHYCORE,
	0xDEADBEEF,
	0};

reg omap5430_control_hdmi_1 = {
	"CONTROL_HDMI_1",
	OMAP5430_CONTROL_HDMI_1,
	0xDEADBEEF,
	0};

reg omap5430_control_hsi = {
	"CONTROL_HSI",
	OMAP5430_CONTROL_HSI,
	0xDEADBEEF,
	0};

reg omap5430_control_ddr3ch1_0 = {
	"CONTROL_DDR3CH1_0",
	OMAP5430_CONTROL_DDR3CH1_0,
	0xDEADBEEF,
	0};

reg omap5430_control_ddr3ch2_0 = {
	"CONTROL_DDR3CH2_0",
	OMAP5430_CONTROL_DDR3CH2_0,
	0xDEADBEEF,
	0};

reg omap5430_control_ddrch1_0 = {
	"CONTROL_DDRCH1_0",
	OMAP5430_CONTROL_DDRCH1_0,
	0xDEADBEEF,
	0};

reg omap5430_control_ddrch1_1 = {
	"CONTROL_DDRCH1_1",
	OMAP5430_CONTROL_DDRCH1_1,
	0xDEADBEEF,
	0};

reg omap5430_control_ddrch2_0 = {
	"CONTROL_DDRCH2_0",
	OMAP5430_CONTROL_DDRCH2_0,
	0xDEADBEEF,
	0};

reg omap5430_control_ddrch2_1 = {
	"CONTROL_DDRCH2_1",
	OMAP5430_CONTROL_DDRCH2_1,
	0xDEADBEEF,
	0};

reg omap5430_control_lpddr2ch1_0 = {
	"CONTROL_LPDDR2CH1_0",
	OMAP5430_CONTROL_LPDDR2CH1_0,
	0xDEADBEEF,
	0};

reg omap5430_control_lpddr2ch1_1 = {
	"CONTROL_LPDDR2CH1_1",
	OMAP5430_CONTROL_LPDDR2CH1_1,
	0xDEADBEEF,
	0};

reg omap5430_control_ddrio_0 = {
	"CONTROL_DDRIO_0",
	OMAP5430_CONTROL_DDRIO_0,
	0xDEADBEEF,
	0};

reg omap5430_control_ddrio_1 = {
	"CONTROL_DDRIO_1",
	OMAP5430_CONTROL_DDRIO_1,
	0xDEADBEEF,
	0};

reg omap5430_control_ddrio_2 = {
	"CONTROL_DDRIO_2",
	OMAP5430_CONTROL_DDRIO_2,
	0xDEADBEEF,
	0};

reg omap5430_control_hyst_1 = {
	"CONTROL_HYST_1",
	OMAP5430_CONTROL_HYST_1,
	0xDEADBEEF,
	0};

reg omap5430_control_usbb_hsic_control = {
	"CONTROL_USBB_HSIC_CONTROL",
	OMAP5430_CONTROL_USBB_HSIC_CONTROL,
	0xDEADBEEF,
	0};

reg omap5430_control_c2c = {
	"CONTROL_C2C",
	OMAP5430_CONTROL_C2C,
	0xDEADBEEF,
	0};

reg omap5430_control_core_control_spare_rw = {
	"CONTROL_CORE_CONTROL_SPARE_RW",
	OMAP5430_CONTROL_CORE_CONTROL_SPARE_RW,
	0xDEADBEEF,
	0};

reg omap5430_control_core_control_spare_r = {
	"CONTROL_CORE_CONTROL_SPARE_R",
	OMAP5430_CONTROL_CORE_CONTROL_SPARE_R,
	0xDEADBEEF,
	0};

reg omap5430_control_core_control_spare_r_c0 = {
	"CONTROL_CORE_CONTROL_SPARE_R_C0",
	OMAP5430_CONTROL_CORE_CONTROL_SPARE_R_C0,
	0xDEADBEEF,
	0};

reg omap5430_control_srcomp_north_side = {
	"CONTROL_SRCOMP_NORTH_SIDE",
	OMAP5430_CONTROL_SRCOMP_NORTH_SIDE,
	0xDEADBEEF,
	0};

reg omap5430_control_srcomp_south_side = {
	"CONTROL_SRCOMP_SOUTH_SIDE",
	OMAP5430_CONTROL_SRCOMP_SOUTH_SIDE,
	0xDEADBEEF,
	0};

reg omap5430_control_srcomp_east_side = {
	"CONTROL_SRCOMP_EAST_SIDE",
	OMAP5430_CONTROL_SRCOMP_EAST_SIDE,
	0xDEADBEEF,
	0};

reg omap5430_control_srcomp_west_side = {
	"CONTROL_SRCOMP_WEST_SIDE",
	OMAP5430_CONTROL_SRCOMP_WEST_SIDE,
	0xDEADBEEF,
	0};

reg omap5430_control_srcomp_code_latch = {
	"CONTROL_SRCOMP_CODE_LATCH",
	OMAP5430_CONTROL_SRCOMP_CODE_LATCH,
	0xDEADBEEF,
	0};

reg omap5430_control_ddrio_ext_0 = {
	"CONTROL_DDRIO_EXT_0",
	OMAP5430_CONTROL_DDRIO_EXT_0,
	0xDEADBEEF,
	0};

reg *omap5430es1_ctrl_module_core_pad_mod[OMAP5430_CTRL_MODULE_CORE_PAD_MOD_REGCOUNT + 1] = {
	&omap5430_control_core_pad_revision,
	&omap5430_control_core_pad_hwinfo,
	&omap5430_control_core_pad_sysconfig,
	&omap5430_control_core_pad0_emmc_clk_pad1_emmc_cmd,
	&omap5430_control_core_pad0_emmc_data0_pad1_emmc_data1,
	&omap5430_control_core_pad0_emmc_data2_pad1_emmc_data3,
	&omap5430_control_core_pad0_emmc_data4_pad1_emmc_data5,
	&omap5430_control_core_pad0_emmc_data6_pad1_emmc_data7,
	&omap5430_control_core_pad0_c2c_clkout0_pad1_c2c_clkout1,
	&omap5430_control_core_pad0_c2c_clkin0_pad1_c2c_clkin1,
	&omap5430_control_core_pad0_c2c_datain0_pad1_c2c_datain1,
	&omap5430_control_core_pad0_c2c_datain2_pad1_c2c_datain3,
	&omap5430_control_core_pad0_c2c_datain4_pad1_c2c_datain5,
	&omap5430_control_core_pad0_c2c_datain6_pad1_c2c_datain7,
	&omap5430_control_core_pad0_c2c_dataout0_pad1_c2c_dataout1,
	&omap5430_control_core_pad0_c2c_dataout2_pad1_c2c_dataout3,
	&omap5430_control_core_pad0_c2c_dataout4_pad1_c2c_dataout5,
	&omap5430_control_core_pad0_c2c_dataout6_pad1_c2c_dataout7,
	&omap5430_control_core_pad0_c2c_data8_pad1_c2c_data9,
	&omap5430_control_core_pad0_c2c_data10_pad1_c2c_data11,
	&omap5430_control_core_pad0_c2c_data12_pad1_c2c_data13,
	&omap5430_control_core_pad0_c2c_data14_pad1_c2c_data15,
	&omap5430_control_core_pad0_llia_wakereqout_pad1_llib_wakereqout,
	&omap5430_control_core_pad0_hsi1_acready_pad1_hsi1_caready,
	&omap5430_control_core_pad0_hsi1_acwake_pad1_hsi1_cawake,
	&omap5430_control_core_pad0_hsi1_acflag_pad1_hsi1_acdata,
	&omap5430_control_core_pad0_hsi1_caflag_pad1_hsi1_cadata,
	&omap5430_control_core_pad0_uart1_tx_pad1_uart1_cts,
	&omap5430_control_core_pad0_uart1_rx_pad1_uart1_rts,
	&omap5430_control_core_pad0_hsi2_caready_pad1_hsi2_acready,
	&omap5430_control_core_pad0_hsi2_cawake_pad1_hsi2_acwake,
	&omap5430_control_core_pad0_hsi2_caflag_pad1_hsi2_cadata,
	&omap5430_control_core_pad0_hsi2_acflag_pad1_hsi2_acdata,
	&omap5430_control_core_pad0_uart2_rts_pad1_uart2_cts,
	&omap5430_control_core_pad0_uart2_rx_pad1_uart2_tx,
	&omap5430_control_core_pad0_usbb1_hsic_strobe_pad1_usbb1_hsic_data,
	&omap5430_control_core_pad0_usbb2_hsic_strobe_pad1_usbb2_hsic_data,
	&omap5430_control_core_pad0_timer10_pwm_evt_pad1_dsiporta_te0,
	&omap5430_control_core_pad0_dsiporta_lane0x_pad1_dsiporta_lane0y,
	&omap5430_control_core_pad0_dsiporta_lane1x_pad1_dsiporta_lane1y,
	&omap5430_control_core_pad0_dsiporta_lane2x_pad1_dsiporta_lane2y,
	&omap5430_control_core_pad0_dsiporta_lane3x_pad1_dsiporta_lane3y,
	&omap5430_control_core_pad0_dsiporta_lane4x_pad1_dsiporta_lane4y,
	&omap5430_control_core_pad0_dsiportc_lane0x_pad1_dsiportc_lane0y,
	&omap5430_control_core_pad0_dsiportc_lane1x_pad1_dsiportc_lane1y,
	&omap5430_control_core_pad0_dsiportc_lane2x_pad1_dsiportc_lane2y,
	&omap5430_control_core_pad0_dsiportc_lane3x_pad1_dsiportc_lane3y,
	&omap5430_control_core_pad0_dsiportc_lane4x_pad1_dsiportc_lane4y,
	&omap5430_control_core_pad0_dsiportc_te0_pad1_timer9_pwm_evt,
	&omap5430_control_core_pad0_i2c4_scl_pad1_i2c4_sda,
	&omap5430_control_core_pad0_mcspi2_clk_pad1_mcspi2_simo,
	&omap5430_control_core_pad0_mcspi2_somi_pad1_mcspi2_cs0,
	&omap5430_control_core_pad0_rfbi_data15_pad1_rfbi_data14,
	&omap5430_control_core_pad0_rfbi_data13_pad1_rfbi_data12,
	&omap5430_control_core_pad0_rfbi_data11_pad1_rfbi_data10,
	&omap5430_control_core_pad0_rfbi_data9_pad1_rfbi_data8,
	&omap5430_control_core_pad0_rfbi_data7_pad1_rfbi_data6,
	&omap5430_control_core_pad0_rfbi_data5_pad1_rfbi_data4,
	&omap5430_control_core_pad0_rfbi_data3_pad1_rfbi_data2,
	&omap5430_control_core_pad0_rfbi_data1_pad1_rfbi_data0,
	&omap5430_control_core_pad0_rfbi_we_pad1_rfbi_cs0,
	&omap5430_control_core_pad0_rfbi_a0_pad1_rfbi_re,
	&omap5430_control_core_pad0_rfbi_hsync0_pad1_rfbi_te_vsync0,
	&omap5430_control_core_pad0_gpio6_182_pad1_gpio6_183,
	&omap5430_control_core_pad0_gpio6_184_pad1_gpio6_185,
	&omap5430_control_core_pad0_gpio6_186_pad1_gpio6_187,
	&omap5430_control_core_pad0_hdmi_cec_pad1_hdmi_hpd,
	&omap5430_control_core_pad0_hdmi_ddc_scl_pad1_hdmi_ddc_sda,
	&omap5430_control_core_pad0_csiportc_lane0x_pad1_csiportc_lane0y,
	&omap5430_control_core_pad0_csiportc_lane1x_pad1_csiportc_lane1y,
	&omap5430_control_core_pad0_csiportb_lane0x_pad1_csiportb_lane0y,
	&omap5430_control_core_pad0_csiportb_lane1x_pad1_csiportb_lane1y,
	&omap5430_control_core_pad0_csiportb_lane2x_pad1_csiportb_lane2y,
	&omap5430_control_core_pad0_csiporta_lane0x_pad1_csiporta_lane0y,
	&omap5430_control_core_pad0_csiporta_lane1x_pad1_csiporta_lane1y,
	&omap5430_control_core_pad0_csiporta_lane2x_pad1_csiporta_lane2y,
	&omap5430_control_core_pad0_csiporta_lane3x_pad1_csiporta_lane3y,
	&omap5430_control_core_pad0_csiporta_lane4x_pad1_csiporta_lane4y,
	&omap5430_control_core_pad0_cam_shutter_pad1_cam_strobe,
	&omap5430_control_core_pad0_cam_globalreset_pad1_timer11_pwm_evt,
	&omap5430_control_core_pad0_timer5_pwm_evt_pad1_timer6_pwm_evt,
	&omap5430_control_core_pad0_timer8_pwm_evt_pad1_i2c3_scl,
	&omap5430_control_core_pad0_i2c3_sda_pad1_gpio8_233,
	&omap5430_control_core_pad0_gpio8_234_pad1_abe_clks,
	&omap5430_control_core_pad0_abedmic_din1_pad1_abedmic_din2,
	&omap5430_control_core_pad0_abedmic_din3_pad1_abedmic_clk1,
	&omap5430_control_core_pad0_abedmic_clk2_pad1_abedmic_clk3,
	&omap5430_control_core_pad0_abeslimbus1_clock_pad1_abeslimbus1_data,
	&omap5430_control_core_pad0_abemcbsp2_dr_pad1_abemcbsp2_dx,
	&omap5430_control_core_pad0_abemcbsp2_fsx_pad1_abemcbsp2_clkx,
	&omap5430_control_core_pad0_abemcpdm_ul_data_pad1_abemcpdm_dl_data,
	&omap5430_control_core_pad0_abemcpdm_frame_pad1_abemcpdm_lb_clk,
	&omap5430_control_core_pad0_wlsdio_clk_pad1_wlsdio_cmd,
	&omap5430_control_core_pad0_wlsdio_data0_pad1_wlsdio_data1,
	&omap5430_control_core_pad0_wlsdio_data2_pad1_wlsdio_data3,
	&omap5430_control_core_pad0_uart5_rx_pad1_uart5_tx,
	&omap5430_control_core_pad0_uart5_cts_pad1_uart5_rts,
	&omap5430_control_core_pad0_i2c2_scl_pad1_i2c2_sda,
	&omap5430_control_core_pad0_mcspi1_clk_pad1_mcspi1_somi,
	&omap5430_control_core_pad0_mcspi1_simo_pad1_mcspi1_cs0,
	&omap5430_control_core_pad0_mcspi1_cs1_pad1_i2c5_scl,
	&omap5430_control_core_pad0_i2c5_sda_pad1_perslimbus2_clock,
	&omap5430_control_core_pad0_perslimbus2_data_pad1_uart6_tx,
	&omap5430_control_core_pad0_uart6_rx_pad1_uart6_cts,
	&omap5430_control_core_pad0_uart6_rts_pad1_uart3_cts_rctx,
	&omap5430_control_core_pad0_uart3_rts_irsd_pad1_uart3_tx_irtx,
	&omap5430_control_core_pad0_uart3_rx_irrx_pad1_usbb3_hsic_strobe,
	&omap5430_control_core_pad0_usbb3_hsic_data_pad1_sdcard_clk,
	&omap5430_control_core_pad0_sdcard_cmd_pad1_sdcard_data2,
	&omap5430_control_core_pad0_sdcard_data3_pad1_sdcard_data0,
	&omap5430_control_core_pad0_sdcard_data1_pad1_usbd0_hs_dp,
	&omap5430_control_core_pad0_usbd0_hs_dm_pad1_i2c1_pmic_scl,
	&omap5430_control_core_pad0_i2c1_pmic_sda_pad1_usbd0_ss_rx,
	&omap5430_control_padconf_wakeupevent_0,
	&omap5430_control_padconf_wakeupevent_1,
	&omap5430_control_padconf_wakeupevent_2,
	&omap5430_control_padconf_wakeupevent_3,
	&omap5430_control_padconf_wakeupevent_4,
	&omap5430_control_padconf_wakeupevent_5,
	&omap5430_control_padconf_wakeupevent_6,
	&omap5430_control_padconf_global,
	&omap5430_control_padconf_mode,
	&omap5430_control_smart1io_padconf_0,
	&omap5430_control_smart1io_padconf_1,
	&omap5430_control_smart1io_padconf_2,
	&omap5430_control_smart2io_padconf_0,
	&omap5430_control_smart2io_padconf_1,
	&omap5430_control_smart2io_padconf_2,
	&omap5430_control_smart3io_padconf_0,
	&omap5430_control_smart3io_padconf_1,
	&omap5430_control_pbias,
	&omap5430_control_i2c_0,
	&omap5430_control_camera_rx,
	&omap5430_control_hdmi_tx_phy,
	&omap5430_control_uniportm,
	&omap5430_control_dsiphy,
	&omap5430_control_mcbsplp,
	&omap5430_control_usb2phycore,
	&omap5430_control_hdmi_1,
	&omap5430_control_hsi,
	&omap5430_control_ddr3ch1_0,
	&omap5430_control_ddr3ch2_0,
	&omap5430_control_ddrch1_0,
	&omap5430_control_ddrch1_1,
	&omap5430_control_ddrch2_0,
	&omap5430_control_ddrch2_1,
	&omap5430_control_lpddr2ch1_0,
	&omap5430_control_lpddr2ch1_1,
	&omap5430_control_ddrio_0,
	&omap5430_control_ddrio_1,
	&omap5430_control_ddrio_2,
	&omap5430_control_hyst_1,
	&omap5430_control_usbb_hsic_control,
	&omap5430_control_c2c,
	&omap5430_control_core_control_spare_rw,
	&omap5430_control_core_control_spare_r,
	&omap5430_control_core_control_spare_r_c0,
	&omap5430_control_srcomp_north_side,
	&omap5430_control_srcomp_south_side,
	&omap5430_control_srcomp_east_side,
	&omap5430_control_srcomp_west_side,
	&omap5430_control_srcomp_code_latch,
	NULL};

reg *omap5430_ctrl_module_core_pad_mod[OMAP5430_CTRL_MODULE_CORE_PAD_MOD_REGCOUNT + 1] = {
	&omap5430_control_core_pad_revision,
	&omap5430_control_core_pad_hwinfo,
	&omap5430_control_core_pad_sysconfig,
	&omap5430_control_core_pad0_emmc_clk_pad1_emmc_cmd,
	&omap5430_control_core_pad0_emmc_data0_pad1_emmc_data1,
	&omap5430_control_core_pad0_emmc_data2_pad1_emmc_data3,
	&omap5430_control_core_pad0_emmc_data4_pad1_emmc_data5,
	&omap5430_control_core_pad0_emmc_data6_pad1_emmc_data7,
	&omap5430_control_core_pad0_c2c_clkout0_pad1_c2c_clkout1,
	&omap5430_control_core_pad0_c2c_clkin0_pad1_c2c_clkin1,
	&omap5430_control_core_pad0_c2c_datain0_pad1_c2c_datain1,
	&omap5430_control_core_pad0_c2c_datain2_pad1_c2c_datain3,
	&omap5430_control_core_pad0_c2c_datain4_pad1_c2c_datain5,
	&omap5430_control_core_pad0_c2c_datain6_pad1_c2c_datain7,
	&omap5430_control_core_pad0_c2c_dataout0_pad1_c2c_dataout1,
	&omap5430_control_core_pad0_c2c_dataout2_pad1_c2c_dataout3,
	&omap5430_control_core_pad0_c2c_dataout4_pad1_c2c_dataout5,
	&omap5430_control_core_pad0_c2c_dataout6_pad1_c2c_dataout7,
	&omap5430_control_core_pad0_c2c_data8_pad1_c2c_data9,
	&omap5430_control_core_pad0_c2c_data10_pad1_c2c_data11,
	&omap5430_control_core_pad0_c2c_data12_pad1_c2c_data13,
	&omap5430_control_core_pad0_c2c_data14_pad1_c2c_data15,
	&omap5430_control_core_pad0_llia_wakereqout_pad1_llib_wakereqout,
	&omap5430_control_core_pad0_hsi1_acready_pad1_hsi1_caready,
	&omap5430_control_core_pad0_hsi1_acwake_pad1_hsi1_cawake,
	&omap5430_control_core_pad0_hsi1_acflag_pad1_hsi1_acdata,
	&omap5430_control_core_pad0_hsi1_caflag_pad1_hsi1_cadata,
	&omap5430_control_core_pad0_uart1_tx_pad1_uart1_cts,
	&omap5430_control_core_pad0_uart1_rx_pad1_uart1_rts,
	&omap5430_control_core_pad0_hsi2_caready_pad1_hsi2_acready,
	&omap5430_control_core_pad0_hsi2_cawake_pad1_hsi2_acwake,
	&omap5430_control_core_pad0_hsi2_caflag_pad1_hsi2_cadata,
	&omap5430_control_core_pad0_hsi2_acflag_pad1_hsi2_acdata,
	&omap5430_control_core_pad0_uart2_rts_pad1_uart2_cts,
	&omap5430_control_core_pad0_uart2_rx_pad1_uart2_tx,
	&omap5430_control_core_pad0_usbb1_hsic_strobe_pad1_usbb1_hsic_data,
	&omap5430_control_core_pad0_usbb2_hsic_strobe_pad1_usbb2_hsic_data,
	&omap5430_control_core_pad0_timer10_pwm_evt_pad1_dsiporta_te0,
	&omap5430_control_core_pad0_dsiporta_lane0x_pad1_dsiporta_lane0y,
	&omap5430_control_core_pad0_dsiporta_lane1x_pad1_dsiporta_lane1y,
	&omap5430_control_core_pad0_dsiporta_lane2x_pad1_dsiporta_lane2y,
	&omap5430_control_core_pad0_dsiporta_lane3x_pad1_dsiporta_lane3y,
	&omap5430_control_core_pad0_dsiporta_lane4x_pad1_dsiporta_lane4y,
	&omap5430_control_core_pad0_dsiportc_lane0x_pad1_dsiportc_lane0y,
	&omap5430_control_core_pad0_dsiportc_lane1x_pad1_dsiportc_lane1y,
	&omap5430_control_core_pad0_dsiportc_lane2x_pad1_dsiportc_lane2y,
	&omap5430_control_core_pad0_dsiportc_lane3x_pad1_dsiportc_lane3y,
	&omap5430_control_core_pad0_dsiportc_lane4x_pad1_dsiportc_lane4y,
	&omap5430_control_core_pad0_dsiportc_te0_pad1_timer9_pwm_evt,
	&omap5430_control_core_pad0_i2c4_scl_pad1_i2c4_sda,
	&omap5430_control_core_pad0_mcspi2_clk_pad1_mcspi2_simo,
	&omap5430_control_core_pad0_mcspi2_somi_pad1_mcspi2_cs0,
	&omap5430_control_core_pad0_rfbi_data15_pad1_rfbi_data14,
	&omap5430_control_core_pad0_rfbi_data13_pad1_rfbi_data12,
	&omap5430_control_core_pad0_rfbi_data11_pad1_rfbi_data10,
	&omap5430_control_core_pad0_rfbi_data9_pad1_rfbi_data8,
	&omap5430_control_core_pad0_rfbi_data7_pad1_rfbi_data6,
	&omap5430_control_core_pad0_rfbi_data5_pad1_rfbi_data4,
	&omap5430_control_core_pad0_rfbi_data3_pad1_rfbi_data2,
	&omap5430_control_core_pad0_rfbi_data1_pad1_rfbi_data0,
	&omap5430_control_core_pad0_rfbi_we_pad1_rfbi_cs0,
	&omap5430_control_core_pad0_rfbi_a0_pad1_rfbi_re,
	&omap5430_control_core_pad0_rfbi_hsync0_pad1_rfbi_te_vsync0,
	&omap5430_control_core_pad0_gpio6_182_pad1_gpio6_183,
	&omap5430_control_core_pad0_gpio6_184_pad1_gpio6_185,
	&omap5430_control_core_pad0_gpio6_186_pad1_gpio6_187,
	&omap5430_control_core_pad0_hdmi_cec_pad1_hdmi_hpd,
	&omap5430_control_core_pad0_hdmi_ddc_scl_pad1_hdmi_ddc_sda,
	&omap5430_control_core_pad0_csiportc_lane0x_pad1_csiportc_lane0y,
	&omap5430_control_core_pad0_csiportc_lane1x_pad1_csiportc_lane1y,
	&omap5430_control_core_pad0_csiportb_lane0x_pad1_csiportb_lane0y,
	&omap5430_control_core_pad0_csiportb_lane1x_pad1_csiportb_lane1y,
	&omap5430_control_core_pad0_csiportb_lane2x_pad1_csiportb_lane2y,
	&omap5430_control_core_pad0_csiporta_lane0x_pad1_csiporta_lane0y,
	&omap5430_control_core_pad0_csiporta_lane1x_pad1_csiporta_lane1y,
	&omap5430_control_core_pad0_csiporta_lane2x_pad1_csiporta_lane2y,
	&omap5430_control_core_pad0_csiporta_lane3x_pad1_csiporta_lane3y,
	&omap5430_control_core_pad0_csiporta_lane4x_pad1_csiporta_lane4y,
	&omap5430_control_core_pad0_cam_shutter_pad1_cam_strobe,
	&omap5430_control_core_pad0_cam_globalreset_pad1_timer11_pwm_evt,
	&omap5430_control_core_pad0_timer5_pwm_evt_pad1_timer6_pwm_evt,
	&omap5430_control_core_pad0_timer8_pwm_evt_pad1_i2c3_scl,
	&omap5430_control_core_pad0_i2c3_sda_pad1_gpio8_233,
	&omap5430_control_core_pad0_gpio8_234_pad1_abe_clks,
	&omap5430_control_core_pad0_abedmic_din1_pad1_abedmic_din2,
	&omap5430_control_core_pad0_abedmic_din3_pad1_abedmic_clk1,
	&omap5430_control_core_pad0_abedmic_clk2_pad1_abedmic_clk3,
	&omap5430_control_core_pad0_abeslimbus1_clock_pad1_abeslimbus1_data,
	&omap5430_control_core_pad0_abemcbsp2_dr_pad1_abemcbsp2_dx,
	&omap5430_control_core_pad0_abemcbsp2_fsx_pad1_abemcbsp2_clkx,
	&omap5430_control_core_pad0_abemcpdm_ul_data_pad1_abemcpdm_dl_data,
	&omap5430_control_core_pad0_abemcpdm_frame_pad1_abemcpdm_lb_clk,
	&omap5430_control_core_pad0_wlsdio_clk_pad1_wlsdio_cmd,
	&omap5430_control_core_pad0_wlsdio_data0_pad1_wlsdio_data1,
	&omap5430_control_core_pad0_wlsdio_data2_pad1_wlsdio_data3,
	&omap5430_control_core_pad0_uart5_rx_pad1_uart5_tx,
	&omap5430_control_core_pad0_uart5_cts_pad1_uart5_rts,
	&omap5430_control_core_pad0_i2c2_scl_pad1_i2c2_sda,
	&omap5430_control_core_pad0_mcspi1_clk_pad1_mcspi1_somi,
	&omap5430_control_core_pad0_mcspi1_simo_pad1_mcspi1_cs0,
	&omap5430_control_core_pad0_mcspi1_cs1_pad1_i2c5_scl,
	&omap5430_control_core_pad0_i2c5_sda_pad1_gpio5_145,
	&omap5430_control_core_pad0_gpio5_146_pad1_uart6_tx,
	&omap5430_control_core_pad0_uart6_rx_pad1_uart6_cts,
	&omap5430_control_core_pad0_uart6_rts_pad1_uart3_cts_rctx,
	&omap5430_control_core_pad0_uart3_rts_irsd_pad1_uart3_tx_irtx,
	&omap5430_control_core_pad0_uart3_rx_irrx_pad1_usbb3_hsic_strobe,
	&omap5430_control_core_pad0_usbb3_hsic_data_pad1_sdcard_clk,
	&omap5430_control_core_pad0_sdcard_cmd_pad1_sdcard_data2,
	&omap5430_control_core_pad0_sdcard_data3_pad1_sdcard_data0,
	&omap5430_control_core_pad0_sdcard_data1_pad1_usbd0_hs_dp,
	&omap5430_control_core_pad0_usbd0_hs_dm_pad1_i2c1_pmic_scl,
	&omap5430_control_core_pad0_i2c1_pmic_sda_pad1_usbd0_ss_rx,
	&omap5430_control_padconf_wakeupevent_0,
	&omap5430_control_padconf_wakeupevent_1,
	&omap5430_control_padconf_wakeupevent_2,
	&omap5430_control_padconf_wakeupevent_3,
	&omap5430_control_padconf_wakeupevent_4,
	&omap5430_control_padconf_wakeupevent_5,
	&omap5430_control_padconf_wakeupevent_6,
	&omap5430_control_padconf_global,
	&omap5430_control_padconf_mode,
	&omap5430_control_smart1io_padconf_0,
	&omap5430_control_smart1io_padconf_1,
	&omap5430_control_smart1io_padconf_2,
	&omap5430_control_smart2io_padconf_0,
	&omap5430_control_smart2io_padconf_1,
	&omap5430_control_smart2io_padconf_2,
	&omap5430_control_smart3io_padconf_0,
	&omap5430_control_smart3io_padconf_1,
	&omap5430_control_pbias,
	&omap5430_control_i2c_0,
	&omap5430_control_camera_rx,
	&omap5430_control_hdmi_tx_phy,
	&omap5430_control_uniportm,
	&omap5430_control_dsiphy,
	&omap5430_control_mcbsplp,
	&omap5430_control_usb2phycore,
	&omap5430_control_hdmi_1,
	&omap5430_control_ddr3ch1_0,
	&omap5430_control_ddr3ch2_0,
	&omap5430_control_ddrch1_0,
	&omap5430_control_ddrch1_1,
	&omap5430_control_ddrch2_0,
	&omap5430_control_ddrch2_1,
	&omap5430_control_lpddr2ch1_0,
	&omap5430_control_lpddr2ch1_1,
	&omap5430_control_ddrio_0,
	&omap5430_control_ddrio_1,
	&omap5430_control_ddrio_2,
	&omap5430_control_hyst_1,
	&omap5430_control_usbb_hsic_control,
	&omap5430_control_c2c,
	&omap5430_control_core_control_spare_rw,
	&omap5430_control_core_control_spare_r,
	&omap5430_control_core_control_spare_r_c0,
	&omap5430_control_srcomp_north_side,
	&omap5430_control_srcomp_south_side,
	&omap5430_control_srcomp_east_side,
	&omap5430_control_srcomp_west_side,
	&omap5430_control_srcomp_code_latch,
	&omap5430_control_ddrio_ext_0,
	NULL};
