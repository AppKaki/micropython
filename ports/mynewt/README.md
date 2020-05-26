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

## Build Log

```bash

> Executing task in folder wasp-os: bash -c -l ' export BUILD_VERBOSE=1 && make -j 1 BOARD=pinetime micropython && echo ✅ ◾ ️Done! ' <

make -C micropython/mpy-cross
make[1]: Entering directory '/Users/Luppy/PineTime/wasp-os/micropython/mpy-cross'
python3 ../py/makeversionhdr.py build/genhdr/mpversion.h
GEN build/genhdr/mpversion.h
CC main.c
clang -I. -Ibuild -I.. -Wall -Werror -Wpointer-arith -Wuninitialized -std=gnu99 -DFFCONF_H=\"lib/oofatfs/ffconf.h\" -Os   -fdata-sections -ffunction-sections -fno-asynchronous-unwind-tables -c -MD -o build/main.o main.c
LINK mpy-cross
clang -o mpy-cross build/py/mpstate.o build/py/nlr.o build/py/nlrx86.o build/py/nlrx64.o build/py/nlrthumb.o build/py/nlrpowerpc.o build/py/nlrxtensa.o build/py/nlrsetjmp.o build/py/malloc.o build/py/gc.o build/py/pystack.o build/py/qstr.o build/py/vstr.o build/py/mpprint.o build/py/unicode.o build/py/mpz.o build/py/reader.o build/py/lexer.o build/py/parse.o build/py/scope.o build/py/compile.o build/py/emitcommon.o build/py/emitbc.o build/py/asmbase.o build/py/asmx64.o build/py/emitnx64.o build/py/asmx86.o build/py/emitnx86.o build/py/asmthumb.o build/py/emitnthumb.o build/py/emitinlinethumb.o build/py/asmarm.o build/py/emitnarm.o build/py/asmxtensa.o build/py/emitnxtensa.o build/py/emitinlinextensa.o build/py/emitnxtensawin.o build/py/formatfloat.o build/py/parsenumbase.o build/py/parsenum.o build/py/emitglue.o build/py/persistentcode.o build/py/runtime.o build/py/runtime_utils.o build/py/scheduler.o build/py/nativeglue.o build/py/ringbuf.o build/py/stackctrl.o build/py/argcheck.o build/py/warning.o build/py/profile.o build/py/map.o build/py/obj.o build/py/objarray.o build/py/objattrtuple.o build/py/objbool.o build/py/objboundmeth.o build/py/objcell.o build/py/objclosure.o build/py/objcomplex.o build/py/objdeque.o build/py/objdict.o build/py/objenumerate.o build/py/objexcept.o build/py/objfilter.o build/py/objfloat.o build/py/objfun.o build/py/objgenerator.o build/py/objgetitemiter.o build/py/objint.o build/py/objint_longlong.o build/py/objint_mpz.o build/py/objlist.o build/py/objmap.o build/py/objmodule.o build/py/objobject.o build/py/objpolyiter.o build/py/objproperty.o build/py/objnone.o build/py/objnamedtuple.o build/py/objrange.o build/py/objreversed.o build/py/objset.o build/py/objsingleton.o build/py/objslice.o build/py/objstr.o build/py/objstrunicode.o build/py/objstringio.o build/py/objtuple.o build/py/objtype.o build/py/objzip.o build/py/opmethods.o build/py/sequence.o build/py/stream.o build/py/binary.o build/py/builtinimport.o build/py/builtinevex.o build/py/builtinhelp.o build/py/modarray.o build/py/modbuiltins.o build/py/modcollections.o build/py/modgc.o build/py/modio.o build/py/modmath.o build/py/modcmath.o build/py/modmicropython.o build/py/modstruct.o build/py/modsys.o build/py/moduerrno.o build/py/modthread.o build/py/vm.o build/py/bc.o build/py/showbc.o build/py/repl.o build/py/smallint.o build/py/frozenmod.o build/main.o build/gccollect.o   -Wl,-map,mpy-cross.map -Wl,-dead_strip -lm 
strip  mpy-cross
size $(find build -path "build/build/frozen*.o") mpy-cross
__TEXT  __DATA  __OBJC  others  dec     hex
303104  20480   0       4294982988      4295306572      100052d4c
make[1]: Leaving directory '/Users/Luppy/PineTime/wasp-os/micropython/mpy-cross'
rm -f micropython/ports/mynewt/build-pinetime/frozen_content.c
make -C micropython/ports/mynewt \
        BOARD=pinetime \
        MICROPY_VFS_LFS2=1 \
        FROZEN_MANIFEST=/Users/Luppy/PineTime/wasp-os/wasp/boards/pinetime/manifest.py
make[1]: Entering directory '/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt'
python3 ../../py/makeversionhdr.py build-pinetime/genhdr/mpversion.h
GEN build-pinetime/genhdr/mpversion.h
GEN build-pinetime/genhdr/qstr.i.last
arm-none-eabi-gcc -E -DNO_QSTR -Ibuild-pinetime/tmp -ffunction-sections -fdata-sections -mthumb -mabi=aapcs -fsingle-precision-constant -Wdouble-promotion -mtune=cortex-m4 -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -I. -I../.. -Ibuild-pinetime -I./../../lib/cmsis/inc -I./modules/machine -I./modules/ubluepy -I./modules/music -I./modules/random -I./modules/ble -I./modules/board -I../../lib/mp-readline -I./drivers/bluetooth -I./drivers -I../../lib/nrfx/ -I../../lib/nrfx/drivers -I../../lib/nrfx/drivers/include -I../../lib/nrfx/mdk -I../../lib/nrfx/hal -I../../lib/nrfx/drivers/src/ -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/boot/split/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/encoding/json/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/encoding/tinycbor/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/hw/drivers/flash/spiflash/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/hw/hal/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/hw/mcu/nordic/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/hw/mcu/nordic/nrf52xxx/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/hw/mcu/nordic/src/ext/nrfx/ -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/hw/mcu/nordic/src/ext/nrfx/mdk -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/hw/sensor/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/kernel/os/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/kernel/os/include/os -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/kernel/os/include/os/arch/cortex_m4 -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/mgmt/imgmgr/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/mgmt/newtmgr/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/mgmt/newtmgr/transport/ble/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/net/oic/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/sys/config/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/sys/defs/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/sys/flash_map/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/sys/log/common/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/sys/log/modlog/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/sys/log/stub/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/sys/sys/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/sys/sysdown/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/sys/sysinit/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-nimble/nimble/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-nimble/nimble/host/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-nimble/nimble/host/services/ans/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-nimble/nimble/host/services/dis/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-nimble/nimble/host/services/gap/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-nimble/nimble/host/services/gatt/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-nimble/nimble/host/store/config/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-nimble/nimble/host/util/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-nimble/nimble/transport -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-nimble/porting/npl/mynewt/include -I../../../../pinetime-rust-mynewt/repos/mcuboot/boot/bootutil/include -I../../../../pinetime-rust-mynewt/bin/targets/nrf52_my_sensor/generated/include -I../../../../pinetime-rust-mynewt/libs/semihosting_console/include -Wall -Werror -g -ansi -std=c11 -nostdlib  -DNRF52832_XXAA -DNRF52 -DNRF52832 -DCONFIG_GPIO_AS_PINRESET -DFFCONF_H=\"lib/oofatfs/ffconf.h\" -DMICROPY_VFS_LFS2=1 -DLFS2_NO_MALLOC -DLFS2_NO_DEBUG -DLFS2_NO_WARN -DLFS2_NO_ERROR -DLFS2_NO_ASSERT -fno-strict-aliasing -Iboards/pinetime -DNRF5_HAL_H='<nrf52_hal.h>' -Os -DNDEBUG -DMICROPY_MODULE_FROZEN_STR -DMICROPY_QSTR_EXTRA_POOL=mp_qstr_frozen_const_pool -DMICROPY_MODULE_FROZEN_MPY main.c >build-pinetime/genhdr/qstr.i.last
GEN build-pinetime/genhdr/qstr.split
python3 ../../py/makeqstrdefs.py split build-pinetime/genhdr/qstr.i.last build-pinetime/genhdr/qstr build-pinetime/genhdr/qstrdefs.collected.h
touch build-pinetime/genhdr/qstr.split
GEN build-pinetime/genhdr/qstrdefs.collected.h
python3 ../../py/makeqstrdefs.py cat build-pinetime/genhdr/qstr.i.last build-pinetime/genhdr/qstr build-pinetime/genhdr/qstrdefs.collected.h
QSTR not updated
python3 ../../tools/makemanifest.py -o build-pinetime/frozen_content.c -v "MPY_DIR=../.." -v "MPY_LIB_DIR=../../../micropython-lib" -v "PORT_DIR=/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt" -v "BOARD_DIR=" -b "build-pinetime" -f"-march=armv7m" /Users/Luppy/PineTime/wasp-os/wasp/boards/pinetime/manifest.py
GEN build-pinetime/frozen_content.c
CC build-pinetime/frozen_content.c
arm-none-eabi-gcc -ffunction-sections -fdata-sections -mthumb -mabi=aapcs -fsingle-precision-constant -Wdouble-promotion -mtune=cortex-m4 -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -I. -I../.. -Ibuild-pinetime -I./../../lib/cmsis/inc -I./modules/machine -I./modules/ubluepy -I./modules/music -I./modules/random -I./modules/ble -I./modules/board -I../../lib/mp-readline -I./drivers/bluetooth -I./drivers -I../../lib/nrfx/ -I../../lib/nrfx/drivers -I../../lib/nrfx/drivers/include -I../../lib/nrfx/mdk -I../../lib/nrfx/hal -I../../lib/nrfx/drivers/src/ -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/boot/split/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/encoding/json/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/encoding/tinycbor/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/hw/drivers/flash/spiflash/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/hw/hal/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/hw/mcu/nordic/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/hw/mcu/nordic/nrf52xxx/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/hw/mcu/nordic/src/ext/nrfx/ -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/hw/mcu/nordic/src/ext/nrfx/mdk -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/hw/sensor/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/kernel/os/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/kernel/os/include/os -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/kernel/os/include/os/arch/cortex_m4 -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/mgmt/imgmgr/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/mgmt/newtmgr/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/mgmt/newtmgr/transport/ble/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/net/oic/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/sys/config/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/sys/defs/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/sys/flash_map/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/sys/log/common/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/sys/log/modlog/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/sys/log/stub/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/sys/sys/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/sys/sysdown/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/sys/sysinit/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-nimble/nimble/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-nimble/nimble/host/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-nimble/nimble/host/services/ans/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-nimble/nimble/host/services/dis/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-nimble/nimble/host/services/gap/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-nimble/nimble/host/services/gatt/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-nimble/nimble/host/store/config/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-nimble/nimble/host/util/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-nimble/nimble/transport -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-nimble/porting/npl/mynewt/include -I../../../../pinetime-rust-mynewt/repos/mcuboot/boot/bootutil/include -I../../../../pinetime-rust-mynewt/bin/targets/nrf52_my_sensor/generated/include -I../../../../pinetime-rust-mynewt/libs/semihosting_console/include -Wall -Werror -g -ansi -std=c11 -nostdlib  -DNRF52832_XXAA -DNRF52 -DNRF52832 -DCONFIG_GPIO_AS_PINRESET -DFFCONF_H=\"lib/oofatfs/ffconf.h\" -DMICROPY_VFS_LFS2=1 -DLFS2_NO_MALLOC -DLFS2_NO_DEBUG -DLFS2_NO_WARN -DLFS2_NO_ERROR -DLFS2_NO_ASSERT -fno-strict-aliasing -Iboards/pinetime -DNRF5_HAL_H='<nrf52_hal.h>' -Os -DNDEBUG -DMICROPY_MODULE_FROZEN_STR -DMICROPY_QSTR_EXTRA_POOL=mp_qstr_frozen_const_pool -DMICROPY_MODULE_FROZEN_MPY -c -MD -o build-pinetime/build-pinetime/frozen_content.o build-pinetime/frozen_content.c
CC main.c
arm-none-eabi-gcc -ffunction-sections -fdata-sections -mthumb -mabi=aapcs -fsingle-precision-constant -Wdouble-promotion -mtune=cortex-m4 -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -I. -I../.. -Ibuild-pinetime -I./../../lib/cmsis/inc -I./modules/machine -I./modules/ubluepy -I./modules/music -I./modules/random -I./modules/ble -I./modules/board -I../../lib/mp-readline -I./drivers/bluetooth -I./drivers -I../../lib/nrfx/ -I../../lib/nrfx/drivers -I../../lib/nrfx/drivers/include -I../../lib/nrfx/mdk -I../../lib/nrfx/hal -I../../lib/nrfx/drivers/src/ -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/boot/split/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/encoding/json/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/encoding/tinycbor/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/hw/drivers/flash/spiflash/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/hw/hal/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/hw/mcu/nordic/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/hw/mcu/nordic/nrf52xxx/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/hw/mcu/nordic/src/ext/nrfx/ -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/hw/mcu/nordic/src/ext/nrfx/mdk -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/hw/sensor/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/kernel/os/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/kernel/os/include/os -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/kernel/os/include/os/arch/cortex_m4 -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/mgmt/imgmgr/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/mgmt/newtmgr/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/mgmt/newtmgr/transport/ble/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/net/oic/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/sys/config/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/sys/defs/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/sys/flash_map/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/sys/log/common/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/sys/log/modlog/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/sys/log/stub/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/sys/sys/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/sys/sysdown/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/sys/sysinit/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-nimble/nimble/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-nimble/nimble/host/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-nimble/nimble/host/services/ans/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-nimble/nimble/host/services/dis/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-nimble/nimble/host/services/gap/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-nimble/nimble/host/services/gatt/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-nimble/nimble/host/store/config/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-nimble/nimble/host/util/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-nimble/nimble/transport -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-nimble/porting/npl/mynewt/include -I../../../../pinetime-rust-mynewt/repos/mcuboot/boot/bootutil/include -I../../../../pinetime-rust-mynewt/bin/targets/nrf52_my_sensor/generated/include -I../../../../pinetime-rust-mynewt/libs/semihosting_console/include -Wall -Werror -g -ansi -std=c11 -nostdlib  -DNRF52832_XXAA -DNRF52 -DNRF52832 -DCONFIG_GPIO_AS_PINRESET -DFFCONF_H=\"lib/oofatfs/ffconf.h\" -DMICROPY_VFS_LFS2=1 -DLFS2_NO_MALLOC -DLFS2_NO_DEBUG -DLFS2_NO_WARN -DLFS2_NO_ERROR -DLFS2_NO_ASSERT -fno-strict-aliasing -Iboards/pinetime -DNRF5_HAL_H='<nrf52_hal.h>' -Os -DNDEBUG -DMICROPY_MODULE_FROZEN_STR -DMICROPY_QSTR_EXTRA_POOL=mp_qstr_frozen_const_pool -DMICROPY_MODULE_FROZEN_MPY -c -MD -o build-pinetime/main.o main.c
CC modules/uos/moduos.c
arm-none-eabi-gcc -ffunction-sections -fdata-sections -mthumb -mabi=aapcs -fsingle-precision-constant -Wdouble-promotion -mtune=cortex-m4 -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -I. -I../.. -Ibuild-pinetime -I./../../lib/cmsis/inc -I./modules/machine -I./modules/ubluepy -I./modules/music -I./modules/random -I./modules/ble -I./modules/board -I../../lib/mp-readline -I./drivers/bluetooth -I./drivers -I../../lib/nrfx/ -I../../lib/nrfx/drivers -I../../lib/nrfx/drivers/include -I../../lib/nrfx/mdk -I../../lib/nrfx/hal -I../../lib/nrfx/drivers/src/ -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/boot/split/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/encoding/json/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/encoding/tinycbor/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/hw/drivers/flash/spiflash/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/hw/hal/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/hw/mcu/nordic/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/hw/mcu/nordic/nrf52xxx/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/hw/mcu/nordic/src/ext/nrfx/ -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/hw/mcu/nordic/src/ext/nrfx/mdk -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/hw/sensor/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/kernel/os/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/kernel/os/include/os -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/kernel/os/include/os/arch/cortex_m4 -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/mgmt/imgmgr/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/mgmt/newtmgr/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/mgmt/newtmgr/transport/ble/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/net/oic/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/sys/config/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/sys/defs/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/sys/flash_map/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/sys/log/common/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/sys/log/modlog/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/sys/log/stub/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/sys/sys/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/sys/sysdown/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/sys/sysinit/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-nimble/nimble/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-nimble/nimble/host/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-nimble/nimble/host/services/ans/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-nimble/nimble/host/services/dis/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-nimble/nimble/host/services/gap/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-nimble/nimble/host/services/gatt/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-nimble/nimble/host/store/config/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-nimble/nimble/host/util/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-nimble/nimble/transport -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-nimble/porting/npl/mynewt/include -I../../../../pinetime-rust-mynewt/repos/mcuboot/boot/bootutil/include -I../../../../pinetime-rust-mynewt/bin/targets/nrf52_my_sensor/generated/include -I../../../../pinetime-rust-mynewt/libs/semihosting_console/include -Wall -Werror -g -ansi -std=c11 -nostdlib  -DNRF52832_XXAA -DNRF52 -DNRF52832 -DCONFIG_GPIO_AS_PINRESET -DFFCONF_H=\"lib/oofatfs/ffconf.h\" -DMICROPY_VFS_LFS2=1 -DLFS2_NO_MALLOC -DLFS2_NO_DEBUG -DLFS2_NO_WARN -DLFS2_NO_ERROR -DLFS2_NO_ASSERT -fno-strict-aliasing -Iboards/pinetime -DNRF5_HAL_H='<nrf52_hal.h>' -Os -DNDEBUG -DMICROPY_MODULE_FROZEN_STR -DMICROPY_QSTR_EXTRA_POOL=mp_qstr_frozen_const_pool -DMICROPY_MODULE_FROZEN_MPY -c -MD -o build-pinetime/modules/uos/moduos.o modules/uos/moduos.c
CC ../../lib/utils/pyexec.c
arm-none-eabi-gcc -ffunction-sections -fdata-sections -mthumb -mabi=aapcs -fsingle-precision-constant -Wdouble-promotion -mtune=cortex-m4 -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -I. -I../.. -Ibuild-pinetime -I./../../lib/cmsis/inc -I./modules/machine -I./modules/ubluepy -I./modules/music -I./modules/random -I./modules/ble -I./modules/board -I../../lib/mp-readline -I./drivers/bluetooth -I./drivers -I../../lib/nrfx/ -I../../lib/nrfx/drivers -I../../lib/nrfx/drivers/include -I../../lib/nrfx/mdk -I../../lib/nrfx/hal -I../../lib/nrfx/drivers/src/ -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/boot/split/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/encoding/json/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/encoding/tinycbor/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/hw/drivers/flash/spiflash/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/hw/hal/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/hw/mcu/nordic/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/hw/mcu/nordic/nrf52xxx/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/hw/mcu/nordic/src/ext/nrfx/ -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/hw/mcu/nordic/src/ext/nrfx/mdk -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/hw/sensor/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/kernel/os/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/kernel/os/include/os -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/kernel/os/include/os/arch/cortex_m4 -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/mgmt/imgmgr/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/mgmt/newtmgr/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/mgmt/newtmgr/transport/ble/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/net/oic/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/sys/config/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/sys/defs/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/sys/flash_map/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/sys/log/common/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/sys/log/modlog/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/sys/log/stub/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/sys/sys/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/sys/sysdown/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/sys/sysinit/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-nimble/nimble/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-nimble/nimble/host/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-nimble/nimble/host/services/ans/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-nimble/nimble/host/services/dis/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-nimble/nimble/host/services/gap/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-nimble/nimble/host/services/gatt/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-nimble/nimble/host/store/config/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-nimble/nimble/host/util/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-nimble/nimble/transport -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-nimble/porting/npl/mynewt/include -I../../../../pinetime-rust-mynewt/repos/mcuboot/boot/bootutil/include -I../../../../pinetime-rust-mynewt/bin/targets/nrf52_my_sensor/generated/include -I../../../../pinetime-rust-mynewt/libs/semihosting_console/include -Wall -Werror -g -ansi -std=c11 -nostdlib  -DNRF52832_XXAA -DNRF52 -DNRF52832 -DCONFIG_GPIO_AS_PINRESET -DFFCONF_H=\"lib/oofatfs/ffconf.h\" -DMICROPY_VFS_LFS2=1 -DLFS2_NO_MALLOC -DLFS2_NO_DEBUG -DLFS2_NO_WARN -DLFS2_NO_ERROR -DLFS2_NO_ASSERT -fno-strict-aliasing -Iboards/pinetime -DNRF5_HAL_H='<nrf52_hal.h>' -Os -DNDEBUG -DMICROPY_MODULE_FROZEN_STR -DMICROPY_QSTR_EXTRA_POOL=mp_qstr_frozen_const_pool -DMICROPY_MODULE_FROZEN_MPY -c -MD -o build-pinetime/lib/utils/pyexec.o ../../lib/utils/pyexec.c
ARCHIVE build-pinetime/micropython.a
arm-none-eabi-ar r build-pinetime/micropython.a build-pinetime/py/mpstate.o build-pinetime/py/nlr.o build-pinetime/py/nlrx86.o build-pinetime/py/nlrx64.o build-pinetime/py/nlrthumb.o build-pinetime/py/nlrpowerpc.o build-pinetime/py/nlrxtensa.o build-pinetime/py/nlrsetjmp.o build-pinetime/py/malloc.o build-pinetime/py/gc.o build-pinetime/py/pystack.o build-pinetime/py/qstr.o build-pinetime/py/vstr.o build-pinetime/py/mpprint.o build-pinetime/py/unicode.o build-pinetime/py/mpz.o build-pinetime/py/reader.o build-pinetime/py/lexer.o build-pinetime/py/parse.o build-pinetime/py/scope.o build-pinetime/py/compile.o build-pinetime/py/emitcommon.o build-pinetime/py/emitbc.o build-pinetime/py/asmbase.o build-pinetime/py/asmx64.o build-pinetime/py/emitnx64.o build-pinetime/py/asmx86.o build-pinetime/py/emitnx86.o build-pinetime/py/asmthumb.o build-pinetime/py/emitnthumb.o build-pinetime/py/emitinlinethumb.o build-pinetime/py/asmarm.o build-pinetime/py/emitnarm.o build-pinetime/py/asmxtensa.o build-pinetime/py/emitnxtensa.o build-pinetime/py/emitinlinextensa.o build-pinetime/py/emitnxtensawin.o build-pinetime/py/formatfloat.o build-pinetime/py/parsenumbase.o build-pinetime/py/parsenum.o build-pinetime/py/emitglue.o build-pinetime/py/persistentcode.o build-pinetime/py/runtime.o build-pinetime/py/runtime_utils.o build-pinetime/py/scheduler.o build-pinetime/py/nativeglue.o build-pinetime/py/ringbuf.o build-pinetime/py/stackctrl.o build-pinetime/py/argcheck.o build-pinetime/py/warning.o build-pinetime/py/profile.o build-pinetime/py/map.o build-pinetime/py/obj.o build-pinetime/py/objarray.o build-pinetime/py/objattrtuple.o build-pinetime/py/objbool.o build-pinetime/py/objboundmeth.o build-pinetime/py/objcell.o build-pinetime/py/objclosure.o build-pinetime/py/objcomplex.o build-pinetime/py/objdeque.o build-pinetime/py/objdict.o build-pinetime/py/objenumerate.o build-pinetime/py/objexcept.o build-pinetime/py/objfilter.o build-pinetime/py/objfloat.o build-pinetime/py/objfun.o build-pinetime/py/objgenerator.o build-pinetime/py/objgetitemiter.o build-pinetime/py/objint.o build-pinetime/py/objint_longlong.o build-pinetime/py/objint_mpz.o build-pinetime/py/objlist.o build-pinetime/py/objmap.o build-pinetime/py/objmodule.o build-pinetime/py/objobject.o build-pinetime/py/objpolyiter.o build-pinetime/py/objproperty.o build-pinetime/py/objnone.o build-pinetime/py/objnamedtuple.o build-pinetime/py/objrange.o build-pinetime/py/objreversed.o build-pinetime/py/objset.o build-pinetime/py/objsingleton.o build-pinetime/py/objslice.o build-pinetime/py/objstr.o build-pinetime/py/objstrunicode.o build-pinetime/py/objstringio.o build-pinetime/py/objtuple.o build-pinetime/py/objtype.o build-pinetime/py/objzip.o build-pinetime/py/opmethods.o build-pinetime/py/sequence.o build-pinetime/py/stream.o build-pinetime/py/binary.o build-pinetime/py/builtinimport.o build-pinetime/py/builtinevex.o build-pinetime/py/builtinhelp.o build-pinetime/py/modarray.o build-pinetime/py/modbuiltins.o build-pinetime/py/modcollections.o build-pinetime/py/modgc.o build-pinetime/py/modio.o build-pinetime/py/modmath.o build-pinetime/py/modcmath.o build-pinetime/py/modmicropython.o build-pinetime/py/modstruct.o build-pinetime/py/modsys.o build-pinetime/py/moduerrno.o build-pinetime/py/modthread.o build-pinetime/py/vm.o build-pinetime/py/bc.o build-pinetime/py/showbc.o build-pinetime/py/repl.o build-pinetime/py/smallint.o build-pinetime/py/frozenmod.o build-pinetime/extmod/moductypes.o build-pinetime/extmod/modujson.o build-pinetime/extmod/modure.o build-pinetime/extmod/moduzlib.o build-pinetime/extmod/moduheapq.o build-pinetime/extmod/modutimeq.o build-pinetime/extmod/moduhashlib.o build-pinetime/extmod/moducryptolib.o build-pinetime/extmod/modubinascii.o build-pinetime/extmod/virtpin.o build-pinetime/extmod/machine_mem.o build-pinetime/extmod/machine_pinbase.o build-pinetime/extmod/machine_signal.o build-pinetime/extmod/machine_pulse.o build-pinetime/extmod/machine_i2c.o build-pinetime/extmod/machine_spi.o build-pinetime/extmod/modbluetooth.o build-pinetime/extmod/modussl_axtls.o build-pinetime/extmod/modussl_mbedtls.o build-pinetime/extmod/modurandom.o build-pinetime/extmod/moduselect.o build-pinetime/extmod/moduwebsocket.o build-pinetime/extmod/modwebrepl.o build-pinetime/extmod/modframebuf.o build-pinetime/extmod/vfs.o build-pinetime/extmod/vfs_blockdev.o build-pinetime/extmod/vfs_reader.o build-pinetime/extmod/vfs_posix.o build-pinetime/extmod/vfs_posix_file.o build-pinetime/extmod/vfs_fat.o build-pinetime/extmod/vfs_fat_diskio.o build-pinetime/extmod/vfs_fat_file.o build-pinetime/extmod/vfs_lfs.o build-pinetime/extmod/utime_mphal.o build-pinetime/extmod/uos_dupterm.o build-pinetime/lib/embed/abort_.o build-pinetime/lib/utils/printf.o build-pinetime/build-pinetime/frozen_content.o build-pinetime/main.o build-pinetime/mphalport.o build-pinetime/help.o build-pinetime/gccollect.o build-pinetime/pin_named_pins.o build-pinetime/fatfs_port.o build-pinetime/drivers/flash.o build-pinetime/drivers/softpwm.o build-pinetime/drivers/ticker.o build-pinetime/drivers/wdt.o build-pinetime/drivers/bluetooth/ble_drv.o build-pinetime/drivers/bluetooth/ble_uart.o build-pinetime/lib/littlefs/lfs2.o build-pinetime/lib/littlefs/lfs2_util.o   build-pinetime/modules/machine/modmachine.o build-pinetime/modules/machine/uart.o build-pinetime/modules/machine/spi.o build-pinetime/modules/machine/i2c.o build-pinetime/modules/machine/adc.o build-pinetime/modules/machine/pin.o build-pinetime/modules/machine/timer.o build-pinetime/modules/machine/rtcounter.o build-pinetime/modules/machine/pwm.o build-pinetime/modules/machine/temp.o build-pinetime/modules/uos/moduos.o build-pinetime/modules/uos/microbitfs.o build-pinetime/modules/utime/modutime.o build-pinetime/modules/board/modboard.o build-pinetime/modules/board/led.o build-pinetime/modules/ubluepy/modubluepy.o build-pinetime/modules/ubluepy/ubluepy_peripheral.o build-pinetime/modules/ubluepy/ubluepy_service.o build-pinetime/modules/ubluepy/ubluepy_characteristic.o build-pinetime/modules/ubluepy/ubluepy_uuid.o build-pinetime/modules/ubluepy/ubluepy_delegate.o build-pinetime/modules/ubluepy/ubluepy_constants.o build-pinetime/modules/ubluepy/ubluepy_descriptor.o build-pinetime/modules/ubluepy/ubluepy_scanner.o build-pinetime/modules/ubluepy/ubluepy_scan_entry.o build-pinetime/modules/music/modmusic.o build-pinetime/modules/music/musictunes.o build-pinetime/modules/ble/modble.o build-pinetime/modules/random/modrandom.o build-pinetime/lib/nrfx/mdk/system_nrf52.o build-pinetime/lib/libm/math.o build-pinetime/lib/libm/fmodf.o build-pinetime/lib/libm/nearbyintf.o build-pinetime/lib/libm/ef_sqrt.o build-pinetime/lib/libm/kf_rem_pio2.o build-pinetime/lib/libm/kf_sin.o build-pinetime/lib/libm/kf_cos.o build-pinetime/lib/libm/kf_tan.o build-pinetime/lib/libm/ef_rem_pio2.o build-pinetime/lib/libm/sf_sin.o build-pinetime/lib/libm/sf_cos.o build-pinetime/lib/libm/sf_tan.o build-pinetime/lib/libm/sf_frexp.o build-pinetime/lib/libm/sf_modf.o build-pinetime/lib/libm/sf_ldexp.o build-pinetime/lib/libm/asinfacosf.o build-pinetime/lib/libm/atanf.o build-pinetime/lib/libm/atan2f.o build-pinetime/lib/mp-readline/readline.o build-pinetime/lib/utils/pyexec.o build-pinetime/lib/utils/sys_stdio_mphal.o build-pinetime/lib/utils/interrupt_char.o build-pinetime/lib/timeutils/timeutils.o build-pinetime/pins_gen.o
arm-none-eabi-ranlib -t build-pinetime/micropython.a
arm-none-eabi-size build-pinetime/micropython.a
   text    data     bss     dec     hex filename
      0       0       0       0       0 mpstate.o (ex build-pinetime/micropython.a)
     32       0       0      32      20 nlr.o (ex build-pinetime/micropython.a)
      0       0       0       0       0 nlrx86.o (ex build-pinetime/micropython.a)
      0       0       0       0       0 nlrx64.o (ex build-pinetime/micropython.a)
    120       0       0     120      78 nlrthumb.o (ex build-pinetime/micropython.a)
      0       0       0       0       0 nlrpowerpc.o (ex build-pinetime/micropython.a)
      0       0       0       0       0 nlrxtensa.o (ex build-pinetime/micropython.a)
      0       0       0       0       0 nlrsetjmp.o (ex build-pinetime/micropython.a)
     84       0       0      84      54 malloc.o (ex build-pinetime/micropython.a)
   3283       0       0    3283     cd3 gc.o (ex build-pinetime/micropython.a)
      0       0       0       0       0 pystack.o (ex build-pinetime/micropython.a)
  10210       0       0   10210    27e2 qstr.o (ex build-pinetime/micropython.a)
    596       0       0     596     254 vstr.o (ex build-pinetime/micropython.a)
   1800       0       0    1800     708 mpprint.o (ex build-pinetime/micropython.a)
    330       0       0     330     14a unicode.o (ex build-pinetime/micropython.a)
   4486       0       0    4486    1186 mpz.o (ex build-pinetime/micropython.a)
     92       0       0      92      5c reader.o (ex build-pinetime/micropython.a)
   2311       0       0    2311     907 lexer.o (ex build-pinetime/micropython.a)
   3765       0       0    3765     eb5 parse.o (ex build-pinetime/micropython.a)
    299       0       0     299     12b scope.o (ex build-pinetime/micropython.a)
  12286       0       0   12286    2ffe compile.o (ex build-pinetime/micropython.a)
     98       0       0      98      62 emitcommon.o (ex build-pinetime/micropython.a)
   2482       0       0    2482     9b2 emitbc.o (ex build-pinetime/micropython.a)
    164       0       0     164      a4 asmbase.o (ex build-pinetime/micropython.a)
      0       0       0       0       0 asmx64.o (ex build-pinetime/micropython.a)
      0       0       0       0       0 emitnx64.o (ex build-pinetime/micropython.a)
      0       0       0       0       0 asmx86.o (ex build-pinetime/micropython.a)
      0       0       0       0       0 emitnx86.o (ex build-pinetime/micropython.a)
    990       0       0     990     3de asmthumb.o (ex build-pinetime/micropython.a)
  11149       0       0   11149    2b8d emitnthumb.o (ex build-pinetime/micropython.a)
      0       0       0       0       0 emitinlinethumb.o (ex build-pinetime/micropython.a)
      0       0       0       0       0 asmarm.o (ex build-pinetime/micropython.a)
      0       0       0       0       0 emitnarm.o (ex build-pinetime/micropython.a)
      0       0       0       0       0 asmxtensa.o (ex build-pinetime/micropython.a)
      0       0       0       0       0 emitnxtensa.o (ex build-pinetime/micropython.a)
      0       0       0       0       0 emitinlinextensa.o (ex build-pinetime/micropython.a)
      0       0       0       0       0 emitnxtensawin.o (ex build-pinetime/micropython.a)
   1128       0       0    1128     468 formatfloat.o (ex build-pinetime/micropython.a)
    110       0       0     110      6e parsenumbase.o (ex build-pinetime/micropython.a)
   1069       0       0    1069     42d parsenum.o (ex build-pinetime/micropython.a)
    190       0       0     190      be emitglue.o (ex build-pinetime/micropython.a)
      0       0       0       0       0 persistentcode.o (ex build-pinetime/micropython.a)
   5147       0       0    5147    141b runtime.o (ex build-pinetime/micropython.a)
    108       0       0     108      6c runtime_utils.o (ex build-pinetime/micropython.a)
     24       0       0      24      18 scheduler.o (ex build-pinetime/micropython.a)
    788       0       0     788     314 nativeglue.o (ex build-pinetime/micropython.a)
    128       0       0     128      80 ringbuf.o (ex build-pinetime/micropython.a)
     92       0       0      92      5c stackctrl.o (ex build-pinetime/micropython.a)
    726       0       0     726     2d6 argcheck.o (ex build-pinetime/micropython.a)
      0       0       0       0       0 warning.o (ex build-pinetime/micropython.a)
      0       0       0       0       0 profile.o (ex build-pinetime/micropython.a)
   1126       0       0    1126     466 map.o (ex build-pinetime/micropython.a)
   2073       0       0    2073     819 obj.o (ex build-pinetime/micropython.a)
   2467       0       0    2467     9a3 objarray.o (ex build-pinetime/micropython.a)
    285       0       0     285     11d objattrtuple.o (ex build-pinetime/micropython.a)
    187       0       0     187      bb objbool.o (ex build-pinetime/micropython.a)
    228       0       0     228      e4 objboundmeth.o (ex build-pinetime/micropython.a)
     92       0       0      92      5c objcell.o (ex build-pinetime/micropython.a)
    254       0       0     254      fe objclosure.o (ex build-pinetime/micropython.a)
   1278       0       0    1278     4fe objcomplex.o (ex build-pinetime/micropython.a)
      0       0       0       0       0 objdeque.o (ex build-pinetime/micropython.a)
   2088       0       0    2088     828 objdict.o (ex build-pinetime/micropython.a)
    176       0       0     176      b0 objenumerate.o (ex build-pinetime/micropython.a)
   2734       0       0    2734     aae objexcept.o (ex build-pinetime/micropython.a)
    158       0       0     158      9e objfilter.o (ex build-pinetime/micropython.a)
   1316       0       0    1316     524 objfloat.o (ex build-pinetime/micropython.a)
   1114       0       0    1114     45a objfun.o (ex build-pinetime/micropython.a)
   1203       0       0    1203     4b3 objgenerator.o (ex build-pinetime/micropython.a)
    168       0       0     168      a8 objgetitemiter.o (ex build-pinetime/micropython.a)
   1190       0       0    1190     4a6 objint.o (ex build-pinetime/micropython.a)
      0       0       0       0       0 objint_longlong.o (ex build-pinetime/micropython.a)
   1267       0       0    1267     4f3 objint_mpz.o (ex build-pinetime/micropython.a)
   2199       0       0    2199     897 objlist.o (ex build-pinetime/micropython.a)
    214       0       0     214      d6 objmap.o (ex build-pinetime/micropython.a)
    681       0       0     681     2a9 objmodule.o (ex build-pinetime/micropython.a)
    232       0       0     232      e8 objobject.o (ex build-pinetime/micropython.a)
     64       0       0      64      40 objpolyiter.o (ex build-pinetime/micropython.a)
    300       0       0     300     12c objproperty.o (ex build-pinetime/micropython.a)
     81       0       0      81      51 objnone.o (ex build-pinetime/micropython.a)
    652       0       0     652     28c objnamedtuple.o (ex build-pinetime/micropython.a)
    631       0       0     631     277 objrange.o (ex build-pinetime/micropython.a)
    164       0       0     164      a4 objreversed.o (ex build-pinetime/micropython.a)
   2215       0       0    2215     8a7 objset.o (ex build-pinetime/micropython.a)
     83       0       0      83      53 objsingleton.o (ex build-pinetime/micropython.a)
    204       0       0     204      cc objslice.o (ex build-pinetime/micropython.a)
   9122       0       0    9122    23a2 objstr.o (ex build-pinetime/micropython.a)
      0       0       0       0       0 objstrunicode.o (ex build-pinetime/micropython.a)
    912       0       0     912     390 objstringio.o (ex build-pinetime/micropython.a)
   1026       0       0    1026     402 objtuple.o (ex build-pinetime/micropython.a)
   4084       0       0    4084     ff4 objtype.o (ex build-pinetime/micropython.a)
    208       0       0     208      d0 objzip.o (ex build-pinetime/micropython.a)
    130       0       0     130      82 opmethods.o (ex build-pinetime/micropython.a)
    801       0       0     801     321 sequence.o (ex build-pinetime/micropython.a)
   1303       0       0    1303     517 stream.o (ex build-pinetime/micropython.a)
   1267       0       0    1267     4f3 binary.o (ex build-pinetime/micropython.a)
   1202       0       0    1202     4b2 builtinimport.o (ex build-pinetime/micropython.a)
    449       0       0     449     1c1 builtinevex.o (ex build-pinetime/micropython.a)
    991       0       0     991     3df builtinhelp.o (ex build-pinetime/micropython.a)
     40       0       0      40      28 modarray.o (ex build-pinetime/micropython.a)
   2863       0       0    2863     b2f modbuiltins.o (ex build-pinetime/micropython.a)
     40       0       0      40      28 modcollections.o (ex build-pinetime/micropython.a)
    348       0       0     348     15c modgc.o (ex build-pinetime/micropython.a)
     56       0       0      56      38 modio.o (ex build-pinetime/micropython.a)
   1371       0       0    1371     55b modmath.o (ex build-pinetime/micropython.a)
      0       0       0       0       0 modcmath.o (ex build-pinetime/micropython.a)
    499       0       0     499     1f3 modmicropython.o (ex build-pinetime/micropython.a)
    921       0       0     921     399 modstruct.o (ex build-pinetime/micropython.a)
    372       0       0     372     174 modsys.o (ex build-pinetime/micropython.a)
      0       0       0       0       0 moduerrno.o (ex build-pinetime/micropython.a)
      0       0       0       0       0 modthread.o (ex build-pinetime/micropython.a)
   3551       0       0    3551     ddf vm.o (ex build-pinetime/micropython.a)
   1082       0       0    1082     43a bc.o (ex build-pinetime/micropython.a)
      0       0       0       0       0 showbc.o (ex build-pinetime/micropython.a)
    974       0       0     974     3ce repl.o (ex build-pinetime/micropython.a)
    126       0       0     126      7e smallint.o (ex build-pinetime/micropython.a)
    318       0       0     318     13e frozenmod.o (ex build-pinetime/micropython.a)
      0       0       0       0       0 moductypes.o (ex build-pinetime/micropython.a)
      0       0       0       0       0 modujson.o (ex build-pinetime/micropython.a)
      0       0       0       0       0 modure.o (ex build-pinetime/micropython.a)
      0       0       0       0       0 moduzlib.o (ex build-pinetime/micropython.a)
      0       0       0       0       0 moduheapq.o (ex build-pinetime/micropython.a)
      0       0       0       0       0 modutimeq.o (ex build-pinetime/micropython.a)
      0       0       0       0       0 moduhashlib.o (ex build-pinetime/micropython.a)
      0       0       0       0       0 moducryptolib.o (ex build-pinetime/micropython.a)
    816       0       0     816     330 modubinascii.o (ex build-pinetime/micropython.a)
     44       0       0      44      2c virtpin.o (ex build-pinetime/micropython.a)
    288       0       0     288     120 machine_mem.o (ex build-pinetime/micropython.a)
    164       0       0     164      a4 machine_pinbase.o (ex build-pinetime/micropython.a)
    342       0       0     342     156 machine_signal.o (ex build-pinetime/micropython.a)
      0       0       0       0       0 machine_pulse.o (ex build-pinetime/micropython.a)
   2582       0       0    2582     a16 machine_i2c.o (ex build-pinetime/micropython.a)
      0       0       0       0       0 machine_spi.o (ex build-pinetime/micropython.a)
      0       0       0       0       0 modbluetooth.o (ex build-pinetime/micropython.a)
      0       0       0       0       0 modussl_axtls.o (ex build-pinetime/micropython.a)
      0       0       0       0       0 modussl_mbedtls.o (ex build-pinetime/micropython.a)
      0       0       0       0       0 modurandom.o (ex build-pinetime/micropython.a)
      0       0       0       0       0 moduselect.o (ex build-pinetime/micropython.a)
      0       0       0       0       0 moduwebsocket.o (ex build-pinetime/micropython.a)
      0       0       0       0       0 modwebrepl.o (ex build-pinetime/micropython.a)
      0       0       0       0       0 modframebuf.o (ex build-pinetime/micropython.a)
   1751       0       0    1751     6d7 vfs.o (ex build-pinetime/micropython.a)
    484       0       0     484     1e4 vfs_blockdev.o (ex build-pinetime/micropython.a)
    186       0       0     186      ba vfs_reader.o (ex build-pinetime/micropython.a)
      0       0       0       0       0 vfs_posix.o (ex build-pinetime/micropython.a)
      0       0       0       0       0 vfs_posix_file.o (ex build-pinetime/micropython.a)
      0       0       0       0       0 vfs_fat.o (ex build-pinetime/micropython.a)
      0       0       0       0       0 vfs_fat_diskio.o (ex build-pinetime/micropython.a)
      0       0       0       0       0 vfs_fat_file.o (ex build-pinetime/micropython.a)
   2282       0       0    2282     8ea vfs_lfs.o (ex build-pinetime/micropython.a)
    222       0       0     222      de utime_mphal.o (ex build-pinetime/micropython.a)
      0       0       0       0       0 uos_dupterm.o (ex build-pinetime/micropython.a)
     35       0       0      35      23 abort_.o (ex build-pinetime/micropython.a)
      0       0       0       0       0 printf.o (ex build-pinetime/micropython.a)
  43555       0       0   43555    aa23 frozen_content.o (ex build-pinetime/micropython.a)
    751       0      12     763     2fb main.o (ex build-pinetime/micropython.a)
    224       0       0     224      e0 mphalport.o (ex build-pinetime/micropython.a)
    434       0       0     434     1b2 help.o (ex build-pinetime/micropython.a)
     80       0       0      80      50 gccollect.o (ex build-pinetime/micropython.a)
    231       0       0     231      e7 pin_named_pins.o (ex build-pinetime/micropython.a)
      8       0       0       8       8 fatfs_port.o (ex build-pinetime/micropython.a)
      0       0       0       0       0 flash.o (ex build-pinetime/micropython.a)
      0       0       0       0       0 softpwm.o (ex build-pinetime/micropython.a)
      0       0       0       0       0 ticker.o (ex build-pinetime/micropython.a)
     96       0       0      96      60 wdt.o (ex build-pinetime/micropython.a)
      0       0       0       0       0 ble_drv.o (ex build-pinetime/micropython.a)
      0       0       0       0       0 ble_uart.o (ex build-pinetime/micropython.a)
  12482       0       0   12482    30c2 lfs2.o (ex build-pinetime/micropython.a)
    120       0       0     120      78 lfs2_util.o (ex build-pinetime/micropython.a)
   1197       0       4    1201     4b1 modmachine.o (ex build-pinetime/micropython.a)
      0       0       0       0       0 uart.o (ex build-pinetime/micropython.a)
    999       0      48    1047     417 spi.o (ex build-pinetime/micropython.a)
    268       0       0     268     10c i2c.o (ex build-pinetime/micropython.a)
    586       0       0     586     24a adc.o (ex build-pinetime/micropython.a)
   1812       0       0    1812     714 pin.o (ex build-pinetime/micropython.a)
    646       0       0     646     286 timer.o (ex build-pinetime/micropython.a)
    641       0      24     665     299 rtcounter.o (ex build-pinetime/micropython.a)
    897       0      24     921     399 pwm.o (ex build-pinetime/micropython.a)
    205       0       0     205      cd temp.o (ex build-pinetime/micropython.a)
    386       0       0     386     182 moduos.o (ex build-pinetime/micropython.a)
   1175       0       0    1175     497 microbitfs.o (ex build-pinetime/micropython.a)
    373       0       0     373     175 modutime.o (ex build-pinetime/micropython.a)
     40       0       0      40      28 modboard.o (ex build-pinetime/micropython.a)
      6       0       0       6       6 led.o (ex build-pinetime/micropython.a)
      0       0       0       0       0 modubluepy.o (ex build-pinetime/micropython.a)
      0       0       0       0       0 ubluepy_peripheral.o (ex build-pinetime/micropython.a)
      0       0       0       0       0 ubluepy_service.o (ex build-pinetime/micropython.a)
      0       0       0       0       0 ubluepy_characteristic.o (ex build-pinetime/micropython.a)
      0       0       0       0       0 ubluepy_uuid.o (ex build-pinetime/micropython.a)
      0       0       0       0       0 ubluepy_delegate.o (ex build-pinetime/micropython.a)
      0       0       0       0       0 ubluepy_constants.o (ex build-pinetime/micropython.a)
      0       0       0       0       0 ubluepy_descriptor.o (ex build-pinetime/micropython.a)
      0       0       0       0       0 ubluepy_scanner.o (ex build-pinetime/micropython.a)
      0       0       0       0       0 ubluepy_scan_entry.o (ex build-pinetime/micropython.a)
      0       0       0       0       0 modmusic.o (ex build-pinetime/micropython.a)
      0       0       0       0       0 musictunes.o (ex build-pinetime/micropython.a)
      0       0       0       0       0 modble.o (ex build-pinetime/micropython.a)
    638       0       0     638     27e modrandom.o (ex build-pinetime/micropython.a)
    736       4       0     740     2e4 system_nrf52.o (ex build-pinetime/micropython.a)
   3296       0       0    3296     ce0 math.o (ex build-pinetime/micropython.a)
    200       0       0     200      c8 fmodf.o (ex build-pinetime/micropython.a)
     76       0       0      76      4c nearbyintf.o (ex build-pinetime/micropython.a)
    146       0       0     146      92 ef_sqrt.o (ex build-pinetime/micropython.a)
   1340       0       0    1340     53c kf_rem_pio2.o (ex build-pinetime/micropython.a)
    136       0       0     136      88 kf_sin.o (ex build-pinetime/micropython.a)
    188       0       0     188      bc kf_cos.o (ex build-pinetime/micropython.a)
    444       0       0     444     1bc kf_tan.o (ex build-pinetime/micropython.a)
   1516       0       0    1516     5ec ef_rem_pio2.o (ex build-pinetime/micropython.a)
    132       0       0     132      84 sf_sin.o (ex build-pinetime/micropython.a)
    128       0       0     128      80 sf_cos.o (ex build-pinetime/micropython.a)
     80       0       0      80      50 sf_tan.o (ex build-pinetime/micropython.a)
     84       0       0      84      54 sf_frexp.o (ex build-pinetime/micropython.a)
     80       0       0      80      50 sf_modf.o (ex build-pinetime/micropython.a)
     48       0       0      48      30 sf_ldexp.o (ex build-pinetime/micropython.a)
    512       0       0     512     200 asinfacosf.o (ex build-pinetime/micropython.a)
    368       0       0     368     170 atanf.o (ex build-pinetime/micropython.a)
    336       0       0     336     150 atan2f.o (ex build-pinetime/micropython.a)
   1098       0      28    1126     466 readline.o (ex build-pinetime/micropython.a)
   1249       1       5    1255     4e7 pyexec.o (ex build-pinetime/micropython.a)
    337       0       0     337     151 sys_stdio_mphal.o (ex build-pinetime/micropython.a)
     44       4       0      48      30 interrupt_char.o (ex build-pinetime/micropython.a)
    734       0       0     734     2de timeutils.o (ex build-pinetime/micropython.a)
   1041       0       0    1041     411 pins_gen.o (ex build-pinetime/micropython.a)
LINK build-pinetime/micropython.elf
arm-none-eabi-gcc -ffunction-sections -fdata-sections -mthumb -mabi=aapcs -fsingle-precision-constant -Wdouble-promotion -mtune=cortex-m4 -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -I. -I../.. -Ibuild-pinetime -I./../../lib/cmsis/inc -I./modules/machine -I./modules/ubluepy -I./modules/music -I./modules/random -I./modules/ble -I./modules/board -I../../lib/mp-readline -I./drivers/bluetooth -I./drivers -I../../lib/nrfx/ -I../../lib/nrfx/drivers -I../../lib/nrfx/drivers/include -I../../lib/nrfx/mdk -I../../lib/nrfx/hal -I../../lib/nrfx/drivers/src/ -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/boot/split/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/encoding/json/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/encoding/tinycbor/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/hw/drivers/flash/spiflash/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/hw/hal/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/hw/mcu/nordic/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/hw/mcu/nordic/nrf52xxx/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/hw/mcu/nordic/src/ext/nrfx/ -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/hw/mcu/nordic/src/ext/nrfx/mdk -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/hw/sensor/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/kernel/os/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/kernel/os/include/os -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/kernel/os/include/os/arch/cortex_m4 -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/mgmt/imgmgr/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/mgmt/newtmgr/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/mgmt/newtmgr/transport/ble/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/net/oic/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/sys/config/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/sys/defs/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/sys/flash_map/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/sys/log/common/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/sys/log/modlog/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/sys/log/stub/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/sys/sys/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/sys/sysdown/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/sys/sysinit/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-nimble/nimble/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-nimble/nimble/host/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-nimble/nimble/host/services/ans/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-nimble/nimble/host/services/dis/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-nimble/nimble/host/services/gap/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-nimble/nimble/host/services/gatt/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-nimble/nimble/host/store/config/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-nimble/nimble/host/util/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-nimble/nimble/transport -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-nimble/porting/npl/mynewt/include -I../../../../pinetime-rust-mynewt/repos/mcuboot/boot/bootutil/include -I../../../../pinetime-rust-mynewt/bin/targets/nrf52_my_sensor/generated/include -I../../../../pinetime-rust-mynewt/libs/semihosting_console/include -Wall -Werror -g -ansi -std=c11 -nostdlib  -DNRF52832_XXAA -DNRF52 -DNRF52832 -DCONFIG_GPIO_AS_PINRESET -DFFCONF_H=\"lib/oofatfs/ffconf.h\" -DMICROPY_VFS_LFS2=1 -DLFS2_NO_MALLOC -DLFS2_NO_DEBUG -DLFS2_NO_WARN -DLFS2_NO_ERROR -DLFS2_NO_ASSERT -fno-strict-aliasing -Iboards/pinetime -DNRF5_HAL_H='<nrf52_hal.h>' -Os -DNDEBUG -DMICROPY_MODULE_FROZEN_STR -DMICROPY_QSTR_EXTRA_POOL=mp_qstr_frozen_const_pool -DMICROPY_MODULE_FROZEN_MPY -Xlinker -Map=build-pinetime/micropython.map -mthumb -mabi=aapcs -Tboards/nrf52832_512k_64k_bldr78.ld -Tboards/memory.ld -Tboards/common.ld -L boards/ -Os -o build-pinetime/micropython.elf build-pinetime/py/mpstate.o build-pinetime/py/nlr.o build-pinetime/py/nlrx86.o build-pinetime/py/nlrx64.o build-pinetime/py/nlrthumb.o build-pinetime/py/nlrpowerpc.o build-pinetime/py/nlrxtensa.o build-pinetime/py/nlrsetjmp.o build-pinetime/py/malloc.o build-pinetime/py/gc.o build-pinetime/py/pystack.o build-pinetime/py/qstr.o build-pinetime/py/vstr.o build-pinetime/py/mpprint.o build-pinetime/py/unicode.o build-pinetime/py/mpz.o build-pinetime/py/reader.o build-pinetime/py/lexer.o build-pinetime/py/parse.o build-pinetime/py/scope.o build-pinetime/py/compile.o build-pinetime/py/emitcommon.o build-pinetime/py/emitbc.o build-pinetime/py/asmbase.o build-pinetime/py/asmx64.o build-pinetime/py/emitnx64.o build-pinetime/py/asmx86.o build-pinetime/py/emitnx86.o build-pinetime/py/asmthumb.o build-pinetime/py/emitnthumb.o build-pinetime/py/emitinlinethumb.o build-pinetime/py/asmarm.o build-pinetime/py/emitnarm.o build-pinetime/py/asmxtensa.o build-pinetime/py/emitnxtensa.o build-pinetime/py/emitinlinextensa.o build-pinetime/py/emitnxtensawin.o build-pinetime/py/formatfloat.o build-pinetime/py/parsenumbase.o build-pinetime/py/parsenum.o build-pinetime/py/emitglue.o build-pinetime/py/persistentcode.o build-pinetime/py/runtime.o build-pinetime/py/runtime_utils.o build-pinetime/py/scheduler.o build-pinetime/py/nativeglue.o build-pinetime/py/ringbuf.o build-pinetime/py/stackctrl.o build-pinetime/py/argcheck.o build-pinetime/py/warning.o build-pinetime/py/profile.o build-pinetime/py/map.o build-pinetime/py/obj.o build-pinetime/py/objarray.o build-pinetime/py/objattrtuple.o build-pinetime/py/objbool.o build-pinetime/py/objboundmeth.o build-pinetime/py/objcell.o build-pinetime/py/objclosure.o build-pinetime/py/objcomplex.o build-pinetime/py/objdeque.o build-pinetime/py/objdict.o build-pinetime/py/objenumerate.o build-pinetime/py/objexcept.o build-pinetime/py/objfilter.o build-pinetime/py/objfloat.o build-pinetime/py/objfun.o build-pinetime/py/objgenerator.o build-pinetime/py/objgetitemiter.o build-pinetime/py/objint.o build-pinetime/py/objint_longlong.o build-pinetime/py/objint_mpz.o build-pinetime/py/objlist.o build-pinetime/py/objmap.o build-pinetime/py/objmodule.o build-pinetime/py/objobject.o build-pinetime/py/objpolyiter.o build-pinetime/py/objproperty.o build-pinetime/py/objnone.o build-pinetime/py/objnamedtuple.o build-pinetime/py/objrange.o build-pinetime/py/objreversed.o build-pinetime/py/objset.o build-pinetime/py/objsingleton.o build-pinetime/py/objslice.o build-pinetime/py/objstr.o build-pinetime/py/objstrunicode.o build-pinetime/py/objstringio.o build-pinetime/py/objtuple.o build-pinetime/py/objtype.o build-pinetime/py/objzip.o build-pinetime/py/opmethods.o build-pinetime/py/sequence.o build-pinetime/py/stream.o build-pinetime/py/binary.o build-pinetime/py/builtinimport.o build-pinetime/py/builtinevex.o build-pinetime/py/builtinhelp.o build-pinetime/py/modarray.o build-pinetime/py/modbuiltins.o build-pinetime/py/modcollections.o build-pinetime/py/modgc.o build-pinetime/py/modio.o build-pinetime/py/modmath.o build-pinetime/py/modcmath.o build-pinetime/py/modmicropython.o build-pinetime/py/modstruct.o build-pinetime/py/modsys.o build-pinetime/py/moduerrno.o build-pinetime/py/modthread.o build-pinetime/py/vm.o build-pinetime/py/bc.o build-pinetime/py/showbc.o build-pinetime/py/repl.o build-pinetime/py/smallint.o build-pinetime/py/frozenmod.o build-pinetime/extmod/moductypes.o build-pinetime/extmod/modujson.o build-pinetime/extmod/modure.o build-pinetime/extmod/moduzlib.o build-pinetime/extmod/moduheapq.o build-pinetime/extmod/modutimeq.o build-pinetime/extmod/moduhashlib.o build-pinetime/extmod/moducryptolib.o build-pinetime/extmod/modubinascii.o build-pinetime/extmod/virtpin.o build-pinetime/extmod/machine_mem.o build-pinetime/extmod/machine_pinbase.o build-pinetime/extmod/machine_signal.o build-pinetime/extmod/machine_pulse.o build-pinetime/extmod/machine_i2c.o build-pinetime/extmod/machine_spi.o build-pinetime/extmod/modbluetooth.o build-pinetime/extmod/modussl_axtls.o build-pinetime/extmod/modussl_mbedtls.o build-pinetime/extmod/modurandom.o build-pinetime/extmod/moduselect.o build-pinetime/extmod/moduwebsocket.o build-pinetime/extmod/modwebrepl.o build-pinetime/extmod/modframebuf.o build-pinetime/extmod/vfs.o build-pinetime/extmod/vfs_blockdev.o build-pinetime/extmod/vfs_reader.o build-pinetime/extmod/vfs_posix.o build-pinetime/extmod/vfs_posix_file.o build-pinetime/extmod/vfs_fat.o build-pinetime/extmod/vfs_fat_diskio.o build-pinetime/extmod/vfs_fat_file.o build-pinetime/extmod/vfs_lfs.o build-pinetime/extmod/utime_mphal.o build-pinetime/extmod/uos_dupterm.o build-pinetime/lib/embed/abort_.o build-pinetime/lib/utils/printf.o build-pinetime/build-pinetime/frozen_content.o build-pinetime/main.o build-pinetime/mphalport.o build-pinetime/help.o build-pinetime/gccollect.o build-pinetime/pin_named_pins.o build-pinetime/fatfs_port.o build-pinetime/drivers/flash.o build-pinetime/drivers/softpwm.o build-pinetime/drivers/ticker.o build-pinetime/drivers/wdt.o build-pinetime/drivers/bluetooth/ble_drv.o build-pinetime/drivers/bluetooth/ble_uart.o build-pinetime/lib/littlefs/lfs2.o build-pinetime/lib/littlefs/lfs2_util.o   build-pinetime/modules/machine/modmachine.o build-pinetime/modules/machine/uart.o build-pinetime/modules/machine/spi.o build-pinetime/modules/machine/i2c.o build-pinetime/modules/machine/adc.o build-pinetime/modules/machine/pin.o build-pinetime/modules/machine/timer.o build-pinetime/modules/machine/rtcounter.o build-pinetime/modules/machine/pwm.o build-pinetime/modules/machine/temp.o build-pinetime/modules/uos/moduos.o build-pinetime/modules/uos/microbitfs.o build-pinetime/modules/utime/modutime.o build-pinetime/modules/board/modboard.o build-pinetime/modules/board/led.o build-pinetime/modules/ubluepy/modubluepy.o build-pinetime/modules/ubluepy/ubluepy_peripheral.o build-pinetime/modules/ubluepy/ubluepy_service.o build-pinetime/modules/ubluepy/ubluepy_characteristic.o build-pinetime/modules/ubluepy/ubluepy_uuid.o build-pinetime/modules/ubluepy/ubluepy_delegate.o build-pinetime/modules/ubluepy/ubluepy_constants.o build-pinetime/modules/ubluepy/ubluepy_descriptor.o build-pinetime/modules/ubluepy/ubluepy_scanner.o build-pinetime/modules/ubluepy/ubluepy_scan_entry.o build-pinetime/modules/music/modmusic.o build-pinetime/modules/music/musictunes.o build-pinetime/modules/ble/modble.o build-pinetime/modules/random/modrandom.o build-pinetime/lib/nrfx/mdk/system_nrf52.o build-pinetime/lib/libm/math.o build-pinetime/lib/libm/fmodf.o build-pinetime/lib/libm/nearbyintf.o build-pinetime/lib/libm/ef_sqrt.o build-pinetime/lib/libm/kf_rem_pio2.o build-pinetime/lib/libm/kf_sin.o build-pinetime/lib/libm/kf_cos.o build-pinetime/lib/libm/kf_tan.o build-pinetime/lib/libm/ef_rem_pio2.o build-pinetime/lib/libm/sf_sin.o build-pinetime/lib/libm/sf_cos.o build-pinetime/lib/libm/sf_tan.o build-pinetime/lib/libm/sf_frexp.o build-pinetime/lib/libm/sf_modf.o build-pinetime/lib/libm/sf_ldexp.o build-pinetime/lib/libm/asinfacosf.o build-pinetime/lib/libm/atanf.o build-pinetime/lib/libm/atan2f.o build-pinetime/lib/mp-readline/readline.o build-pinetime/lib/utils/pyexec.o build-pinetime/lib/utils/sys_stdio_mphal.o build-pinetime/lib/utils/interrupt_char.o build-pinetime/lib/timeutils/timeutils.o build-pinetime/pins_gen.o -L /usr/local/Cellar/arm-none-eabi-gcc/7-2018-q2-update/gcc/bin/../lib/gcc/arm-none-eabi/7.3.1/thumb/v7e-m/fpv4-sp/hard/ -lgcc
build-pinetime/py/gc.o: In function `gc_init':
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/../../py/gc.c:142: undefined reference to `memset'
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/../../py/gc.c:146: undefined reference to `memset'
build-pinetime/py/gc.o: In function `gc_alloc':
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/../../py/gc.c:530: undefined reference to `memset'
build-pinetime/py/gc.o: In function `gc_realloc':
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/../../py/gc.c:756: undefined reference to `memset'
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/../../py/gc.c:791: undefined reference to `memcpy'
build-pinetime/py/qstr.o: In function `qstr_find_strn':
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/../../py/qstr.c:181: undefined reference to `memcmp'
build-pinetime/py/qstr.o: In function `qstr_from_strn':
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/../../py/qstr.c:251: undefined reference to `memcpy'
build-pinetime/py/qstr.o: In function `qstr_from_str':
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/../../py/qstr.c:192: undefined reference to `strlen'
build-pinetime/py/vstr.o: In function `vstr_add_strn':
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/../../py/vstr.c:182: undefined reference to `memmove'
build-pinetime/py/vstr.o: In function `vstr_ins_blank_bytes':
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/../../py/vstr.c:195: undefined reference to `memmove'
build-pinetime/py/vstr.o: In function `vstr_add_str':
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/../../py/vstr.c:177: undefined reference to `strlen'
build-pinetime/py/vstr.o: In function `vstr_cut_out_bytes':
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/../../py/vstr.c:231: undefined reference to `memmove'
build-pinetime/py/mpprint.o: In function `mp_print_str':
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/../../py/mpprint.c:54: undefined reference to `strlen'
build-pinetime/py/mpprint.o: In function `mp_vprintf':
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/../../py/mpprint.c:501: undefined reference to `strlen'
build-pinetime/py/mpz.o: In function `mpz_clone':
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/../../py/mpz.c:715: undefined reference to `memcpy'
build-pinetime/py/mpz.o: In function `mpz_set':
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/../../py/mpz.c:726: undefined reference to `memcpy'
build-pinetime/py/mpz.o: In function `mpz_set_from_float':
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/../../py/mpz.c:822: undefined reference to `memset'
build-pinetime/py/mpz.o: In function `mpn_shl':
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/../../py/mpz.c:102: undefined reference to `memset'
build-pinetime/py/mpz.o: In function `mpz_mul_inpl':
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/../../py/mpz.c:1316: undefined reference to `memset'
build-pinetime/py/mpz.o: In function `mpz_divmod_inpl':
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/../../py/mpz.c:1490: undefined reference to `memset'
build-pinetime/py/mpz.o: In function `mpz_as_str_inpl':
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/../../py/mpz.c:1672: undefined reference to `memcpy'
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/../../py/mpz.c:1714: undefined reference to `strlen'
build-pinetime/py/lexer.o: In function `mp_lexer_to_next':
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/../../py/lexer.c:551: undefined reference to `strcmp'
build-pinetime/py/compile.o: In function `do_import_name':
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/../../py/compile.c:1135: undefined reference to `memcpy'
build-pinetime/py/compile.o: In function `mp_compile_to_raw_code':
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/../../py/compile.c:3428: undefined reference to `memset'
build-pinetime/py/asmbase.o: In function `mp_asm_base_start_pass':
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/../../py/asmbase.c:51: undefined reference to `memset'
build-pinetime/py/runtime.o: In function `mp_call_prepare_args_n_kw_var':
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/../../py/runtime.c:708: undefined reference to `memcpy'
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/../../py/runtime.c:765: undefined reference to `memcpy'
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/../../py/runtime.c:729: undefined reference to `memcpy'
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/../../py/runtime.c:729: undefined reference to `memcpy'
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/../../py/runtime.c:745: undefined reference to `memcpy'
build-pinetime/py/runtime.o:/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/../../py/runtime.c:1405: more undefined references to `memcpy' follow
build-pinetime/py/nativeglue.o:(.rodata.mp_fun_table+0xc8): undefined reference to `memset'
build-pinetime/py/nativeglue.o:(.rodata.mp_fun_table+0xcc): undefined reference to `memmove'
build-pinetime/py/objarray.o: In function `array_extend':
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/../../py/objarray.c:374: undefined reference to `memcpy'
build-pinetime/py/objarray.o: In function `array_append':
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/../../py/objarray.c:339: undefined reference to `memset'
build-pinetime/py/objarray.o: In function `array_subscr':
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/../../py/objarray.c:454: undefined reference to `memcpy'
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/../../py/objarray.c:454: undefined reference to `memmove'
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/../../py/objarray.c:458: undefined reference to `memset'
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/../../py/objarray.c:451: undefined reference to `memmove'
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/../../py/objarray.c:451: undefined reference to `memmove'
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/../../py/objarray.c:482: undefined reference to `memcpy'
build-pinetime/py/objarray.o: In function `array_binary_op':
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/../../py/objarray.c:275: undefined reference to `memcpy'
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/../../py/objarray.c:275: undefined reference to `memcpy'
build-pinetime/py/objarray.o: In function `array_construct':
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/../../py/objarray.c:130: undefined reference to `memcpy'
build-pinetime/py/objarray.o: In function `bytearray_make_new':
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/../../py/objarray.c:191: undefined reference to `memset'
build-pinetime/py/objarray.o: In function `mp_obj_new_bytearray':
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/../../py/objarray.c:597: undefined reference to `memcpy'
build-pinetime/py/objboundmeth.o: In function `mp_call_method_self_n_kw':
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/../../py/objboundmeth.c:69: undefined reference to `memcpy'
build-pinetime/py/objclosure.o: In function `closure_call':
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/../../py/objclosure.c:48: undefined reference to `memcpy'
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/../../py/objclosure.c:49: undefined reference to `memcpy'
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/../../py/objclosure.c:54: undefined reference to `memcpy'
build-pinetime/py/objclosure.o:/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/../../py/objclosure.c:55: more undefined references to `memcpy' follow
build-pinetime/py/objexcept.o: In function `mp_obj_new_exception_msg':
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/../../py/objexcept.c:347: undefined reference to `strlen'
build-pinetime/py/objexcept.o: In function `mp_obj_new_exception_msg_varg':
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/../../py/objexcept.c:395: undefined reference to `strlen'
build-pinetime/py/objfloat.o: In function `float_print':
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/../../py/objfloat.c:125: undefined reference to `strchr'
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/../../py/objfloat.c:125: undefined reference to `strchr'
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/../../py/objfloat.c:125: undefined reference to `strchr'
build-pinetime/py/objfun.o: In function `mp_obj_new_fun_bc':
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/../../py/objfun.c:387: undefined reference to `memcpy'
build-pinetime/py/objint.o: In function `int_to_bytes':
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/../../py/objint.c:432: undefined reference to `memset'
build-pinetime/py/objint.o: In function `mp_int_format_size':
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/../../py/objint.c:209: undefined reference to `strlen'
build-pinetime/py/objint.o: In function `mp_obj_int_formatted':
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/../../py/objint.c:282: undefined reference to `strlen'
build-pinetime/py/objint_mpz.o: In function `mp_obj_int_to_bytes_impl':
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/../../py/objint_mpz.c:117: undefined reference to `memset'
build-pinetime/py/objlist.o: In function `mp_obj_list_append':
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/../../py/objlist.c:240: undefined reference to `memset'
build-pinetime/py/objlist.o: In function `list_clear':
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/../../py/objlist.c:346: undefined reference to `memset'
build-pinetime/py/objlist.o: In function `list_pop':
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/../../py/objlist.c:276: undefined reference to `memmove'
build-pinetime/py/objlist.o: In function `list_extend':
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/../../py/objlist.c:256: undefined reference to `memset'
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/../../py/objlist.c:259: undefined reference to `memcpy'
build-pinetime/py/objlist.o: In function `mp_obj_list_init':
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/../../py/objlist.c:461: undefined reference to `memset'
build-pinetime/py/objlist.o: In function `list_binary_op':
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/../../py/objlist.c:112: undefined reference to `memcpy'
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/../../py/objlist.c:112: undefined reference to `memcpy'
build-pinetime/py/objlist.o: In function `list_subscr':
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/../../py/objlist.c:167: undefined reference to `memmove'
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/../../py/objlist.c:169: undefined reference to `memset'
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/../../py/objlist.c:187: undefined reference to `memcpy'
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/../../py/objlist.c:212: undefined reference to `memmove'
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/../../py/objlist.c:212: undefined reference to `memmove'
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/../../py/objlist.c:215: undefined reference to `memcpy'
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/../../py/objlist.c:215: undefined reference to `memmove'
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/../../py/objlist.c:218: undefined reference to `memset'
build-pinetime/py/objmodule.o: In function `mp_module_search_umodule':
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/../../py/objmodule.c:272: undefined reference to `strcmp'
build-pinetime/py/objnamedtuple.o: In function `namedtuple_make_new':
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/../../py/objnamedtuple.c:116: undefined reference to `memcpy'
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/../../py/objnamedtuple.c:119: undefined reference to `memset'
build-pinetime/py/objnamedtuple.o: In function `mp_obj_new_namedtuple_base':
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/../../py/objnamedtuple.c:147: undefined reference to `memset'
build-pinetime/py/objset.o: In function `set_copy':
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/../../py/objset.c:181: undefined reference to `memcpy'
build-pinetime/py/objstr.o: In function `str_count':
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/../../py/objstr.c:1730: undefined reference to `memcmp'
build-pinetime/py/objstr.o: In function `find_subbytes':
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/../../py/objstr.c:286: undefined reference to `memcmp'
build-pinetime/py/objstr.o: In function `mp_obj_new_str_copy':
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/../../py/objstr.c:2013: undefined reference to `memcpy'
build-pinetime/py/objstr.o: In function `str_join':
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/../../py/objstr.c:486: undefined reference to `memcpy'
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/../../py/objstr.c:490: undefined reference to `memcpy'
build-pinetime/py/objstr.o: In function `str_replace':
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/../../py/objstr.c:1649: undefined reference to `memcpy'
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/../../py/objstr.c:1660: undefined reference to `memcpy'
build-pinetime/py/objstr.o:/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/../../py/objstr.c:1665: more undefined references to `memcpy' follow
build-pinetime/py/objstr.o: In function `bytes_make_new':
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/../../py/objstr.c:234: undefined reference to `memset'
build-pinetime/py/objstr.o: In function `mp_obj_str_equal':
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/../../py/objstr.c:2106: undefined reference to `memcmp'
build-pinetime/py/objstr.o: In function `mp_obj_str_binary_op':
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/../../py/objstr.c:391: undefined reference to `memcpy'
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/../../py/objstr.c:392: undefined reference to `memcpy'
build-pinetime/py/objstr.o: In function `mp_obj_str_split':
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/../../py/objstr.c:555: undefined reference to `memcmp'
build-pinetime/py/objstr.o: In function `str_rsplit':
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/../../py/objstr.c:661: undefined reference to `memcmp'
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/../../py/objstr.c:677: undefined reference to `memmove'
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/../../py/objstr.c:678: undefined reference to `memset'
build-pinetime/py/objstr.o: In function `str_startswith':
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/../../py/objstr.c:765: undefined reference to `memcmp'
build-pinetime/py/objstr.o: In function `str_endswith':
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/../../py/objstr.c:780: undefined reference to `memcmp'
build-pinetime/py/objstr.o: In function `isalignment':
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/../../py/objstr.c:905: undefined reference to `strchr'
build-pinetime/py/objstr.o: In function `istype':
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/../../py/objstr.c:909: undefined reference to `strchr'
build-pinetime/py/objstr.o: In function `isalignment':
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/../../py/objstr.c:905: undefined reference to `strchr'
build-pinetime/py/objstringio.o: In function `stringio_copy_on_write':
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/../../py/objstringio.c:75: undefined reference to `memcpy'
build-pinetime/py/objstringio.o: In function `stringio_write':
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/../../py/objstringio.c:102: undefined reference to `memset'
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/../../py/objstringio.c:104: undefined reference to `memcpy'
build-pinetime/py/objstringio.o: In function `stringio_read':
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/../../py/objstringio.c:65: undefined reference to `memcpy'
build-pinetime/py/objtuple.o: In function `mp_obj_tuple_binary_op':
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/../../py/objtuple.c:152: undefined reference to `memcpy'
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/../../py/objtuple.c:152: undefined reference to `memcpy'
build-pinetime/py/objtuple.o: In function `mp_obj_tuple_subscr':
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/../../py/objtuple.c:191: undefined reference to `memcpy'
build-pinetime/py/objtype.o: In function `instance_subscr':
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/../../py/objtype.c:816: undefined reference to `memset'
build-pinetime/py/objtype.o: In function `mp_obj_instance_make_new':
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/../../py/objtype.c:317: undefined reference to `memcpy'
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/../../py/objtype.c:349: undefined reference to `memcpy'
build-pinetime/py/sequence.o: In function `mp_seq_multiply':
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/../../py/sequence.c:41: undefined reference to `memcpy'
build-pinetime/py/sequence.o: In function `mp_seq_cmp_bytes':
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/../../py/sequence.c:166: undefined reference to `memcmp'
build-pinetime/py/binary.o: In function `mp_binary_get_val':
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/../../py/binary.c:210: undefined reference to `strlen'
build-pinetime/py/binary.o: In function `mp_binary_set_int':
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/../../py/binary.c:236: undefined reference to `memcpy'
build-pinetime/py/binary.o: In function `mp_binary_set_val':
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/../../py/binary.c:307: undefined reference to `memset'
build-pinetime/py/builtinimport.o: In function `mp_builtin___import__':
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/../../py/builtinimport.c:323: undefined reference to `memcpy'
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/../../py/builtinimport.c:326: undefined reference to `memcpy'
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/../../py/builtinimport.c:347: undefined reference to `strchr'
build-pinetime/py/builtinhelp.o: In function `mp_help_add_from_names':
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/../../py/builtinhelp.c:70: undefined reference to `strlen'
build-pinetime/py/modstruct.o: In function `struct_pack_into_internal':
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/../../py/modstruct.c:202: undefined reference to `memcpy'
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/../../py/modstruct.c:203: undefined reference to `memset'
build-pinetime/py/modstruct.o: In function `struct_pack':
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/../../py/modstruct.c:221: undefined reference to `memset'
build-pinetime/py/bc.o: In function `mp_setup_code_state':
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/../../py/bc.c:144: undefined reference to `memset'
build-pinetime/py/repl.o: In function `mp_repl_autocomplete':
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/../../py/repl.c:187: undefined reference to `strncmp'
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/../../py/repl.c:217: undefined reference to `memcmp'
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/../../py/repl.c:241: undefined reference to `strncmp'
build-pinetime/py/frozenmod.o: In function `mp_frozen_stat_helper':
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/../../py/frozenmod.c:102: undefined reference to `strlen'
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/../../py/frozenmod.c:105: undefined reference to `strlen'
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/../../py/frozenmod.c:106: undefined reference to `memcmp'
build-pinetime/py/frozenmod.o: In function `mp_find_frozen_str':
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/../../py/frozenmod.c:52: undefined reference to `strlen'
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/../../py/frozenmod.c:53: undefined reference to `memcmp'
build-pinetime/py/frozenmod.o: In function `mp_find_frozen_mpy':
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/../../py/frozenmod.c:88: undefined reference to `strlen'
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/../../py/frozenmod.c:89: undefined reference to `memcmp'
build-pinetime/extmod/machine_i2c.o: In function `mp_hal_i2c_scl_release':
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/../../extmod/machine_i2c.c:53: undefined reference to `hal_gpio_write'
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/../../extmod/machine_i2c.c:56: undefined reference to `hal_gpio_read'
build-pinetime/extmod/machine_i2c.o: In function `mp_hal_i2c_sda_release':
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/../../extmod/machine_i2c.c:70: undefined reference to `hal_gpio_write'
build-pinetime/extmod/machine_i2c.o: In function `mp_hal_i2c_sda_low':
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/../../extmod/machine_i2c.c:66: undefined reference to `hal_gpio_write'
build-pinetime/extmod/machine_i2c.o: In function `mp_hal_i2c_init':
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/../../extmod/machine_i2c.c:104: undefined reference to `hal_gpio_init_in'
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/../../extmod/machine_i2c.c:105: undefined reference to `hal_gpio_init_in'
build-pinetime/extmod/machine_i2c.o: In function `mp_hal_i2c_sda_read':
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/../../extmod/machine_i2c.c:74: undefined reference to `hal_gpio_read'
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/../../extmod/machine_i2c.c:74: undefined reference to `hal_gpio_read'
build-pinetime/extmod/machine_i2c.o: In function `mp_machine_i2c_transfer_adaptor':
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/../../extmod/machine_i2c.c:278: undefined reference to `memcpy'
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/../../extmod/machine_i2c.c:264: undefined reference to `memcpy'
build-pinetime/extmod/vfs.o: In function `mp_vfs_proxy_call':
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/../../extmod/vfs.c:124: undefined reference to `memcpy'
build-pinetime/extmod/vfs.o: In function `mp_vfs_umount':
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/../../extmod/vfs.c:273: undefined reference to `memcmp'
build-pinetime/extmod/vfs.o: In function `mp_vfs_getcwd':
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/../../extmod/vfs.c:355: undefined reference to `strlen'
build-pinetime/extmod/vfs.o: In function `mp_vfs_lookup_path':
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/../../extmod/vfs.c:75: undefined reference to `strncmp'
build-pinetime/extmod/vfs.o: In function `mp_vfs_autodetect':
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/../../extmod/vfs.c:181: undefined reference to `memcmp'
build-pinetime/extmod/vfs.o: In function `lookup_path':
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/../../extmod/vfs.c:105: undefined reference to `strlen'
build-pinetime/extmod/vfs.o: In function `mp_vfs_mkdir':
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/../../extmod/vfs.c:446: undefined reference to `strcmp'
build-pinetime/extmod/vfs.o: In function `mp_vfs_import_stat':
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/../../extmod/vfs.c:143: undefined reference to `strlen'
build-pinetime/extmod/vfs_reader.o: In function `mp_reader_new_file':
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/../../extmod/vfs_reader.c:74: undefined reference to `strlen'
build-pinetime/extmod/vfs_lfs.o: In function `mp_vfs_lfs2_ilistdir_it_iternext':
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/../../extmod/vfs_lfsx.c:177: undefined reference to `strlen'
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/../../extmod/vfs_lfsx.c:179: undefined reference to `strlen'
build-pinetime/extmod/vfs_lfs.o: In function `mp_vfs_lfs2_init_config':
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/../../extmod/vfs_lfsx.c:67: undefined reference to `memset'
build-pinetime/extmod/vfs_lfs.o: In function `mp_vfs_lfs2_chdir':
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/../../extmod/vfs_lfsx.c:279: undefined reference to `strlen'
build-pinetime/main.o: In function `get_main_task':
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/main.c:88: undefined reference to `os_task_info_get_next'
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/main.c:89: undefined reference to `console_printf'
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/main.c:89: undefined reference to `console_flush'
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/main.c:90: undefined reference to `strcmp'
build-pinetime/main.o: In function `get_micropython_stack_start':
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/main.c:101: undefined reference to `console_printf'
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/main.c:101: undefined reference to `console_flush'
build-pinetime/main.o: In function `get_micropython_stack_end':
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/main.c:111: undefined reference to `console_printf'
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/main.c:111: undefined reference to `console_flush'
build-pinetime/main.o: In function `get_micropython_heap_start':
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/main.c:118: undefined reference to `console_printf'
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/main.c:118: undefined reference to `console_flush'
build-pinetime/main.o: In function `get_micropython_heap_end':
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/main.c:125: undefined reference to `console_printf'
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/main.c:125: undefined reference to `console_flush'
build-pinetime/main.o: In function `do_str':
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/main.c:130: undefined reference to `strlen'
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/main.c:132: undefined reference to `console_printf'
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/main.c:132: undefined reference to `console_flush'
build-pinetime/main.o: In function `start_micropython':
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/main.c:302: undefined reference to `console_printf'
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/main.c:302: undefined reference to `console_flush'
build-pinetime/main.o: In function `nlr_jump_fail':
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/main.c:389: undefined reference to `console_printf'
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/main.c:389: undefined reference to `console_flush'
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/main.c:390: undefined reference to `console_flush'
build-pinetime/mphalport.o: In function `mp_hal_stdout_tx_strn':
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/mphalport.c:85: undefined reference to `console_buffer'
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/mphalport.c:85: undefined reference to `console_flush'
build-pinetime/mphalport.o: In function `mp_hal_stdout_tx_str':
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/mphalport.c:104: undefined reference to `strlen'
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/mphalport.c:104: undefined reference to `console_buffer'
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/mphalport.c:104: undefined reference to `console_flush'
build-pinetime/gccollect.o: In function `gc_collect':
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/gccollect.c:53: undefined reference to `console_printf'
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/gccollect.c:53: undefined reference to `console_flush'
build-pinetime/lib/littlefs/lfs2.o: In function `lfs2_bd_read':
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/../../lib/littlefs/lfs2.c:62: undefined reference to `memcpy'
build-pinetime/lib/littlefs/lfs2.o: In function `lfs2_dir_getslice':
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/../../lib/littlefs/lfs2.c:548: undefined reference to `memset'
build-pinetime/lib/littlefs/lfs2.o: In function `lfs2_dir_find':
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/../../lib/littlefs/lfs2.c:1081: undefined reference to `strspn'
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/../../lib/littlefs/lfs2.c:1082: undefined reference to `strcspn'
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/../../lib/littlefs/lfs2.c:1086: undefined reference to `memcmp'
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/../../lib/littlefs/lfs2.c:1096: undefined reference to `strspn'
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/../../lib/littlefs/lfs2.c:1097: undefined reference to `strcspn'
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/../../lib/littlefs/lfs2.c:1102: undefined reference to `memcmp'
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/../../lib/littlefs/lfs2.c:1144: undefined reference to `strchr'
build-pinetime/lib/littlefs/lfs2.o: In function `lfs2_cache_zero':
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/../../lib/littlefs/lfs2.c:23: undefined reference to `memset'
build-pinetime/lib/littlefs/lfs2.o: In function `lfs2_dir_getread':
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/../../lib/littlefs/lfs2.c:598: undefined reference to `memcpy'
build-pinetime/lib/littlefs/lfs2.o: In function `lfs2_bd_prog':
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/../../lib/littlefs/lfs2.c:186: undefined reference to `memcpy'
build-pinetime/lib/littlefs/lfs2.o: In function `lfs2_dir_read':
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/../../lib/littlefs/lfs2.c:2003: undefined reference to `memset'
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/../../lib/littlefs/lfs2.c:2014: undefined reference to `strcpy'
build-pinetime/lib/littlefs/lfs2.o: In function `lfs2_dir_getinfo':
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/../../lib/littlefs/lfs2.c:1005: undefined reference to `strcpy'
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/../../lib/littlefs/lfs2.c:1005: undefined reference to `strcpy'
build-pinetime/lib/littlefs/lfs2.o: In function `lfs2_mount':
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/../../lib/littlefs/lfs2.c:3597: undefined reference to `memset'
build-pinetime/lib/littlefs/lfs2.o: In function `lfs2_fs_traverse':
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/../../lib/littlefs/lfs2.c:3726: undefined reference to `memset'
build-pinetime/lib/littlefs/lfs2.o: In function `lfs2_alloc':
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/../../lib/littlefs/lfs2.c:482: undefined reference to `memset'
build-pinetime/lib/littlefs/lfs2.o: In function `lfs2_file_relocate':
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/../../lib/littlefs/lfs2.c:2551: undefined reference to `memcpy'
build-pinetime/lib/littlefs/lfs2.o: In function `lfs2_file_flush':
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/../../lib/littlefs/lfs2.c:2596: undefined reference to `memset'
build-pinetime/lib/littlefs/lfs2.o: In function `lfs2_fs_deorphan':
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/../../lib/littlefs/lfs2.c:3983: undefined reference to `memset'
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/../../lib/littlefs/lfs2.c:3984: undefined reference to `memset'
build-pinetime/lib/littlefs/lfs2.o: In function `lfs2_mkdir':
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/../../lib/littlefs/lfs2.c:1866: undefined reference to `strlen'
build-pinetime/lib/littlefs/lfs2.o: In function `lfs2_file_opencfg':
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/../../lib/littlefs/lfs2.c:2354: undefined reference to `strlen'
build-pinetime/lib/littlefs/lfs2.o: In function `lfs2_rename':
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/../../lib/littlefs/lfs2.c:3238: undefined reference to `strlen'
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/../../lib/littlefs/lfs2.c:3190: undefined reference to `strlen'
build-pinetime/lib/littlefs/lfs2.o: In function `lfs2_format':
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/../../lib/littlefs/lfs2.c:3518: undefined reference to `memset'
build-pinetime/modules/machine/modmachine.o: In function `machine_info':
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/modules/machine/modmachine.c:115: undefined reference to `console_printf'
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/modules/machine/modmachine.c:116: undefined reference to `console_printf'
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/modules/machine/modmachine.c:117: undefined reference to `console_printf'
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/modules/machine/modmachine.c:118: undefined reference to `console_printf'
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/modules/machine/modmachine.c:119: undefined reference to `console_printf'
build-pinetime/modules/machine/modmachine.o:/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/modules/machine/modmachine.c:120: more undefined references to `console_printf' follow
build-pinetime/modules/machine/modmachine.o: In function `machine_info':
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/modules/machine/modmachine.c:152: undefined reference to `__text'
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/modules/machine/modmachine.c:152: undefined reference to `__etext'
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/modules/machine/modmachine.c:152: undefined reference to `__exidx_start'
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/modules/machine/modmachine.c:152: undefined reference to `__data_start__'
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/modules/machine/modmachine.c:152: undefined reference to `__data_end__'
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/modules/machine/modmachine.c:152: undefined reference to `__bss_start__'
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/modules/machine/modmachine.c:152: undefined reference to `__bss_end__'
build-pinetime/modules/machine/spi.o: In function `spi_find':
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/modules/machine/spi.c:142: undefined reference to `strcmp'
build-pinetime/modules/machine/spi.o: In function `spi_transfer':
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/modules/machine/spi.c:158: undefined reference to `hal_spi_txrx'
build-pinetime/modules/machine/spi.o: In function `mp_machine_spi_read':
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/modules/machine/spi.c:392: undefined reference to `memset'
build-pinetime/modules/machine/spi.o: In function `mp_machine_spi_readinto':
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/modules/machine/spi.c:401: undefined reference to `memset'
build-pinetime/modules/machine/i2c.o: In function `machine_hard_i2c_make_new':
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/modules/machine/i2c.c:104: undefined reference to `hal_i2c_config'
build-pinetime/modules/machine/i2c.o: In function `machine_hard_i2c_transfer_single':
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/modules/machine/i2c.c:162: undefined reference to `hal_i2c_master_read'
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/modules/machine/i2c.c:166: undefined reference to `hal_i2c_master_write'
build-pinetime/modules/machine/adc.o: In function `machine_adc_value_read':
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/modules/machine/adc.c:185: undefined reference to `console_printf'
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/modules/machine/adc.c:185: undefined reference to `console_flush'
build-pinetime/modules/machine/adc.o: In function `machine_adc_make_new':
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/modules/machine/adc.c:147: undefined reference to `console_printf'
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/modules/machine/adc.c:147: undefined reference to `console_flush'
build-pinetime/modules/machine/adc.o: In function `machine_adc_battery_level':
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/modules/machine/adc.c:276: undefined reference to `console_printf'
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/modules/machine/adc.c:276: undefined reference to `console_flush'
build-pinetime/modules/machine/adc.o: In function `machine_adc_value':
adc.c:(.text.machine_adc_value+0x4): undefined reference to `console_printf'
adc.c:(.text.machine_adc_value+0x8): undefined reference to `console_flush'
build-pinetime/modules/machine/adc.o: In function `adc_init0':
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/modules/machine/adc.c:85: undefined reference to `console_printf'
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/modules/machine/adc.c:85: undefined reference to `console_flush'
build-pinetime/modules/machine/adc.o: In function `machine_adc_value_read':
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/modules/machine/adc.c:185: undefined reference to `console_printf'
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/modules/machine/adc.c:185: undefined reference to `console_flush'
build-pinetime/modules/machine/pin.o: In function `pin_on':
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/modules/machine/pin.c:282: undefined reference to `hal_gpio_write'
build-pinetime/modules/machine/pin.o: In function `pin_off':
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/modules/machine/pin.c:275: undefined reference to `hal_gpio_write'
build-pinetime/modules/machine/pin.o: In function `pin_obj_init_helper':
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/modules/machine/pin.c:361: undefined reference to `hal_gpio_write'
build-pinetime/modules/machine/pin.o: In function `pin_irq':
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/modules/machine/pin.c:513: undefined reference to `console_printf'
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/modules/machine/pin.c:513: undefined reference to `console_flush'
build-pinetime/modules/machine/pin.o: In function `pin_call':
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/modules/machine/pin.c:265: undefined reference to `hal_gpio_read'
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/modules/machine/pin.c:268: undefined reference to `hal_gpio_write'
build-pinetime/modules/machine/timer.o: In function `machine_timer_deinit':
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/modules/machine/timer.c:234: undefined reference to `console_printf'
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/modules/machine/timer.c:234: undefined reference to `console_flush'
build-pinetime/modules/machine/timer.o: In function `machine_timer_stop':
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/modules/machine/timer.c:220: undefined reference to `console_printf'
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/modules/machine/timer.c:220: undefined reference to `console_flush'
build-pinetime/modules/machine/timer.o: In function `machine_timer_start':
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/modules/machine/timer.c:206: undefined reference to `console_printf'
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/modules/machine/timer.c:206: undefined reference to `console_flush'
build-pinetime/modules/machine/timer.o: In function `machine_timer_period':
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/modules/machine/timer.c:192: undefined reference to `console_printf'
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/modules/machine/timer.c:192: undefined reference to `console_flush'
build-pinetime/modules/machine/timer.o: In function `machine_timer_make_new':
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/modules/machine/timer.c:138: undefined reference to `console_printf'
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/modules/machine/timer.c:138: undefined reference to `console_flush'
build-pinetime/modules/machine/timer.o: In function `timer_init0':
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/modules/machine/timer.c:73: undefined reference to `console_printf'
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/modules/machine/timer.c:73: undefined reference to `console_flush'
build-pinetime/modules/machine/rtcounter.o: In function `machine_rtc_deinit':
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/modules/machine/rtcounter.c:269: undefined reference to `console_printf'
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/modules/machine/rtcounter.c:269: undefined reference to `console_flush'
build-pinetime/modules/machine/rtcounter.o: In function `machine_rtc_stop':
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/modules/machine/rtcounter.c:238: undefined reference to `console_printf'
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/modules/machine/rtcounter.c:238: undefined reference to `console_flush'
build-pinetime/modules/machine/rtcounter.o: In function `machine_rtc_start':
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/modules/machine/rtcounter.c:224: undefined reference to `console_printf'
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/modules/machine/rtcounter.c:224: undefined reference to `console_flush'
build-pinetime/modules/machine/rtcounter.o: In function `machine_rtc_counter':
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/modules/machine/rtcounter.c:253: undefined reference to `console_printf'
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/modules/machine/rtcounter.c:253: undefined reference to `console_flush'
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/modules/machine/rtcounter.c:254: undefined reference to `os_time_get'
build-pinetime/modules/machine/rtcounter.o: In function `machine_rtc_make_new':
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/modules/machine/rtcounter.c:182: undefined reference to `console_printf'
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/modules/machine/rtcounter.c:182: undefined reference to `console_flush'
build-pinetime/modules/machine/pwm.o: In function `machine_hard_pwm_deinit':
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/modules/machine/pwm.c:334: undefined reference to `console_printf'
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/modules/machine/pwm.c:334: undefined reference to `console_flush'
build-pinetime/modules/machine/pwm.o: In function `machine_hard_pwm_init':
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/modules/machine/pwm.c:278: undefined reference to `console_printf'
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/modules/machine/pwm.c:278: undefined reference to `console_flush'
build-pinetime/modules/uos/microbitfs.o: In function `microbit_file_close':
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/modules/uos/microbitfs.c:505: undefined reference to `console_printf'
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/modules/uos/microbitfs.c:505: undefined reference to `console_flush'
build-pinetime/modules/uos/microbitfs.o: In function `microbit_file_write':
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/modules/uos/microbitfs.c:479: undefined reference to `console_printf'
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/modules/uos/microbitfs.c:479: undefined reference to `console_flush'
build-pinetime/modules/uos/microbitfs.o: In function `advance':
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/modules/uos/microbitfs.c:422: undefined reference to `console_printf'
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/modules/uos/microbitfs.c:422: undefined reference to `console_flush'
build-pinetime/modules/uos/microbitfs.o: In function `clear_file':
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/modules/uos/microbitfs.c:346: undefined reference to `console_printf'
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/modules/uos/microbitfs.c:346: undefined reference to `console_flush'
build-pinetime/modules/uos/microbitfs.o: In function `microbit_file_read':
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/modules/uos/microbitfs.c:453: undefined reference to `console_printf'
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/modules/uos/microbitfs.c:453: undefined reference to `console_flush'
build-pinetime/modules/uos/microbitfs.o: In function `microbit_filesystem_init':
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/modules/uos/microbitfs.c:187: undefined reference to `console_printf'
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/modules/uos/microbitfs.c:187: undefined reference to `console_flush'
build-pinetime/modules/uos/microbitfs.o: In function `microbit_file_open':
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/modules/uos/microbitfs.c:357: undefined reference to `console_printf'
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/modules/uos/microbitfs.c:357: undefined reference to `console_flush'
build-pinetime/modules/uos/microbitfs.o: In function `uos_mbfs_import_stat':
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/modules/uos/microbitfs.c:571: undefined reference to `strlen'
build-pinetime/modules/uos/microbitfs.o: In function `microbit_file_open':
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/modules/uos/microbitfs.c:357: undefined reference to `console_printf'
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/modules/uos/microbitfs.c:357: undefined reference to `console_flush'
build-pinetime/lib/mp-readline/readline.o: In function `mp_hal_move_cursor_back':
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/../../lib/mp-readline/readline.c:75: undefined reference to `snprintf'
build-pinetime/lib/mp-readline/readline.o: In function `readline_init0':
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/../../lib/mp-readline/readline.c:48: undefined reference to `memset'
build-pinetime/lib/mp-readline/readline.o: In function `readline_push_history':
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/../../lib/mp-readline/readline.c:436: undefined reference to `strcmp'
build-pinetime/lib/mp-readline/readline.o: In function `str_dup_maybe':
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/../../lib/mp-readline/readline.c:52: undefined reference to `strlen'
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/../../lib/mp-readline/readline.c:57: undefined reference to `memcpy'
build-pinetime/lib/utils/pyexec.o: In function `parse_compile_execute':
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/../../lib/utils/pyexec.c:129: undefined reference to `printf'
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/../../lib/utils/pyexec.c:134: undefined reference to `printf'
build-pinetime/lib/utils/pyexec.o: In function `pyexec_frozen_module':
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/../../lib/utils/pyexec.c:559: undefined reference to `strlen'
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/../../lib/utils/pyexec.c:573: undefined reference to `printf'
collect2: error: ld returned 1 exit status
make[1]: *** [Makefile:367: build-pinetime/micropython.elf] Error 1
make[1]: Leaving directory '/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt'
make: *** [Makefile:37: micropython] Error 2
The terminal process terminated with exit code: 2

Terminal will be reused by tasks, press any key to close it.
```