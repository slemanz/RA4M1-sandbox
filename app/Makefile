CC=arm-none-eabi-gcc
TARGET=flash

MACH=-mcpu=cortex-m4
FLOAT=-mfloat-abi=soft

BUILD_DIR = Build
ROOT_DIR = ..

LINKER= -T $(ROOT_DIR)/linkers/R7FA4M1AB.ld
MAP_FILE= -Wl,-Map=$(BUILD_DIR)/$(TARGET).map

CFLAGS= -c $(MACH) -mthumb $(FLOAT) -std=gnu99 -Wall -O0 -g \
		--specs=nano.specs -ffunction-sections -fdata-sections

LDFLAGS = $(MACH) -mthumb $(FLOAT) --specs=nosys.specs $(LINKER) $(MAP_FILE) -g \
			-Wl,--gc-sections -static --specs=nano.specs -Wl,--start-group -lc -lm \
			-Wl,--end-group -Wl,--print-memory-usage

OBJCOPY=arm-none-eabi-objcopy

###########################################
#				 INCLUDES
###########################################

INCLUDES+= -I $(ROOT_DIR)/app/Inc/
INCLUDES+= -I $(ROOT_DIR)/drivers/Inc/
INCLUDES+= -I $(ROOT_DIR)/common/Inc/

############################################
# 				SOURCE FILES
############################################

OBJS		+= $(BUILD_DIR)/main.o
OBJS		+= $(BUILD_DIR)/config.o
OBJS		+= $(BUILD_DIR)/syscalls.o
OBJS		+= $(BUILD_DIR)/startup.o

DRIVERS		+= $(BUILD_DIR)/driver_clock.o
DRIVERS		+= $(BUILD_DIR)/driver_systick.o
DRIVERS		+= $(BUILD_DIR)/driver_gpio.o
DRIVERS		+= $(BUILD_DIR)/driver_sci.o

CORE		+= $(BUILD_DIR)/simple-timer.o

BSP			+= $(BUILD_DIR)/led.o

PREREQ = $(BUILD_DIR)/

all: $(PREREQ) $(BUILD_DIR)/$(TARGET).elf

$(PREREQ):
	mkdir $(PREREQ)

$(BUILD_DIR)/%.o: $(ROOT_DIR)/app/Src/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -o $(BUILD_DIR)/$(*).o $(ROOT_DIR)/app/Src/$(*).c

$(BUILD_DIR)/%.o: $(ROOT_DIR)/drivers/Src/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -o $(BUILD_DIR)/$(*).o $(ROOT_DIR)/drivers/Src/$(*).c

$(BUILD_DIR)/%.o: $(ROOT_DIR)/common/Src/core/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -o $(BUILD_DIR)/$(*).o $(ROOT_DIR)/common/Src/core/$(*).c

$(BUILD_DIR)/%.o: $(ROOT_DIR)/common/Src/bsp/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -o $(BUILD_DIR)/$(*).o $(ROOT_DIR)/common/Src/bsp/$(*).c

$(BUILD_DIR)/%.o: $(ROOT_DIR)/linkers/*.c
	$(CC) $(CFLAGS) $(INCLUDES) -o $(BUILD_DIR)/$(*).o $(ROOT_DIR)/linkers/$(*).c

# TARGET ELF
$(BUILD_DIR)/$(TARGET).elf: $(OBJS) $(DRIVERS) $(CORE) $(BSP)
	$(CC) $(LDFLAGS) -o $@ $^
	$(OBJCOPY) -O binary $(BUILD_DIR)/$(TARGET).elf $(BUILD_DIR)/$(TARGET).bin
	arm-none-eabi-size $(BUILD_DIR)/$(TARGET).elf

load:
	jlink flash.jlink

clean:
	rm -rf $(BUILD_DIR)/*.map $(BUILD_DIR)/*.o