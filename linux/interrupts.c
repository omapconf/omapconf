/*
 *
 * @Component			OMAPCONF
 * @Filename			interrupts.c
 * @Description			Linux Kernel /proc/interrupts APIs
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


#include <lib.h>
#include <interrupts.h>
#include <cpuinfo.h>
#include <string.h>


/* #define INTERRUPTS_DEBUG */
#ifdef INTERRUPTS_DEBUG
#define dprintf(format, ...)	 printf(format, ## __VA_ARGS__)
#else
#define dprintf(format, ...)
#endif


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		irq_snapshot_save
 * @BRIEF		save a copy of the /proc/interrupts file
 * @RETURNS		0 in case of success
 *			IRQ_ERR_ARG
 *			IRQ_ERR_NOT_AVAILABLE
 *			IRQ_ERR_UNEXPECTED
 * @param[in,out]	file: copy file name
 * @DESCRIPTION		save a copy of the /proc/interrupts file
 *//*------------------------------------------------------------------------ */
int irq_snapshot_save(char *file)
{
	FILE *from, *to;
	char ch;

	if (file == NULL) {
		fprintf(stderr, "%s(): file == NULL!!!\n", __func__);
		return IRQ_ERR_ARG;
	}

	/* Open source file */
	from = fopen("/proc/interrupts", "rb");
	if (from == NULL) {
		fprintf(stderr, "%s(): cannot open /proc/interrupts file!\n",
			__func__);
		return IRQ_ERR_NOT_AVAILABLE;
	}

	/* Open destination file */
	to = fopen(file, "wb");
	if (to == NULL) {
		fprintf(stderr, "%s(): cannot open %s file!\n", __func__, file);
		return IRQ_ERR_ARG;
	}

	/* Copy the file */
	while (!feof(from)) {
		ch = fgetc(from);
		if (ferror(from)) {
			fprintf(stderr, "%s(): error reading "
				"/proc/interrupts file.\n", __func__);
			return IRQ_ERR_UNEXPECTED;
		}
		if (!feof(from))
			fputc(ch, to);
		if (ferror(to)) {
			fprintf(stderr, "%s(): error writing "
				"%s file.\n", __func__, file);
			return IRQ_ERR_UNEXPECTED;
		}
	}

	/* Close source file */
	if (fclose(from) == EOF) {
		fprintf(stderr, "%s(): error closing /proc/interrupts file.\n",
			__func__);
		return IRQ_ERR_UNEXPECTED;
	}

	/* Close destination file */
	if (fclose(to) == EOF) {
		fprintf(stderr, "%s(): error closing %s file.\n",
			__func__, file);
		return IRQ_ERR_UNEXPECTED;
	}

	return 0;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		irq_total_count_get
 * @BRIEF		return the total number of times CPU was interrupted
 * @RETURNS		0 in case of success
 *			IRQ_ERR_ARG
 *			IRQ_ERR_MALLOC
 *			IRQ_ERR_INTERNAL
 * @param[in,out]	fp: file descriptor of an opened /proc/interrupts file
 * @DESCRIPTION		return the total number of times CPU was interrupted
 *//*------------------------------------------------------------------------ */
int irq_total_count_get(FILE *fp)
{
	unsigned int cpu_count;
	char line[256];
	unsigned int irq_nbr, cpu0_irq_count, cpu1_irq_count, cpu2_irq_count,
		cpu3_irq_count, cpu4_irq_count, cpu5_irq_count, cpu6_irq_count,
		cpu7_irq_count, total_irq_count;
	char irq_ctrl_name[256], dev_name[256];
	int ret;

	cpu_count = cpu_online_cores_count_get();
	if (cpu_count == 0) {
		fprintf(stderr, "%s(): cpu_count == 0!\n", __func__);
		return IRQ_ERR_CPU;
	}
	if (fp == NULL) {
		fprintf(stderr, "%s(): fp == NULL!!!\n", __func__);
		return IRQ_ERR_ARG;
	}

	/* Get total interrupt count in fp */
	total_irq_count = 0;
	rewind(fp);
	while (fgets(line, sizeof(line), fp) != NULL) {
		dprintf("%s(): line = %s\n", __func__, line);
		cpu0_irq_count = cpu1_irq_count = 0;
		switch (cpu_count) {
		case 1:
			ret = sscanf(line, "%d: %d %s %s",
				&irq_nbr, &cpu0_irq_count,
				irq_ctrl_name, dev_name);
			if (ret != 4)
				continue;
			break;
		case 2:
			ret = sscanf(line, "%d: %d %d %s %s",
				&irq_nbr, &cpu0_irq_count, &cpu1_irq_count,
				irq_ctrl_name, dev_name);
			if (ret != 5)
				continue;
			break;
		case 4:
			ret = sscanf(line, "%d: %d %d %d %d %s %s",
				&irq_nbr, &cpu0_irq_count, &cpu1_irq_count,
				&cpu2_irq_count, &cpu3_irq_count,
				irq_ctrl_name, dev_name);
			if (ret != 7)
				continue;
			break;
		case 6:
			ret = sscanf(line, "%d: %d %d %d %d %d %d %s %s",
				&irq_nbr, &cpu0_irq_count, &cpu1_irq_count,
				&cpu2_irq_count, &cpu3_irq_count,
				&cpu4_irq_count, &cpu5_irq_count,
				irq_ctrl_name, dev_name);
			if (ret != 9)
				continue;
			break;
		case 8:
			ret = sscanf(line, "%d: %d %d %d %d %d %d %d %d %s %s",
				&irq_nbr, &cpu0_irq_count, &cpu1_irq_count,
				&cpu2_irq_count, &cpu3_irq_count,
				&cpu4_irq_count, &cpu5_irq_count,
				&cpu6_irq_count, &cpu7_irq_count,
				irq_ctrl_name, dev_name);
			if (ret != 11)
				continue;
			break;
		default:
			fprintf(stderr, "%s(): unknown architecture!\n",
				__func__);
		}
		dprintf("%s(): irq_nbr=%d, cpu0_irq_count=%d, "
			"cpu1_irq_count=%d\n",
			__func__, irq_nbr, cpu0_irq_count, cpu1_irq_count);
		total_irq_count += cpu0_irq_count + cpu1_irq_count;
		dprintf("%s(): total_irq_count=%d\n", __func__,
			total_irq_count);
	}
	rewind(fp);

	return total_irq_count;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		irq_count_get
 * @BRIEF		return the number of times a given interrupt woke up
 *			the CPU
 * @RETURNS		0 in case of success
 *			IRQ_ERR_ARG
 *			IRQ_ERR_MALLOC
 *			IRQ_ERR_INTERNAL
 * @param[in]		n: interrupt line number
 * @param[in,out]	fp: file descriptor of an opened /proc/interrupts file
 * @DESCRIPTION		return the number of times a given interrupt woke up
 *			the CPU
 *//*------------------------------------------------------------------------ */
int irq_count_get(unsigned int n, FILE *fp)
{
	unsigned int cpu_count;
	char line[256];
	unsigned int irq_nbr, cpu0_irq_count, cpu1_irq_count, cpu2_irq_count,
		cpu3_irq_count, cpu4_irq_count, cpu5_irq_count,
		cpu6_irq_count, cpu7_irq_count;
	char irq_ctrl_name[256], dev_name[256];
	int ret;

	cpu_count = cpu_online_cores_count_get();
	if (cpu_count == 0) {
		fprintf(stderr, "%s(): cpu_count == 0!\n", __func__);
		return IRQ_ERR_CPU;
	}
	if (fp == NULL) {
		fprintf(stderr, "%s(): fp == NULL!!!\n", __func__);
		return IRQ_ERR_ARG;
	}

	dprintf("%s(): getting irq #%u count ...\n", __func__, n);

	rewind(fp);
	ret = 0;
	while (fgets(line, sizeof(line), fp) != NULL) {
		dprintf("%s(): line = %s\n", __func__, line);
		cpu0_irq_count = cpu1_irq_count = cpu2_irq_count =
			cpu3_irq_count = cpu4_irq_count = cpu5_irq_count =
			cpu6_irq_count = cpu7_irq_count = 0;
		switch (cpu_count) {
		case 1:
			ret = sscanf(line, "%d: %d %s %s",
				&irq_nbr, &cpu0_irq_count,
				irq_ctrl_name, dev_name);
			if (ret != 4)
				continue;
			break;
		case 2:
			ret = sscanf(line, "%d: %d %d %s %s",
				&irq_nbr, &cpu0_irq_count, &cpu1_irq_count,
				irq_ctrl_name, dev_name);
			if (ret != 5)
				continue;
			break;
		case 4:
			ret = sscanf(line, "%d: %d %d %d %d %s %s",
				&irq_nbr, &cpu0_irq_count, &cpu1_irq_count,
				&cpu2_irq_count, &cpu3_irq_count,
				irq_ctrl_name, dev_name);
			if (ret != 7)
				continue;
			break;
		case 6:
			ret = sscanf(line, "%d: %d %d %d %d %d %d %s %s",
				&irq_nbr, &cpu0_irq_count, &cpu1_irq_count,
				&cpu2_irq_count, &cpu3_irq_count,
				&cpu4_irq_count, &cpu5_irq_count,
				irq_ctrl_name, dev_name);
			if (ret != 9)
				continue;
			break;
		case 8:
			ret = sscanf(line, "%d: %d %d %d %d %d %d %d %d %s %s",
				&irq_nbr, &cpu0_irq_count, &cpu1_irq_count,
				&cpu2_irq_count, &cpu3_irq_count,
				&cpu4_irq_count, &cpu5_irq_count,
				&cpu6_irq_count, &cpu7_irq_count,
				irq_ctrl_name, dev_name);
			if (ret != 11)
				continue;
			break;
		default:
			fprintf(stderr, "%s(): unknown architecture!\n",
				__func__);
			rewind(fp);
			return IRQ_ERR_INTERNAL;
		}
		dprintf("%s(): found line = %s\n", __func__, line);
		dprintf("%s(): irq_nbr=%d, cpu0_irq_count=%d, cpu1_irq_count=%d"
			" cpu2_irq_count=%d cpu3_irq_count=%d cpu4_irq_count=%d"
			" cpu5_irq_count=%d, cpu6_irq_count=%d, "
			"cpu7_irq_count=%d\n", __func__, irq_nbr,
				cpu0_irq_count, cpu1_irq_count,
				cpu2_irq_count, cpu3_irq_count,
				cpu4_irq_count, cpu5_irq_count,
				cpu6_irq_count, cpu7_irq_count);
		if (irq_nbr == n) {
			ret = cpu0_irq_count + cpu1_irq_count + cpu2_irq_count +
				cpu3_irq_count + cpu4_irq_count +
				cpu5_irq_count + cpu6_irq_count +
				cpu7_irq_count;
			break;
		}
	}
	dprintf("%s(): irq #%u count = %u\n", __func__, n, ret);
	rewind(fp);

	return ret;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		irq_dev_name_get
 * @BRIEF		return the name of the device associated to the
 *			interrupt line n
 * @RETURNS		name of the device associated to the interrupt line n
 *			NULL if not found
 * @param[in]		n: interrupt line number
 * @param[in,out]	fp: file descriptor of an opened /proc/interrupts file
 * @param[in,out]	name: name of the device associated to the interrupt
 *				line n
 * @DESCRIPTION		return the name of the device associated to the
 *			interrupt line n
 *//*------------------------------------------------------------------------ */
char *irq_dev_name_get(unsigned int n, FILE *fp, char name[256])
{
	unsigned int cpu_count;
	char line[256];
	unsigned int irq_nbr, cpu0_irq_count, cpu1_irq_count, cpu2_irq_count,
		cpu3_irq_count, cpu4_irq_count, cpu5_irq_count,
		cpu6_irq_count, cpu7_irq_count;
	char irq_ctrl_name[256], dev_name[256];
	char *pch;
	int ret;

	dprintf("%s(): looking for irq #%u name ...\n", __func__, n);
	cpu_count = cpu_online_cores_count_get();
	if (cpu_count == 0) {
		fprintf(stderr, "%s(): cpu_count == 0!\n", __func__);
		return NULL;
	}
	if (fp == NULL) {
		fprintf(stderr, "%s(): fp == NULL!!!\n", __func__);
		return NULL;
	}
	if (name == NULL) {
		fprintf(stderr, "%s(): name == NULL!!!\n", __func__);
		return NULL;
	}

	rewind(fp);
	while (fgets(line, sizeof(line), fp) != NULL) {
		/* Remove newline character at end of line */
		line[strlen(line) - 1] = '\0';
		dprintf("%s(): line = %s\n", __func__, line);
		switch (cpu_count) {
		case 1:
			ret = sscanf(line, "%d: %d %s %s",
				&irq_nbr, &cpu0_irq_count,
				irq_ctrl_name, dev_name);
			if (ret != 4)
				continue;
			break;
		case 2:
			ret = sscanf(line, "%d: %d %d %s %s",
				&irq_nbr, &cpu0_irq_count, &cpu1_irq_count,
				irq_ctrl_name, dev_name);
			if (ret != 5)
				continue;
			break;
		case 4:
			ret = sscanf(line, "%d: %d %d %d %d %s %s",
				&irq_nbr, &cpu0_irq_count, &cpu1_irq_count,
				&cpu2_irq_count, &cpu3_irq_count,
				irq_ctrl_name, dev_name);
			if (ret != 7)
				continue;
			break;
		case 6:
			ret = sscanf(line, "%d: %d %d %d %d %d %d %s %s",
				&irq_nbr, &cpu0_irq_count, &cpu1_irq_count,
				&cpu2_irq_count, &cpu3_irq_count,
				&cpu4_irq_count, &cpu5_irq_count,
				irq_ctrl_name, dev_name);
			if (ret != 9)
				continue;
			break;
		case 8:
			ret = sscanf(line, "%d: %d %d %d %d %d %d %d %d %s %s",
				&irq_nbr, &cpu0_irq_count, &cpu1_irq_count,
				&cpu2_irq_count, &cpu3_irq_count,
				&cpu4_irq_count, &cpu5_irq_count,
				&cpu6_irq_count, &cpu7_irq_count,
				irq_ctrl_name, dev_name);
			if (ret != 11)
				continue;
			break;
		default:
			fprintf(stderr, "%s(): unknown architecture!\n",
				__func__);
			rewind(fp);
			return NULL;
		}
		if (irq_nbr == n) {
			/*
			 * Device names may not be only single worded, so sscanf
			 * may not retrieve the full name.
			 * Solution: find the position of the controller name,
			 * shift pointer from its length + 2 space characters,
			 * and this is the pointer to the device name string.
			 */
			pch = strstr(line, irq_ctrl_name);
			pch = pch + strlen(irq_ctrl_name) + 2;
			strcpy(name, pch);
			rewind(fp);
			dprintf("%s(%d)=%s\n", __func__, n, name);
			return name;
		}
	}
	dprintf("%s(): irq #%u name not found?!...\n", __func__, n);
	rewind(fp);
	return NULL;
}
#undef dprintf
#ifdef INTERRUPTS_DEBUG
#define dprintf(format, ...)	 printf(format, ## __VA_ARGS__)
#else
#define dprintf(format, ...)
#endif


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		irq_occurred
 * @BRIEF		check if an interrupt fired between 2 /proc/interrupts
 *			snapshots
 * @RETURNS		IRQ_ERR_ARG
 *			0 if interrupt didn't wake up the CPU
 *			>0 number of times interrupt did wake up the CPU
 * @param[in]		n: IRQ line number
 * @param[in,out]	fp1: file descriptor of an opened /proc/interrupts file
 * @param[in,out]	fp2: file descriptor of a 2nd opened /proc/interrupts
 *				file
 * @DESCRIPTION		check if an interrupt fired between 2 /proc/interrupts
 *			snapshots
 *//*------------------------------------------------------------------------ */
int irq_occurred(unsigned int n, FILE *fp1, FILE *fp2)
{
	int count1, count2;

	if (fp1 == NULL) {
		fprintf(stderr, "%s(): fp1 == NULL!!!\n", __func__);
		return IRQ_ERR_ARG;
	}
	if (fp2 == NULL) {
		fprintf(stderr, "%s(): fp2 == NULL!!!\n", __func__);
		return IRQ_ERR_ARG;
	}

	count2 = irq_count_get(n, fp2);
	if (count2 < 0)
		return count2;
	count1 = irq_count_get(n, fp1);
	if (count1 < 0)
		return count1;

	return count2 - count1;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		irq_occurred_list_get
 * @BRIEF		parse 2 snapshots of /proc/interrupts file and fill list
 *			with information about occurred interrupt(s)
 * @RETURNS		0 in case of success
 *			IRQ_ERR_ARG
 * @param[in,out]	fp1: file descriptor of an opened /proc/interrupts file
 * @param[in,out]	fp2: file descriptor of a 2nd opened /proc/interrupts
 *			file
 * @param[in,out]	list: generic list where to store irq stats
 * @DESCRIPTION		parse 2 snapshots of /proc/interrupts file and fill list
 *			with information about occurred interrupt(s)
 *//*------------------------------------------------------------------------ */
int irq_occurred_list_get(FILE *fp1, FILE *fp2, genlist *list)
{
	unsigned int occurred_irqs_count;
	unsigned int irq_nbr;
	int count;
	irq_info inf;

	if (fp1 == NULL) {
		fprintf(stderr, "%s(): fp1 == NULL!!!\n", __func__);
		return IRQ_ERR_ARG;
	}
	if (fp2 == NULL) {
		fprintf(stderr, "%s(): fp2 == NULL!!!\n", __func__);
		return IRQ_ERR_ARG;
	}
	if (list == NULL) {
		fprintf(stderr, "%s(): list == NULL!!!\n", __func__);
		return IRQ_ERR_ARG;
	}

	genlist_init(list);
	occurred_irqs_count = 0;
	for (irq_nbr = 0; irq_nbr < 512; irq_nbr++) {
		count = irq_occurred(irq_nbr, fp1, fp2);
		if (count <= 0)
			continue;

		dprintf("%s(): IRQ #%d occurred %d times\n",
			__func__, irq_nbr, count);
		inf.nbr = irq_nbr;
		inf.count = count;
		irq_dev_name_get(irq_nbr, fp1, inf.dev_name);
		genlist_addtail(list, (void *) &inf, sizeof(irq_info));
		occurred_irqs_count++;
	}

	return occurred_irqs_count;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		irq_occurred_list_sort
 * @BRIEF		sort list by irq occurrence decreasing order
 * @RETURNS		0 in case of success
 *			IRQ_ERR_ARG
 *			IRQ_ERR_INTERNAL
 * @param[in,out]	list: populated list of IRQ stats.
 * @DESCRIPTION		sort list by irq occurrence decreasing order.
 *			Use bubble sort algorithm.
 *//*------------------------------------------------------------------------ */
int irq_occurred_list_sort(genlist *list)
{
	unsigned int i, max, tmpmax;
	irq_info inf1, inf2;

	if (list == NULL) {
		fprintf(stderr, "%s(): list = NULL!\n", __func__);
		return IRQ_ERR_ARG;
	}
	max = genlist_getcount(list);

	while (max > 0) {
		tmpmax = 0;
		for (i = 0; i < max - 1; i++) {
			genlist_get(list, i, (irq_info *) &inf1);
			genlist_get(list, i + 1, (irq_info *) &inf2);
			if (inf1.count < inf2.count) {
				genlist_add(list, (void *) &inf2,
					sizeof(irq_info), i);
				genlist_remove(list, i + 2);
				tmpmax = i + 1;
			}
		}
		max = tmpmax;
	}

	return 0;
}
