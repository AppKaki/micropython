# MicroPython Port To Mynewt for PineTime Smart Watch (nRF52)

This is a port of MicroPython to Mynewt for PineTime Smart Watch (nRF52). Based on the nRF and Zephyr ports.

Why? So that MicroPython will support Wireless Firmware Updates over Bluetooth LE based on open-source NimBLE Bluetooth Stack, MCUBoot Bootloader and MCU Manager...

1. _["MCUBoot Bootloader for PineTime Smart Watch (nRF52)"](https://lupyuen.github.io/pinetime-rust-mynewt/articles/mcuboot)_

1. _["Wireless Firmware Update In Action on PineTime Smart Watch (nRF52)"](https://lupyuen.github.io/pinetime-rust-mynewt/articles/dfutest)_

1. _["Firmware Update over Bluetooth Low Energy on PineTime Smart Watch"](https://lupyuen.github.io/pinetime-rust-mynewt/articles/dfu)_

1. _["Configure Mynewt for SPI Flash on PineTime Smart Watch (nRF52)"](https://lupyuen.github.io/pinetime-rust-mynewt/articles/spiflash)_

## Supported Features

TODO

* UART
* SPI
* LEDs
* Pins
* ADC
* I2C
* PWM (nRF52 only)
* Temperature
* RTC (Real Time Counter. Low-Power counter)
* BLE support including:
  * Peripheral role on nrf51 targets
  * Central role and Peripheral role on nrf52 targets
  * _REPL over Bluetooth LE_ (optionally using WebBluetooth)
  * ubluepy: Bluetooth LE module for MicroPython
  * 1 non-connectable advertiser while in connection

## Tested Hardware

* PineTime Smart Watch (nRF52)

## Compile and Flash

TODO

Prerequisite steps for building the nrf port:

    git clone <URL>.git micropython
    cd micropython
    make -C mpy-cross

By default, PineTime (nrf52832) is used as compile target. To build and flash issue the following command inside the ports/mynewt/ folder:

    make submodules
    make
    make flash

Alternatively the target board could be defined:

     make BOARD=mynewt
     make BOARD=mynewt flash

## Compile without LTO enabled

TODO

As a space optimization, LTO (Link Time Optimization) has been enabled on all
targets in the nrf-port. The `-flto` linker flag can be toggled easily by using
the argument LTO when building. The example below shows how to disable LTO for
the compilation:

    make BOARD=mynewt LTO=0

**Note**: There have been several issues with use of LTO in conjunction with
GNU ARM Embedded Toolchain 7.2.1/4Q17. It's recommended to use a toolchain after
this release, for example 7.3.1/2Q18 or 8.2.1/4Q18. The alternative would be to
build the target using the LTO=0 as described above.

## Compile with frozen modules

TODO

Frozen modules are Python modules compiled to bytecode and added to the firmware
image, as part of MicroPython. They can be imported as usual, using the `import`
statement. The advantage is that frozen modules use a lot less RAM as the
bytecode is stored in flash, not in RAM like when importing from a filesystem.
Also, frozen modules are available even when no filesystem is present to import
from.

To use frozen modules, put them in a directory (e.g. `freeze/`) and supply
`make` with the given directory. For example:

     make BOARD=mynewt FROZEN_MPY_DIR=freeze

## Enable MICROPY_VFS_FAT

TODO

As the `oofatfs` module is not having header guards that can exclude the implementation compile time, this port provides a flag to enable it explicitly. The MICROPY_VFS_FAT is by default set to 0 and has to be set to 1 if `oofatfs` files should be compiled. This will be in addition of setting `MICROPY_VFS` in mpconfigport.h.

For example:

     make BOARD=mynewt MICROPY_VFS_FAT=1

## Target Boards and Make Flags

TODO

Target Board (BOARD) | Bluetooth Stack (SD)    | Bluetooth Support      | Flash Util
---------------------|-------------------------|------------------------|-------------------------------
mynewt               | NimBLE                  | Peripheral and Central | TODO

## Bluetooth LE REPL

TODO

The port also implements a BLE REPL driver. This feature is disabled by default, as it will deactivate the UART REPL when activated. As some of the nRF devices only have one UART, using the BLE REPL free's the UART instance such that it can be used as a general UART peripheral not bound to REPL.

The configuration can be enabled by editing the `bluetooth_conf.h` and set `MICROPY_PY_BLE_NUS` to 1.

When enabled you have different options to test it:
* [NUS Console for Linux](https://github.com/tralamazza/nus_console) (recommended)
* [WebBluetooth REPL](https://aykevl.nl/apps/nus/) (experimental)

Other:
* nRF UART application for IPhone/Android

WebBluetooth mode can also be configured by editing `bluetooth_conf.h` and set `BLUETOOTH_WEBBLUETOOTH_REPL` to 1. This will alternate advertisement between Eddystone URL and regular connectable advertisement. The Eddystone URL will point the phone or PC to download [WebBluetooth REPL](https://aykevl.nl/apps/nus/) (experimental), which subsequently can be used to connect to the Bluetooth REPL from the PC or Phone browser.

## Building without the built-in MicroPython compiler

TODO

This minimal port can be built with the built-in MicroPython compiler
disabled.  This will reduce the firmware by about 20k on a Thumb2 machine,
and by about 40k on 32-bit x86.  Without the compiler the REPL will be
disabled, but pre-compiled scripts can still be executed.

To test out this feature, change the `MICROPY_ENABLE_COMPILER` config
option to "0" in the mpconfigport.h file in this directory.  Then
recompile and run the firmware and it will execute the frozentest.py
file.
