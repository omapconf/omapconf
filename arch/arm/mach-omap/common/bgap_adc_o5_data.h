/*
 *
 * @Component			OMAPCONF
 * @Filename			bgap_adc_o5_data.h
 * @Description			ADC Code Versus Temperature data for OMAP5:
 *				converts the control VBGAPTS temperatur sensor's
 *				register data that was captured from the ADC to
 *				temperature in Celcius
 * @Author			José Peña <pena@ti.com>
 * @Date			2013
 * @Copyright			Texas Instruments Incorporated
 *
 *
 * Copyright (C) 2013 Texas Instruments Incorporated - http://www.ti.com/
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


#ifndef __BGAP_ADC_OMAP5_DATA_H__
#define __BGAP_ADC_OMAP5_DATA_H__


#include <stdio.h>


/*
 * Array index is the ADC code - 540
 * returns the MAX temperature corresponding to the ADC code
 */
static const short int bgap_o5_conversion_table[] = {
	/*	540,	541,	542,	543,	544,	545,	546,	547,	548,	549, */
		-40,	-40,	-40,	-40,	-39,	-39,	-38,	-38,	-38,	-37,

	/*	550,	551,	552,	553,	554,	555,	556,	557,	558,	559, */
		-37,	-36,	-36,	-36,	-35,	-35,	-34,	-34,	-33,	-33,

	/*	560,	561,	562,	563,	564,	565,	566,	567,	568,	569, */
		-32,	-32,	-32,	-31,	-31,	-30,	-30,	-30,	-29,	-29,

	/*	570,	571,	572,	573,	574,	575,	576,	577,	578,	579, */
		-28,	-28,	-28,	-27,	-26,	-26,	-26,	-25,	-25,	-24,

	/*	580,	581,	582,	583,	584,	585,	586,	587,	588,	589, */
		-24,	-24,	-23,	-23,	-22,	-22,	-22,	-21,	-21,	-20,

	/*	590,	591,	592,	593,	594,	595,	596,	597,	598,	599, */
		-20,	-19,	-19,	-18,	-18,	-18,	-17,	-17,	-16,	-16,

	/*	600,	601,	602,	603,	604,	605,	606,	607,	608,	609, */
		-16,	-15,	-15,	-14,	-14,	-14,	-13,	-13,	-12,	-12,

	/*	610,	611,	612,	613,	614,	615,	616,	617,	618,	619, */
		-11,	-11,	-10,	-10,	-10,	-9,	-9,	-8,	-8,	-8,

	/*	620,	621,	622,	623,	624,	625,	626,	627,	628,	629, */
		-7,	-7,	-6,	-6,	-6,	-5,	-5,	-4,	-4,	-3,

	/*	630,	631,	632,	633,	634,	635,	636,	637,	638,	639, */
		-3,	-2,	-2,	-2,	-1,	-1,	0,	0,	0,	1,

	/*	640,	641,	642,	643,	644,	645,	646,	647,	648,	649, */
		1,	2,	2,	2,	3,	3,	4,	4,	5,	5,

	/*	650,	651,	652,	653,	654,	655,	656,	657,	658,	659, */
		6,	6,	6,	7,	7,	8,	8,	8,	9,	9,

	/*	660,	661,	662,	663,	664,	665,	666,	667,	668,	669, */
		10,	10,	10,	11,	11,	12,	12,	12,	13,	13,

	/*	670,	671,	672,	673,	674,	675,	676,	677,	678,	679, */
		14,	14,	15,	15,	16,	16,	16,	17,	17,	18,

	/*	680,	681,	682,	683,	684,	685,	686,	687,	688,	689, */
		18,	18,	19,	19,	20,	20,	20,	21,	21,	22,

	/*	690,	691,	692,	693,	694,	695,	696,	697,	698,	699, */
		22,	23,	23,	24,	24,	24,	25,	25,	26,	26,

	/*	700,	701,	702,	703,	704,	705,	706,	707,	708,	709, */
		26,	27,	27,	28,	28,	28,	29,	29,	30,	30,

	/*	710,	711,	712,	713,	714,	715,	716,	717,	718,	719, */
		30,	31,	31,	32,	32,	33,	33,	34,	34,	34,

	/*	720,	721,	722,	723,	724,	725,	726,	727,	728,	729, */
		35,	35,	36,	36,	36,	37,	37,	38,	38,	38,

	/*	730,	731,	732,	733,	734,	735,	736,	737,	738,	739, */
		39,	39,	40,	40,	40,	41,	41,	42,	42,	42,

	/*	740,	741,	742,	743,	744,	745,	746,	747,	748,	749, */
		43,	43,	44,	44,	45,	45,	46,	46,	46,	47,

	/*	750,	751,	752,	753,	754,	755,	756,	757,	758,	759, */
		47,	48,	48,	48,	49,	49,	50,	50,	50,	51,

	/*	760,	761,	762,	763,	764,	765,	766,	767,	768,	769, */
		51,	52,	52,	52,	53,	53,	54,	54,	54,	55,

	/*	770,	771,	772,	773,	774,	775,	776,	777,	778,	779, */
		55,	56,	56,	57,	57,	58,	58,	58,	59,	59,

	/*	780,	781,	782,	783,	784,	785,	786,	787,	788,	789, */
		60,	60,	60,	61,	61,	62,	62,	62,	63,	63,

	/*	790,	791,	792,	793,	794,	795,	796,	797,	798,	799, */
		64,	64,	64,	65,	65,	66,	66,	66,	67,	67,

	/*	800,	801,	802,	803,	804,	805,	806,	807,	808,	809, */
		68,	68,	68,	69,	69,	70,	70,	70,	71,	71,

	/*	810,	811,	812,	813,	814,	815,	816,	817,	818,	819, */
		72,	72,	73,	73,	74,	74,	74,	75,	75,	76,

	/*	820,	821,	822,	823,	824,	825,	826,	827,	828,	829, */
		76,	76,	77,	77,	78,	78,	78,	79,	79,	80,

	/*	830,	831,	832,	833,	834,	835,	836,	837,	838,	839, */
		80,	80,	81,	81,	82,	82,	82,	83,	83,	84,

	/*	840,	841,	842,	843,	844,	845,	846,	847,	848,	849, */
		84,	84,	85,	85,	86,	86,	86,	87,	87,	88,

	/*	850,	851,	852,	853,	854,	855,	856,	857,	858,	859, */
		88,	88,	89,	89,	90,	90,	90,	91,	91,	92,

	/*	860,	861,	862,	863,	864,	865,	866,	867,	868,	869, */
		92,	92,	93,	93,	94,	94,	94,	95,	95,	96,

	/*	870,	871,	872,	873,	874,	875,	876,	877,	878,	879, */
		96,	96,	97,	97,	98,	98,	99,	99,	100,	100,

	/*	880,	881,	882,	883,	884,	885,	886,	887,	888,	889, */
		100,	101,	101,	102,	102,	102,	103,	103,	104,	104,

	/*	890,	891,	892,	893,	894,	895,	896,	897,	898,	899, */
		104,	105,	105,	106,	106,	106,	107,	107,	108,	108,

	/*	900,	901,	902,	903,	904,	905,	906,	907,	908,	909, */
		108,	109,	109,	110,	110,	110,	111,	111,	112,	112,

	/*	910,	911,	912,	913,	914,	915,	916,	917,	918,	919, */
		112,	113,	113,	114,	114,	114,	115,	115,	116,	116,

	/*	920,	921,	922,	923,	924,	925,	926,	927,	928,	929, */
		116,	117,	117,	118,	118,	118,	119,	119,	120,	120,

	/*	930,	931,	932,	933,	934,	935,	936,	937,	938,	939, */
		120,	121,	121,	122,	122,	122,	123,	123,	124,	124,

	/*	940,	941,	942,	943,	944,	945*/
		124,	125,	125,	125,	125,	125
};

#define OMAP5_ADC_TABLE_BEGIN	540
/* returns a 10 bit field use in combination with << for 10bits other than LSB */
#define OMAP5_ADC_MASK		0x3ff
#define OMAP5_ADC_SHIFT		0

/* FIFO tagged temperature */
enum dtemp_tags
{
  DTEMP_TAG_0 = 0,
  DTEMP_TAG_1 = 1,
  DTEMP_TAG_2 = 2,
  DTEMP_TAG_3 = 3,
  DTEMP_TAG_4 = 4,
  NUM_DTEMP_TAGS
};

#endif
