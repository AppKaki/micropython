# Select the board to build for: if not given on the command line,
# then default to pinetime.
BOARD ?= pinetime
ifeq ($(wildcard boards/$(BOARD)/.),)
$(error Invalid BOARD specified)
endif

# TODO: Verify that it is a valid target.

include boards/$(BOARD)/mpconfigboard.mk

# Add NimBLE to build
BUILD ?= build-$(BOARD)
include ../../py/mkenv.mk
#### TODO include drivers/bluetooth/bluetooth_common.mk

LD_FILES += boards/memory.ld boards/common.ld

ifneq ($(LD_FILE),)
	# Use custom LD file
	LD_FILES = $(LD_FILE)
endif

-include boards/$(BOARD)/modules/boardmodules.mk

# qstr definitions (must come before including py.mk)
QSTR_DEFS = qstrdefsport.h $(BUILD)/pins_qstr.h

# include py core make definitions
include ../../py/py.mk

MICROPY_VFS_FAT ?= 0
MPY_CROSS = ../../mpy-cross/mpy-cross
MPY_TOOL = ../../tools/mpy-tool.py

CROSS_COMPILE = arm-none-eabi-

INC += -I.
INC += -I../..
INC += -I$(BUILD)
INC += -I./../../lib/cmsis/inc
INC += -I./modules/machine
INC += -I./modules/ubluepy
INC += -I./modules/music
INC += -I./modules/random
INC += -I./modules/ble
INC += -I./modules/board
INC += -I../../lib/mp-readline
INC += -I./drivers/bluetooth
INC += -I./drivers
INC += -I../../lib/nrfx/
INC += -I../../lib/nrfx/drivers
INC += -I../../lib/nrfx/drivers/include
INC += -I../../lib/nrfx/mdk
INC += -I../../lib/nrfx/hal
INC += -I../../lib/nrfx/drivers/src/

# Include folders for Mynewt. TODO: Move Mynewt as sub repo of MicroPython
MYNEWT_ROOT=../../../../pinetime-rust-mynewt
MYNEWT_CORE=$(MYNEWT_ROOT)/repos/apache-mynewt-core
MYNEWT_NIMBLE=$(MYNEWT_ROOT)/repos/apache-mynewt-nimble
MYNEWT_MCUBOOT=$(MYNEWT_ROOT)/repos/mcuboot

# Mynewt Core
INC += -I$(MYNEWT_CORE)/boot/split/include
INC += -I$(MYNEWT_CORE)/encoding/json/include
INC += -I$(MYNEWT_CORE)/encoding/tinycbor/include
INC += -I$(MYNEWT_CORE)/hw/drivers/flash/spiflash/include
INC += -I$(MYNEWT_CORE)/hw/hal/include
INC += -I$(MYNEWT_CORE)/hw/mcu/nordic/include
INC += -I$(MYNEWT_CORE)/hw/mcu/nordic/nrf52xxx/include
INC += -I$(MYNEWT_CORE)/hw/mcu/nordic/src/ext/nrfx/
INC += -I$(MYNEWT_CORE)/hw/mcu/nordic/src/ext/nrfx/mdk
INC += -I$(MYNEWT_CORE)/hw/sensor/include
INC += -I$(MYNEWT_CORE)/kernel/os/include
INC += -I$(MYNEWT_CORE)/kernel/os/include/os
INC += -I$(MYNEWT_CORE)/kernel/os/include/os/arch/cortex_m4
INC += -I$(MYNEWT_CORE)/mgmt/imgmgr/include
INC += -I$(MYNEWT_CORE)/mgmt/newtmgr/include
INC += -I$(MYNEWT_CORE)/mgmt/newtmgr/transport/ble/include
INC += -I$(MYNEWT_CORE)/net/oic/include
INC += -I$(MYNEWT_CORE)/sys/config/include
INC += -I$(MYNEWT_CORE)/sys/defs/include
INC += -I$(MYNEWT_CORE)/sys/flash_map/include
INC += -I$(MYNEWT_CORE)/sys/log/common/include
INC += -I$(MYNEWT_CORE)/sys/log/modlog/include
INC += -I$(MYNEWT_CORE)/sys/log/stub/include
INC += -I$(MYNEWT_CORE)/sys/sys/include
INC += -I$(MYNEWT_CORE)/sys/sysdown/include
INC += -I$(MYNEWT_CORE)/sys/sysinit/include

# Mynewt NimBLE Bluetooth Stack
INC += -I$(MYNEWT_NIMBLE)/nimble/include
INC += -I$(MYNEWT_NIMBLE)/nimble/host/include
INC += -I$(MYNEWT_NIMBLE)/nimble/host/services/ans/include
INC += -I$(MYNEWT_NIMBLE)/nimble/host/services/dis/include
INC += -I$(MYNEWT_NIMBLE)/nimble/host/services/gap/include
INC += -I$(MYNEWT_NIMBLE)/nimble/host/services/gatt/include
INC += -I$(MYNEWT_NIMBLE)/nimble/host/store/config/include
INC += -I$(MYNEWT_NIMBLE)/nimble/host/util/include
INC += -I$(MYNEWT_NIMBLE)/nimble/transport
INC += -I$(MYNEWT_NIMBLE)/porting/npl/mynewt/include

# Mynewt MCUBoot Bootloader
INC += -I$(MYNEWT_MCUBOOT)/boot/bootutil/include

# Mynewt Custom Libraries
INC += -I$(MYNEWT_ROOT)/bin/targets/nrf52_my_sensor/generated/include
INC += -I$(MYNEWT_ROOT)/libs/semihosting_console/include

MCU_VARIANT_UPPER = $(shell echo $(MCU_VARIANT) | tr '[:lower:]' '[:upper:]')
MCU_SUB_VARIANT_UPPER = $(shell echo $(MCU_SUB_VARIANT) | tr '[:lower:]' '[:upper:]')

# Figure out correct system file to use base on chip sub-variant name.
SYSTEM_C_SRC :=
ifeq ($(MCU_SUB_VARIANT),nrf51822)
	SYSTEM_C_SRC += $(addprefix lib/nrfx/mdk/, system_nrf51.c)
        NRF_DEFINES += -D$(MCU_VARIANT_UPPER)
else ifeq ($(MCU_SUB_VARIANT),nrf52832)
	SYSTEM_C_SRC += $(addprefix lib/nrfx/mdk/, system_nrf52.c)
        NRF_DEFINES += -D$(MCU_VARIANT_UPPER)
else ifeq ($(MCU_SUB_VARIANT),nrf52840)
	SYSTEM_C_SRC += $(addprefix lib/nrfx/mdk/, system_nrf52840.c)
	# Do not pass MCU_VARIANT_UPPER flag, as NRF52 defines NRF52832 only.
else ifeq ($(MCU_SUB_VARIANT),nrf9160)
        SYSTEM_C_SRC += $(addprefix lib/nrfx/mdk/, system_nrf9160.c)
        NRF_DEFINES += -D$(MCU_VARIANT_UPPER)
endif

NRF_DEFINES += -D$(MCU_SUB_VARIANT_UPPER)
NRF_DEFINES += -DCONFIG_GPIO_AS_PINRESET

CFLAGS_CORTEX_M = -mthumb -mabi=aapcs -fsingle-precision-constant -Wdouble-promotion

CFLAGS_MCU_m33 = $(CFLAGS_CORTEX_M) -mcpu=cortex-m33 -march=armv8-m.main+dsp -mcmse -mfpu=fpv5-sp-d16 -mfloat-abi=hard

CFLAGS_MCU_m4 = $(CFLAGS_CORTEX_M) -mtune=cortex-m4 -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard

CFLAGS_MCU_m0 = $(CFLAGS_CORTEX_M) -fshort-enums -mtune=cortex-m0 -mcpu=cortex-m0 -mfloat-abi=soft -fno-builtin

# Disable Link Time Optimisation because we are creating a Library, not an Executable
LTO ?= 0
ifeq ($(LTO),1)
CFLAGS += -flto
else
CFLAGS += -ffunction-sections -fdata-sections
LDFLAGS += -Wl,--gc-sections
endif


CFLAGS += $(CFLAGS_MCU_$(MCU_SERIES))
CFLAGS += $(INC) -Wall -Werror -g -ansi -std=c11 -nostdlib $(COPT) $(NRF_DEFINES) $(CFLAGS_MOD)
CFLAGS += -fno-strict-aliasing
CFLAGS += -Iboards/$(BOARD)
CFLAGS += -DNRF5_HAL_H='<$(MCU_VARIANT)_hal.h>'

LDFLAGS = $(CFLAGS)
LDFLAGS += -Xlinker -Map=$(@:.elf=.map)
LDFLAGS += -mthumb -mabi=aapcs $(addprefix -T,$(LD_FILES)) -L boards/

#Debugging/Optimization
ifeq ($(DEBUG), 1)
#ASMFLAGS += -g -gtabs+
CFLAGS += -O0 -ggdb
LDFLAGS += -O0
else
CFLAGS += -Os -DNDEBUG
LDFLAGS += -Os
endif

# Options for mpy-cross
MPY_CROSS_FLAGS += -march=armv7m

LIBS = \

ifeq ($(MCU_VARIANT), nrf52)

SRC_LIB += $(addprefix lib/,\
        libm/math.c \
        libm/fmodf.c \
        libm/nearbyintf.c \
        libm/ef_sqrt.c \
        libm/kf_rem_pio2.c \
        libm/kf_sin.c \
        libm/kf_cos.c \
        libm/kf_tan.c \
        libm/ef_rem_pio2.c \
        libm/sf_sin.c \
        libm/sf_cos.c \
        libm/sf_tan.c \
        libm/sf_frexp.c \
        libm/sf_modf.c \
        libm/sf_ldexp.c \
        libm/asinfacosf.c \
        libm/atanf.c \
        libm/atan2f.c \
	)

endif

ifeq ($(MCU_VARIANT), nrf91)

SRC_LIB += $(addprefix lib/,\
        libm/math.c \
        libm/fmodf.c \
        libm/nearbyintf.c \
        libm/ef_sqrt.c \
        libm/kf_rem_pio2.c \
        libm/kf_sin.c \
        libm/kf_cos.c \
        libm/kf_tan.c \
        libm/ef_rem_pio2.c \
        libm/sf_sin.c \
        libm/sf_cos.c \
        libm/sf_tan.c \
        libm/sf_frexp.c \
        libm/sf_modf.c \
        libm/sf_ldexp.c \
        libm/asinfacosf.c \
        libm/atanf.c \
        libm/atan2f.c \
        )

include drivers/secureboot/secureboot.mk

endif

SRC_LIB += $(addprefix lib/,\
	libc/string0.c \
	mp-readline/readline.c \
	utils/pyexec.c \
	utils/sys_stdio_mphal.c \
	utils/interrupt_char.c \
	timeutils/timeutils.c \
	)

ifeq ($(MICROPY_FATFS), 1)
SRC_LIB += $(addprefix lib/,\
        oofatfs/ff.c \
        oofatfs/ffunicode.c \
        )
endif

SRC_C += \
	main.c \
	mphalport.c \
	help.c \
	gccollect.c \
	pin_named_pins.c \
	fatfs_port.c \
	drivers/flash.c \
	drivers/softpwm.c \
	drivers/ticker.c \
	drivers/wdt.c \
	drivers/bluetooth/ble_drv.c \
	drivers/bluetooth/ble_uart.c \

ifeq ($(MCU_SUB_VARIANT), nrf52840)

INC += -I./drivers/usb
INC += -I../../lib/tinyusb/src

SRC_C += $(addprefix drivers/usb/,\
	usb_cdc.c \
	usb_descriptors.c \
	)

SRC_C += $(addprefix lib/tinyusb/src/,\
	common/tusb_fifo.c \
	device/usbd.c \
	device/usbd_control.c \
	class/cdc/cdc_device.c \
	tusb.c \
	portable/nordic/nrf5x/dcd_nrf5x.c \
	portable/nordic/nrf5x/hal_nrf5x.c \
	)
endif

DRIVERS_SRC_C += $(addprefix modules/,\
	machine/modmachine.c \
	machine/uart.c \
	machine/spi.c \
	machine/i2c.c \
	machine/adc.c \
	machine/pin.c \
	machine/timer.c \
	machine/rtcounter.c \
	machine/pwm.c \
	machine/temp.c \
	uos/moduos.c \
	uos/microbitfs.c \
	utime/modutime.c \
	board/modboard.c \
	board/led.c \
	ubluepy/modubluepy.c \
	ubluepy/ubluepy_peripheral.c \
	ubluepy/ubluepy_service.c \
	ubluepy/ubluepy_characteristic.c \
	ubluepy/ubluepy_uuid.c \
	ubluepy/ubluepy_delegate.c \
	ubluepy/ubluepy_constants.c \
	ubluepy/ubluepy_descriptor.c \
	ubluepy/ubluepy_scanner.c \
	ubluepy/ubluepy_scan_entry.c \
	music/modmusic.c \
	music/musictunes.c \
	ble/modble.c \
	random/modrandom.c \
	)

# Custom micropython startup file with smaller interrupt vector table
# than the file provided in nrfx.
SRC_C += \
	device/startup_$(MCU_SUB_VARIANT).c \

ifneq ($(FROZEN_MPY_DIR),)
FROZEN_MPY_PY_FILES := $(shell find -L $(FROZEN_MPY_DIR) -type f -name '*.py')
FROZEN_MPY_MPY_FILES := $(addprefix $(BUILD)/,$(FROZEN_MPY_PY_FILES:.py=.mpy))
endif

LIBGCC_FILE_NAME = $(shell $(CC) $(CFLAGS) -print-libgcc-file-name)
LIBS += -L $(dir $(LIBGCC_FILE_NAME)) -lgcc

OBJ += $(PY_O) $(addprefix $(BUILD)/, $(SRC_C:.c=.o))
OBJ += $(addprefix $(BUILD)/, $(SRC_MOD:.c=.o))
OBJ += $(addprefix $(BUILD)/, $(SRC_NRFX:.c=.o))
OBJ += $(addprefix $(BUILD)/, $(SRC_NRFX_HAL:.c=.o))
OBJ += $(addprefix $(BUILD)/, $(DRIVERS_SRC_C:.c=.o))
OBJ += $(addprefix $(BUILD)/, $(SYSTEM_C_SRC:.c=.o))
OBJ += $(addprefix $(BUILD)/, $(SRC_LIB:.c=.o))
OBJ += $(BUILD)/pins_gen.o

$(BUILD)/$(OOFATFS_DIR)/ff.o: COPT += -Os
$(filter $(PY_BUILD)/../extmod/vfs_fat_%.o, $(PY_O)): COPT += -Os

.PHONY: all flash deploy sd binary hex

## By default, generate micropython.a library
all: library binary

## Output is micropython.a
OUTPUT_FILENAME = micropython

## Create .a library from .o object files
library: $(BUILD)/$(OUTPUT_FILENAME).a

$(BUILD)/$(OUTPUT_FILENAME).a: $(OBJ)
	$(ECHO) "ARCHIVE $@"
	$(Q)$(AR) r $@ $(OBJ)
	$(Q)$(RANLIB) -t $@
	$(Q)$(SIZE) $@

## Create binary .bin file from the .out file
binary: $(BUILD)/$(OUTPUT_FILENAME).bin

$(BUILD)/$(OUTPUT_FILENAME).bin: $(BUILD)/$(OUTPUT_FILENAME).elf
	$(OBJCOPY) -O binary $< $@

## Create binary .hex file from the .out file
hex: $(BUILD)/$(OUTPUT_FILENAME).hex

$(BUILD)/$(OUTPUT_FILENAME).hex: $(BUILD)/$(OUTPUT_FILENAME).elf
	$(OBJCOPY) -O ihex $< $@

## Create .elf ELF firmware image from .o object files
$(BUILD)/$(OUTPUT_FILENAME).elf: $(OBJ)
	$(ECHO) "LINK $@"
	$(Q)$(CC) $(LDFLAGS) -o $@ $(OBJ) $(LIBS)
	$(Q)$(SIZE) $@

# List of sources for qstr extraction
SRC_QSTR += $(SRC_C) $(SRC_LIB) $(DRIVERS_SRC_C) $(SRC_BOARD_MODULES)

# Append any auto-generated sources that are needed by sources listed in
# SRC_QSTR
SRC_QSTR_AUTO_DEPS +=

# Making OBJ use an order-only depenedency on the generated pins.h file
# has the side effect of making the pins.h file before we actually compile
# any of the objects. The normal dependency generation will deal with the
# case when pins.h is modified. But when it doesn't exist, we don't know
# which source files might need it.
$(OBJ): | $(HEADER_BUILD)/pins.h

# Use a pattern rule here so that make will only call make-pins.py once to make
# both pins_gen.c and pins.h
$(BUILD)/%_gen.c $(HEADER_BUILD)/%.h $(HEADER_BUILD)/%_af_const.h $(BUILD)/%_qstr.h: boards/$(BOARD)/%.csv $(MAKE_PINS) $(AF_FILE) $(PREFIX_FILE) | $(HEADER_BUILD)
	$(ECHO) "Create $@"
	$(Q)$(PYTHON) $(MAKE_PINS) --board $(BOARD_PINS) --af $(AF_FILE) --prefix $(PREFIX_FILE) --hdr $(GEN_PINS_HDR) --qstr $(GEN_PINS_QSTR) --af-const $(GEN_PINS_AF_CONST) --af-py $(GEN_PINS_AF_PY) > $(GEN_PINS_SRC)

$(BUILD)/pins_gen.o: $(BUILD)/pins_gen.c
	$(call compile_c)

MAKE_PINS = boards/make-pins.py
BOARD_PINS = boards/$(BOARD)/pins.csv
AF_FILE = $(MCU_VARIANT)_af.csv
PREFIX_FILE = boards/$(MCU_VARIANT)_prefix.c
GEN_PINS_SRC = $(BUILD)/pins_gen.c
GEN_PINS_HDR = $(HEADER_BUILD)/pins.h
GEN_PINS_QSTR = $(BUILD)/pins_qstr.h
GEN_PINS_AF_CONST = $(HEADER_BUILD)/pins_af_const.h
GEN_PINS_AF_PY = $(BUILD)/pins_af.py

ifneq ($(FROZEN_MANIFEST)$(FROZEN_DIR),)
# To use frozen source modules, put your .py files in a subdirectory (eg scripts/)
# and then invoke make with FROZEN_DIR=scripts (be sure to build from scratch).
CFLAGS += -DMICROPY_MODULE_FROZEN_STR
endif

ifneq ($(FROZEN_MANIFEST)$(FROZEN_MPY_DIR),)
# To use frozen bytecode, put your .py files in a subdirectory (eg frozen/) and
# then invoke make with FROZEN_MPY_DIR=frozen (be sure to build from scratch).
CFLAGS += -DMICROPY_QSTR_EXTRA_POOL=mp_qstr_frozen_const_pool
CFLAGS += -DMICROPY_MODULE_FROZEN_MPY
endif

$(PY_BUILD)/nlr%.o: CFLAGS += -Os -fno-lto

include ../../py/mkrules.mk

