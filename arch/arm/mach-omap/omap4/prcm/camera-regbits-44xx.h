/* ======================================================================= *//**
 * @Component			OMAPCONF
 * @Filename			camera-regbits-44xx.h
 * @Description			OMAP4 Camera Configuration
 * @Author			Edward Lee (edward.lee@ti.com)
 * @Date			2012
 * @Copyright			TEXAS INSTRUMENTS Incorporated
 *//*======================================================================== */
/*
 * camera-regbits-44xx.h
 *
 * OMAP Power Configuration Tool ("omapconf")
 *  OMAP4 Camera Configuration
 *
 * Copyright (C) 2012 Texas Instruments, Inc.
 *
 * Written by Edward Lee (edward.lee@ti.com)
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301 USA.
 */


#ifndef __CAMERA_REGBITS_44XX_H__
#define __CAMERA_REGBITS_44XX_H__

typedef unsigned int _Uint32t;

/* Aparently these are somewhat generic accross ISS sub-blocks */
struct iss_csi2_sysconfig_bits {
	_Uint32t auto_idle:1;
	_Uint32t soft_reset:1;
	_Uint32t __reserved1:10;
	_Uint32t mstandby_mode:2;
	_Uint32t __reserved2:18;
};

/* CAREFUL: Bits under TI Maximum restrictions! */
struct iss_revision_bits {
	_Uint32t y_minor:6;
	_Uint32t custom:2;
	_Uint32t x_major:3;
	_Uint32t r_rtl:5;
	_Uint32t func:12;
	_Uint32t __reserved1:2;
	_Uint32t scheme:2;
};

/* ISS HL */
struct iss_hl_sysconfig_bits {
	_Uint32t softreset:1;
	_Uint32t __reserved1:1;
	_Uint32t idlemode:2;
	_Uint32t standbymode:2;
	_Uint32t __reserved2:26;
};

enum iss_ctrl_input_sel {
	ISS_CTRL_INPUT_SEL_CSI2A,
	ISS_CTRL_INPUT_SEL_CSI2B,
	ISS_CTRL_INPUT_SEL_CCP2,
	ISS_CTRL_INPUT_SEL_CPI,
};

enum iss_ctrl_input_sel2 {
	ISS_CTRL_INPUT_SEL_1,
	ISS_CTRL_INPUT_SEL_CSI2C,
	ISS_CTRL_INPUT_SEL_CSI3,
	RESERVED,
};

struct iss_ctrl_bits {
	_Uint32t sync_detect:2;
	_Uint32t input_sel:2;
	_Uint32t iss_clk_div:2;
	_Uint32t __reserved1:10;
	_Uint32t ccp2r_tag_cnt:4;
	_Uint32t ccp2w_tag_cnt:4;
	_Uint32t csi2_a_tag_cnt:4;
	_Uint32t csi2_b_tag_cnt:4;
};

struct iss_clk_bits {
	_Uint32t simcop:1;
	_Uint32t isp:1;
	_Uint32t csi2_a:1;
	_Uint32t csi2_b:1;
	_Uint32t ccp2:1;
	_Uint32t __reserved1:23;
	_Uint32t vport0_clk:1;
	_Uint32t vport1_clk:1;
	_Uint32t vport2_clk:1;
	_Uint32t vport3_clk:1;/* OMAP4460 and OMAP4470 only */
};

struct iss_pm_status_bits {
	_Uint32t csi2_a_pm:2;
	_Uint32t csi2_b_pm:2;
	_Uint32t ccp2_pm:2;
	_Uint32t isp_pm:2;
	_Uint32t simcop_pm:2;
	_Uint32t bte_pm:2;
	_Uint32t cbuff_pm:2;
	_Uint32t __reserved1:18;
};

struct iss_top_irq_regs {
	_Uint32t	status_raw;
	_Uint32t	status;
	_Uint32t	enable_set;
	_Uint32t	enable_clr;
};

struct iss_top_regs {
	struct iss_revision_bits	hl_revision;
	_Uint32t			__reserved1[3];
	struct iss_hl_sysconfig_bits	hl_sysconfig;
	_Uint32t			__reserved2[3];
	struct iss_top_irq_regs		irq[6];
	struct iss_ctrl_bits		ctrl;
	struct iss_clk_bits		clkctrl;
	struct iss_clk_bits		clkstat;
	struct iss_pm_status_bits	pm_status;
};

/* CAREFUL: Bits under TI Maximum restrictions! */
struct iss_csi2_revision_bits {
	_Uint32t minor:4;
	_Uint32t major:4;
	_Uint32t __reserved1:24;
};

struct iss_csi2_sysstatus_bits {
	_Uint32t reset_done:1;
	_Uint32t __reserved1:31;
};

enum iss_csi2_ctrl_vp_out_ctrl {
	CSI2_CTRL_VP_OUT_CTRL_DIV1,
	CSI2_CTRL_VP_OUT_CTRL_DIV2,
	CSI2_CTRL_VP_OUT_CTRL_DIV3,
	CSI2_CTRL_VP_OUT_CTRL_DIV4,
};

struct iss_csi2_ctrl_bits {
	_Uint32t if_en:1;
	_Uint32t __reserved1:1;
	_Uint32t ecc_en:1;
	_Uint32t frame:1;
	_Uint32t endianness:1;
	_Uint32t burst_size:2;
	_Uint32t dbg_en:1;
	_Uint32t vp_out_ctrl:2;
	_Uint32t streaming_32_bit:1;
	_Uint32t vp_only_en:1;
	_Uint32t __reserved2:1;
	_Uint32t non_posted_write:1;
	_Uint32t __reserved3:1;
	_Uint32t vp_clk_en:1;
	_Uint32t burst_size_expand:1;
	_Uint32t mflag_levl:1;
	_Uint32t mflag_levh:1;
	_Uint32t __reserved4:7;
};

struct iss_csi2_complexio_cfg_bits {
	_Uint32t clock_position:3;
	_Uint32t clock_pol:1;
	_Uint32t data1_position:3;
	_Uint32t data1_pol:1;
	_Uint32t data2_position:3;
	_Uint32t data2_pol:1;
	_Uint32t data3_position:3;
	_Uint32t data3_pol:1;
	_Uint32t data4_position:3;
	_Uint32t data4_pol:1;
	_Uint32t __reserved1:4;
	_Uint32t pwr_auto:1;
	_Uint32t pwr_status:2;
	_Uint32t pwr_cmd:2;
	_Uint32t reset_done:1;
	_Uint32t reset_ctrl:1;
	_Uint32t __reserved2:1;
};

struct iss_csi2_timing_bits {
	_Uint32t stop_state_counter_io1:13;
	_Uint32t stop_state_x4_io1:1;
	_Uint32t stop_state_x16_io1:1;
	_Uint32t force_rx_mode_io1:1;
	_Uint32t __reserved1:16;
};

struct iss_csi2_ctx_ctrl1_bits {
	_Uint32t ctx_en:1;
	_Uint32t line_modulo:1;
	_Uint32t vp_force:1;
	_Uint32t ping_pong:1;
	_Uint32t count_unlock:1;
	_Uint32t cs_en:1;
	_Uint32t eol_en:1;
	_Uint32t eof_en:1;
	_Uint32t count:8;
	_Uint32t fec_number:8;
	_Uint32t transcode:4;
	_Uint32t hscale:1;
	_Uint32t __reserved1:1;
	_Uint32t generic:1;
	_Uint32t byteswap:1;
};

struct iss_csi2_ctx_ctrl2_bits {
	_Uint32t format:10;
	_Uint32t dpcm_pred:1;
	_Uint32t virtual_id:2;
	_Uint32t user_def_mapping:2;
	_Uint32t __reserved1:1;
	_Uint32t frame:16;
};

struct iss_csi2_ctx_ctrl3_bits {
	_Uint32t line_number:16;
	_Uint32t alpha:14;
	_Uint32t __reserved1:2;
};

struct iss_csi2_ctx_regs {
	struct iss_csi2_ctx_ctrl1_bits		ctrl1;
	struct iss_csi2_ctx_ctrl2_bits		ctrl2;
	_Uint32t				dat_ofst;
	_Uint32t				dat_ping_addr;
	_Uint32t				dat_pong_addr;
	_Uint32t				irq_enable;
	_Uint32t				irq_status;
	struct iss_csi2_ctx_ctrl3_bits		ctrl3;
};

struct iss_csi2_regs {
	struct iss_csi2_revision_bits		revision;
	_Uint32t				__reserved1[3];
	struct iss_csi2_sysconfig_bits		sysconfig;
	struct iss_csi2_sysstatus_bits		sysstatus;
	_Uint32t				irqenable;
	_Uint32t				irqstatus;
	_Uint32t				__reserved2[8];
	struct iss_csi2_ctrl_bits		ctrl;
	_Uint32t				dbg_h;
	_Uint32t				__reserved3[2];
	struct iss_csi2_complexio_cfg_bits	complexio_cfg;
	_Uint32t				complexio_irqstatus;
	_Uint32t				__reserved4;
	_Uint32t				short_packet;
	_Uint32t				complexio_irqenable;
	_Uint32t				__reserved5;
	_Uint32t				dbg_p;
	struct iss_csi2_timing_bits		timing;
	struct iss_csi2_ctx_regs		ctx[8];
};

struct iss_ccp2_regs {
	_Uint32t				revision;
	_Uint32t				sysconfig;
	_Uint32t				sysstatus;
	_Uint32t				lc01_irqenable;
	_Uint32t				lc01_irqstatus;
	_Uint32t				lc23_irqenable;
	_Uint32t				lc23_irqstatus;
	_Uint32t				__reserved1[4];
	_Uint32t				lcm_irqenable;
	_Uint32t				lcm_irqstatus;
	_Uint32t				__reserved2[3];
	_Uint32t				ctrl;
	_Uint32t				dbg;
	_Uint32t				gnq;
	_Uint32t				ctrl1;
	_Uint32t				__reserve4[96];
	_Uint32t				lcm_ctrl;
	_Uint32t				lcm_vsize;
	_Uint32t				lcm_hsize;
	_Uint32t				lcm_prefetch;
	_Uint32t				lcm_src_addr;
	_Uint32t				lcm_src_ofst;
	_Uint32t				lcm_dst_addr;
	_Uint32t				lcm_dst_ofst;
	_Uint32t				lcm_history;


};

/* ISP5_SYS1 */
struct iss_isp5_sysconfig_bits {
	_Uint32t auto_idle:1;
	_Uint32t softreset:1;
	_Uint32t __reserved1:2;
	_Uint32t standbymode:2;
	_Uint32t __reserved2:26;
};

struct iss_isp5_ctrl_bits {
	_Uint32t ocp_wrnp:1;
	_Uint32t vbusm_cpriority:3;
	_Uint32t vbusm_cids:4;
	_Uint32t psync_clk_sel:1;
	_Uint32t sync_enable:1;
	_Uint32t ipipeif_clk_enable:1;
	_Uint32t ipipe_clk_enable:1;
	_Uint32t rsz_clk_enable:1;
	_Uint32t h3a_clk_enable:1;
	_Uint32t isif_clk_enable:1;
	_Uint32t bl_clk_enable:1;
	_Uint32t __reserved1:4;
	_Uint32t mstandby_wait:1;
	_Uint32t mflag:1;
	_Uint32t pclk_inv:1;
	_Uint32t vd_pulse_ext:1;
	_Uint32t mstandby:1;
	_Uint32t dpc_evt_ini:1;
	_Uint32t hst_rd_chk:1;
	_Uint32t bsc_rd_chk:1;
	_Uint32t __reserved2:2;
	_Uint32t dma3_cfg:2;
};

struct iss_isp5_sys1_regs {
	struct iss_revision_bits		revision;
	_Uint32t				hwinfo1;
	_Uint32t				hwinfo2;
	_Uint32t				__reserved1;
	struct iss_isp5_sysconfig_bits		sysconfig;
	_Uint32t				__reserved2[4];
	struct iss_top_irq_regs			irq[4];
	_Uint32t				dmaenable_set;
	_Uint32t				dmaenable_clr;
	struct iss_isp5_ctrl_bits		ctrl;
	_Uint32t				pg;
	_Uint32t				pg_pulse_ctrl;
	_Uint32t				pg_frame_size;
	_Uint32t				mpsr;
	_Uint32t				bl_mtc1;
	_Uint32t				bl_mtc2;
	_Uint32t				bl_vbusm;
};

/* ISS_RESIZER */
struct iss_resizer_revision_bits {
	_Uint32t minor:4;
	_Uint32t major:4;
	_Uint32t __reserved1:24;
};

struct iss_resizer_sysconfig_bits {
	_Uint32t autogating:1;
	_Uint32t __reserved1:7;
	_Uint32t rsza_clk_en:1;
	_Uint32t rszb_clk_en:1;
	_Uint32t __reserved2:22;
};

struct iss_resizer_ab_regs {
	_Uint32t				en;
	_Uint32t				mode;
	_Uint32t				n420;
	_Uint32t				i_vps;
	_Uint32t				i_hps;
	_Uint32t				o_vsz;
	_Uint32t				o_hsz;
	_Uint32t				v_phs_y;
	_Uint32t				v_phs_c;
	_Uint32t				v_dif;
	_Uint32t				v_typ;
	_Uint32t				v_lpf;
	_Uint32t				h_phs;
	_Uint32t				h_phs_adj;
	_Uint32t				h_dif;
	_Uint32t				h_typ;
	_Uint32t				h_lpf;
	_Uint32t				dwn_en;
	_Uint32t				dwn_av;
	_Uint32t				rgb_en;
	_Uint32t				rgb_typ;
	_Uint32t				rgb_bld;
	_Uint32t				sdr_y_bad_h;
	_Uint32t				sdr_y_bad_l;
	_Uint32t				sdr_y_sad_h;
	_Uint32t				sdr_y_sad_l;
	_Uint32t				sdr_y_oft;
	_Uint32t				sdr_y_ptr_s;
	_Uint32t				sdr_y_ptr_e;
	_Uint32t				sdr_c_bad_h;
	_Uint32t				sdr_c_bad_l;
	_Uint32t				sdr_c_sad_h;
	_Uint32t				sdr_c_sad_l;
	_Uint32t				sdr_c_oft;
	_Uint32t				sdr_c_ptr_s;
	_Uint32t				sdr_c_ptr_e;
};

struct iss_resizer_src_en_bits {
	_Uint32t				en:1;
	_Uint32t				__reserved:31;
};

struct iss_resizer_src_mode_bits {
	_Uint32t				ost:1;
	_Uint32t				wrt:1;
	_Uint32t				__reserved:30;
};

struct iss_resizer_src_fmt0_bits {
	_Uint32t				sel:1;
	_Uint32t				bypass:1;
	_Uint32t				__reserved:30;
};

struct iss_resizer_src_fmt1_bits {
	_Uint32t				raw:1;
	_Uint32t				in420:1;
	_Uint32t				col:1;
	_Uint32t				chr:1;
	_Uint32t				__reserved:28;
};

struct iss_resizer_regs {
	struct iss_resizer_revision_bits	revision;
	struct iss_resizer_sysconfig_bits	sysconfig;
	_Uint32t				__reserved1;
	_Uint32t				in_fifo_ctrl;
	_Uint32t				gnc;
	_Uint32t				fracdiv;
	_Uint32t				__reserved2[2];
	struct iss_resizer_src_en_bits		src_en;
	struct iss_resizer_src_mode_bits	src_mode;
	struct iss_resizer_src_fmt0_bits	src_fmt0;
	struct iss_resizer_src_fmt1_bits	src_fmt1;
	_Uint32t				src_vps;
	_Uint32t				src_vsz;
	_Uint32t				src_hps;
	_Uint32t				src_hsz;
	_Uint32t				dma_rza;
	_Uint32t				dma_rzb;
	_Uint32t				dma_sta;
	_Uint32t				gck_mmr;
	_Uint32t				__reserved3;
	_Uint32t				gck_sdr;
	_Uint32t				irq_rza;
	_Uint32t				irq_rzb;
	_Uint32t				yuv_y_min;
	_Uint32t				yuv_y_max;
	_Uint32t				yuv_c_min;
	_Uint32t				yuv_c_max;
	_Uint32t				yuv_phs;
	_Uint32t				seq;
	struct iss_resizer_ab_regs		rza;
	struct iss_resizer_ab_regs		rzb;
};

/* ISS_IPIPE */
struct iss_ipipe_src_en_bits {
	_Uint32t				en:1;
	_Uint32t				__reserved:31;
};

struct iss_ipipe_src_mode_bits {
	_Uint32t				ost:1;
	_Uint32t				wrt:1;
	_Uint32t				__reserved:30;
};

struct iss_ipipe_src_fmt_bits {
	_Uint32t				fmt:2;
	_Uint32t				__reserved:30;
};

struct iss_ipipe_regs {
	struct iss_ipipe_src_en_bits		src_en;
	struct iss_ipipe_src_mode_bits		src_mode;
	struct iss_ipipe_src_fmt_bits		src_fmt;
	_Uint32t				src_col;
	_Uint32t				src_vps;
	_Uint32t				src_vsz;
	_Uint32t				src_hps;
	_Uint32t				src_hsz;
	_Uint32t				sel_sbu;
	_Uint32t				src_sta;
	_Uint32t				gck_mmr;
	_Uint32t				gck_pix;
	_Uint32t				__reserved1;
	/* TODO: Add the rest! */
};

/* ISS_ISIF */
struct iss_isif_syncen_bits {
	_Uint32t				syen:1;
	_Uint32t				dwen:1;
	_Uint32t				__reserved:30;
};

struct iss_isif_modeset_bits {
	_Uint32t				hdvdd:1;
	_Uint32t				fidd:1;
	_Uint32t				vdpol:1;
	_Uint32t				hdpol:1;
	_Uint32t				fdpol:1;/* OMAP4460 and OMAP4470 only */
	_Uint32t				swen:1;
	_Uint32t				dpol:1;
	_Uint32t				ccdmd:1;
	_Uint32t				ccdw:3;
	_Uint32t				ovf:1;
	_Uint32t				inpmod:2;
	_Uint32t				hlpf:1;/* OMAP4460 and OMAP4470 only */
	_Uint32t				__reserved3:17;
};

struct iss_isif_ccdcfg_bits {
	_Uint32t				sdrpack:2;
	_Uint32t				__reserved1:2;
	_Uint32t				ycinswp:1;
	_Uint32t				bt656:1;
	_Uint32t				fidmd:2;
	_Uint32t				wenlog:1;
	_Uint32t				trgsel:1;
	_Uint32t				extrg:1;
	_Uint32t				y8pos:1;
	_Uint32t				bswd:1;
	_Uint32t				msbinvi:1;
	_Uint32t				__reserved2:1;
	_Uint32t				vldc:1;
	_Uint32t				__reserved3:16;
};

struct iss_isif_regs {
	struct iss_isif_syncen_bits		syncen;
	struct iss_isif_modeset_bits		modeset;
	_Uint32t				hdw;
	_Uint32t				vdw;
	_Uint32t				ppln;
	_Uint32t				lpfr;
	_Uint32t				sph;
	_Uint32t				lnh;
	_Uint32t				__reserved1[2];
	_Uint32t				lnv;
	_Uint32t				culh;
	_Uint32t				culv;
	_Uint32t				hsize;
	_Uint32t				__reserved2;
	_Uint32t				cadu;
	_Uint32t				cadl;
	_Uint32t				lincfg0;
	_Uint32t				lincfg1;
	_Uint32t				ccolp;
	_Uint32t				crgain;
	_Uint32t				cgrgain;
	_Uint32t				cgbgain;
	_Uint32t				cbgain;
	_Uint32t				cofsta;
	_Uint32t				vdint[3];
	_Uint32t				misc;
	_Uint32t				cgammawd;
	_Uint32t				rec656if;
	struct iss_isif_ccdcfg_bits		ccdcfg;
	_Uint32t				dfcctl;
	_Uint32t				vdfsatlv;
	_Uint32t				dfcmemctl;
	_Uint32t				dfcmem[5];
	_Uint32t				clampcfg;
	/* TODO: Add the rest! */
};

/* ISS_IPIPEIF */
struct iss_ipipeif_enable_bits {
	_Uint32t				enable:1;
	_Uint32t				syncoff:1;
	_Uint32t				__reserved:30;
};

struct iss_ipipeif_cfg1_bits {
	_Uint32t				oneshot:1;
	_Uint32t				decim:1;
	_Uint32t				inpsrc2:2;
	_Uint32t				__reserved1:3;
	_Uint32t				avgfilt:1;
	_Uint32t				unpack:2;
	_Uint32t				clksel:1;
	_Uint32t				datasft:3;
	_Uint32t				inpsrc1:2;
	_Uint32t				__reserved2:16;
};

struct iss_ipipeif_cfg2_bits {
	_Uint32t				intsw:1;
	_Uint32t				hdpol:1;
	_Uint32t				vdpol:1;
	_Uint32t				yuv16:1;
	_Uint32t				__reserved1:1;
	_Uint32t				dfsdir:1;
	_Uint32t				yuv8:1;
	_Uint32t				yuv8p:1;
	_Uint32t				__reserved2:24;
};

struct iss_ipipeif_regs {
	struct iss_ipipeif_enable_bits		enable;
	struct iss_ipipeif_cfg1_bits		cfg1;
	_Uint32t				ppln;
	_Uint32t				lpfr;
	_Uint32t				hnum;
	_Uint32t				vnum;
	_Uint32t				addru;
	_Uint32t				addrl;
	_Uint32t				adofs;
	_Uint32t				rsz;
	_Uint32t				gain;
	_Uint32t				dpcm;
	struct iss_ipipeif_cfg2_bits		cfg2;
	_Uint32t				inirsz;
	_Uint32t				oclip;
	_Uint32t				dtudf;
	_Uint32t				clkdiv;
	_Uint32t				dpc1;
	_Uint32t				dpc2;
	_Uint32t				rsz3a;
	_Uint32t				inirsz3a;
};

/* ISS_H3A */
struct iss_h3a_regs {
	struct iss_revision_bits		pid;
};

#endif
