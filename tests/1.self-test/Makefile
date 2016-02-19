include Makefile.common

USERID=$(shell id -u)

all : MK_BUILD_DIR BUILD_C_OBJ BUILD_ASM_OBJ BUILD_ELF BUILD_HEX BUILD_LST BUILD_SYM SHOW_SIZE

program-all : program lfuse hfuse efuse

program :
	$(info User Id is $(USERID))
    ifeq ($(USERID),0)
		$(info Running as root... OK)
    else
		$(info You must be root to execute this command)
		$(SUDO)
    endif
	$(DUDE) -c $(PROGRAMMER) -p $(DEVICE) -U flash:w:$(BIN_FOLDER)/$(TARGET).hex:i
	
lfuse :
	$(info User Id is $(USERID))
    ifeq ($(USERID),0)
		$(info Running as root... OK)
    else
		$(info You must be root to execute this command)
		$(SUDO)
    endif
	$(DUDE) -c $(PROGRAMMER) -p $(DEVICE) -U lfuse:w:$(LFUSE):m

hfuse :
	$(info User Id is $(USERID))
    ifeq ($(USERID),0)
		$(info Running as root... OK)
    else
		$(info You must be root to execute this command)
		$(SUDO)
    endif
	$(DUDE) -c $(PROGRAMMER) -p $(DEVICE) -U hfuse:w:$(HFUSE):m

efuse :
	$(info User Id is $(USERID))
    ifeq ($(USERID),0)
		$(info Running as root... OK)
    else
		$(info You must be root to execute this command)
		$(SUDO)
    endif
	$(DUDE) -c $(PROGRAMMER) -p $(DEVICE) -U efuse:w:$(EFUSE):m

clean : CLEAN_C_OBJ CLEAN_ASM_OBJ
	rm -f $(BIN_FOLDER)/$(TARGET).elf \
		$(BIN_FOLDER)/$(TARGET).hex \
		$(BIN_FOLDER)/$(TARGET).lst \
		$(BIN_FOLDER)/$(TARGET).sym
	rm -rf $(BIN_FOLDER)

MK_BUILD_DIR :
	mkdir -p $(BIN_FOLDER)

BUILD_C_OBJ : Makefile_C
	make -f Makefile_C all

BUILD_ASM_OBJ : Makefile_ASM
	make -f Makefile_ASM all

BUILD_ELF :
	@echo "\033[33m"Linking ... :"\033[0m"
ifeq ($(C_SRC_FILES),)
	$(LD) $(LD_FLAGS) $(C_OBJ) $(ASM_OBJ) --output $(BIN_FOLDER)/$(TARGET).elf
else
	$(LD) $(LD_FLAGS) $(C_OBJ) $(ASM_OBJ) --output $(BIN_FOLDER)/$(TARGET).elf $(LINKER_FLAGS)
endif


BUILD_HEX :
	@echo "\033[33m"Creating HEX file ... :"\033[0m"
	$(OBJCOPY) -j .text -j .data -j .eeprom -O ihex \
	$(BIN_FOLDER)/$(TARGET).elf $(BIN_FOLDER)/$(TARGET).hex

BUILD_LST :
	@echo "\033[33m"Creating LIST file ... :"\033[0m" 
	$(OBJDUMP) -h -S -C \
	$(BIN_FOLDER)/$(TARGET).elf > $(BIN_FOLDER)/$(TARGET).lst

BUILD_SYM :
	@echo "\033[33m"Creating SYM file ... :"\033[0m"
	$(NM) -n $(BIN_FOLDER)/$(TARGET).elf > $(BIN_FOLDER)/$(TARGET).sym

SHOW_SIZE :
	@echo "\033[33m"
	$(SIZE) -C --mcu=$(DEVICE) $(BIN_FOLDER)/$(TARGET).elf
	@echo "\033[0m"


CLEAN_C_OBJ :
	make -f Makefile_C clean
	
CLEAN_ASM_OBJ :
	make -f Makefile_ASM clean
