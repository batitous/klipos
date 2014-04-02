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

BUILD_PATH=./build

EXE=./$(NAME)-$(mcu).a


# external library
LIB_USE=-lc 

## Macro to compile and link:
COMPILER=$(GCC) $(COMPILER_OPTION) $(DEFINE) $(INCLUDE) -c
LINKER=$(GCC) $(LINKER_OPTION) -o $(EXE_MAIN)

# Library command:
AR_CMD=$(AR) -rv -o $(EXE)

# Object search path:
OBJ_FILES =$(patsubst %.c,$(BUILD_PATH)/%.o,$(SOURCE))

## compiler & linker macro :

build: $(OBJ_FILES)
	@$(AR_CMD) $(OBJ_FILES)
	
vpath %.c $(SOURCE_PATH)

$(BUILD_PATH)/%.o : %.c
	@echo $<
	@$(COMPILER) -o $@ $<
	
clean:
	rm $(BUILD_PATH)/*

cleanbuild:
	rm $(BUILD_PATH)/*
