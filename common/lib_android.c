/*
 *
 * @Component			OMAPCONF
 * @Filename			lib_android.c
 * @Description			Android Library for OMAPCONF
 * @Author			Patrick Titiano (p-titiano@ti.com)
 * @Date			2010
 * @Copyright			Texas Instruments Incorporated
 *
 *
 * Copyright (C) 2010 Texas Instruments Incorporated - http://www.ti.com/
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


#include <lib_android.h>
#include <stdio.h>
#include <lib.h>
#include <string.h>


/* #define LIB_ANDROID_DEBUG */
#ifdef LIB_ANDROID_DEBUG
#define dprintf(format, ...)	 printf(format, ## __VA_ARGS__)
#else
#define dprintf(format, ...)
#endif


const char *android_pastry_names[PASTRY_ID_MAX] = {
	"GingerBread",
	"HoneyComb",
	"Ice Cream Sandwich",
	"Jelly Bean",
	"Unknown"};


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		os_is_android
 * @BRIEF		check if running OS is Android.
 * @RETURNS		1 if running OS is Android.
 *			0 if running OS is NOT Android.
 * @DESCRIPTION		check if running OS is Android.
 *//*------------------------------------------------------------------------ */
unsigned short os_is_android(void)
{
	FILE *fp = NULL;

	/*
	 * Try to open /sys/power/wake_lock file.
	 * If successfull, OS is Android (Generic Linux Kernel does not
	 * support it).
	 */
	fp = fopen("/sys/power/wake_lock", "r");
	if (fp == NULL) {
		return 0;
	} else {
		fclose(fp);
		return 1;
	}
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		wakelock_acquire
 * @BRIEF		acquire wakelock to avoid device off mode to happen.
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_NOT_AVAILABLE
 * @DESCRIPTION		acquire wakelock to avoid device off mode to happen.
 *//*------------------------------------------------------------------------ */
int wakelock_acquire(void)
{
	FILE *fp = NULL;

	fp = fopen("/sys/power/wake_lock", "w");
	if (fp == NULL) {
		fprintf(stderr, "%s(): error OS is not Android!!!\n", __func__);
		return OMAPCONF_ERR_NOT_AVAILABLE;
	}

	fprintf(fp, "omapconf");
	fclose(fp);
	return 0;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		wakelock_release
 * @BRIEF		release wakelock.
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_NOT_AVAILABLE
 * @DESCRIPTION		release wakelock.
 *//*------------------------------------------------------------------------ */
int wakelock_release(void)
{
	FILE *fp = NULL;

	fp = fopen("/sys/power/wake_unlock", "w");
	if (fp == NULL) {
		fprintf(stderr, "%s(): error OS is not Android!!!\n", __func__);
		return OMAPCONF_ERR_NOT_AVAILABLE;
	}

	fprintf(fp, "omapconf");
	fclose(fp);
	return 0;
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		android_pastry_name_get
 * @BRIEF		return pastry name
 * @RETURNS		pastry name
 *			NULL in case of incorrect id
 * @param[in]		id: pastry ID
 * @DESCRIPTION		return pastry name
 *//*------------------------------------------------------------------------ */
const char *android_pastry_name_get(android_pastry_id id)
{
	CHECK_ARG_LESS_THAN(id, PASTRY_ID_MAX, NULL);

	return android_pastry_names[id];
}


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		android_pastry_get
 * @BRIEF		retrieve the running Android pastry,
 *			parsing "/system/build.prop".
 * @RETURNS		Android pastry
 *			PASTRY_UNKNOWN if the running pastry is unknown
 *			PASTRY_ID_MAX if OS is not Android or in case of error
 * @DESCRIPTION		retrieve the running Android pastry,
 *			parsing "/system/build.prop".
 *//*------------------------------------------------------------------------ */
android_pastry_id android_pastry_get(void)
{
	FILE *fp = NULL;
	char *version_file = NULL;
	char line[256];
	unsigned int version, rev_major, rev_minor;
	int ret;
	static android_pastry_id pastry_id =
		(android_pastry_id) (PASTRY_ID_MAX + 1);

	if (pastry_id != PASTRY_ID_MAX + 1) {
		/* Pastry already retrieved, return saved value */
		dprintf("%s(): pastry is %s (%u)\n", __func__,
			android_pastry_name_get(pastry_id), pastry_id);
		return pastry_id;
	}

	if (!os_is_android()) {
		pastry_id = PASTRY_ID_MAX;
		return pastry_id;
	}

	fp = fopen("/system/build.prop", "r");
	if (fp == NULL) {
		fprintf(stderr, "%s(): could not open %s file?!\n",
			__func__, version_file);
		pastry_id = PASTRY_ID_MAX;
		return pastry_id;
	}

	/* Retrieve pastry */
	while (fgets(line, 256, fp) != NULL) {
		/* Remove endind '\n' */
		line[strlen(line) - 1] = '\0';
		dprintf("%s(): line=%s len=%u\n", __func__, line, strlen(line));
		/* Looking for the "ro.build.version.release" property line */
		if (strstr(line, "ro.build.version.release=") == NULL)
			continue;
		fclose(fp);
		dprintf("%s(): ro.build.version.release line found.\n",
			__func__);
		ret = sscanf(line, "ro.build.version.release=%u.%u.%u",
			&version, &rev_major, &rev_minor);
		dprintf("%s(): sscanf()=%u,"
			" version=%u rev_major=%u rev_minor=%u\n",
			__func__, ret, version, rev_major, rev_minor);
		if (ret < 2) {
			pastry_id = PASTRY_UNKNOWN;
			dprintf("%s(): pastry unknown, sscanf()=%u\n",
				__func__, ret);
		} else {
			if (version == 2)
				pastry_id = PASTRY_GB;
			else if (version == 3)
				pastry_id = PASTRY_HC;
			else if ((version == 4) && (rev_major == 0))
				pastry_id = PASTRY_ICS;
			else if ((version == 4) && (rev_major >= 1))
				pastry_id = PASTRY_JB;
			else
				pastry_id = PASTRY_UNKNOWN;
		}
		dprintf("%s(): pastry is %s (%u)\n", __func__,
			android_pastry_name_get(pastry_id), pastry_id);
		return pastry_id;
	}

	fclose(fp);
	pastry_id = PASTRY_ID_MAX;
	dprintf("%s(): eof reached! pastry is %s (%u)\n", __func__,
		android_pastry_name_get(pastry_id), pastry_id);
	return pastry_id;
}
