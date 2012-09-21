/*
 *
 * @Component			OMAPCONF
 * @Filename			l2cc44xx.c
 * @Description			Dump L2CC registers Config/Analyse L2CC events
 * @Author			Steve Korson (s-korson@ti.com)
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


#include <mpuss44xx.h>
#include <lib44xx.h>
#include <help.h>
#include <lib.h>
#include <mem.h>
#include <cpuinfo.h>
#include <string.h>
/*
// skorson
// order matters - this needs types from lib44xx.h
*/
#include <l2cc44xx.h>

/* #define L2CC44XX_DEBUG */
#ifdef L2CC44XX_DEBUG
#define dprintf(format, ...)	 printf(format, ## __VA_ARGS__)
#else
#define dprintf(format, ...)
#endif


/**
 * Function: l2cc44xx_init_regtable
 * Role: initialize regtable
 * Parameters:
 *	n/a
 * Return:
 *	n/a
 *
 * skorson:
 *   Decided to build the regtable for L2CC in the mpuss44xx.h header
 *   as a constant. This may or may not need to be changed.
 */

/*
int l2cc44xx_init_regtable(void)
{
	return 0;
}

*/


/**
 * Function: l2cc44xx_name2addr
 * Role: retrieve physical address of a register, given its name.
 * Parameters:
 *	n/a
 * Return:
 *	n/a
 *
 * skorson:
 *   Decided against a special l2cc name2addr. Can use the already
 *   defined name2addr directly.
 */

/*
int l2cc44xx_name2addr(char *name, unsigned int *addr)
{
		return 0
}
*/


/**
 * Function: l2cc44xx_perf_cnt_configure
 * Role: Resets and configures the PL310 event counters but does not enable.
 *       Enabling will be left for just prior to usage.
 * Parameters:
 *	counter_inst: L2CC (PL310) counter - 0 through 1 valid.
 *	filter: filter table entry (also its filter value.)
 *      reset: boolean whether to reset the couter or not.
 *
 * Return:
 *	0 in case of success
 *
 */
int	  l2cc44xx_perf_cnt_configure(unsigned int counter_inst, unsigned int filter, unsigned int reset)
{
	unsigned int filter_addr = 0;
	unsigned int addr = 0;
	unsigned int data = 0;
	int ret = 0;


	/* early on check that our counter_inst is valid, and if so extract the filter_addr. */
	switch (counter_inst) {
	case 0:
		ret = name2addr("EVENT_COUNTER0_CONFIGURATION", &filter_addr,
			(reg_table *) omap4_mpuss_pl310_reg_table);
		break;
	case 1:
		ret = name2addr("EVENT_COUNTER1_CONFIGURATION", &filter_addr,
			(reg_table *) omap4_mpuss_pl310_reg_table);
		break;
	default:
		fprintf(stderr, "%s(): bad L2CC(PL310) event counter instance! (%u)!\n",
			__func__, counter_inst);
		return OMAPCONF_ERR_ARG;
	}

	/* setup the address for the configuration register, and data for reset if selected */
	ret = name2addr("EVENT_COUNTER_CONTROL", &addr,
		(reg_table *) omap4_mpuss_pl310_reg_table);
	if (ret != 0) {
		dprintf("PL310 Incorrect Config Addr!\n");
		}

	data = reset << (counter_inst+1); /* Counter 0 reset is bit 1, counter 1 is bit 2... */

	dprintf("PL310 config Addr: %x, Data: 0x%x\n", addr, data);

	ret = mem_write(addr, data);
	if (ret != 0) {
		fprintf(stderr, "%s(): error writing L2CC (PL310) EVENT_COUNTER_CONTROL reg!\n",
			__func__);
		return OMAPCONF_ERR_REG_ACCESS;
	}

	/* Setup the data for the filter. Its a simple left-shift to account for the currently */
	/* unused two interrupt bits. */

	data = filter << 2;
	ret = mem_write(filter_addr, data);
	if (ret != 0) {
		fprintf(stderr, "%s(): error writing L2CC (PL310) EVENT_COUNTER_CONTROL reg!\n",
			__func__);
		return OMAPCONF_ERR_REG_ACCESS;
	}
	dprintf("PL310 config Addr: %x, Data: 0x%x\n", filter_addr, data);

	return 0;
}


/**
 * Function: l2cc44xx_perf_cnt_enable
 * Role: Enables the L2CC performance counters.
 * Parameters:
 *	none
 * Return:
 *	0 in case of success
 *	OMAPCONF_ERR_REG_ACCESS
 */
int l2cc44xx_perf_cnt_enable()
{
	unsigned int addr = 0;
	unsigned int data = 0;
	int ret = 0;

	printf("\n### WARNING ###: L2$ counters will be lost (reset) accross MPU domain power transitions.\n\n");

	/*
	 * Setup the address for the configuration register,
	 * and data for reset if selected
	 */
	ret = name2addr("EVENT_COUNTER_CONTROL", &addr,
		(reg_table *) omap4_mpuss_pl310_reg_table);

	data = 0x1; /* Enable is bit 0 */
	ret = mem_write(addr, data);
	if (ret != 0) {
		fprintf(stderr, "%s(): error writing L2CC (PL310) EVENT_COUNTER_CONTROL reg!\n",
			__func__);
		return OMAPCONF_ERR_REG_ACCESS;
	}

	return 0;
}


/**
 * Function: l2cc44xx_perf_cnt_disable
 * Role: Disables the L2CC performance counters.
 * Parameters:
 *
 * Return:
 *	0 in case of success
 *
 */
int	  l2cc44xx_perf_cnt_disable()
{
	unsigned int addr = 0;
	unsigned int data = 0;
	int ret = 0;
	/* setup the address for the configuration register, and data for reset if selected */
	ret = name2addr("EVENT_COUNTER_CONTROL", &addr,
		(reg_table *) omap4_mpuss_pl310_reg_table);

	data = 0x0; /* Enable is bit 0. // Other bits are OK to write 0.s (i.e. no read/mod/write) */
	ret = mem_write(addr, data);
	if (ret != 0) {
		fprintf(stderr, "%s(): error writing L2CC (PL310) EVENT_COUNTER_CONTROL reg!\n",
			__func__);
		return OMAPCONF_ERR_REG_ACCESS;
	}

	return 0;
}


/**
 * Function: l2cc44xx_get_perf_cnt
 * Role: retrieve performance counter value as configured (filtered)
 * Parameters:
 *	emif_id: EMIF instance
 *	cnt_id: performance counter ID
 * Return:
 *	performance counter value as configured
 *	0 in case of error
 */
unsigned int l2cc44xx_get_perf_cnt (unsigned int counter_inst)
{
	unsigned int addr = 0;
	unsigned int data = 0xDEADBEEF;
	int ret = 0;


	/* early on check that our counter_inst is valid, and if so extract the filter_addr. */
	switch (counter_inst) {
	case 0:
		ret = name2addr("EVENT_COUNTER0_VALUE", &addr,
			(reg_table *) omap4_mpuss_pl310_reg_table);
		break;
	case 1:
		ret = name2addr("EVENT_COUNTER1_VALUE", &addr,
			(reg_table *) omap4_mpuss_pl310_reg_table);
		break;
	default:
		fprintf(stderr, "%s(): bad L2CC(PL310) event counter instance! (%u)!\n",
			__func__, counter_inst);
		return OMAPCONF_ERR_ARG;
	}

	/* setup the address for the configuration register, and data for reset if selected */
	ret = mem_read(addr, &data);
	if (ret != 0) {
		fprintf(stderr, "%s(): error reading L2CC(PL310) EVENT COUNT %2x VALUE reg!\n",
			__func__, counter_inst);
		return OMAPCONF_ERR_REG_ACCESS;
	}

	return data;

}


/**
 * Function: l2cc44xx_main
 * Role:
 * Parameters:
 *	argc: shell input argument number
 *	argv: shell input argument(s)
 * Return:
 *	0 in case of success
 *      OMAPCONF_ERR_ARG
 *      OMAPCONF_ERR_CPU
 *	OMAPCONF_ERR_INTERNAL
 *
 *
 * skorson
 * Perhaps later move the dump regs for l2cc from mpuss44xx.c to here?
 */


/*
// int l2cc44xx_main(int argc, char *argv[])
// {
// 	int ret;
//
// 	if (!cpu_is_omap44xx())
// 		return OMAPCONF_ERR_CPU;
//
// 	if (argc == 3) {
// 		if (strcmp(argv[2], "dump") == 0) {
// // skorson
// // No init required; reg table is defined as constant in header...
// //			if (!init_done)
// //				emif44xx_init_regtable();
// 			ret = dumpregs(l2cc_reg_table);
// 		} else {
// 			help(HELP_L2CC);
// 			ret = OMAPCONF_ERR_ARG;
// 		}
// 	} else {
// 		help(HELP_L2CC);
// 		ret = OMAPCONF_ERR_ARG;
// 	}
//
// 	return ret;
// }
*/
