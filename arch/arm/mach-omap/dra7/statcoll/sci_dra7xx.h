/*
 * sci_dra7xx.h
 *
 * Statistic Collector Instrumentation Library
 * - Device speciifc definitions required by the API
 *
 * Copyright (C) 2011, 2012, 2013 Texas Instruments Incorporated - http://www.ti.com/
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

#ifndef SCI_DRA7XX_H
#define SCI_DRA7XX_H

/*! \file sci_dra7xx.h
    DRA7xx device specific CPTLib definitions
*/

/*! \enum sci_probeid_sdram
    Probe selection for sdram statistic collectors.
*/
enum sci_probeid_sdram_dra {
    SCI_EMIF1_DRA,					/*!< EMIF1 */
    SCI_EMIF2_DRA,					/*!< EMIF2 */
    SCI_MA_MPU_P1_DRA,				/*!< MA_MPU_P1 */
    SCI_MA_MPU_P2_DRA				/*!< MA_MPU_P2 */
};

/*! \enum sci_probeid_mstr
    Probe selection for master statistic collectors.
    Note: Order for probe_name_table indexing - not probe ids.
    For probe_ids a probe_map table is used (see sci_config_dra7xx.h).
 */
enum sci_probeid_mstr_dra {
	SCI_MPU_DRA,			/*!< MPU */
	SCI_MMU1_DRA,			/*!< MMU1 */
	SCI_EDMA_TC0_RD_DRA,	/*!< EDMA TC0 RD */
	SCI_EDMA_TC0_WR_DRA,	/*!< EDMA TC0 WR */
	SCI_EDMA_TC1_RD_DRA,	/*!< EDMA TC1 RD */
	SCI_EDMA_TC1_WR_DRA,	/*!< EDMA TC1 WR */
	SCI_VIP1_P1_DRA,		/*!< VIP1 P1 */
	SCI_VIP1_P2_DRA,		/*!< VIP1 P2 */
	SCI_VIP2_P1_DRA,		/*!< VIP2 P1 */
	SCI_VIP2_P2_DRA,		/*!< VIP2 P2 */
	SCI_VIP3_P1_DRA,		/*!< VIP3 P1 */
	SCI_VIP3_P2_DRA,		/*!< VIP3 P2 */
	SCI_VPE_P1_DRA,			/*!< VIPE P1 */
	SCI_VPE_P2_DRA,			/*!< VIPE P2 */
	SCI_EVE1_TC0_DRA,		/*!< EVE1 TC0 */
	SCI_EVE1_TC1_DRA,		/*!< EVE1 TC1 */
	SCI_EVE2_TC0_DRA,		/*!< EVE2 TC0 */
	SCI_EVE2_TC1_DRA,		/*!< EVE2 TC1 */
	SCI_DSP1_MDMA_DRA,		/*!< DSP1 MDMA */
	SCI_DSP1_EDMA_DRA,		/*!< DSP1 EDMA */
	SCI_DSP2_MDMA_DRA,		/*!< DSP2 MDMA */
	SCI_DSP2_EDMA_DRA,		/*!< DSP2 EDMA */
	SCI_IVA_DRA,			/*!< IVA */
	SCI_GPU_P1_DRA,			/*!< GPU P1 */
	SCI_GPU_P2_DRA,			/*!< GPU P2 */
	SCI_BB2D_P1_DRA,		/*!< BB2D P1 */
	SCI_DSS_DRA,			/*!< DSS */
	SCI_MMU2_DRA,			/*!< MMU2 */
	SCI_IPU1_DRA,			/*!< IPU1 */
	SCI_IPU2_DRA,			/*!< IPU2 */
	SCI_DMA_SYSTEM_RD_DRA,	/*!< DMA SYSTEM RD */
	SCI_DMA_SYSTEM_WR_DRA, 	/*!< DMA SYSTEM WR */
	SCI_USB1_DRA,			/*!< USB1 */
	SCI_USB2_DRA,			/*!< USB2 */
	SCI_USB3_DRA,			/*!< USB3 */
	SCI_USB4_DRA,			/*!< USB4 */
	SCI_PCIE_SS1_DRA,		/*!< PCIE SS1 */
	SCI_PCIE_SS2_DRA,		/*!< PCIE SS2 */
	SCI_DSP1_CFG_DRA,		/*!< DSP1 CFG */
	SCI_DSP2_CFG_DRA,		/*!< DSP2 CFG */
	SCI_GMAC_SW_DRA,		/*!< GMAC SW */
	SCI_MMC1_DRA,			/*!< MMC1 */
	SCI_MMC2_DRA,			/*!< MMC2 */
	SCI_SATA_DRA,			/*!< SATA */
	SCI_MLB_DRA,			/*!< MLB */
	SCI_BB2D_P2_DRA,		/*!< BB2D P2 */
	SCI_IEEE1500_DRA,		/*!< IEEE1500 */
	SCI_DEBUGSS_DRA,		/*!< DEBUGSS */
	SCI_VCP1_DRA,			/*!< VCP1 */
	SCI_OCMC_RAM1_DRA,		/*!< OCMC RAM1 */
	SCI_OCMC_RAM2_DRA,		/*!< OCMC RAM2 */
	SCI_OCMC_RAM3_DRA,		/*!< OCMC RAM3 */
	SCI_GPMC_DRA,			/*!< GPMC */
	SCI_MCASP1_DRA,			/*!< MCASP1 */
	SCI_MCASP2_DRA,			/*!< MCASP2 */
	SCI_MCASP3_DRA,			/*!< MCASP3 */
	SCI_VCP2_DRA			/*!< VCP2 */
};

/*! \enum sci_master_addr
     Master address enumerations.
*/
enum sci_master_addr_dra {
    SCI_MSTID_MPU_DRA = 0x0,				/*!< MPU */
    SCI_MSTID_DAP_DRA = 0x10,				/*!< DAP */
    SCI_MSTID_IEEE1500_2_OCP_DRA = 0x14,	/*!< IEEE1500 */
	SCI_MSTID_DSP1_MDMA_DRA = 0x20,			/*!< DSP1 MDMA */
	SCI_MSTID_DSP1_CFG_DRA = 0x24,			/*!< DSP1 CFG */
	SCI_MSTID_DSP1_DMA_DRA = 0x28,			/*!< DSP1 DMA */
	SCI_MSTID_DSP2_DMA_DRA = 0x2C,			/*!< DSP2 DMA */
	SCI_MSTID_DSP2_CFG_DRA = 0x30,			/*!< DSP2 CFG */
	SCI_MSTID_DSP2_MDMA_DRA = 0x34,			/*!< DSP2 MDMA */
	SCI_MSTID_IVA_ICONT1_DRA = 0x3A,		/*!< IVA ICONT1 */
	SCI_MSTID_EVE1_P1_DRA = 0x42,			/*!< EVE1 P1 */
	SCI_MSTID_EVE2_P1_DRA = 0x46,			/*!< EVE2 P1 */
	SCI_MSTID_IPU1_DRA = 0x60,				/*!< IPU1 */
	SCI_MSTID_IPU2_DRA = 0x64,				/*!< IPU2 */
	SCI_MSTID_SDMA_RD_DRA = 0x68,			/*!< SDMA RD */
	SCI_MSTID_SDMA_WR_DRA = 0x6A,			/*!< SDMA WR */
	SCI_MSTID_EDMA_TC1_WR_DRA = 0x70,		/*!< EDMA TC1 WR */
	SCI_MSTID_EDMA_TC1_RD_DRA = 0x72 ,		/*!< EDMA TC1 RD */
	SCI_MSTID_EDMA_TC2_WR_DRA = 0x74,		/*!< EDMA TC2 WR */
	SCI_MSTID_EDMA_TC2_RD_DRA = 0x76,		/*!< EDMA TC2 RD */
	SCI_MSTID_DSS_DRA =0x80,				/*!< DSS */
	SCI_MSTID_MLB_DRA = 0x84,				/*!< MLB */
	SCI_MSTID_MMU1_DRA = 0x86,				/*!< MMU1 */
	SCI_MSTID_PCIE_SS1_DRA = 0x88,			/*!< PCIE SS1 */
	SCI_MSTID_PCIE_SS2_DRA = 0x8C,			/*!< PCIE SS2 */
	SCI_MSTID_MMU2_DRA = 0x8E,				/*!< MMU2 */
	SCI_MSTID_VIP1_P1_DRA = 0x90,			/*!< VIP1 P1 */
	SCI_MSTID_VIP1_P2_DRA = 0x92,			/*!< VIP1 P2 */
	SCI_MSTID_VIP2_P1_DRA = 0x94,			/*!< VIP2 P1 */
	SCI_MSTID_VIP2_P2_DRA = 0x96,			/*!< VIP2 P2 */
	SCI_MSTID_VIP3_P1_DRA = 0x98,			/*!< VIP3 P1 */
	SCI_MSTID_VIP3_P2_DRA = 0x9A,			/*!< VIP3 P2 */
	SCI_MSTID_VPE_P1_DRA = 0x9C,			/*!< VIPE P1 */
	SCI_MSTID_VPE_P2_DRA = 0x9E,			/*!< VIPE P2 */
	SCI_MSTID_MMC1_DRA = 0xA0,				/*!< MMC1 */
	SCI_MSTID_GPU_P1_DRA = 0xA2,			/*!< GPU */
	SCI_MSTID_MMC2_DRA = 0xA4,				/*!< MMC2 */
	SCI_MSTID_GPU_P2_DRA = 0xA6,			/*!< GPU P2 */
	SCI_MSTID_BB2D_P1_DRA = 0xA8,			/*!< BB2D P1 */
	SCI_MSTID_BB2D_P2_DRA = 0xAA,			/*!< BB2D P2 */
	SCI_MSTID_GMAC_SW_DRA = 0xAC,			/*!< GMAC SW */
	SCI_MSTID_USB4_DRA = 0xB0 ,				/*!< USB4 */
	SCI_MSTID_USB1_DRA = 0xB4,				/*!< USB1 */
	SCI_MSTID_USB2_DRA = 0xB8,				/*!< USB2 */
	SCI_MSTID_USB3_DRA = 0xBC,				/*!< USB3 */
	SCI_MSTID_SATA_DRA = 0xCC,				/*!< SATA */
	SCI_MSTID_EVE1_P2_DRA = 0xD2,			/*!< EVE1 P2 */
	SCI_MSTID_EVE2_P2_DRA = 0xD6,			/*!< EVE2 P2 */
	SCI_MASTID_ALL_DRA						/*!< Select all masters */
};

/*! \enum sci_slave_addr
    Slave address enumerations.
*/
enum sci_slave_addr_dra {
	SCI_SLVID_DMM_P1_DRA = 0x02,			/*!< DMM P1 */
	SCI_SLVID_DMM_P2_DRA = 0x03,			/*!< DMM P2 */
	SCI_SLVID_DSP1_SDMA_DRA = 0x04,			/*!< DSP1 SDMA */
	SCI_SLVID_DSP2_SDMA_DRA = 0x05,			/*!< DSP2 SDMA */
	SCI_SLVID_DSS_DRA = 0x06,				/*!< DSS */
	SCI_SLVID_EVE1_DRA = 0x07,				/*!< EVE1 */
	SCI_SLVID_EVE2_DRA = 0x08,				/*!< EVE2 */
	SCI_SLVID_BB2D_DRA = 0x0B,				/*!< BB2D */
	SCI_SLVID_GPMC_DRA = 0x0C,				/*!< GPMC */
	SCI_SLVID_GPU_DRA = 0x0D,				/*!< GPU */
	SCI_SLVID_HOST_CLK1_1_DRA = 0x0E,		/*!< HOST CLK1 1 */
	SCI_SLVID_HOST_CLK1_2_DRA = 0x0F,		/*!< HOST CLK1 2 */
	SCI_SLVID_IPU1_DRA = 0x10,				/*!< IPU1 */
	SCI_SLVID_IPU2_DRA = 0x11,				/*!< IPU2 */
	SCI_SLVID_IVA_CONFIG_DRA = 0x12,		/*!< IVA CONFIG */
	SCI_SLVID_IVA_SL2IF_DRA = 0x13,			/*!< IVA SL2IF */
	SCI_SLVID_L4_CFG_DRA = 0x14,			/*!< L4 CFG */
	SCI_SLVID_L4_PER1_P1_DRA = 0x15,		/*!< L4 PER1 P1 */
	SCI_SLVID_L4_PER1_P2_DRA = 0x16,		/*!< L4 PER1 P2 */
	SCI_SLVID_L4_PER1_P3_DRA = 0x17,		/*!< L4 PER1 P3 */
	SCI_SLVID_L4_PER2_P1_DRA = 0x18,		/*!< L4 PER2 P1 */
	SCI_SLVID_L3_INSTR_DRA = 0x19,			/*!< L3 INSTR */
	SCI_SLVID_L4_PER2_P3_DRA = 0x1A,		/*!< L4 PER2 P3 */
	SCI_SLVID_L4_PER3_P1_DRA = 0x1B,		/*!< L4 PER3 P1 */
	SCI_SLVID_L4_PER3_P2_DRA = 0x1C,		/*!< L4 PER3 P2 */
	SCI_SLVID_L4_PER3_P3_DRA = 0x1D,		/*!< L4 PER3 P3 */
	SCI_SLVID_L4_WKUP_DRA = 0x1E,			/*!< L4 WKUP */
	SCI_SLVID_MCASP1_DRA = 0x1F,			/*!< MCASP1 */
	SCI_SLVID_MCASP2_DRA = 0x20,			/*!< MCASP2 */
	SCI_SLVID_MCASP3_DRA = 0x21,			/*!< MCASP3 */
	SCI_SLVID_MMU1_DRA = 0x22,				/*!< MMU1 */
	SCI_SLVID_MMU2_DRA = 0x23,				/*!< MMU2 */
	SCI_SLVID_OCMC_RAM1_DRA = 0x24,			/*!< OCMC RAM1 */
	SCI_SLVID_OCMC_RAM2_DRA = 0x25,			/*!< OCMC RAM2 */
	SCI_SLVID_OCMC_RAM3_DRA = 0x26,			/*!< OCMC RAM3 */
	SCI_SLVID_OCMC_ROM_DRA = 0x27,			/*!< OCMC ROM */
	SCI_SLVID_PCIE_SS1_DRA = 0x28,			/*!< PCIE SS12 */
	SCI_SLVID_PCIE_SS2_DRA = 0x29,			/*!< PCIE SS2 */
	SCI_SLVID_EDMA_TPCC_DRA = 0x30,			/*!< EDMA TPCC */
	SCI_SLVID_EDMA_TC1_DRA = 0x31,			/*!< EDMA TC1 */
	SCI_SLVID_EDMA_TC2_DRA = 0x32,			/*!< EDMA TC2 */
	SCI_SLVID_VCP1_DRA = 0x36,				/*!< VCP1 */
	SCI_SLVID_VCP2_DRA = 0x37,				/*!< VCP2 */
	SCI_SLVID_QSPI_DRA = 0x39,				/*!< QSPI */
	SCI_SLVID_HOST_CLK2_1_DRA = 0x40,		/*!< HOST CLK2 1 */
	SCI_SLVID_DEBUGSS_CT_TBR_DRA = 0x41,	/*!< DEBUGSS CT TBR */
	SCI_SLVID_L4_PER2_P2_DRA = 0x42,		/*!< L4 PER2 P2 */
	SCI_SLVID_ALL_DRA						/*!< Select all slaves */
};
#endif // #ifndef SCI_DRA7XX_H
