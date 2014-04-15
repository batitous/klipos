##########################################################################################
##                        main makefile to compile Klipos project                       ##
##########################################################################################
## Don't edit this file:                                                                ##
## -The toolchain configuration is located in Makefile.toolchainconfig                  ##
## -The project options (name, src filelist, Cflags…) is located in Makefile.options    ##
## -Klipos config is located in Klipos directory                                        ##
##########################################################################################

# Clean Makefile variables
SOURCE = 
HEADER = 
SOURCE_PATH = 
INCLUDE = 

include Makefile.toolchainconfig
include Makefile.options

KLIPOS_TOOLS=$(KLIPOS_PATH)/tools/

include $(KLIPOS_PATH)/klipos/Makefile.klipos

SOURCE += $(SOURCE_PROJECT)
SOURCE_PATH += $(SOURCE_PATH_PROJECT) 
INCLUDE += $(HEADER_PROJECT)

BUILD_PATH=./build

EXE=$(BUILD_PATH)/$(NAME).hex
EXE_MAIN=$(BUILD_PATH)/$(NAME).elf
EXE_BIN=$(BUILD_PATH)/$(NAME).bin

# external library
LIB_USE=-lc 

## Macro to compile and link:
COMPILER=$(GCC) $(COMPILER_OPTION) $(DEFINE) $(INCLUDE) -c
LINKER=$(GCC) $(LINKER_OPTION) -o $(EXE_MAIN)

# Object search path:
OBJ_FILES =$(patsubst %.c,$(BUILD_PATH)/%.o,$(SOURCE))

## compiler & linker macro :

build: $(OBJ_FILES)
	@$(LINKER) $(OBJ_FILES) $(LIB_USE)
	@$(HEX) --output-target ihex $(EXE_MAIN) $(EXE)
	@$(HEX) --strip-unneeded -O binary $(EXE_MAIN) $(EXE_BIN)
	@$(CRC) $(EXE_BIN)
	@$(SIZE) --target=ihex $(EXE)
	@$(SIZE) -A $(EXE_MAIN)
	
vpath %.c $(SOURCE_PATH)

$(BUILD_PATH)/%.o : %.c
	@echo $<
	@$(COMPILER) -o $@ $<

dump:
	$(DISASM) -d $(EXE_MAIN)

dump1:
	/opt/arm-cs-tools/bin/arm-eabi-readelf -a $(EXE_MAIN)
	
clean:
	rm $(BUILD_PATH)/*

cleanbuild:
	rm $(BUILD_PATH)/*


flash:
	$(FTDI) $(EXE) -wipe /dev/cu.SLAB_USBtoUART  115200 12000

usb:
	sudo $(USB) $(EXE_BIN)