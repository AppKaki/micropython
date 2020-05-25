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
GEN build-pinetime/genhdr/qstrdefs.collected.h
python3 ../../py/makeqstrdefs.py cat build-pinetime/genhdr/qstr.i.last build-pinetime/genhdr/qstr build-pinetime/genhdr/qstrdefs.collected.h
QSTR not updated
python3 ../../tools/makemanifest.py -o build-pinetime/frozen_content.c -v "MPY_DIR=../.." -v "MPY_LIB_DIR=../../../micropython-lib" -v "PORT_DIR=/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt" -v "BOARD_DIR=" -b "build-pinetime" -f"-march=armv7m" /Users/Luppy/PineTime/wasp-os/wasp/boards/pinetime/manifest.py
GEN build-pinetime/frozen_content.c
CC build-pinetime/frozen_content.c
arm-none-eabi-gcc -flto -mthumb -mabi=aapcs -fsingle-precision-constant -Wdouble-promotion -mtune=cortex-m4 -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -I. -I../.. -Ibuild-pinetime -I./../../lib/cmsis/inc -I./modules/machine -I./modules/ubluepy -I./modules/music -I./modules/random -I./modules/ble -I./modules/board -I../../lib/mp-readline -I./drivers/bluetooth -I./drivers -I../../lib/nrfx/ -I../../lib/nrfx/drivers -I../../lib/nrfx/drivers/include -I../../lib/nrfx/mdk -I../../lib/nrfx/hal -I../../lib/nrfx/drivers/src/ -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/boot/split/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/encoding/json/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/encoding/tinycbor/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/hw/drivers/flash/spiflash/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/hw/hal/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/hw/mcu/nordic/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/hw/mcu/nordic/nrf52xxx/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/hw/mcu/nordic/src/ext/nrfx/ -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/hw/mcu/nordic/src/ext/nrfx/mdk -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/hw/sensor/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/kernel/os/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/kernel/os/include/os -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/kernel/os/include/os/arch/cortex_m4 -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/mgmt/imgmgr/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/mgmt/newtmgr/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/mgmt/newtmgr/transport/ble/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/net/oic/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/sys/config/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/sys/defs/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/sys/flash_map/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/sys/log/common/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/sys/log/modlog/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/sys/log/stub/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/sys/sys/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/sys/sysdown/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/sys/sysinit/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-nimble/nimble/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-nimble/nimble/host/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-nimble/nimble/host/services/ans/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-nimble/nimble/host/services/dis/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-nimble/nimble/host/services/gap/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-nimble/nimble/host/services/gatt/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-nimble/nimble/host/store/config/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-nimble/nimble/host/util/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-nimble/nimble/transport -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-nimble/porting/npl/mynewt/include -I../../../../pinetime-rust-mynewt/repos/mcuboot/boot/bootutil/include -I../../../../pinetime-rust-mynewt/bin/targets/nrf52_my_sensor/generated/include -I../../../../pinetime-rust-mynewt/libs/semihosting_console/include -Wall -Werror -g -ansi -std=c11 -nostdlib  -DNRF52832_XXAA -DNRF52 -DNRF52832 -DCONFIG_GPIO_AS_PINRESET -DFFCONF_H=\"lib/oofatfs/ffconf.h\" -DMICROPY_VFS_LFS2=1 -DLFS2_NO_MALLOC -DLFS2_NO_DEBUG -DLFS2_NO_WARN -DLFS2_NO_ERROR -DLFS2_NO_ASSERT -fno-strict-aliasing -Iboards/pinetime -DNRF5_HAL_H='<nrf52_hal.h>' -Os -DNDEBUG -DMICROPY_MODULE_FROZEN_STR -DMICROPY_QSTR_EXTRA_POOL=mp_qstr_frozen_const_pool -DMICROPY_MODULE_FROZEN_MPY -c -MD -o build-pinetime/build-pinetime/frozen_content.o build-pinetime/frozen_content.c
CC modules/uos/moduos.c
arm-none-eabi-gcc -flto -mthumb -mabi=aapcs -fsingle-precision-constant -Wdouble-promotion -mtune=cortex-m4 -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -I. -I../.. -Ibuild-pinetime -I./../../lib/cmsis/inc -I./modules/machine -I./modules/ubluepy -I./modules/music -I./modules/random -I./modules/ble -I./modules/board -I../../lib/mp-readline -I./drivers/bluetooth -I./drivers -I../../lib/nrfx/ -I../../lib/nrfx/drivers -I../../lib/nrfx/drivers/include -I../../lib/nrfx/mdk -I../../lib/nrfx/hal -I../../lib/nrfx/drivers/src/ -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/boot/split/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/encoding/json/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/encoding/tinycbor/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/hw/drivers/flash/spiflash/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/hw/hal/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/hw/mcu/nordic/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/hw/mcu/nordic/nrf52xxx/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/hw/mcu/nordic/src/ext/nrfx/ -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/hw/mcu/nordic/src/ext/nrfx/mdk -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/hw/sensor/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/kernel/os/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/kernel/os/include/os -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/kernel/os/include/os/arch/cortex_m4 -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/mgmt/imgmgr/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/mgmt/newtmgr/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/mgmt/newtmgr/transport/ble/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/net/oic/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/sys/config/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/sys/defs/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/sys/flash_map/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/sys/log/common/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/sys/log/modlog/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/sys/log/stub/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/sys/sys/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/sys/sysdown/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/sys/sysinit/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-nimble/nimble/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-nimble/nimble/host/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-nimble/nimble/host/services/ans/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-nimble/nimble/host/services/dis/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-nimble/nimble/host/services/gap/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-nimble/nimble/host/services/gatt/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-nimble/nimble/host/store/config/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-nimble/nimble/host/util/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-nimble/nimble/transport -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-nimble/porting/npl/mynewt/include -I../../../../pinetime-rust-mynewt/repos/mcuboot/boot/bootutil/include -I../../../../pinetime-rust-mynewt/bin/targets/nrf52_my_sensor/generated/include -I../../../../pinetime-rust-mynewt/libs/semihosting_console/include -Wall -Werror -g -ansi -std=c11 -nostdlib  -DNRF52832_XXAA -DNRF52 -DNRF52832 -DCONFIG_GPIO_AS_PINRESET -DFFCONF_H=\"lib/oofatfs/ffconf.h\" -DMICROPY_VFS_LFS2=1 -DLFS2_NO_MALLOC -DLFS2_NO_DEBUG -DLFS2_NO_WARN -DLFS2_NO_ERROR -DLFS2_NO_ASSERT -fno-strict-aliasing -Iboards/pinetime -DNRF5_HAL_H='<nrf52_hal.h>' -Os -DNDEBUG -DMICROPY_MODULE_FROZEN_STR -DMICROPY_QSTR_EXTRA_POOL=mp_qstr_frozen_const_pool -DMICROPY_MODULE_FROZEN_MPY -c -MD -o build-pinetime/modules/uos/moduos.o modules/uos/moduos.c
CC ../../lib/utils/pyexec.c
arm-none-eabi-gcc -flto -mthumb -mabi=aapcs -fsingle-precision-constant -Wdouble-promotion -mtune=cortex-m4 -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -I. -I../.. -Ibuild-pinetime -I./../../lib/cmsis/inc -I./modules/machine -I./modules/ubluepy -I./modules/music -I./modules/random -I./modules/ble -I./modules/board -I../../lib/mp-readline -I./drivers/bluetooth -I./drivers -I../../lib/nrfx/ -I../../lib/nrfx/drivers -I../../lib/nrfx/drivers/include -I../../lib/nrfx/mdk -I../../lib/nrfx/hal -I../../lib/nrfx/drivers/src/ -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/boot/split/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/encoding/json/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/encoding/tinycbor/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/hw/drivers/flash/spiflash/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/hw/hal/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/hw/mcu/nordic/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/hw/mcu/nordic/nrf52xxx/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/hw/mcu/nordic/src/ext/nrfx/ -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/hw/mcu/nordic/src/ext/nrfx/mdk -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/hw/sensor/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/kernel/os/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/kernel/os/include/os -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/kernel/os/include/os/arch/cortex_m4 -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/mgmt/imgmgr/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/mgmt/newtmgr/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/mgmt/newtmgr/transport/ble/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/net/oic/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/sys/config/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/sys/defs/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/sys/flash_map/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/sys/log/common/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/sys/log/modlog/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/sys/log/stub/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/sys/sys/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/sys/sysdown/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/sys/sysinit/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-nimble/nimble/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-nimble/nimble/host/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-nimble/nimble/host/services/ans/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-nimble/nimble/host/services/dis/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-nimble/nimble/host/services/gap/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-nimble/nimble/host/services/gatt/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-nimble/nimble/host/store/config/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-nimble/nimble/host/util/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-nimble/nimble/transport -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-nimble/porting/npl/mynewt/include -I../../../../pinetime-rust-mynewt/repos/mcuboot/boot/bootutil/include -I../../../../pinetime-rust-mynewt/bin/targets/nrf52_my_sensor/generated/include -I../../../../pinetime-rust-mynewt/libs/semihosting_console/include -Wall -Werror -g -ansi -std=c11 -nostdlib  -DNRF52832_XXAA -DNRF52 -DNRF52832 -DCONFIG_GPIO_AS_PINRESET -DFFCONF_H=\"lib/oofatfs/ffconf.h\" -DMICROPY_VFS_LFS2=1 -DLFS2_NO_MALLOC -DLFS2_NO_DEBUG -DLFS2_NO_WARN -DLFS2_NO_ERROR -DLFS2_NO_ASSERT -fno-strict-aliasing -Iboards/pinetime -DNRF5_HAL_H='<nrf52_hal.h>' -Os -DNDEBUG -DMICROPY_MODULE_FROZEN_STR -DMICROPY_QSTR_EXTRA_POOL=mp_qstr_frozen_const_pool -DMICROPY_MODULE_FROZEN_MPY -c -MD -o build-pinetime/lib/utils/pyexec.o ../../lib/utils/pyexec.c
LINK build-pinetime/firmware.elf
arm-none-eabi-gcc -flto -mthumb -mabi=aapcs -fsingle-precision-constant -Wdouble-promotion -mtune=cortex-m4 -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -I. -I../.. -Ibuild-pinetime -I./../../lib/cmsis/inc -I./modules/machine -I./modules/ubluepy -I./modules/music -I./modules/random -I./modules/ble -I./modules/board -I../../lib/mp-readline -I./drivers/bluetooth -I./drivers -I../../lib/nrfx/ -I../../lib/nrfx/drivers -I../../lib/nrfx/drivers/include -I../../lib/nrfx/mdk -I../../lib/nrfx/hal -I../../lib/nrfx/drivers/src/ -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/boot/split/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/encoding/json/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/encoding/tinycbor/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/hw/drivers/flash/spiflash/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/hw/hal/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/hw/mcu/nordic/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/hw/mcu/nordic/nrf52xxx/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/hw/mcu/nordic/src/ext/nrfx/ -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/hw/mcu/nordic/src/ext/nrfx/mdk -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/hw/sensor/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/kernel/os/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/kernel/os/include/os -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/kernel/os/include/os/arch/cortex_m4 -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/mgmt/imgmgr/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/mgmt/newtmgr/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/mgmt/newtmgr/transport/ble/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/net/oic/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/sys/config/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/sys/defs/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/sys/flash_map/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/sys/log/common/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/sys/log/modlog/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/sys/log/stub/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/sys/sys/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/sys/sysdown/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-core/sys/sysinit/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-nimble/nimble/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-nimble/nimble/host/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-nimble/nimble/host/services/ans/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-nimble/nimble/host/services/dis/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-nimble/nimble/host/services/gap/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-nimble/nimble/host/services/gatt/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-nimble/nimble/host/store/config/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-nimble/nimble/host/util/include -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-nimble/nimble/transport -I../../../../pinetime-rust-mynewt/repos/apache-mynewt-nimble/porting/npl/mynewt/include -I../../../../pinetime-rust-mynewt/repos/mcuboot/boot/bootutil/include -I../../../../pinetime-rust-mynewt/bin/targets/nrf52_my_sensor/generated/include -I../../../../pinetime-rust-mynewt/libs/semihosting_console/include -Wall -Werror -g -ansi -std=c11 -nostdlib  -DNRF52832_XXAA -DNRF52 -DNRF52832 -DCONFIG_GPIO_AS_PINRESET -DFFCONF_H=\"lib/oofatfs/ffconf.h\" -DMICROPY_VFS_LFS2=1 -DLFS2_NO_MALLOC -DLFS2_NO_DEBUG -DLFS2_NO_WARN -DLFS2_NO_ERROR -DLFS2_NO_ASSERT -fno-strict-aliasing -Iboards/pinetime -DNRF5_HAL_H='<nrf52_hal.h>' -Os -DNDEBUG -DMICROPY_MODULE_FROZEN_STR -DMICROPY_QSTR_EXTRA_POOL=mp_qstr_frozen_const_pool -DMICROPY_MODULE_FROZEN_MPY -Xlinker -Map=build-pinetime/firmware.map -mthumb -mabi=aapcs -Tboards/nrf52832_512k_64k_bldr78.ld -Tboards/memory.ld -Tboards/common.ld -L boards/ -Os -o build-pinetime/firmware.elf build-pinetime/py/mpstate.o build-pinetime/py/nlr.o build-pinetime/py/nlrx86.o build-pinetime/py/nlrx64.o build-pinetime/py/nlrthumb.o build-pinetime/py/nlrpowerpc.o build-pinetime/py/nlrxtensa.o build-pinetime/py/nlrsetjmp.o build-pinetime/py/malloc.o build-pinetime/py/gc.o build-pinetime/py/pystack.o build-pinetime/py/qstr.o build-pinetime/py/vstr.o build-pinetime/py/mpprint.o build-pinetime/py/unicode.o build-pinetime/py/mpz.o build-pinetime/py/reader.o build-pinetime/py/lexer.o build-pinetime/py/parse.o build-pinetime/py/scope.o build-pinetime/py/compile.o build-pinetime/py/emitcommon.o build-pinetime/py/emitbc.o build-pinetime/py/asmbase.o build-pinetime/py/asmx64.o build-pinetime/py/emitnx64.o build-pinetime/py/asmx86.o build-pinetime/py/emitnx86.o build-pinetime/py/asmthumb.o build-pinetime/py/emitnthumb.o build-pinetime/py/emitinlinethumb.o build-pinetime/py/asmarm.o build-pinetime/py/emitnarm.o build-pinetime/py/asmxtensa.o build-pinetime/py/emitnxtensa.o build-pinetime/py/emitinlinextensa.o build-pinetime/py/emitnxtensawin.o build-pinetime/py/formatfloat.o build-pinetime/py/parsenumbase.o build-pinetime/py/parsenum.o build-pinetime/py/emitglue.o build-pinetime/py/persistentcode.o build-pinetime/py/runtime.o build-pinetime/py/runtime_utils.o build-pinetime/py/scheduler.o build-pinetime/py/nativeglue.o build-pinetime/py/ringbuf.o build-pinetime/py/stackctrl.o build-pinetime/py/argcheck.o build-pinetime/py/warning.o build-pinetime/py/profile.o build-pinetime/py/map.o build-pinetime/py/obj.o build-pinetime/py/objarray.o build-pinetime/py/objattrtuple.o build-pinetime/py/objbool.o build-pinetime/py/objboundmeth.o build-pinetime/py/objcell.o build-pinetime/py/objclosure.o build-pinetime/py/objcomplex.o build-pinetime/py/objdeque.o build-pinetime/py/objdict.o build-pinetime/py/objenumerate.o build-pinetime/py/objexcept.o build-pinetime/py/objfilter.o build-pinetime/py/objfloat.o build-pinetime/py/objfun.o build-pinetime/py/objgenerator.o build-pinetime/py/objgetitemiter.o build-pinetime/py/objint.o build-pinetime/py/objint_longlong.o build-pinetime/py/objint_mpz.o build-pinetime/py/objlist.o build-pinetime/py/objmap.o build-pinetime/py/objmodule.o build-pinetime/py/objobject.o build-pinetime/py/objpolyiter.o build-pinetime/py/objproperty.o build-pinetime/py/objnone.o build-pinetime/py/objnamedtuple.o build-pinetime/py/objrange.o build-pinetime/py/objreversed.o build-pinetime/py/objset.o build-pinetime/py/objsingleton.o build-pinetime/py/objslice.o build-pinetime/py/objstr.o build-pinetime/py/objstrunicode.o build-pinetime/py/objstringio.o build-pinetime/py/objtuple.o build-pinetime/py/objtype.o build-pinetime/py/objzip.o build-pinetime/py/opmethods.o build-pinetime/py/sequence.o build-pinetime/py/stream.o build-pinetime/py/binary.o build-pinetime/py/builtinimport.o build-pinetime/py/builtinevex.o build-pinetime/py/builtinhelp.o build-pinetime/py/modarray.o build-pinetime/py/modbuiltins.o build-pinetime/py/modcollections.o build-pinetime/py/modgc.o build-pinetime/py/modio.o build-pinetime/py/modmath.o build-pinetime/py/modcmath.o build-pinetime/py/modmicropython.o build-pinetime/py/modstruct.o build-pinetime/py/modsys.o build-pinetime/py/moduerrno.o build-pinetime/py/modthread.o build-pinetime/py/vm.o build-pinetime/py/bc.o build-pinetime/py/showbc.o build-pinetime/py/repl.o build-pinetime/py/smallint.o build-pinetime/py/frozenmod.o build-pinetime/extmod/moductypes.o build-pinetime/extmod/modujson.o build-pinetime/extmod/modure.o build-pinetime/extmod/moduzlib.o build-pinetime/extmod/moduheapq.o build-pinetime/extmod/modutimeq.o build-pinetime/extmod/moduhashlib.o build-pinetime/extmod/moducryptolib.o build-pinetime/extmod/modubinascii.o build-pinetime/extmod/virtpin.o build-pinetime/extmod/machine_mem.o build-pinetime/extmod/machine_pinbase.o build-pinetime/extmod/machine_signal.o build-pinetime/extmod/machine_pulse.o build-pinetime/extmod/machine_i2c.o build-pinetime/extmod/machine_spi.o build-pinetime/extmod/modbluetooth.o build-pinetime/extmod/modussl_axtls.o build-pinetime/extmod/modussl_mbedtls.o build-pinetime/extmod/modurandom.o build-pinetime/extmod/moduselect.o build-pinetime/extmod/moduwebsocket.o build-pinetime/extmod/modwebrepl.o build-pinetime/extmod/modframebuf.o build-pinetime/extmod/vfs.o build-pinetime/extmod/vfs_blockdev.o build-pinetime/extmod/vfs_reader.o build-pinetime/extmod/vfs_posix.o build-pinetime/extmod/vfs_posix_file.o build-pinetime/extmod/vfs_fat.o build-pinetime/extmod/vfs_fat_diskio.o build-pinetime/extmod/vfs_fat_file.o build-pinetime/extmod/vfs_lfs.o build-pinetime/extmod/utime_mphal.o build-pinetime/extmod/uos_dupterm.o build-pinetime/lib/embed/abort_.o build-pinetime/lib/utils/printf.o build-pinetime/build-pinetime/frozen_content.o build-pinetime/main.o build-pinetime/mphalport.o build-pinetime/help.o build-pinetime/gccollect.o build-pinetime/pin_named_pins.o build-pinetime/fatfs_port.o build-pinetime/drivers/flash.o build-pinetime/drivers/softpwm.o build-pinetime/drivers/ticker.o build-pinetime/drivers/wdt.o build-pinetime/drivers/bluetooth/ble_drv.o build-pinetime/drivers/bluetooth/ble_uart.o build-pinetime/device/startup_nrf52832.o build-pinetime/lib/littlefs/lfs2.o build-pinetime/lib/littlefs/lfs2_util.o   build-pinetime/modules/machine/modmachine.o build-pinetime/modules/machine/uart.o build-pinetime/modules/machine/spi.o build-pinetime/modules/machine/i2c.o build-pinetime/modules/machine/adc.o build-pinetime/modules/machine/pin.o build-pinetime/modules/machine/timer.o build-pinetime/modules/machine/rtcounter.o build-pinetime/modules/machine/pwm.o build-pinetime/modules/machine/temp.o build-pinetime/modules/uos/moduos.o build-pinetime/modules/uos/microbitfs.o build-pinetime/modules/utime/modutime.o build-pinetime/modules/board/modboard.o build-pinetime/modules/board/led.o build-pinetime/modules/ubluepy/modubluepy.o build-pinetime/modules/ubluepy/ubluepy_peripheral.o build-pinetime/modules/ubluepy/ubluepy_service.o build-pinetime/modules/ubluepy/ubluepy_characteristic.o build-pinetime/modules/ubluepy/ubluepy_uuid.o build-pinetime/modules/ubluepy/ubluepy_delegate.o build-pinetime/modules/ubluepy/ubluepy_constants.o build-pinetime/modules/ubluepy/ubluepy_descriptor.o build-pinetime/modules/ubluepy/ubluepy_scanner.o build-pinetime/modules/ubluepy/ubluepy_scan_entry.o build-pinetime/modules/music/modmusic.o build-pinetime/modules/music/musictunes.o build-pinetime/modules/ble/modble.o build-pinetime/modules/random/modrandom.o build-pinetime/lib/nrfx/mdk/system_nrf52.o build-pinetime/lib/libm/math.o build-pinetime/lib/libm/fmodf.o build-pinetime/lib/libm/nearbyintf.o build-pinetime/lib/libm/ef_sqrt.o build-pinetime/lib/libm/kf_rem_pio2.o build-pinetime/lib/libm/kf_sin.o build-pinetime/lib/libm/kf_cos.o build-pinetime/lib/libm/kf_tan.o build-pinetime/lib/libm/ef_rem_pio2.o build-pinetime/lib/libm/sf_sin.o build-pinetime/lib/libm/sf_cos.o build-pinetime/lib/libm/sf_tan.o build-pinetime/lib/libm/sf_frexp.o build-pinetime/lib/libm/sf_modf.o build-pinetime/lib/libm/sf_ldexp.o build-pinetime/lib/libm/asinfacosf.o build-pinetime/lib/libm/atanf.o build-pinetime/lib/libm/atan2f.o build-pinetime/lib/libc/string0.o build-pinetime/lib/mp-readline/readline.o build-pinetime/lib/utils/pyexec.o build-pinetime/lib/utils/sys_stdio_mphal.o build-pinetime/lib/utils/interrupt_char.o build-pinetime/lib/timeutils/timeutils.o build-pinetime/pins_gen.o -L /usr/local/Cellar/arm-none-eabi-gcc/7-2018-q2-update/gcc/bin/../lib/gcc/arm-none-eabi/7.3.1/thumb/v7e-m/fpv4-sp/hard/ -lgcc
/var/folders/gp/jb0b68fn3b187mgyyrjml3km0000gn/T//ccGhMnle.ltrans2.ltrans.o: In function `mp_hal_i2c_scl_release':
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/../../extmod/machine_i2c.c:53: undefined reference to `hal_gpio_write'
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/../../extmod/machine_i2c.c:56: undefined reference to `hal_gpio_read'
/var/folders/gp/jb0b68fn3b187mgyyrjml3km0000gn/T//ccGhMnle.ltrans2.ltrans.o: In function `mp_hal_i2c_sda_read.isra.6':
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/../../extmod/machine_i2c.c:74: undefined reference to `hal_gpio_read'
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/../../extmod/machine_i2c.c:74: undefined reference to `hal_gpio_read'
/var/folders/gp/jb0b68fn3b187mgyyrjml3km0000gn/T//ccGhMnle.ltrans2.ltrans.o: In function `mp_hal_i2c_init':
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/../../extmod/machine_i2c.c:104: undefined reference to `hal_gpio_init_in'
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/../../extmod/machine_i2c.c:105: undefined reference to `hal_gpio_init_in'
/var/folders/gp/jb0b68fn3b187mgyyrjml3km0000gn/T//ccGhMnle.ltrans2.ltrans.o: In function `mp_hal_stdout_tx_strn':
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/mphalport.c:85: undefined reference to `console_buffer'
/var/folders/gp/jb0b68fn3b187mgyyrjml3km0000gn/T//ccGhMnle.ltrans2.ltrans.o: In function `mp_hal_stdout_tx_str':
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/mphalport.c:104: undefined reference to `console_buffer'
/var/folders/gp/jb0b68fn3b187mgyyrjml3km0000gn/T//ccGhMnle.ltrans2.ltrans.o: In function `adc_init0':
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/modules/machine/adc.c:85: undefined reference to `console_printf'
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/modules/machine/adc.c:85: undefined reference to `console_flush'
/var/folders/gp/jb0b68fn3b187mgyyrjml3km0000gn/T//ccGhMnle.ltrans2.ltrans.o: In function `timer_init0':
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/modules/machine/timer.c:73: undefined reference to `console_printf'
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/modules/machine/timer.c:73: undefined reference to `console_flush'
/var/folders/gp/jb0b68fn3b187mgyyrjml3km0000gn/T//ccGhMnle.ltrans2.ltrans.o: In function `microbit_filesystem_init':
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/modules/uos/microbitfs.c:185: undefined reference to `console_printf'
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/modules/uos/microbitfs.c:185: undefined reference to `console_flush'
/var/folders/gp/jb0b68fn3b187mgyyrjml3km0000gn/T//ccGhMnle.ltrans2.ltrans.o: In function `pyexec_friendly_repl':
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/../../lib/utils/pyexec.c:507: undefined reference to `machine_hard_uart_type'
/var/folders/gp/jb0b68fn3b187mgyyrjml3km0000gn/T//ccGhMnle.ltrans2.ltrans.o: In function `mp_hal_i2c_sda_low.isra.4':
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/../../extmod/machine_i2c.c:66: undefined reference to `hal_gpio_write'
/var/folders/gp/jb0b68fn3b187mgyyrjml3km0000gn/T//ccGhMnle.ltrans2.ltrans.o: In function `mp_hal_i2c_sda_release.isra.3':
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/../../extmod/machine_i2c.c:70: undefined reference to `hal_gpio_write'
/var/folders/gp/jb0b68fn3b187mgyyrjml3km0000gn/T//ccGhMnle.ltrans2.ltrans.o: In function `mp_hal_stdout_tx_strn':
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/mphalport.c:85: undefined reference to `console_flush'
/var/folders/gp/jb0b68fn3b187mgyyrjml3km0000gn/T//ccGhMnle.ltrans2.ltrans.o: In function `mp_hal_stdout_tx_str':
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/mphalport.c:104: undefined reference to `console_flush'
/var/folders/gp/jb0b68fn3b187mgyyrjml3km0000gn/T//ccGhMnle.ltrans4.ltrans.o: In function `spi_transfer':
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/modules/machine/spi.c:158: undefined reference to `hal_spi_txrx'
/var/folders/gp/jb0b68fn3b187mgyyrjml3km0000gn/T//ccGhMnle.ltrans4.ltrans.o: In function `machine_hard_pwm_deinit.isra.1':
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/modules/machine/pwm.c:334: undefined reference to `console_printf'
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/modules/machine/pwm.c:334: undefined reference to `console_flush'
/var/folders/gp/jb0b68fn3b187mgyyrjml3km0000gn/T//ccGhMnle.ltrans4.ltrans.o: In function `machine_hard_pwm_init.isra.2':
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/modules/machine/pwm.c:278: undefined reference to `console_printf'
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/modules/machine/pwm.c:278: undefined reference to `console_flush'
/var/folders/gp/jb0b68fn3b187mgyyrjml3km0000gn/T//ccGhMnle.ltrans4.ltrans.o: In function `machine_rtc_deinit.lto_priv.455':
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/modules/machine/rtcounter.c:269: undefined reference to `console_printf'
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/modules/machine/rtcounter.c:269: undefined reference to `console_flush'
/var/folders/gp/jb0b68fn3b187mgyyrjml3km0000gn/T//ccGhMnle.ltrans4.ltrans.o: In function `machine_rtc_stop.lto_priv.453':
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/modules/machine/rtcounter.c:238: undefined reference to `console_printf'
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/modules/machine/rtcounter.c:238: undefined reference to `console_flush'
/var/folders/gp/jb0b68fn3b187mgyyrjml3km0000gn/T//ccGhMnle.ltrans4.ltrans.o: In function `machine_rtc_start.lto_priv.452':
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/modules/machine/rtcounter.c:224: undefined reference to `console_printf'
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/modules/machine/rtcounter.c:224: undefined reference to `console_flush'
/var/folders/gp/jb0b68fn3b187mgyyrjml3km0000gn/T//ccGhMnle.ltrans4.ltrans.o: In function `machine_rtc_make_new.lto_priv.350':
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/modules/machine/rtcounter.c:182: undefined reference to `console_printf'
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/modules/machine/rtcounter.c:182: undefined reference to `console_flush'
/var/folders/gp/jb0b68fn3b187mgyyrjml3km0000gn/T//ccGhMnle.ltrans4.ltrans.o: In function `machine_timer_deinit.lto_priv.459':
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/modules/machine/timer.c:234: undefined reference to `console_printf'
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/modules/machine/timer.c:234: undefined reference to `console_flush'
/var/folders/gp/jb0b68fn3b187mgyyrjml3km0000gn/T//ccGhMnle.ltrans4.ltrans.o: In function `machine_timer_stop.lto_priv.458':
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/modules/machine/timer.c:220: undefined reference to `console_printf'
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/modules/machine/timer.c:220: undefined reference to `console_flush'
/var/folders/gp/jb0b68fn3b187mgyyrjml3km0000gn/T//ccGhMnle.ltrans4.ltrans.o: In function `machine_timer_start.lto_priv.457':
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/modules/machine/timer.c:206: undefined reference to `console_printf'
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/modules/machine/timer.c:206: undefined reference to `console_flush'
/var/folders/gp/jb0b68fn3b187mgyyrjml3km0000gn/T//ccGhMnle.ltrans4.ltrans.o: In function `machine_timer_period.lto_priv.456':
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/modules/machine/timer.c:192: undefined reference to `console_printf'
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/modules/machine/timer.c:192: undefined reference to `console_flush'
/var/folders/gp/jb0b68fn3b187mgyyrjml3km0000gn/T//ccGhMnle.ltrans4.ltrans.o: In function `machine_timer_make_new.lto_priv.353':
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/modules/machine/timer.c:138: undefined reference to `console_printf'
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/modules/machine/timer.c:138: undefined reference to `console_flush'
/var/folders/gp/jb0b68fn3b187mgyyrjml3km0000gn/T//ccGhMnle.ltrans4.ltrans.o: In function `pin_irq.lto_priv.442':
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/modules/machine/pin.c:513: undefined reference to `console_printf'
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/modules/machine/pin.c:513: undefined reference to `console_flush'
/var/folders/gp/jb0b68fn3b187mgyyrjml3km0000gn/T//ccGhMnle.ltrans4.ltrans.o: In function `machine_adc_battery_level':
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/modules/machine/adc.c:276: undefined reference to `console_printf'
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/modules/machine/adc.c:276: undefined reference to `console_flush'
/var/folders/gp/jb0b68fn3b187mgyyrjml3km0000gn/T//ccGhMnle.ltrans4.ltrans.o: In function `machine_adc_value_read':
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/modules/machine/adc.c:185: undefined reference to `console_printf'
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/modules/machine/adc.c:185: undefined reference to `console_flush'
/var/folders/gp/jb0b68fn3b187mgyyrjml3km0000gn/T//ccGhMnle.ltrans4.ltrans.o: In function `machine_adc_read_u16.lto_priv.451':
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/modules/machine/adc.c:216: undefined reference to `console_printf'
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/modules/machine/adc.c:216: undefined reference to `console_flush'
/var/folders/gp/jb0b68fn3b187mgyyrjml3km0000gn/T//ccGhMnle.ltrans4.ltrans.o: In function `machine_rtc_counter.lto_priv.454':
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/modules/machine/rtcounter.c:253: undefined reference to `console_printf'
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/modules/machine/rtcounter.c:253: undefined reference to `console_flush'
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/modules/machine/rtcounter.c:254: undefined reference to `os_time_get'
/var/folders/gp/jb0b68fn3b187mgyyrjml3km0000gn/T//ccGhMnle.ltrans4.ltrans.o: In function `pin_high.lto_priv.433':
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/modules/machine/pin.c:416: undefined reference to `hal_gpio_write'
/var/folders/gp/jb0b68fn3b187mgyyrjml3km0000gn/T//ccGhMnle.ltrans4.ltrans.o: In function `pin_low.lto_priv.432':
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/modules/machine/pin.c:407: undefined reference to `hal_gpio_write'
/var/folders/gp/jb0b68fn3b187mgyyrjml3km0000gn/T//ccGhMnle.ltrans4.ltrans.o: In function `pin_obj_init_helper':
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/modules/machine/pin.c:361: undefined reference to `hal_gpio_write'
/var/folders/gp/jb0b68fn3b187mgyyrjml3km0000gn/T//ccGhMnle.ltrans4.ltrans.o: In function `pin_call.lto_priv.340':
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/modules/machine/pin.c:265: undefined reference to `hal_gpio_read'
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/modules/machine/pin.c:268: undefined reference to `hal_gpio_write'
/var/folders/gp/jb0b68fn3b187mgyyrjml3km0000gn/T//ccGhMnle.ltrans4.ltrans.o: In function `machine_hard_i2c_transfer_single':
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/modules/machine/i2c.c:162: undefined reference to `hal_i2c_master_read'
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/modules/machine/i2c.c:166: undefined reference to `hal_i2c_master_write'
/var/folders/gp/jb0b68fn3b187mgyyrjml3km0000gn/T//ccGhMnle.ltrans4.ltrans.o: In function `machine_hard_i2c_make_new':
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/modules/machine/i2c.c:104: undefined reference to `hal_i2c_config'
/var/folders/gp/jb0b68fn3b187mgyyrjml3km0000gn/T//ccGhMnle.ltrans4.ltrans.o: In function `machine_adc_make_new.lto_priv.347':
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/modules/machine/adc.c:147: undefined reference to `console_printf'
/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt/modules/machine/adc.c:147: undefined reference to `console_flush'
collect2: error: ld returned 1 exit status
make[1]: *** [Makefile:402: build-pinetime/firmware.elf] Error 1
make[1]: Leaving directory '/Users/Luppy/PineTime/wasp-os/micropython/ports/mynewt'
make: *** [Makefile:37: micropython] Error 2
The terminal process terminated with exit code: 2
```