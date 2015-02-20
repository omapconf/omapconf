###############################################################################
#                                                                             #
#                                  OMAPCONF                                   #
#                                                                             #
#      A Powerful Diagnostic Tool for Texas Instruments OMAP Processors       #
###############################################################################



ABOUT:
------

OMAPCONF is a Linux user-space standalone application designed to provide a
quick'n easy way to diagnose (monitor/debug/audit...) TI OMAP configuration/status
dynamically at runtime, in any situation:
 * Any Linux distribution (Ubuntu, ...)
 * Any Android release (Froyo, GingerBread, HoneyComb, Ice-Cream Sandwich, Jelly Bean, ...)
 * TI official platforms (blaze, panda, ...),
 * Custom OMAP platforms, etc.
 * With no single kernel recompilation needed

OMAPCONF leverages "/dev/mem" special device to directly access complete
TI OMAP memory space (registers, ...).



SUPPORT:
--------

OMAPCONF CURRENTLY SUPPORTS TI AM335x, AM437x, OMAP44XX AND OMAP54XX DEVICES.
LEGACY TI OMAP PLATFORMS (OMAP[1-2-3]) ARE NOT SUPPORTED.

THIS SOFTWARE IS PROVIDED AS IS, WITH NO SUPPORT OR MAINTENANCE COMMITMENT FROM
TEXAS INSTRUMENTS INCORPORATED.



Build instructions (Ubuntu):
----------------------------

OMAPCONF is available as a Ubuntu package.
To proceed with package installation type the following:

	# sudo apt-get install tiomapconf

Once package is installed, you can check which omapconf version you are using:

	# dpkg -l tiomapconf

Package is available via TI OMAP4 Ubuntu PPA.
See [the OMAPpedia page](http://www.omappedia.org/wiki/PandaBoard_Ubuntu_PPA "Your mouse is hovering over this link") for further instructions.



Build instructions (other Linux Distributions):
-----------------------------------------------
To only build the output binary file:
	# make CROSS_COMPILE=arm-none-linux-gnueabi- omapconf

NB:
	- CROSS_COMPILE variable must be set to point to the correct compiler.
	- By default, omapconf is statically built, to ease sharing.
	  In case it is not needed or size matters, it is possible to build it dynamically, by setting variable STATIC_BUILD to "".
	  # export STATIC_BUILD=
	  or
	  # make CROSS_COMPILE=arm-none-linux-gnueabi- STATIC_BUILD= omapconf

To build and install ompaconf:

	# make CROSS_COMPILE=arm-none-linux-gnueabi- DESTDIR=YOUR_DIR install

YOUR_DIR is a destination directory where omapconf output binary file will be
copied (e.g. ubuntu/android filesystem)

That's it!



Build instructions and installation via ADB (Android):
------------------------------------------------------
Make sure your Android device is connected to host via ADB:

	# adb kill-server
	# adb devices
	* daemon not running. starting it now *
	* daemon started successfully *
	List of devices attached
	 emulator-5554	device
	# adb root

To build and install ompaconf for Android via ADB:

	# make CROSS_COMPILE=arm-none-linux-gnueabi- install_android

OMAPCONF binary will be copied to /data directory (known writable directory)
on your Android device. You may get it copied to a different directory by
updating Makefile at your convenience.



Help:
-----

Type "./omapconf --help" to get complete list of available commands and options.
Note that in case of incorrect command/option, help will also be displayed.

A dedicated wiki page is available [here](https://github.com/omapconf/omapconf/wiki "Github Wiki").
