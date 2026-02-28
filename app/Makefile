CC=arm-none-eabi-gcc
TARGET=flash

MACH=-mcpu=cortex-m4
FLOAT=-mfloat-abi=soft

DIR_BUILD 	= Build
DIR_ROOT 	= ..
DIR_DEVICE 	= $(DIR_ROOT)/drivers/Device

LINKER = -T $(DIR_DEVICE)/linkers/R7FA4M1AB.ld
MAP_FILE = -Wl,-Map=$(DIR_BUILD)/$(TARGET).map

CFLAGS= -c $(MACH) -mthumb $(FLOAT) -std=gnu99 -Wall -O0 -g \
		--specs=nano.specs -ffunction-sections -fdata-sections

LDFLAGS = $(MACH) -mthumb $(FLOAT) --specs=nosys.specs $(LINKER) $(MAP_FILE) -g \
			-Wl,--gc-sections -static --specs=nano.specs -Wl,--start-group -lc -lm \
			-Wl,--end-group -Wl,--print-memory-usage

OBJCOPY=arm-none-eabi-objcopy

###########################################
#				 INCLUDES
###########################################

INCLUDES+= -I $(DIR_ROOT)/app/Inc
INCLUDES+= -I $(DIR_ROOT)/drivers/Inc
INCLUDES+= -I $(DIR_ROOT)/common/Inc
INCLUDES+= -I $(DIR_ROOT)/interface/Inc

############################################
# 				SOURCE FILES
############################################

OBJS		+= $(DIR_BUILD)/main.o
OBJS		+= $(DIR_BUILD)/config.o
OBJS		+= $(DIR_BUILD)/syscalls.o
OBJS		+= $(DIR_BUILD)/startup.o

DRIVERS		+= $(DIR_BUILD)/driver_clock.o
DRIVERS		+= $(DIR_BUILD)/driver_systick.o
DRIVERS		+= $(DIR_BUILD)/driver_gpio.o
DRIVERS		+= $(DIR_BUILD)/driver_sci.o
DRIVERS		+= $(DIR_BUILD)/driver_interrupt.o

INTERFACE	+= $(DIR_BUILD)/interface_comm.o
INTERFACE	+= $(DIR_BUILD)/protocol_sci.o
INTERFACE	+= $(DIR_BUILD)/interface_timebase.o
INTERFACE	+= $(DIR_BUILD)/interface_io.o

CORE		+= $(DIR_BUILD)/simple-timer.o
CORE		+= $(DIR_BUILD)/cli.o
CORE		+= $(DIR_BUILD)/uprint.o

BSP			+= $(DIR_BUILD)/led.o

SHARED		+= $(DIR_BUILD)/ring-buffer.o

PREREQ = $(DIR_BUILD)

all: $(PREREQ) $(DIR_BUILD)/$(TARGET).elf

$(PREREQ):
	mkdir $(PREREQ)

$(DIR_BUILD)/%.o: Src/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -o $(DIR_BUILD)/$(*).o Src/$(*).c

$(DIR_BUILD)/%.o: $(DIR_ROOT)/drivers/Src/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -o $(DIR_BUILD)/$(*).o $(DIR_ROOT)/drivers/Src/$(*).c

$(DIR_BUILD)/%.o: $(DIR_ROOT)/interface/Src/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -o $(DIR_BUILD)/$(*).o $(DIR_ROOT)/interface/Src/$(*).c

$(DIR_BUILD)/%.o: $(DIR_ROOT)/common/Src/core/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -o $(DIR_BUILD)/$(*).o $(DIR_ROOT)/common/Src/core/$(*).c

$(DIR_BUILD)/%.o: $(DIR_ROOT)/common/Src/bsp/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -o $(DIR_BUILD)/$(*).o $(DIR_ROOT)/common/Src/bsp/$(*).c

$(DIR_BUILD)/%.o: $(DIR_ROOT)/common/Src/shared/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -o $(DIR_BUILD)/$(*).o $(DIR_ROOT)/common/Src/shared/$(*).c

$(DIR_BUILD)/%.o: $(DIR_DEVICE)/startup/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -o $(DIR_BUILD)/$(*).o $(DIR_DEVICE)/startup/$(*).c

$(DIR_BUILD)/%.o: $(DIR_DEVICE)/system/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -o $(DIR_BUILD)/$(*).o $(DIR_DEVICE)/system/$(*).c

# TARGET ELF
$(DIR_BUILD)/$(TARGET).elf: $(OBJS) $(DRIVERS) $(CORE) $(BSP) $(SHARED) $(INTERFACE)
	$(CC) $(LDFLAGS) -o $@ $^
	$(OBJCOPY) -O binary $(DIR_BUILD)/$(TARGET).elf $(DIR_BUILD)/$(TARGET).bin
	arm-none-eabi-size $(DIR_BUILD)/$(TARGET).elf

load:
	jlink flash.jlink

clean:
	rm -rf $(DIR_BUILD)/*.map $(DIR_BUILD)/*.o