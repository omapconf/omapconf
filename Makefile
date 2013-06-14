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


DEF_INC := $(shell $(CROSS_COMPILE)gcc  -print-file-name=include)


DEF_INC_PATH = -I. -Icommon -Ipmic -Iaudioic -Ilinux -Ii2c-tools\
	-Iarch/arm/mach-omap/common\
	-Iarch/arm/mach-omap/common/prcm\
	-Iarch/arm/mach-omap/common/statcoll\
	-Iarch/arm/mach-omap/omap4\
	-Iarch/arm/mach-omap/omap4/prcm\
	-Iarch/arm/mach-omap/omap4/dpll\
	-Iarch/arm/mach-omap/omap4/pmi\
	-Iarch/arm/mach-omap/omap5\
	-Iarch/arm/mach-omap/omap5/prcm\
	-Iarch/arm/mach-omap/omap5/dpll\
	-Iarch/arm/mach-omap/omap5/ctrlmod\
	-Iarch/arm/mach-omap/dra7


STATIC_BUILD ?= -static


MYCFLAGS+=$(CFLAGS) -D_OMAP5430 -D_SC_VER_1_16 -c -Wall -Wextra\
	-Wno-missing-field-initializers -I$(DEF_INC) $(DEF_INC_PATH)\
	$(STATIC_BUILD)


DESTDIR ?= target




OMAPSOURCES=\
		arch/arm/mach-omap/common/prcm/prcm-module.c\
		arch/arm/mach-omap/common/prcm/clkdm.c\
		arch/arm/mach-omap/common/prcm/pwrdm.c\
		arch/arm/mach-omap/common/prcm/abb.c\
		arch/arm/mach-omap/common/prcm/clkdm_dependency.c\
		arch/arm/mach-omap/common/prcm/vp.c\
		arch/arm/mach-omap/common/prcm/vc.c\
		arch/arm/mach-omap/common/dpll.c\
		arch/arm/mach-omap/common/sr.c\
		arch/arm/mach-omap/common/emif.c\
		arch/arm/mach-omap/common/module.c\
		arch/arm/mach-omap/common/clockdomain.c\
		arch/arm/mach-omap/common/powerdomain.c\
		arch/arm/mach-omap/common/voltdomain.c\
		arch/arm/mach-omap/common/statcoll/sci_swcapture.c\
		arch/arm/mach-omap/common/statcoll/sci.c\
		arch/arm/mach-omap/common/statcoll/cToolsHelper.c\
		arch/arm/mach-omap/common/timestamp_32k.c

OMAPOBJECTS=	$(OMAPSOURCES:.c=.o)




OMAP4SOURCES=\
		arch/arm/mach-omap/omap4/prcm/module44xx-data.c\
		arch/arm/mach-omap/omap4/prcm/clock44xx.c\
		arch/arm/mach-omap/omap4/prcm/clkdm44xx.c\
		arch/arm/mach-omap/omap4/prcm/pwrdm44xx.c\
		arch/arm/mach-omap/omap4/prcm/voltdm44xx.c\
		arch/arm/mach-omap/omap4/prcm/abb44xx.c\
		arch/arm/mach-omap/omap4/prcm/vp44xx.c\
		arch/arm/mach-omap/omap4/prcm/vp44xx-data.c\
		arch/arm/mach-omap/omap4/prcm/vc44xx.c\
		arch/arm/mach-omap/omap4/prcm/gfx44xx.c\
		arch/arm/mach-omap/omap4/prcm/ivahd44xx.c\
		arch/arm/mach-omap/omap4/prcm/abe44xx.c\
		arch/arm/mach-omap/omap4/prcm/l3init44xx.c\
		arch/arm/mach-omap/omap4/prcm/mpu44xx.c\
		arch/arm/mach-omap/omap4/prcm/wkdep44xx.c\
		arch/arm/mach-omap/omap4/prcm/core44xx.c\
		arch/arm/mach-omap/omap4/prcm/per44xx.c\
		arch/arm/mach-omap/omap4/prcm/dsp44xx.c\
		arch/arm/mach-omap/omap4/prcm/prcm44xx.c\
		arch/arm/mach-omap/omap4/prcm/camera44xx.c\
		arch/arm/mach-omap/omap4/prcm/dep44xx.c\
		arch/arm/mach-omap/omap4/prcm/alwon44xx.c\
		arch/arm/mach-omap/omap4/prcm/emu44xx.c\
		arch/arm/mach-omap/omap4/prcm/dss44xx.c\
		arch/arm/mach-omap/omap4/prcm/cam44xx.c\
		arch/arm/mach-omap/omap4/prcm/wkup44xx.c\
		arch/arm/mach-omap/omap4/dpll/dpll44xx.c\
		arch/arm/mach-omap/omap4/dpll/dpll44xx-data.c\
		arch/arm/mach-omap/omap4/dpll/dpll4470-data-38_4MHz.c\
		arch/arm/mach-omap/omap4/dpll/dpll4460-data-38_4MHz.c\
		arch/arm/mach-omap/omap4/dpll/dpll4430-data-38_4MHz.c\
		arch/arm/mach-omap/omap4/pmi/coresight44xx.c\
		arch/arm/mach-omap/omap4/pmi/stm44xx.c\
		arch/arm/mach-omap/omap4/pmi/pmi44xx.c\
		arch/arm/mach-omap/omap4/pmi/pmi44xx_pwrdm.c\
		arch/arm/mach-omap/omap4/pmi/pmi44xx_voltdm.c\
		arch/arm/mach-omap/omap4/pmi/power_trace44xx.c\
		arch/arm/mach-omap/omap4/module44xx.c\
		arch/arm/mach-omap/omap4/cpuinfo44xx.c\
		arch/arm/mach-omap/omap4/lib44xx.c\
		arch/arm/mach-omap/omap4/audit44xx.c\
		arch/arm/mach-omap/omap4/mpuss44xx.c\
		arch/arm/mach-omap/omap4/smartreflex44xx.c\
		arch/arm/mach-omap/omap4/main44xx.c\
		arch/arm/mach-omap/omap4/hwobs44xx.c\
		arch/arm/mach-omap/omap4/temperature44xx.c\
		arch/arm/mach-omap/omap4/ctt44xx.c\
		arch/arm/mach-omap/omap4/pct44xx.c\
		arch/arm/mach-omap/omap4/emif44xx.c\
		arch/arm/mach-omap/omap4/counters44xx.c\
		arch/arm/mach-omap/omap4/l2cc44xx.c\
		arch/arm/mach-omap/omap4/display44xx.c\
		arch/arm/mach-omap/omap4/uc_audit44xx.c\
		arch/arm/mach-omap/omap4/help44xx.c\
		arch/arm/mach-omap/omap4/sr44xx-data.c\
		arch/arm/mach-omap/omap4/pads44xx.c\
		arch/arm/mach-omap/omap4/opp44xx.c


OMAP4OBJECTS=	$(OMAP4SOURCES:.c=.o)




OMAP5SOURCES=\
		arch/arm/mach-omap/omap5/prcm/cm54xxes1-defs.c\
		arch/arm/mach-omap/omap5/prcm/cm54xx-defs.c\
		arch/arm/mach-omap/omap5/prcm/cm54xx.c\
		arch/arm/mach-omap/omap5/prcm/prm54xxes1-defs.c\
		arch/arm/mach-omap/omap5/prcm/prm54xx-defs.c\
		arch/arm/mach-omap/omap5/prcm/prm54xx.c\
		arch/arm/mach-omap/omap5/prcm/clock54xx.c\
		arch/arm/mach-omap/omap5/prcm/abb54xx.c\
		arch/arm/mach-omap/omap5/prcm/vp54xx.c\
		arch/arm/mach-omap/omap5/prcm/vc54xx.c\
		arch/arm/mach-omap/omap5/prcm/clkdm_dependency54xx.c\
		arch/arm/mach-omap/omap5/prcm/clkdm_dependency54xxes1-data.c\
		arch/arm/mach-omap/omap5/prcm/clkdm_dependency54xx-data.c\
		arch/arm/mach-omap/omap5/prcm/prcm54xx.c\
		arch/arm/mach-omap/omap5/prcm/voltdm54xx.c\
		arch/arm/mach-omap/omap5/prcm/pwrdm54xx.c\
		arch/arm/mach-omap/omap5/prcm/clkdm54xx.c\
		arch/arm/mach-omap/omap5/prcm/module54xx.c\
		arch/arm/mach-omap/omap5/dpll/dpll54xx.c\
		arch/arm/mach-omap/omap5/dpll/dpll54xx-data.c\
		arch/arm/mach-omap/omap5/dpll/dpll54xx-data-19_2MHz.c\
		arch/arm/mach-omap/omap5/dpll/dpll54xx-data-38_4MHz.c\
		arch/arm/mach-omap/omap5/ctrlmod/ctrlmod_core54xx-defs.c\
		arch/arm/mach-omap/omap5/ctrlmod/ctrlmod_core_pad54xx-defs.c\
		arch/arm/mach-omap/omap5/ctrlmod/ctrlmod_wkup54xx-defs.c\
		arch/arm/mach-omap/omap5/ctrlmod/ctrlmod_wkup_pad54xx-defs.c\
		arch/arm/mach-omap/omap5/ctrlmod/ctrlmod54xx.c\
		arch/arm/mach-omap/omap5/ctrlmod/ctrlmod54xx-data.c\
		arch/arm/mach-omap/omap5/abe54xx.c\
		arch/arm/mach-omap/omap5/cpuinfo54xx.c\
		arch/arm/mach-omap/omap5/main54xx.c\
		arch/arm/mach-omap/omap5/sr54xx-defs.c\
		arch/arm/mach-omap/omap5/sr54xx.c\
		arch/arm/mach-omap/omap5/help54xx.c\
		arch/arm/mach-omap/omap5/audit54xx.c\
		arch/arm/mach-omap/omap5/lib54xx.c\
		arch/arm/mach-omap/omap5/temp54xx.c\
		arch/arm/mach-omap/omap5/sysconfig54xx-defs.c\
		arch/arm/mach-omap/omap5/hwobs54xx.c\
		arch/arm/mach-omap/omap5/emif54xxes1-defs.c\
		arch/arm/mach-omap/omap5/emif54xx-defs.c\
		arch/arm/mach-omap/omap5/emif54xx.c\
		arch/arm/mach-omap/omap5/ctt54xx.c\
		arch/arm/mach-omap/omap5/opp54xx.c

OMAP5OBJECTS=	$(OMAP5SOURCES:.c=.o)




DRA7SOURCES=\
		arch/arm/mach-omap/dra7/cpuinfo_dra7xx.c

DRA7OBJECTS=	$(DRA7SOURCES:.c=.o)




SOURCES=\
		omapconf.c\
		common/lib.c\
		common/reg.c\
		common/autoadjust_table.c\
		common/genlist.c\
		common/cpuinfo.c\
		common/help.c\
		common/audit.c\
                common/lib_android.c\
                common/mem.c\
                common/trace.c\
                common/opp.c\
                common/temperature.c\
		pmic/pmic.c

OBJECTS=	$(SOURCES:.c=.o)




PMICSOURCES=	pmic/twl603x.c pmic/tps62361.c pmic/twl603x_lib.c

PMICOBJECTS=	$(PMICSOURCES:.c=.o)




AUDIOICSOURCES=	audioic/twl6040.c audioic/twl6040_lib.c

AUDIOICOBJECTS=	$(AUDIOICSOURCES:.c=.o)




LINUXSOURCES=	linux/cpufreq.c linux/cstate.c linux/interrupts.c\
		linux/timer_stats.c linux/linux_mem.c


LINUXOBJECTS=	$(LINUXSOURCES:.c=.o)




I2CSOURCES=\
		i2c-tools/i2cbusses.c\
		i2c-tools/i2cget.c\
		i2c-tools/i2cset.c\
		i2c-tools/util.c\

I2COBJECTS=	$(I2CSOURCES:.c=.o)



ALLSOURCES=	$(SOURCES) $(OMAPSOURCES) $(OMAP4SOURCES) $(OMAP5SOURCES)\
		$(DRA7SOURCES) $(LINUXSOURCES) $(PMICSOURCES)\
		$(AUDIOICSOURCES) $(I2CSOURCES)


ALLOBJECTS=	$(OBJECTS) $(OMAPOBJECTS) $(OMAP4OBJECTS) $(OMAP5OBJECTS)\
		$(DRA7OBJECTS) $(LINUXOBJECTS) $(PMICOBJECTS)\
		$(AUDIOICOBJECTS) $(I2COBJECTS)




EXECUTABLE=	omapconf


.PHONY:	tags cscope

all: 		$(EXECUTABLE)




$(EXECUTABLE):	$(ALLOBJECTS) builddate.o
		$(CC) $(STATIC_BUILD) $(LDFLAGS) $(ALLOBJECTS) builddate.o \
		-lrt -o $@




.c.o:
		$(CC) $(MYCFLAGS) $< -o $@




builddate.c:	$(ALLOBJECTS)
		echo 'char *builddate="'`date`'";' > builddate.c





install: 	$(EXECUTABLE)
		install -d $(DESTDIR)
		install omapconf $(DESTDIR)




install_android: $(EXECUTABLE)
		adb push omapconf /data/


tags: $(ALLSOURCES)
	ctags $(ALLSOURCES)


cscope: $(ALLSOURCES)
	cscope -b $(ALLSOURCES)


clean:
		rm -f $(EXECUTABLE) *.o builddate.c
		rm -f $(OBJECTS)
		rm -f $(LINUXOBJECTS)
		rm -f $(OMAPOBJECTS)
		rm -f $(OMAP4OBJECTS)
		rm -f $(OMAP5OBJECTS)
		rm -f $(DRA7OBJECTS)
		rm -f $(PMICOBJECTS)
		rm -f $(AUDIOICOBJECTS)
		rm -f $(I2COBJECTS)
		rm -f tags cscope.out
