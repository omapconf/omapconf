/*
 * sci.h
 *
 * Statistic Collector Instrumentation Library 
 * - Device speciifc definitions required by the API
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

#ifndef SCI_DEV_H
#define SCI_DEV_H

/*
 * The following are extenral device specific definitions
 */
#if defined(_OMAP4430) || defined(_OMAP4460)

/*! \par probeid_sdram Probe selection for sdram statistic collectors. */
enum probeid_sdram { 
    SCI_EMIF1, 
    SCI_EMIF2
};

/*! \par probeid_mstr Probe selection for master statistic collectors. */
enum probeid_mstr { 
    SCI_MODENA,
    SCI_TESLA,    
    SCI_SDMA_RD,
    SCI_SDMA_WR, 
    SCI_DSS,
    SCI_ISS, 
    SCI_IVAHD, 
    SCI_SGX, 
    SCI_DUCATI
};

/*! \par sci_master_addr Master address enumerations. */
enum sci_master_addr { 
    SCI_MSTID_MPUSS = 0x0,     
    SCI_MSTID_DAP = 0x10,
    SCI_MSTID_IEEE1500 = 0x14,
    SCI_MSTID_TESLA = 0x20,
    SCI_MSTID_IVAHD = 0x30,
    SCI_MSTID_ISS = 0x40,
    SCI_MSTID_DUCATI = 0x44,
    SCI_MSTID_FACE_DETECT_SMP = 0x48,
    SCI_MSTID_SDMA_RD = 0x50,
    SCI_MSTID_SDMA_WR = 0x54,
    SCI_MSTID_CRYPTO_DMA_RD = 0x58,
    SCI_MSTID_CRYPTO_DMA_WR = 0x5C,
    SCI_MSTID_SGX = 0x60,
    SCI_MSTID_DSS = 0x70,
    SCI_MSTID_SAD2D = 0x80,
    SCI_MSTID_HSI = 0x90,
    SCI_MSTID_MMC1 = 0xA0,
    SCI_MSTID_MMC2 = 0xA4,
    SCI_MSTID_MMC6_MID = 0xA8,
    SCI_MSTID_UNIPRO1 = 0xB0,
    SCI_MSTID_USB_HOST_HS_SMP = 0xC0,
    SCI_MSTID_USB_OTG_HS = 0xC4,
    SCI_MSTID_USB_HOST_FS_SMP = 0xC8, 
    SCI_MASTID_ALL                             
};

/*! \par sci_slave_addr Slave address enumerations. */
enum sci_slave_addr { 
    SCI_SLVID_HOST_CLK1 = 0x0, 
    SCI_SLVID_DMM1_NIU = 0x1,
    SCI_SLVID_DMM2_NIU_SMP = 0x2,
    SCI_SLVID_ABE_NIU = 0x3,
    SCI_SLVID_L4CFG_NIU = 0x4,
    SCI_SLVID_HOST_CLK2 = 0x6,
    SCI_SLVID_GPMC_NIU = 0x7,
    SCI_SLVID_OCMRAM_NIU = 0x8,
    SCI_SLVID_DSS_NIU = 0x9,
    SCI_SLVID_ISS_NIU = 0xA,
    SCI_SLVID_DUCATI_NIU = 0xB,
    SCI_SLVID_SGX_NIU = 0xC,
    SCI_SLVID_IVAHD_NIU = 0xD,
    SCI_SLVID_SL2_NIU = 0xE,
    SCI_SLVID_L4PER0_NIU = 0xF,
    SCI_SLVID_L4PER1_NIU = 0x10,
    SCI_SLVID_L4PER2_NIU = 0x11,
    SCI_SLVID_L4PER3_NIU = 0x12,
    SCI_SLVID_AES1_NIU = 0x13,
    SCI_SLVID_AES2_NIU = 0x14,
    SCI_SLVID_SHA1_NIU = 0x15,
    SCI_SLVID_MODEM_MID = 0x16,
    SCI_SLVID_HOST_CLK3 = 0x18,
    SCI_SLVID_DEBUGSS_NIU = 0x19, 
    SCI_SLVID_ALL                            
};



#endif

#if defined(_OMAP5430) || defined(_OMAP4470)

/*! \par probeid_sdram Probe selection for sdram statistic collectors. */
enum probeid_sdram { 
    SCI_EMIF1, 
    SCI_EMIF2, 
    SCI_MA_MPU_P1, 
    SCI_MA_MPU_P2, 
    SCI_EMIF_LL
};

/*! \par probeid_mstr Probe selection for master statistic collectors. */
enum probeid_mstr { 
    SCI_MPU, 
    SCI_DSP, 
    SCI_SDMA_RD, 
    SCI_SDMA_WR, 
    SCI_DSS,
    SCI_ISS, 
    SCI_GPU_P1, 
    SCI_IVA, 
    SCI_GPU_P2, 
    SCI_IPU
};

/*! \par sci_master_addr Master address enumerations. */
enum sci_master_addr { 
    SCI_MSTID_MPUSS = 0x0, 
    SCI_MSTID_DAP = 0x10,                              
    SCI_MSTID_DSP = 0x20,              
    SCI_MSTID_IVA = 0x30,
    SCI_MSTID_ISS = 0x40,
    SCI_MSTID_IPU = 0x44,              
    SCI_MSTID_FDIF = 0x48,            
    SCI_MSTID_SDMA_RD = 0x50,
    SCI_MSTID_SDMA_WR = 0x54,                                     
    SCI_MSTID_GPU_P1 = 0x60,           
    SCI_MSTID_GPU_P2 = 0x64,
    SCI_MSTID_BB2D_P1 = 0x68,
    SCI_MSTID_BB2D_P2 = 0x6C,
    SCI_MSTID_DSS = 0x70,          
    SCI_MSTID_C2C = 0x80,              
#if defined(_OMAP5430)
    SCI_MSTID_LLI = 0x84,
#endif
    SCI_MSTID_HSI = 0x90,
#if defined(_OMAP5430)
    SCI_MSTID_UNIPRO1 = 0x94,          
    SCI_MSTID_UNIPRO2 = 0x98,          
#endif
    SCI_MSTID_MMC1 = 0xA0,
    SCI_MSTID_MMC2 = 0xA4,
#if defined(_OMAP5430)
    SCI_MSTID_SATA = 0xA8,                                                
#endif
    SCI_MSTID_USB_HOST_HS = 0xC0,
    SCI_MSTID_USB_OTG_HS = 0xC4,
    SCI_MSTID_USB_OTG_FS = 0xC8,
#if defined(_OMAP5430)
    SCI_MSTID_USB3 = 0xCC,
#endif
    SCI_MASTID_ALL
};

/*! \par sci_slave_addr Slave address enumerations. */
enum sci_slave_addr { 
    SCI_SLVID_HOST_CLK1 = 0x0,                       
    SCI_SLVID_DMM_P1_TARG = 0x1,           
    SCI_SLVID_DMM_P2_TARG = 0x2,           
    SCI_SLVID_ABE_TARG = 0x3,
    SCI_SLVID_L4_CFG_TARG = 0x4,
    SCI_SLVID_HOST_CLK2 = 0x6,
    SCI_SLVID_GPMC_TARG= 0x7,
    SCI_SLVID_OCM_RAM_TARG = 0x8,
    SCI_SLVID_DSS_TARG = 0x9,
    SCI_SLVID_ISS_TARG = 0xA,
    SCI_SLVID_IPU_TARG = 0xB,              
    SCI_SLVID_GPU_TARG = 0xC,              
    SCI_SLVID_IVA_TARG = 0xD,
    SCI_SLVID_SL2_TARG = 0xE,
    SCI_SLVID_L4_PER_P0_TARG = 0xF,
    SCI_SLVID_L4_PER_P1_TARG = 0x10,
    SCI_SLVID_L4_PER_P2_TARG = 0x11,
    SCI_SLVID_L4_PER_P3_TARG = 0x12,
    SCI_SLVID_C2C_TARG = 0x16,             
    SCI_SLVID_LLI_TARG = 0x17,             
    SCI_SLVID_HOST_CLK3 = 0x18,
    SCI_SLVID_L3_INSTR_TARG = 0x19,        
    SCI_SLVID_CAL_TARG = 0x1A,
    SCI_SLVID_DEBUGSS_CT_TBR_TARG = 0x1C,  
    SCI_SLVID_ALL                            
};

#endif
#endif // #ifndef SCI_DEV_H
