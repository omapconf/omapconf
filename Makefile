#/*
# *
# * @Component			OMAPCONF
# * @Filename			Makefile
# * @Description		Makefile for omapconf
# * @Author			Patrick Titiano (p-titiano@ti.com)
# * @Date			2006
# * @Copyright			Texas Instruments Incorporated
# *
# *
# * Copyright (C) 2006 Texas Instruments Incorporated - http://www.ti.com/
# *
# *
# *  Redistribution and use in source and binary forms, with or without
# *  modification, are permitted provided that the following conditions
# *  are met:
# *
# *    Redistributions of source code must retain the above copyright
# *    notice, this list of conditions and the following disclaimer.
# *
# *    Redistributions in binary form must reproduce the above copyright
# *    notice, this list of conditions and the following disclaimer in the
# *    documentation and/or other materials provided with the
# *    distribution.
# *
# *    Neither the name of Texas Instruments Incorporated nor the names of
# *    its contributors may be used to endorse or promote products derived
# *    from this software without specific prior written permission.
# *
# *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
# *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
# *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
# *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
# *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
# *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
# *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
# *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
# *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
# *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
# *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
# *
# */

CC = $(CROSS_COMPILE)gcc
DEF_INC := $(shell $(CC) -print-file-name=include)
STATIC_BUILD ?= -static
MYCFLAGS += $(CFLAGS) -D_OMAP5430 -D_SC_VER_1_16 -c $(STATIC_BUILD) -Wall \
            -Wextra -Wno-missing-field-initializers -I. -Icommon -Ipmic \
            -Iaudioic -Ilinux -Istatcoll -Iomap4 -Iomap5 -Ii2c-tools \
            -I$(DEF_INC)
DESTDIR ?= target


OMAP4SOURCES=	omap4/clock44xx.c omap4/clkdm44xx.c omap4/pwrdm44xx.c\
		omap4/voltdm44xx.c omap4/module44xx.c omap4/cpuinfo44xx.c\
		omap4/lib44xx.c omap4/gfx44xx.c omap4/ivahd44xx.c\
		omap4/abe44xx.c omap4/wkup44xx.c omap4/audit44xx.c\
		omap4/l3init44xx.c omap4/mpuss44xx.c omap4/alwon44xx.c\
		omap4/emu44xx.c omap4/smartreflex44xx.c omap4/main44xx.c\
		omap4/dpll44xx.c omap4/mpu44xx.c omap4/wkdep44xx.c\
		omap4/core44xx.c omap4/per44xx.c omap4/dsp44xx.c\
		omap4/dss44xx.c omap4/cam44xx.c omap4/hwobs44xx.c\
		omap4/abb44xx.c omap4/temperature44xx.c omap4/ctt44xx.c\
		omap4/pct44xx.c omap4/emif44xx.c omap4/coresight44xx.c\
		omap4/stm44xx.c omap4/pmi44xx.c omap4/pmi44xx_pwrdm.c\
		omap4/counters44xx.c omap4/l2cc44xx.c\
		omap4/pmi44xx_voltdm.c omap4/power_trace44xx.c\
		omap4/display44xx.c omap4/prcm44xx.c omap4/camera44xx.c\
		omap4/dep44xx.c omap4/uc_audit44xx.c\
		omap4/help44xx.c omap4/module44xx-data.c\
		omap4/vc44xx.c omap4/sr44xx-data.c omap4/vp44xx.c\
		omap4/vp44xx-data.c omap4/dpll44xx-data.c\
		omap4/dpll4470-data-38_4MHz.c\
		omap4/dpll4460-data-38_4MHz.c\
		omap4/dpll4430-data-38_4MHz.c omap4/pads44xx.c\
		omap4/opp44xx.c

OMAP4OBJECTS=	$(OMAP4SOURCES:.c=.o)


OMAP5SOURCES=	omap5/cpuinfo54xx.c omap5/main54xx.c omap5/cm54xx-defs.c\
		omap5/cm54xx.c omap5/prm54xx-defs.c omap5/prm54xx.c\
		omap5/sr54xx-defs.c omap5/sr54xx.c omap5/dss54xx.c\
		omap5/wkupaon54xx.c omap5/cam54xx.c omap5/dsp54xx.c\
		omap5/abe54xx.c omap5/gpu54xx.c omap5/coreaon54xx.c\
		omap5/iva54xx.c omap5/mpu54xx.c omap5/l3init54xx.c\
		omap5/core54xx.c omap5/l4per54xx.c omap5/prmdevice54xx.c\
		omap5/emu54xx.c omap5/ckgen54xx.c omap5/instr54xx.c\
		omap5/help54xx.c omap5/dpll54xx.c omap5/prcm54xx.c\
		omap5/clock54xx.c omap5/voltdm54xx.c omap5/pwrdm54xx.c\
		omap5/clkdm54xx.c omap5/module54xx-data.c\
		omap5/module54xx.c omap5/dpll54xx-data.c\
		omap5/dpll54xx-data-19_2MHz.c\
		omap5/dpll54xx-data-38_4MHz.c\
		omap5/audit54xx.c omap5/lib54xx.c\
		omap5/ctrlmod_core54xx-defs.c\
		omap5/ctrlmod_core_pad54xx-defs.c\
		omap5/ctrlmod_wkup54xx-defs.c\
		omap5/ctrlmod_wkup_pad54xx-defs.c omap5/ctrlmod54xx.c\
		omap5/ctrlmod54xx-data.c omap5/temp54xx.c\
		omap5/sysconfig54xx-defs.c omap5/hwobs54xx.c\
		omap5/abb54xx.c omap5/emif54xx-defs.c omap5/emif54xx.c\
		omap5/clkdm_dependency54xx-data.c\
		omap5/clkdm_dependency54xx.c omap5/ctt54xx.c\
		omap5/vp54xx.c omap5/vc54xx.c omap5/opp54xx.c

OMAP5OBJECTS=	$(OMAP5SOURCES:.c=.o)


SOURCES=	omapconf.c builddate.c common/lib.c common/reg.c\
		common/autoadjust_table.c common/genlist.c common/abb.c\
		common/module.c common/clkdm.c common/pwrdm.c pmic/pmic.c\
		common/cpuinfo.c common/dpll.c i2c-tools/i2cbusses.c\
		i2c-tools/i2cget.c i2c-tools/i2cset.c i2c-tools/util.c\
		common/help.c common/clkdm_dependency.c\
		common/vp.c common/vc.c common/sr.c common/audit.c\
		statcoll/sci_swcapture.c statcoll/sci.c\
		statcoll/cToolsHelper.c common/timestamp_32k.c\
		common/lib_android.c common/mem.c common/emif.c\
		common/trace.c common/opp.c common/voltdm.c\
		common/temperature.c

OBJECTS=	$(SOURCES:.c=.o)


PMICSOURCES=	pmic/twl603x.c pmic/tps62361.c pmic/twl603x_lib.c


PMICOBJECTS=	$(PMICSOURCES:.c=.o)


AUDIOICSOURCES=	audioic/twl6040.c audioic/twl6040_lib.c


AUDIOICOBJECTS=	$(AUDIOICSOURCES:.c=.o)


LINUXSOURCES=	linux/cpufreq.c linux/cstate.c linux/interrupts.c\
		linux/timer_stats.c linux/linux_mem.c


LINUXOBJECTS=	$(LINUXSOURCES:.c=.o)


ALLOBJECTS=	$(OBJECTS) $(OMAP4OBJECTS) $(OMAP5OBJECTS) $(LINUXOBJECTS) \
		$(PMICOBJECTS) $(AUDIOICOBJECTS)


EXECUTABLE=	omapconf


all: 		$(SOURCES) $(ALLOBJECTS) $(EXECUTABLE)



$(EXECUTABLE):	$(ALLOBJECTS)
		$(CC) $(STATIC_BUILD) $(LDFLAGS) $(ALLOBJECTS) -lrt -o $@
		rm -f builddate.c


.c.o:
		$(CC) $(MYCFLAGS) $< -o $@


builddate.c:
		echo 'char *builddate="'`date`'";' > builddate.c


install: 	omapconf
		install -d $(DESTDIR)
		install omapconf $(DESTDIR)


install_android:omapconf
		adb push omapconf /data/


clean:
		rm -f omapconf *.o builddate.c
		rm -f $(OBJECTS)
		rm -f $(LINUXOBJECTS)
		rm -f $(OMAP4OBJECTS)
		rm -f $(OMAP5OBJECTS)
		rm -f $(PMICOBJECTS)
		rm -f $(AUDIOICOBJECTS)
