################################################################################
#Project Name:
PROJECT = blinky
DEVICE=__SAMD21G18A__
################################################################################
#Project Directory
PROJDIR=$(HOME)/Dev/samd21proj/$(PROJECT)
################################################################################
#ASF Directory
ASFDIR=$(HOME)/Applications/xdk-asf-3.34.2
ASFSAM0DIR=$(ASFDIR)/sam0
ASFSAM0UTILSDIR=$(ASFSAM0DIR)/utils
################################################################################
#J-Link Directory
JLINKDIR=$(HOME)/Applications/JLink_Linux_V616c_x86_64/
################################################################################
#necessary source files (barebones) 
SOURCE+=$(ASFSAM0UTILSDIR)/syscalls/gcc/syscalls.c
SOURCE+=$(ASFSAM0UTILSDIR)/stdio/read.c
SOURCE+=$(ASFSAM0UTILSDIR)/stdio/write.c
SOURCE+=$(ASFSAM0UTILSDIR)/cmsis/samd21/source/system_samd21.c
SOURCE+=$(ASFSAM0UTILSDIR)/cmsis/samd21/source/gcc/startup_samd21.c 

SOURCE+=$(PROJDIR)/src/main.c

###############################################################################
#Include paths to all barebone necessary headers
INCLUDE_PATHS += -I$(ASFSAM0UTILSDIR)
INCLUDE_PATHS += -I$(ASFSAM0UTILSDIR)/header_files/
INCLUDE_PATHS += -I$(ASFSAM0UTILSDIR)/cmsis/samd21/include/
INCLUDE_PATHS += -I$(ASFSAM0UTILSDIR)/cmsis/samd21/include/component
INCLUDE_PATHS += -I$(ASFSAM0UTILSDIR)/cmsis/samd21/include/instance
INCLUDE_PATHS += -I$(ASFSAM0UTILSDIR)/cmsis/samd21/include/pio
INCLUDE_PATHS += -I$(ASFSAM0UTILSDIR)/cmsis/samd21/source
INCLUDE_PATHS += -I$(ASFSAM0UTILSDIR)/preprocessor
INCLUDE_PATHS += -I$(ASFSAM0UTILSDIR)/stdio/stdio_serial

INCLUDE_PATHS += -I$(ASFDIR)/thirdparty/CMSIS/Include
INCLUDE_PATHS += -I$(ASFDIR)/common/utils
INCLUDE_PATHS += -I$(ASFDIR)/common/utils/interrupt

###############################################################################
#Linker script
LINKER_SCRIPT = $(ASFSAM0UTILSDIR)/linker_scripts/samd21/gcc/samd21g18a_flash.ld

###############################################################################
#ASFDRIVER

################################################################################
#arm-none-eabi- toolchain shortcuts
GDBTUI  = $(GCC_BIN)arm-none-eabi-gdb -tui
AS      = $(GCC_BIN)arm-none-eabi-as
AR      = $(GCC_BIN)arm-none-eabi-ar
CC      = $(GCC_BIN)arm-none-eabi-gcc
CPP     = $(GCC_BIN)arm-none-eabi-g++
LD      = $(GCC_BIN)arm-none-eabi-gcc
OBJCOPY = $(GCC_BIN)arm-none-eabi-objcopy
OBJDUMP = $(GCC_BIN)arm-none-eabi-objdump
SIZE 	= $(GCC_BIN)arm-none-eabi-size
RANLIB  = $(GCC_BIN)arm-none-eabi-ranlib
HEX     = $(OBJCOPY) -O ihex
BIN     = $(OBJCOPY) -O binary -S
############################################################################
# set DEBUG variable to 1 if building for debug, 0 for release

DEBUG=n

###########################################################################
#compiler and linker flags
COMMON_FLAGS = -mthumb -mcpu=cortex-m0plus -D$(DEVICE)

ifeq ($(DEBUG), Y)
    COMMON_FLAGS +=   -O0 -g
else
    COMMON_FLAGS += -Os 
endif

WFLAGS = \
-Wall -Wstrict-prototypes \
-Werror-implicit-function-declaration -Wpointer-arith -std=gnu99 \
-ffunction-sections -fdata-sections -Wchar-subscripts -Wcomment -Wformat=2 \
-Wimplicit-int -Wmain -Wparentheses -Wsequence-point -Wreturn-type -Wswitch \
-Wtrigraphs -Wunused -Wuninitialized -Wunknown-pragmas -Wfloat-equal -Wundef \
-Wbad-function-cast -Wwrite-strings -Waggregate-return \
-Wformat -Wmissing-format-attribute \
-Wno-deprecated-declarations -Wpacked -Wredundant-decls -Wnested-externs \
-Wlong-long -Wunreachable-code -Wcast-align \
-Wno-missing-braces -Wno-overflow -Wno-shadow -Wno-attributes -Wno-packed -Wno-pointer-sign

CFLAGS = $(COMMON_FLAGS) \
--param max-inline-insns-single=500 \
-fno-strict-aliasing -fdata-sections -ffunction-sections -mlong-calls \
$(WFLAGS)

#-x -pipe -nostdlib \

LDFLAGS= $(COMMON_FLAGS) \
-Wall -Wl,--cref -Wl,-Map,$(PROJECT).map -Wl,--check-sections -Wl,--gc-sections -Wl,--warn-common \
-Wl,--warn-section-align -Wl,--warn-unresolved-symbols -Wl,--unresolved-symbols=report-all \
-T$(LINKER_SCRIPT) --specs=nano.specs --specs=nosys.specs \
-lc -lgcc -lnosys -lm

#-save-temps

#########################################################################
#Build and clean commands. Note that compiling and link happens at the same time

all: $(SOURCE)
	$(CC)  $(SOURCE) $(CFLAGS)  $(INCLUDE_PATHS) $(LDFLAGS) -o $(PROJECT).axf
	$(SIZE) $(PROJECT).axf
	$(HEX) $(PROJECT).axf  $(PROJECT).hex
	$(BIN) $(PROJECT).axf  $(PROJECT).bin

clean:
	-rm -rf $(PROJECT).axf
	-rm -rf $(PROJECT).hex
	-rm -rf $(PROJECT).bin
	-rm -rf $(PROJECT).map

jlinkflash: $(PROJECT).bin
	$(JLINKDIR)/JLinkExe -if swd -device ATSAMD21G18 -speed 4000 -CommanderScript flashbinary.jlink
