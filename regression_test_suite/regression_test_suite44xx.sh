#!/data/busybox/bin/bash
#=================================================================================
# FILE: regression_test_suite44xx.sh
#
# USAGE: regression_test_suite44xx.sh ref_version new_version
#
# DESCRIPTION: OMAPCONF No Regression Test Suite for OMAP4 platform.
#		Compare omapconf output from reference and new versions.
#		Report any discrepency.
#
# OPTIONS:
#		ref_version: name of the reference binary, INCLUDING PATH.
#		new_version: name of the new binary to be tested, INCLUDING PATH.
# REQUIREMENTS: TO BE RUN ON OMAP4 PLATFORM ONLY
# BUGS: ---
# NOTES: ---
# AUTHOR: Patrick Titiano
# COMPANY: Texas Instruments France
VERSION=1.01
# CREATED: 2011-09-06
# REVISION: ---
#=================================================================================


#=== FUNCTION ====================================================================
# NAME: compare
# DESCRIPTION: compare command result of 2 versions of omapconf
#		Save log in file.
# PARAMETER
#		1: omapconf command to be tested (including all parameters
#		2: test identification string
#		3: display new line at end of function (0: no, 1: yes)
# CREATED: 2011-04-01 / AUTHOR: Patrick Titiano
#=================================================================================
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

	if [ "$1" = "dump dpll" ]; then
		# EMIF clocks may be gated or not, ignore it
		$ref_omapconf_bin $1 | grep -v CM_DIV_M2_DPLL_CORE | grep -v CM_DIV_M4_DPLL_CORE &> $logfile_ref
		$new_omapconf_bin $1 | grep -v CM_DIV_M2_DPLL_CORE | grep -v CM_DIV_M4_DPLL_CORE &> $logfile_new
	elif [ "$1" = "show pwst" ]; then
		# ignore EMIF status (always changing)
		$ref_omapconf_bin $1 | grep -v EMIF > $logfile_ref
		$new_omapconf_bin $1 | grep -v EMIF > $logfile_new
	elif [ "$1" = "dump prcm CORE" ]; then
		# ignore EMIF status (always changing)
		$ref_omapconf_bin $1 | grep -v EMIF > $logfile_ref
		$new_omapconf_bin $1 | grep -v EMIF > $logfile_new
	elif [ "$1" = "show prcm CORE" ]; then
		# ignore EMIF status (always changing)
		$ref_omapconf_bin $1 | grep -v "Idle Status" | grep -v PHY_ROOT_CLK | grep -v DLL_CLK | grep -v L3_EMIF_ICLK > $logfile_ref
		$new_omapconf_bin $1 | grep -v "Idle Status" | grep -v PHY_ROOT_CLK | grep -v DLL_CLK | grep -v L3_EMIF_ICLK > $logfile_new
	elif [ "$1" = "show prcm CORE cfg" ]; then
		# ignore EMIF status (always changing)
		$ref_omapconf_bin $1 | grep -v "Idle Status" | grep -v PHY_ROOT_CLK | grep -v DLL_CLK | grep -v L3_EMIF_ICLK > $logfile_ref
		$new_omapconf_bin $1 | grep -v "Idle Status" | grep -v PHY_ROOT_CLK | grep -v DLL_CLK | grep -v L3_EMIF_ICLK > $logfile_new
	elif [ "$1" = "show dpll cfg" ]; then
		# ignore Status (may be changing)
		$ref_omapconf_bin $1 | grep -v Status > $logfile_ref
		$new_omapconf_bin $1 | grep -v Status > $logfile_new
	elif [ "$1" = "dump sr" ]; then
		# ignore SR runtime status registers (always changing)
		$ref_omapconf_bin $1 | grep -v SENVAL | grep -v SENERROR > $logfile_ref
		$new_omapconf_bin $1 | grep -v SENVAL | grep -v SENERROR > $logfile_new
	elif [ "$1" = "show sr cfg" ]; then
		# ignore SR runtime status registers (always changing)
		$ref_omapconf_bin $1 | grep -v SENERROR | grep -v AVGERROR > $logfile_ref
		$new_omapconf_bin $1 | grep -v SENERROR | grep -v AVGERROR > $logfile_new
	elif [ "$1" = "dump emif" ]; then
		# ignore EMIF performance counters registers (always changing)
		$ref_omapconf_bin $1 | grep -v PERF_CNT_1 | grep -v PERF_CNT_2 | grep -v PERF_CNT_TIM > $logfile_ref
		$new_omapconf_bin $1 | grep -v PERF_CNT_1 | grep -v PERF_CNT_2 | grep -v PERF_CNT_TIM > $logfile_new
	elif [ "$1" = "audit sysconfig" ]; then
		# ignore MMC1 (may be active or inactive depending on filesystem accesses)
		$ref_omapconf_bin $1 | grep -v MMC1 > $logfile_ref
		$new_omapconf_bin $1 | grep -v MMC1 > $logfile_new
	elif [ "$1" = "audit full" ]; then
		# ignore MMC1 (may be active or inactive depending on filesystem accesses)
		$ref_omapconf_bin $1 | grep -v MMC1 | grep -v SYSCONFIG > $logfile_ref
		$new_omapconf_bin $1 | grep -v MMC1 | grep -v SYSCONFIG > $logfile_new
	elif [ "$1" = "audit homescreen full_log" ]; then
		# ignore EMIF status (always changing)
		$ref_omapconf_bin $1 | grep -v EMIF > $logfile_ref
		# Append summary file to logfile and ignore OMAPCONF header
		cat home_screen_uc_audit_summary.txt | grep -v OMAPCONF >> $logfile_ref
		# Append details file to logfile and ignore OMAPCONF header
		cat home_screen_uc_audit_details.txt | grep -v OMAPCONF >> $logfile_ref
		$new_omapconf_bin $1 | grep -v EMIF > $logfile_new
		# Append summary file to logfile and ignore OMAPCONF header
		cat home_screen_uc_audit_summary.txt | grep -v OMAPCONF >> $logfile_new
		# Append details file to logfile and ignore OMAPCONF header
		cat home_screen_uc_audit_details.txt | grep -v OMAPCONF >> $logfile_new
	elif [ "$1" = "audit os_idle full_log" ]; then
		# ignore EMIF status (always changing)
		$ref_omapconf_bin $1 | grep -v EMIF > $logfile_ref
		# Append summary file to logfile and ignore OMAPCONF header
		cat os_idle_uc_audit_summary.txt | grep -v OMAPCONF >> $logfile_ref
		# Append details file to logfile and ignore OMAPCONF header
		cat os_idle_uc_audit_details.txt | grep -v OMAPCONF >> $logfile_ref
		$new_omapconf_bin $1 | grep -v EMIF > $logfile_new
		# Append summary file to logfile and ignore OMAPCONF header
		cat os_idle_uc_audit_summary.txt | grep -v OMAPCONF >> $logfile_new
		# Append details file to logfile and ignore OMAPCONF header
		cat os_idle_uc_audit_details.txt | grep -v OMAPCONF >> $logfile_new
	elif [ "$1" = "audit mp3 full_log" ]; then
		# ignore EMIF status (always changing)
		$ref_omapconf_bin $1 | grep -v EMIF > $logfile_ref
		# Append summary file to logfile and ignore OMAPCONF header
		cat mp3_playback_uc_audit_summary.txt | grep -v OMAPCONF >> $logfile_ref
		# Append details file to logfile and ignore OMAPCONF header
		cat mp3_playback_uc_audit_details.txt | grep -v OMAPCONF >> $logfile_ref
		$new_omapconf_bin $1 | grep -v EMIF > $logfile_new
		# Append summary file to logfile and ignore OMAPCONF header
		cat mp3_playback_uc_audit_summary.txt | grep -v OMAPCONF >> $logfile_new
		# Append details file to logfile and ignore OMAPCONF header
		cat mp3_playback_uc_audit_details.txt | grep -v OMAPCONF >> $logfile_new
	elif [ "$1" = "audit play720p full_log" ]; then
		# ignore EMIF status (always changing)
		$ref_omapconf_bin $1 | grep -v EMIF > $logfile_ref
		# Append summary file to logfile and ignore OMAPCONF header
		cat avplayback_720p_uc_audit_summary.txt | grep -v OMAPCONF >> $logfile_ref
		# Append details file to logfile and ignore OMAPCONF header
		cat avplayback_720p_uc_audit_details.txt | grep -v OMAPCONF >> $logfile_ref
		$new_omapconf_bin $1 | grep -v EMIF > $logfile_new
		# Append summary file to logfile and ignore OMAPCONF header
		cat avplayback_720p_uc_audit_summary.txt | grep -v OMAPCONF >> $logfile_new
		# Append details file to logfile and ignore OMAPCONF header
		cat avplayback_720p_uc_audit_details.txt | grep -v OMAPCONF >> $logfile_new
	elif [ "$1" = "audit play1080p full_log" ]; then
		# ignore EMIF status (always changing)
		$ref_omapconf_bin $1 | grep -v EMIF > $logfile_ref
		# Append summary file to logfile and ignore OMAPCONF header
		cat avplayback_1080p_uc_audit_summary.txt | grep -v OMAPCONF >> $logfile_ref
		# Append details file to logfile and ignore OMAPCONF header
		cat avplayback_1080p_uc_audit_details.txt | grep -v OMAPCONF >> $logfile_ref
		$new_omapconf_bin $1 | grep -v EMIF > $logfile_new
		# Append summary file to logfile and ignore OMAPCONF header
		cat avplayback_1080p_uc_audit_summary.txt | grep -v OMAPCONF >> $logfile_new
		# Append details file to logfile and ignore OMAPCONF header
		cat avplayback_1080p_uc_audit_details.txt | grep -v OMAPCONF >> $logfile_new
	elif [ "$1" = "audit rec1080p full_log" ]; then
		# ignore EMIF status (always changing)
		$ref_omapconf_bin $1 | grep -v EMIF > $logfile_ref
		# Append summary file to logfile and ignore OMAPCONF header
		cat avrecord_1080p_uc_audit_summary.txt | grep -v OMAPCONF >> $logfile_ref
		# Append details file to logfile and ignore OMAPCONF header
		cat avrecord_1080p_uc_audit_details.txt | grep -v OMAPCONF >> $logfile_ref
		$new_omapconf_bin $1 | grep -v EMIF > $logfile_new
		# Append summary file to logfile and ignore OMAPCONF header
		cat avrecord_1080p_uc_audit_summary.txt | grep -v OMAPCONF >> $logfile_new
		# Append details file to logfile and ignore OMAPCONF header
		cat avrecord_1080p_uc_audit_details.txt | grep -v OMAPCONF >> $logfile_new
	else
		$ref_omapconf_bin $1 > $logfile_ref
		$new_omapconf_bin $1 > $logfile_new
	fi

	# First line of log file will always be different (contains OMAPCONF/CHIPS/BUILD revision numbers).
	# busybox diff doesn't support -I option.
	# Use sed to remove first lines of log files before doing the diff.
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
tests_list="rw pwst opp dpll prcm sr dep abb abe emif temp export pmic audioic audit uc_audit trace mpuss camera display hwobs"

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
	echo "Usage: regression_test_suite44xx.sh reference_binary new_binary [item]"
	echo "  Use 'item' (optional) to select a specific set of test(s)."
	echo "  'item' can be: $tests_list"
	echo "  If omitted, full suite will be run by default."
	exit 3
fi


# Check reference and new omapconf binaries found
if [ ! -s $ref_omapconf_bin ]; then
	echo "Reference binary not found! ($ref_omapconf_bin)"
	exit 1
fi
if [ ! -s $new_omapconf_bin ]; then
	echo "New binary not found! ($new_omapconf_bin)"
	exit 2
fi


ref_rev=$($ref_omapconf_bin --version | grep OMAPCONF | awk '{print $3}')
new_rev=$($new_omapconf_bin --version | grep OMAPCONF | awk '{print $3}')
if [ $DEBUG = 1 ]; then
	echo "ref_rev = $ref_rev"
	echo "new_rev = $new_rev"
fi


omap_cpu=$($new_omapconf_bin --cpuinfo | grep perf | awk '{print $1}')
opp_list_4430="300000 600000 800000 1008000"
opp_list_4460="350000 700000 920000 1200000 1500000"
opp_list_4470="396800 800000 1100000 1300000 1500000"
if [ $omap_cpu = OMAP4430 ]; then
	opp_list=$opp_list_4430
elif [ $omap_cpu = OMAP4460 ]; then
	opp_list=$opp_list_4460
elif [ $omap_cpu = OMAP4470 ]; then
	opp_list=$opp_list_4470
else
	opp_list=$opp_list_4430
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
echo 1 > /sys/devices/system/cpu/cpu1/online


# Test HELP function(s)
if  [ $all_tests = 1 ]; then
	compare "--help" "HELP" 1
fi


# Test RW function(s)
if  [ $all_tests = 1 ] || [ $tests = rw ]; then
	compare "read 0x4A307300" "READ ADDRESS" 0
	compare "read PM_L3INIT_PWRSTCTRL" "READ TRM NAME" 0
	compare "write 0x4A307300 0xDEADBEEF" "WRITE ADDRESS" 0
	compare "write PM_L3INIT_PWRSTST 0xDEADBEEF" "WRITE TRM NAME" 0
	compare "dump 0x48243400 0x4824340C" "DUMP RANGE" 0
	compare "set bit PM_L3INIT_PWRSTST 0x0" "SET BIT NAME" 0
	compare "clear bit PM_L3INIT_PWRSTST 0x0" "CLEAR BIT NAME" 0
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
	compare "dump dpll" "DUMP DPLLS" 0
	for opp in $opp_list
	do
		echo $opp > /sys/devices/system/cpu/cpu0/cpufreq/scaling_setspeed
		compare "show dpll cfg" "SHOW DPLL CFG $opp" 0
	done
	echo | tee -a $logfile
fi


# Test PRCM SHOW & DUMP function(s)
if  [ $all_tests = 1 ] || [ $tests = prcm ]; then
	compare "dump prcm mpu" "DUMP PRCM MPU" 0
	echo 0 > /sys/devices/system/cpu/cpu1/online
	sleep 1
	compare "show prcm mpu cfg" "SHOW PRCM MPU CFG CPU1 OUT" 0
	echo 1 > /sys/devices/system/cpu/cpu1/online
	sleep 1
	compare "show prcm mpu cfg" "SHOW PRCM MPU CFG CPU1 IN" 0

	for pwrdm in CORE DSP DSS CAM GFX IVAHD PER ABE WKUP L3INIT ALWON EMU
	do
		compare "dump prcm $pwrdm" "DUMP PRCM $pwrdm" 0
		compare "show prcm $pwrdm" "SHOW PRCM $pwrdm" 0
		compare "show prcm $pwrdm cfg" "SHOW PRCM $pwrdm CFG" 0
	done
	echo | tee -a $logfile

# Test Power Domain DEP function(s)
	for pwrdm in MPU CORE DSP DSS CAM GFX IVAHD PER L3INIT EMU
	do
		compare "show prcm $pwrdm dep" "PRCM $pwrdm DEP" 0
	done
	echo | tee -a $logfile

# Test PRCM MPU IRQ function
	compare "show prcm irq" "MPU IRQ" 1
fi


# Test Static Dependency function(s)
if  [ $all_tests = 1 ] || [ $tests = dep ] || [ $tests = prcm ]; then
	CM_MPU_STATICDEP=`$1 read CM_MPU_STATICDEP`
	CM_IVAHD_STATICDEP=`$1 read CM_IVAHD_STATICDEP`
	CM_DSP_STATICDEP=`$1 read CM_DSP_STATICDEP`
	CM_C2C_STATICDEP=`$1 read CM_C2C_STATICDEP`
	CM_SDMA_STATICDEP=`$1 read CM_SDMA_STATICDEP`
	CM_MPU_M3_STATICDEP=`$1 read CM_MPU_M3_STATICDEP`
	CM_CAM_STATICDEP=`$1 read CM_CAM_STATICDEP`
	CM_DSS_STATICDEP=`$1 read CM_DSS_STATICDEP`
	CM_GFX_STATICDEP=`$1 read CM_GFX_STATICDEP`
	CM_L3INIT_STATICDEP=`$1 read CM_L3INIT_STATICDEP`

	compare "dump prcm statdep" "DUMP STATDEP" 0
	compare "show prcm statdep" "CFG STATDEP" 0

	compare "clear prcm statdep mpu L4WKUP" "CLEAR PRCM STATDEP MPU L4WKUP" 0
	compare "set prcm statdep mpu L4WKUP" "SET PRCM STATDEP MPU L4WKUP" 0
	compare "clear prcm statdep mpu ALWONCORE" "CLEAR PRCM STATDEP MPU ALWONCORE" 0
	compare "set prcm statdep mpu ALWONCORE" "SET PRCM STATDEP MPU ALWONCORE" 0

	for clkdm in IVAHD DSP C2C SDMA MPU_M3 CAM DSS GFX L3INIT
	do
		compare "set prcm statdep $clkdm all" "SET PRCM STATDEP $clkdm ALL" 0
		compare "clear prcm statdep $clkdm all" "CLEAR PRCM STATDEP $clkdm ALL" 0
	done

	$1 write CM_MPU_STATICDEP 0x$CM_MPU_STATICDEP
	$1 write CM_IVAHD_STATICDEP 0x$CM_IVAHD_STATICDEP
	$1 write CM_DSP_STATICDEP 0x$CM_DSP_STATICDEP
	$1 write CM_C2C_STATICDEP 0x$CM_C2C_STATICDEP
	$1 write CM_SDMA_STATICDEP 0x$CM_SDMA_STATICDEP
	$1 write CM_MPU_M3_STATICDEP 0x$CM_MPU_M3_STATICDEP
	$1 write CM_CAM_STATICDEP 0x$CM_CAM_STATICDEP
	$1 write CM_DSS_STATICDEP 0x$CM_DSS_STATICDEP
	$1 write CM_GFX_STATICDEP 0x$CM_GFX_STATICDEP
	$1 write CM_L3INIT_STATICDEP 0x$CM_L3INIT_STATICDEP

	echo | tee -a $logfile
fi


# Test MPUSS function(s)
if  [ $all_tests = 1 ] || [ $tests = mpuss ]; then
	compare "dump mpuss scu" "DUMP MPUSS SCU" 0
	compare "dump mpuss l2c" "DUMP MPUSS L2C" 0
	compare "dump mpuss gic" "DUMP MPUSS GIC" 0
	compare "dump mpuss wkg" "DUMP MPUSS WKG" 0
	compare "dump mpuss scm" "DUMP MPUSS SCM" 0

	compare "show mpuss scu cfg" "SHOW MPUSS SCU CFG" 0
	compare "show mpuss gic cfg" "SHOW MPUSS GIC CFG" 1
fi


# Test WKDEP function(s)
if  [ $all_tests = 1 ] || [ $tests = dep ] || [ $tests = prcm ]; then
	compare "dump prcm wkdep" "DUMP PRCM WKDEP" 0
	compare "show prcm wkdep cfg" "SHOW PRCM WKDEP CFG" 1
fi


# Test SR function(s)
if  [ $all_tests = 1 ] || [ $tests = sr ]; then
	compare "dump sr" "DUMP SR" 0
	compare "show sr cfg" "SHOW SR CFG" 0
	compare "show sr status" "SHOW SR STATUS" 1
fi


# Test ABB function(s)
if  [ $all_tests = 1 ] || [ $tests = abb ]; then
	compare "dump prcm abb" "DUMP ABB" 0
	compare "show prcm abb cfg" "SHOW ABB CFG" 1
fi


# Test ABE function(s)
if  [ $all_tests = 1 ] || [ $tests = abe ]; then
	compare "dump abe" "DUMP ABE" 0
	compare "show abe atc" "SHOW ABE ATC" 0
	compare "show abe cfg" "SHOW ABE CFG" 1
fi


# Test EMIF function(s)
if  [ $all_tests = 1 ] || [ $tests = emif ]; then
	compare "dump emif" "DUMP EMIF" 1
fi


# Test TEMP function(s)
if  [ $all_tests = 1 ] || [ $tests = temp ]; then
	compare "show temp" "SHOW TEMP" 0
	compare "show temp bandgap" "SHOW TEMP BANDGAP" 0
	compare "show temp pcb" "SHOW TEMP PCB" 0
	compare "show temp hotspot" "SHOW TEMP HOTSPOT" 0
	compare "show temp mem1" "SHOW TEMP MEM1" 0
	compare "show temp mem2" "SHOW TEMP MEM2" 1
fi


# Test EXPORT function(s)
if  [ $all_tests = 1 ] || [ $tests = export ]; then
	compare "export ctt" "EXPORT CTT STDOUT" 0
	compare "export ctt ctt.rd1" "EXPORT CTT RD1" 1
	rm -f *.rd1

# Test PCT function(s)
	compare "export pct" "EXPORT PCT STDOUT" 0
	compare "export pct pct.rd1" "EXPORT PCT RD1" 1
	rm -f *.rd1
fi


# Test PMIC function(s)
if  [ $all_tests = 1 ] || [ $tests = pmic ]; then
	compare "dump pmic" "DUMP PMIC" 0
	compare "show pmic cfg" "SHOW PMIC CFG" 0
	compare "show pmic ldocfg" "SHOW PMIC LDOCFG" 0
	compare "show pmic smpscfg" "SHOW PMIC SMPSCFG" 0
	compare "show pmic rescfg" "SHOW PMIC RESCFG" 0
	compare "show pmic devpwrgrpstat" "SHOW PMIC DEVPWRGRPSTAT" 0
	compare "set pmic devpwrgrp MOD ON" "SET PMIC DEVPWRGRP MOD ON" 1
fi


# Test AUDIOIC function(s)
if  [ $all_tests = 1 ] || [ $tests = audioic ]; then
	compare "dump audioic" "DUMP AUDIOIC" 0
	compare "show audioic" "SHOW AUDIOIC" 0
	compare "show audioic cfg" "SHOW AUDIOIC CFG" 0
	compare "show audioic gains" "SHOW AUDIOIC GAINS" 0
	compare "read audioic 0x01" "READ AUDIOIC 0x01" 0
	compare "read audioic ASICID" "READ AUDIOIC ASICID" 0
	compare "write audioic 0x12 0x10" "WRITE AUDIOIC 0x12 0x10" 0
	compare "write audioic HSGAIN 0x10" "WRITE AUDIOIC HSGAIN 0x10" 1
fi


# Test CAMERA function(s)
if  [ $all_tests = 1 ] || [ $tests = camera ]; then
	compare "show camera cfg" "SHOW CAMERA CFG" 0
	compare "dump camera all" "DUMP CAMERA ALL" 1
fi


# Test DISPLAY function(s)
if  [ $all_tests = 1 ] || [ $tests = display ]; then
	compare "dump display all" "DUMP DISPLAY ALL" 1
fi


# Test AUDIT function(s)
if  [ $all_tests = 1 ] || [ $tests = audit ]; then
#compare "audit dplls" "AUDIT DPLLS" 0
	compare "audit sysconfig" "AUDIT SYSCONFIG" 0
	compare "audit statdep" "AUDIT STATDEP" 0
	compare "audit avs full" "AUDIT AVS FULL" 0
	rm -f sr_avs_audit_report.txt
	compare "audit pads" "AUDIT PADS" 0
	compare "audit dpll" "AUDIT DPLL" 0
	compare "audit dpll -o all -d all" "AUDIT DPLL ALL" 0
	compare "audit dpll -o opp100 -d iva" "AUDIT DPLL CORE OPP100" 0
	rm -f dpll_audit_report.txt
	compare "audit full" "AUDIT FULL" 0
	rm -f full_audit_report.txt
	for opp in $opp_list
	do
		echo $opp > /sys/devices/system/cpu/cpu0/cpufreq/scaling_setspeed
		compare "audit clkspeed" "AUDIT CLKSPEED $opp" 0
		compare "audit avs" "AUDIT AVS $opp" 0
		rm -f sr_avs_audit_report.txt
	done
	compare "audit perf 2" "AUDIT PERF" 1
	rm -f performance_audit_summary.txt
fi


# Test UC AUDIT function(s)
if  [ $all_tests = 1 ] || [ $tests = uc_audit ]; then
	compare "audit os_idle full_log" "AUDIT OS_IDLE" 0
	rm -f os_idle_uc_audit_summary.txt
	rm -f os_idle_uc_audit_details.txt

	compare "audit mp3 full_log" "AUDIT MP3" 0
	rm -f mp3_playback_uc_audit_summary.txt
	rm -f mp3_playback_uc_audit_details.txt

	compare "audit play720p full_log" "AUDIT PLAY720P" 0
	rm -f avplayback_720p_uc_audit_summary.txt
	rm -f avplayback_720p_uc_audit_details.txt

	compare "audit play1080p full_log" "AUDIT PLAY1080P" 0
	rm -f avplayback_1080p_uc_audit_summary.txt
	rm -f avplayback_1080p_uc_audit_details.txt

	compare "audit rec1080p full_log" "AUDIT REC1080P" 0
	rm -f avrecord_1080p_uc_audit_summary.txt
	rm -f avrecord_1080p_uc_audit_details.txt

	compare "audit homescreen full_log" "AUDIT HOMESCREEN" 1
	rm -f home_screen_uc_audit_summary.txt
	rm -f home_screen_uc_audit_details.txt
fi


# Test TRACE function(s)
if  [ $all_tests = 1 ] || [ $tests = trace ]; then
	compare "trace pwrdm 2" "TRACE PWRDM" 0
	rm -f etb_trace.txt
	rm -f pmi_pwrdm_events_trace.log
	rm -f pwrdm_transitions.csv
	rm -f pwrdm_transitions_stats.txt
	compare "trace opp 2" "TRACE OPP" 0
	rm -f etb_trace.txt
	rm -f voltage_transitions_trace.log
	rm -f omap_vdd_trace.dat
	rm -f gnuplot_draw_voltage_charts.plt
	rm -f gnuplot_create_voltage_traces_jpg.plt
	rm -f voltage_traces.jpg
	compare "trace perf 2" "TRACE PERF" 1
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
	compare "setup hwobs pinmux" "HWOBS SETUP PINMUX" 0
	compare "enable hwobs" "HWOBS TEST ENABLE" 1
	compare "setup hwobs prcm 0 CM2 0x10" "HWOBS SETUP PRCM 0 CM2 0X10" 0
	compare "setup hwobs mpuss 0x3" "HWOBS SETUP MPU 0x3" 0
	compare "setup hwobs abe on" "HWOBS SETUP ABE ON" 0
	compare "setup hwobs abe reserved" "HWOBS SETUP ABE RESERVED" 0
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

