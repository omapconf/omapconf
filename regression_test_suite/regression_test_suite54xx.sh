#!/data/busybox/bin/bash
#===================================================================================
# FILE: regression_test_suite54xx.sh
#
# USAGE: regression_test_suite54xx.sh ref_version new_version
#
# DESCRIPTION: OMAPCONF No Regression Test Suite for OMAP5 platform.
#		Compare omapconf output from reference and new versions.
#		Report any discrepency.
#
# OPTIONS:
#		ref_version: name of the reference binary, INCLUDING PATH.
#		new_version: name of the new binary to be tested, INCLUDING PATH.
# REQUIREMENTS: TO BE RUN ON OMAP5 PLATFORM ONLY
# BUGS: ---
# NOTES: ---
# AUTHOR: Patrick Titiano
# COMPANY: Texas Instruments France
VERSION=1.02
# CREATED: 2011-12-22
# REVISION: ---
#===================================================================================


#=== FUNCTION ==================================================================
# NAME: compare
# DESCRIPTION: compare command result of 2 versions of omapconf
#		Save log in file.
# PARAMETER
#		1: omapconf command to be tested (including all parameters
#		2: test identification string
#		3: display new line at end of function (0: no, 1: yes)
# CREATED: 2011-12-16 / AUTHOR: Patrick Titiano
#===============================================================================
# Function
function compare {
	if [ $DEBUG = 1 ]; then
		echo "compare: arg1 = $1"
		echo "compare: arg2 = $2"
		echo "compare: arg3 = $3"
	fi

	# Generate names for log files based on omapconf revision and command tested
	logfile_ref=omapconf_"$(echo $2 | tr ' ' '_')"_ref_v"$ref_rev".log
	logfile_new=omapconf_"$(echo $2 | tr ' ' '_')"_new_v"$new_rev".log
	if [ $DEBUG = 1 ]; then
		echo "compare: logfile_ref = $logfile_ref"
		echo "compare: logfile_new = $logfile_new"
	fi

	# Execute the command with reference and new omapconf,
	# saving printed data into log files
	if [ $DEBUG = 1 ]; then
		echo "compare: $ref_omapconf_bin $1 > $logfile_ref"
		echo "compare: $new_omapconf_bin $1 > $logfile_new"
	fi

	$ref_omapconf_bin $1 &> $logfile_ref
	$new_omapconf_bin $1 &> $logfile_new

	# First line of log file will always be different (contains OMAPCONF/CHIPS/BUILD revision numbers).
	# busybox diff doesn't support -I option.
	# Use sed to remove first lines of log files before doing the diff.
	sed -i '1d' $logfile_ref
	sed -i '1d' $logfile_new
	sed -i '1d' $logfile_ref
	sed -i '1d' $logfile_new
	sed -i '1d' $logfile_ref
	sed -i '1d' $logfile_new
	sed -i '1d' $logfile_ref
	sed -i '1d' $logfile_new
	sed -i '1d' $logfile_ref
	sed -i '1d' $logfile_new
	sed -i '1d' $logfile_ref
	sed -i '1d' $logfile_new

	# Check if both log files are identical, indicating no regression occured.
	diff $logfile_ref $logfile_new > diff.log
	rm $logfile_ref $logfile_new

	# Increment counters depending on test results
	test_cpt=$[$test_cpt+1]
	if [ -s diff.log ]; then
		echo "$2 function regression test FAILED!" | tee -a $logfile
		cat diff.log >> $logfile
		cat diff.log
		test_fail_cpt=$[$test_fail_cpt+1]
	else
		echo "$2 function regression test passed." | tee -a $logfile
		test_pass_cpt=$[$test_pass_cpt+1]
	fi

	# Delete diff file
	rm diff.log

	if [ $3 = 1 ]; then
		echo | tee -a $logfile
	fi
}

rm -f $logfile
echo
echo OMAPCONF Non-Regression Test Suite v$VERSION | tee $logfile
echo | tee -a $logfile

#---------------------------------------------------------------------------------
# Init Variables
#---------------------------------------------------------------------------------
DEBUG=0
test_cpt=0
test_pass_cpt=0
test_fail_cpt=0
tests_list="rw pwst opp dpll prcm sr mpu dep abb abe emif temp export pmic audioic audit uc_audit trace camera display hwobs ctrlmod"

ref_omapconf_bin=$1
new_omapconf_bin=$2
if [ $DEBUG = 1 ]; then
	echo "ref_omapconf_bin = $ref_omapconf_bin"
	echo "new_omapconf_bin = $new_omapconf_bin"
fi

# Check number of arguments is ok
if [ $# = 2 ]; then
	all_tests=1
elif [ $# = 3 ]; then
	all_tests=0
	tests=$3
	tests_ok=0
	for t in $tests_list
	do
		if [ $t = $tests ]; then
			tests_ok=1
		fi
	done
	if [ $tests_ok = 0 ]; then
		echo "Invalid 'item'! ($tests)"
		echo "'item' can only be: $tests_list"
		exit 3
	fi
else
	echo "Usage: regression_test_suite54xx.sh reference_binary new_binary [item]"
	echo "  Use 'item' (optional) to select a specific set of test(s)."
	echo "  'item' can be: $tests_list"
	echo "  If omitted, full suite will be run by default."
	echo
	exit 3
fi

# Check reference and new omapconf binaries found
if [ ! -s $ref_omapconf_bin ]; then
	echo "Reference binary not found! ($ref_omapconf_bin)"
	echo
	exit 1
fi
if [ ! -s $new_omapconf_bin ]; then
	echo "New binary not found! ($new_omapconf_bin)"
	echo
	exit 2
fi

# Check reference register file is present
if [ ! -s regression_test_suite54xx_ref_settings.xml ]; then
	echo "Reference Register XML file ('regression_test_suite54xx_ref_settings.xml') not found!"
	echo "To generate it, type: # omapconf export xml regression_test_suite54xx_ref_settings.xml"
	echo
	exit 1
fi

ref_rev=$($ref_omapconf_bin --version | grep OMAPCONF | awk '{print $3}')
new_rev=$($new_omapconf_bin --version | grep OMAPCONF | awk '{print $3}')
if [ $DEBUG = 1 ]; then
	echo "ref_rev = $ref_rev"
	echo "new_rev = $new_rev"
fi

omap_cpu=$($new_omapconf_bin --cpuinfo | grep perf | awk '{print $1}')
opp_list_5430="400000 800000 1100000"

if [ $omap_cpu = OMAP5430 ]; then
	opp_list=$opp_list_5430
fi
logfile=omapconf_from_v"$ref_rev"_to_v"$new_rev"_no_reg_test.log
cpufreq_gov=$(cat /sys/devices/system/cpu/cpu0/cpufreq/scaling_governor)
#---------------------------------------------------------------------------------


echo Comparing OMAPCONF revision $new_rev against revision $ref_rev | tee -a $logfile
echo Running on $omap_cpu
echo omapconf_no_reg_test > /sys/power/wake_lock

# Force userspace governor to control OPP and not alter diff results
echo Current CPUFreq governor is $cpufreq_gov, switching to userspace instead.
echo userspace > /sys/devices/system/cpu/cpu0/cpufreq/scaling_governor
echo Switch to max OPP with 2 CPUs to speed up regression tests
echo 1500000 > /sys/devices/system/cpu/cpu0/cpufreq/scaling_setspeed


# Test RW function(s)
if  [ $all_tests = 1 ] || [ $tests = rw ]; then
	compare "read 0x4A307300" "READ ADDRESS" 0
#	compare "read PM_L3INIT_PWRSTCTRL" "READ TRM NAME" 0
	compare "write 0x4A307300 0xDEADBEEF" "WRITE ADDRESS" 0
#	compare "write PM_L3INIT_PWRSTST 0xDEADBEEF" "WRITE TRM NAME" 0
	compare "dump 0x48243400 0x4824340C" "DUMP RANGE" 0
#	compare "set bit PM_L3INIT_PWRSTST 0x0" "SET BIT NAME" 0
#	compare "clear bit PM_L3INIT_PWRSTST 0x0" "CLEAR BIT NAME" 0
	compare "read i2c 1 0x4A 0x87" "I2C READ" 0
	compare "write i2c 1 0x49 0x02 0xAA" "I2C WRITE" 1
fi


# Test PWST function(s)
if  [ $all_tests = 1 ] || [ $tests = pwst ]; then
	compare "show pwst" "SHOW PWST" 1
fi


# Test OPP function(s) at each possible OPP
if  [ $all_tests = 1 ] || [ $tests = opp ]; then
	for opp in $opp_list
	do
		echo $opp > /sys/devices/system/cpu/cpu0/cpufreq/scaling_setspeed
		compare "show opp" "SHOW OPP $opp" 0
	done
	echo | tee -a $logfile
fi


# Test DPLLS function(s)
if  [ $all_tests = 1 ] || [ $tests = dpll ]; then
	compare "dump dpll" "DUMP DPLL" 0
	compare "dump dpll mpu" "DUMP DPLL MPU" 0
	compare "dump dpll iva" "DUMP DPLL IVA" 0
	compare "dump dpll core" "DUMP DPLL CORE" 0
	compare "dump dpll per" "DUMP DPLL PER" 0
	compare "dump dpll abe" "DUMP DPLL ABE" 0
	compare "dump dpll usb" "DUMP DPLL USB" 0
	compare "dump dpll unipro1" "DUMP DPLL UNIPRO1" 0
	compare "dump dpll unipro2" "DUMP DPLL UNIPRO2" 0

	for opp in $opp_list
	do
		echo $opp > /sys/devices/system/cpu/cpu0/cpufreq/scaling_setspeed
		compare "show dpll cfg" "SHOW DPLL CFG $opp" 0
		compare "show dpll" "SHOW DPLL $opp" 0
	done
	echo | tee -a $logfile
fi


if  [ $all_tests = 1 ] || [ $tests = prcm ]; then
# Test PRCM DUMP function(s)
	for pwrdm in MPU CORE DSP DSS CAM GPU IVA L4PER ABE L3INIT DEV EMU INSTR CKGEN WKUPAON COREAON ALL
	do
		compare "dump prcm $pwrdm" "DUMP PRCM $pwrdm" 0
	done
	compare "dump prcm" "DUMP PRCM" 0
	echo | tee -a $logfile

# Test PRCM SHOW function
	for pwrdm in MPU CORE DSP DSS CAM GPU IVA L4PER ABE L3INIT EMU WKUPAON COREAON ALL
	do
		compare "show prcm $pwrdm" "SHOW PRCM $pwrdm" 0
		compare "show prcm $pwrdm cfg" "SHOW PRCM $pwrdm CFG" 0
	done
	echo | tee -a $logfile

	for clkdm in L4CFG EMIF IPU L3MAIN1 L3MAIN2 L3INSTR C2C DMA MIPIEXT
	do
		compare "show prcm core $clkdm" "SHOW PRCM CORE $clkdm" 0
		compare "show prcm core $clkdm cfg" "SHOW PRCM CORE $clkdm CFG" 0
	done

	compare "show prcm" "SHOW PRCM" 0
	compare "show prcm cfg" "SHOW PRCM CFG" 1
fi


if  [ $all_tests = 1 ] || [ $tests = prcm ] || [ $tests = dep ]; then
# Test Static Dependency function(s)
	CM_CAM_STATICDEP=`$1 read 0x4A009004`
	CM_IPU_STATICDEP=`$1 read 0x4A008904`
	CM_C2C_STATICDEP=`$1 read 0x4A008C04`
	CM_DMA_STATICDEP=`$1 read 0x4A008A04`
	CM_MIPIEXT_STATICDEP=`$1 read 0x4A008C84`
	CM_DSS_STATICDEP=`$1 read 0x4A009104`
	CM_L3INIT_STATICDEP=`$1 read 0x4A009304`
	CM_DSP_STATICDEP=`$1 read 0x4A004404`
	CM_GPU_STATICDEP=`$1 read 0x4A009204`
	CM_IVA_STATICDEP=`$1 read 0x4A008F04`
	CM_MPU_STATICDEP=`$1 read 0x4A004304`

	compare "dump prcm dep" "DUMP PRCM DEP" 0
	compare "show prcm dep" "SHOW PRCM DEP" 0
	compare "show prcm dep cfg" "SHOW PRCM DEP CFG" 0
	compare "show prcm statdep" "SHOW PRCM STATDEP" 0
	compare "show prcm statdep cfg" "SHOW PRCM STATDEP CFG" 0
	compare "show prcm dyndep" "SHOW PRCM DYNDEP" 0
	compare "show prcm dyndep cfg" "SHOW PRCM DYNDEP CFG" 0


#	for clkdm_from in EMU WKUPAON COREAON CAM L4CFG EMIF IPU L3MAIN2 L3INSTR L3MAIN1 C2C DMA MIPIEXT DSS CUSTEFUSE L3INIT L4PER L4SEC ABE DSP GPU IVA MPU
	for clkdm_from in WKUPAON CAM EMIF L3MAIN2 L3MAIN1 DMA DSS L3INIT DSP MPU
	do
#		for clkdm_to in EMU WKUPAON COREAON CAM L4CFG EMIF IPU L3MAIN2 L3INSTR L3MAIN1 C2C DMA MIPIEXT DSS CUSTEFUSE L3INIT L4PER L4SEC ABE DSP GPU IVA MPU ALL
		for clkdm_to in EMU COREAON L4CFG IPU L3INSTR C2C MIPIEXT CUSTEFUSE L4PER ABE IVA MPU ALL
		do
			compare "set prcm statdep $clkdm_from $clkdm_to" "SET PRCM STATDEP $clkdm_from $clkdm_to" 0
			compare "clear prcm statdep $clkdm_from $clkdm_to" "CLEAR PRCM STATDEP $clkdm_from $clkdm_to" 0
		done
	done

	$1 write 0x4A009004 0x$CM_CAM_STATICDEP
	$1 write 0x4A008904 0x$CM_IPU_STATICDEP
	$1 write 0x4A008C04 0x$CM_C2C_STATICDEP
	$1 write 0x4A008A04 0x$CM_DMA_STATICDEP
	$1 write 0x4A008C84 0x$CM_MIPIEXT_STATICDEP
	$1 write 0x4A009104 0x$CM_DSS_STATICDEP
	$1 write 0x4A009304 0x$CM_L3INIT_STATICDEP
	$1 write 0x4A004404 0x$CM_DSP_STATICDEP
	$1 write 0x4A009204 0x$CM_GPU_STATICDEP
	$1 write 0x4A008F04 0x$CM_IVA_STATICDEP
	$1 write 0x4A004304 0x$CM_MPU_STATICDEP

	echo | tee -a $logfile
fi


# Test SR functions
if  [ $all_tests = 1 ] || [ $tests = sr ]; then
	for mod in  MPU CORE MM
	do
		compare "dump sr $mod" "DUMP SR $mod" 0
	done
	compare "dump sr" "DUMP SR" 0
	compare "show sr" "SHOW SR" 0
	compare "show sr cfg" "SHOW SR CFG" 0
	compare "show sr status" "SHOW SR STATUS" 1
fi


# Test CONTROL MODULE DUMP function(s)
if  [ $all_tests = 1 ] || [ $tests = ctrlmod ]; then
	for mod in  ALL CORE CORE_PAD WKUP WKUP_PAD
	do
		compare "dump ctrlmod $mod" "DUMP CTRLMOD $mod" 0
	done
	compare "dump ctrlmod" "DUMP CTRLMOD" 0
	echo | tee -a $logfile
fi


# Test TEMPERATURE function(s)
if  [ $all_tests = 1 ] || [ $tests = temp ]; then
	compare "show temp" "SHOW TEMP" 0
	compare "show temp all" "SHOW TEMP ALL" 0
	compare "show temp mpu" "SHOW TEMP MPU" 0
	compare "show temp mpu_hotspot" "SHOW TEMP MPU HOTSPOT" 0
	compare "show temp gpu" "SHOW TEMP GPU" 0
	compare "show temp gpu_hotspot" "SHOW TEMP GPU HOTSPOT" 0
	compare "show temp core" "SHOW TEMP CORE" 0
	compare "show temp mem1" "SHOW TEMP MEM1" 0
	compare "show temp mem2" "SHOW TEMP MEM2" 0
	compare "show temp pcb" "SHOW TEMP PCB" 0
	compare "show temp case" "SHOW TEMP CASE" 1
	compare "show temp charger" "SHOW TEMP CHARGER" 1
fi


# Test EXPORT function(s)
if  [ $all_tests = 1 ] || [ $tests = export ]; then
	compare "export ctt" "CTT DUMP" 0
	compare "export ctt ctt.rd1" "CTT RD1" 1
	rm -f *.rd1
fi

# Test ABB function(s)
if  [ $all_tests = 1 ] || [ $tests = prcm ] || [ $tests = abb ]; then
	compare "dump prcm abb" "DUMP PRCM ABB" 0
	compare "show prcm abb" "SHOW PRCM ABB" 0
	compare "show prcm abb cfg" "SHOW PRCM ABB CFG" 1
fi


# Test EMIF function(s)
if  [ $all_tests = 1 ] || [ $tests = emif ]; then
	compare "dump emif" "DUMP EMIF" 1
fi


# Test ABE function(s)
if  [ $all_tests = 1 ] || [ $tests = abe ]; then
	compare "dump abe" "ABE DUMP" 0
	compare "show abe atc" "SHOW ABE ATC" 0
	compare "show abe cfg" "SHOW ABE CFG" 0
	compare "show abe" "SHOW ABE" 1
fi


# Test AUDIOIC function(s)
if  [ $all_tests = 1 ] || [ $tests = audioic ]; then
	compare "dump audioic" "DUMP AUDIOIC" 0
	compare "show audioic cfg" "SHOW AUDIOIC CFG" 0
	compare "show audioic gains" "SHOW AUDIOIC GAINS" 0
	compare "read audioic 0x01" "READ AUDIOIC 0x01" 0
	compare "read audioic ASICID" "READ AUDIOIC ASICID" 0
	compare "write audioic 0x01 0x01" "WRITE AUDIOIC 0x01" 0
	compare "write audioic ASICID 0x01" "WRITE AUDIOIC ASICID 0x01" 1
fi


# Test PMIC function(s)
if  [ $all_tests = 1 ] || [ $tests = pmic ]; then
	compare "dump pmic" "DUMP PMIC" 1
fi


# Test AUDIT function(s)
if  [ $all_tests = 1 ] || [ $tests = audit ]; then
	for opp in $opp_list
	do
		echo $opp > /sys/devices/system/cpu/cpu0/cpufreq/scaling_setspeed
		compare "audit dpll" "AUDIT DPLL $opp" 0
		compare "audit dpll -d core" "AUDIT DPLL $opp CORE" 0
		compare "audit dpll -o nom" "AUDIT DPLL $opp FORCED OPP NOM" 0
		compare "audit dpll -o nom -d core" "AUDIT DPLL $opp CORE FORCED OPP NOM" 0
		compare "audit dpll -o all -d all" "AUDIT DPLL $opp ALL" 0
		compare "audit clkspeed" "AUDIT CLKSPEED $opp" 0
	done

	compare "audit sysconfig" "AUDIT SYSCONFIG" 0 "audit sysconfig"
	compare "audit io" "AUDIT IO" 0 "audit io"
	compare "audit statdep" "AUDIT STATDEP" 0 "audit statdep"
	compare "audit full" "AUDIT FULL" 0 "audit full"
	compare "audit perf 2" "AUDIT PERF" 1 "audit perf 2"
	rm -f performance_audit_summary.txt
fi


# Test TRACE function(s)
if  [ $all_tests = 1 ] || [ $tests = trace ]; then
	compare "trace perf -t 2 -s 1 -d 1" "TRACE PERF" 1
	rm -f omap_performance_trace.dat
	rm -f omap_performance_stats.txt
	rm -f gnuplot_draw_perf_charts.plt
	rm -f gnuplot_create_perf_jpg.plt
	rm -f omap_performances_trace.jpg
fi


# Test HWOBS function(s)
if  [ $all_tests = 1 ] || [ $tests = hwobs ]; then
	compare "test hwobs zero" "HWOBS TEST ZERO (UNITIALIZED)" 0
	compare "test hwobs one" "HWOBS TEST ONE (UNITIALIZED)" 0
	compare "enable hwobs" "HWOBS TEST ENABLE (UNITIALIZED)" 0
	compare "show hwobs cfg" "HWOBS CFG (UNITIALIZED)" 0
	compare "setup hwobs prcm 0 CM2 0x10" "HWOBS SETUP PRCM 0 CM2 0X10  (UNITIALIZED)" 1
	compare "setup hwobs pinmux WKUP" "HWOBS SETUP PINMUX WKUP" 0
	compare "setup hwobs pinmux CORE_C2C" "HWOBS SETUP PINMUX  CORE_C2C" 0
	compare "setup hwobs pinmux ALL" "HWOBS SETUP PINMUX ALL" 0
	compare "enable hwobs" "HWOBS TEST ENABLE" 1
	compare "setup hwobs prcm 0 CM2 0x10" "HWOBS SETUP PRCM 0 CM2 0X10" 0
	compare "setup hwobs mpuss 0x3" "HWOBS SETUP MPU 0x3" 0
	compare "show hwobs cfg" "HWOBS CFG" 1
fi


echo | tee -a $logfile
echo "OMAPCONF Regression Test Results:" | tee -a $logfile
echo "  Number of tests: $test_cpt" | tee -a $logfile
pct=$[$[$test_pass_cpt*100]/$test_cpt]
echo "  Number of passing test(s): $test_pass_cpt ($pct%)" | tee -a $logfile
pct=$[100-$pct]
echo "  Number of failing test(s): $test_fail_cpt ($pct%)" | tee -a $logfile
echo | tee -a $logfile
if [ $test_pass_cpt = $test_cpt ]; then
	echo "All regression tests passed, congrats!!! :-)" | tee -a $logfile
else
	echo "Boooh, $test_fail_cpt regression(s) detected!" | tee -a $logfile
fi
echo "cat $logfile for detailed log." | tee -a $logfile
echo

# Restore CPUFreq governor
echo $cpufreq_gov > /sys/devices/system/cpu/cpu0/cpufreq/scaling_governor
echo omapconf_no_reg_test > /sys/power/wake_unlock

