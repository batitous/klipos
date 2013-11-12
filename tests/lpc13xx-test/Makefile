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
include $(KLIPOS_PATH)/Makefile.klipos

SOURCE += $(SOURCE_PROJECT)
SOURCE_PATH += $(SOURCE_PATH_PROJECT) 

BUILD_PATH=./build

EXE=$(BUILD_PATH)/$(NAME).hex
EXE_MAIN=$(BUILD_PATH)/$(NAME).elf
EXE_BIN=$(BUILD_PATH)/$(NAME).bin

# external library
LIB_USE=-lc $(BUILD_PATH)/startup.o

## Macro to compile and link:
COMPILER=$(GCC) $(COMPILER_OPTION) $(DEFINE) $(INCLUDE) -c
ASM_GCC=$(ASM) $(ASM_OPTIONS)
LINKER=$(GCC) $(LINKER_OPTION) -o $(EXE_MAIN)
HEX_OPTIONS= --output-target ihex $(EXE_MAIN) $(EXE)

# Object search path:
OBJ_FILES =$(patsubst %.c,$(BUILD_PATH)/%.o,$(SOURCE))

## compiler & linker & library macro :

build: $(OBJ_FILES)
	@$(ASM_GCC) $(HW_STARTUP_ASM) -o $(BUILD_PATH)/startup.o
	@$(LINKER) $(OBJ_FILES) $(LIB_USE)
	@$(HEX) $(HEX_OPTIONS)
	@$(HEX) --strip-unneeded -O binary $(EXE_MAIN) $(EXE_BIN)
	@$(CRC) $(EXE_BIN)
	@$(SIZE) --target=ihex $(EXE)
	@$(SIZE) -A $(EXE_MAIN)

lib: $(OBJ_FILES)
	$(ARCHIVER_CMD) $(OBJ_FILES)
	
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
	$(FTDI) $(EXE) -wipe /dev/cu.usbserial-004013FD  115200 12000

usb:
	sudo $(USB) $(EXE_BIN)