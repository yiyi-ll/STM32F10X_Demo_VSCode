TARGET = STM32F10X

# č编译生成文件夹
BUILD_DIR = Obj
 
# C源文件
C_SOURCES =  \
Src/USER/src/main.c \
Src/CORE/src/core_cm3.c \
Src/CORE/src/system_stm32f10x.c \
Src/FWLIB/src/misc.c \
Src/FWLIB/src/stm32f10x_gpio.c \
Src/FWLIB/src/stm32f10x_rcc.c \
Src/FWLIB/src/stm32f10x_adc.c \
Src/FWLIB/src/stm32f10x_bkp.c \
Src/FWLIB/src/stm32f10x_can.c \
Src/FWLIB/src/stm32f10x_cec.c \
Src/FWLIB/src/stm32f10x_crc.c \
Src/FWLIB/src/stm32f10x_dac.c \
Src/FWLIB/src/stm32f10x_dbgmcu.c \
Src/FWLIB/src/stm32f10x_dma.c \
Src/FWLIB/src/stm32f10x_exti.c \
Src/FWLIB/src/stm32f10x_flash.c \
Src/FWLIB/src/stm32f10x_fsmc.c \
Src/FWLIB/src/stm32f10x_i2c.c \
Src/FWLIB/src/stm32f10x_iwdg.c \
Src/FWLIB/src/stm32f10x_pwr.c \
Src/FWLIB/src/stm32f10x_rtc.c \
Src/FWLIB/src/stm32f10x_sdio.c \
Src/FWLIB/src/stm32f10x_spi.c \
Src/FWLIB/src/stm32f10x_tim.c \
Src/FWLIB/src/stm32f10x_usart.c \
Src/FWLIB/src/stm32f10x_wwdg.c \
Src/FWLIB/src/stm32f10x_it.c \
Src/FreeRTOS/src/croutine.c \
Src/FreeRTOS/src/event_groups.c \
Src/FreeRTOS/src/list.c \
Src/FreeRTOS/src/port.c \
Src/FreeRTOS/src/queue.c \
Src/FreeRTOS/src/stream_buffer.c \
Src/FreeRTOS/src/tasks.c \
Src/FreeRTOS/src/timers.c \
Src/FreeRTOS/src/heap_4.c \
Src/BSP/src/bsp_abit_delay.c \
Src/BSP/src/bsp_abit_usart.c \
Src/Bsp/src/bsp_abit_printf.c \
Src/Bsp/src/bsp_abit_humiture.c \
Src/Bsp/src/bsp_abit_gpio.c \
Src/Bsp/src/bsp_abit_nvic.c
 
######################################
 
 
 
# ASM sources
ASM_SOURCES =  \
Src/CORE/src/startup_stm32f10x_hd.s
 
######################################
# building variables
######################################
# debug build?
DEBUG = 1
# optimization
OPT = -Og
 
 
#######################################
# binaries
#######################################
PREFIX = arm-none-eabi-
ifdef GCC_PATH
CC = $(GCC_PATH)/$(PREFIX)gcc
AS = $(GCC_PATH)/$(PREFIX)gcc -x assembler-with-cpp
CP = $(GCC_PATH)/$(PREFIX)objcopy
SZ = $(GCC_PATH)/$(PREFIX)size
else
CC = $(PREFIX)gcc
AS = $(PREFIX)gcc -x assembler-with-cpp
CP = $(PREFIX)objcopy
SZ = $(PREFIX)size
endif
HEX = $(CP) -O ihex
BIN = $(CP) -O binary -S
 
#######################################
# CFLAGS
#######################################
# cpu
CPU = -mcpu=cortex-m3
 
# fpu
# NONE for Cortex-M0/M0+/M3
 
# float-abi
 
# mcu
MCU = $(CPU) -mthumb $(FPU) $(FLOAT-ABI)
 
# macros for gcc
# AS defines
AS_DEFS = 
 
# C defines   宏定义标志
C_DEFS =  \
-DUSE_STDPERIPH_DRIVER \
-DSTM32F10X_HD
 
# AS includes
AS_INCLUDES = 
 
# C includes  C头文件路径
C_INCLUDES =  \
-ISrc/BSP/inc \
-ISrc/CORE/inc \
-ISrc/FWLIB/inc \
-ISrc/USER/inc \
-ISrc/FreeRTOS/inc
 
# compile gcc flags
ASFLAGS = $(MCU) $(AS_DEFS) $(AS_INCLUDES) $(OPT) -Wall -fdata-sections -ffunction-sections
 
CFLAGS = $(MCU) $(C_DEFS) $(C_INCLUDES) $(OPT) -Wall -fdata-sections -ffunction-sections
 
ifeq ($(DEBUG), 1)
CFLAGS += -g -gdwarf-2
endif
 
 
# Generate dependency information
CFLAGS += -MMD -MP -MF"$(@:%.o=%.d)"
 
 
#######################################
# LDFLAGS
#######################################
# link script  链接配置文件
LDSCRIPT = Src/CORE/src/stm32_flash.ld
 
# libraries
#LIBS = -lc -lm -lnosys 
LIBS = -lc
LIBDIR = 
#LDFLAGS = $(MCU) -specs=nano.specs -T$(LDSCRIPT) $(LIBDIR) $(LIBS) -Wl,-Map=$(BUILD_DIR)/$(TARGET).map,--cref -Wl,--gc-sections
LDFLAGS = $(MCU) --specs=nano.specs --specs=nosys.specs -std=c99 -T$(LDSCRIPT) $(LIBDIR) $(LIBS) -Wl,-Map=$(BUILD_DIR)/$(TARGET).map,--cref -Wl,--gc-sections
 
# default action: build all
all: $(BUILD_DIR)/$(TARGET).elf $(BUILD_DIR)/$(TARGET).hex $(BUILD_DIR)/$(TARGET).bin
 
 
#######################################
# build the application
#######################################
# list of objects
OBJECTS = $(addprefix $(BUILD_DIR)/,$(notdir $(C_SOURCES:.c=.o)))
vpath %.c $(sort $(dir $(C_SOURCES)))
# list of ASM program objects
OBJECTS += $(addprefix $(BUILD_DIR)/,$(notdir $(ASM_SOURCES:.s=.o)))
vpath %.s $(sort $(dir $(ASM_SOURCES)))
 
$(BUILD_DIR)/%.o: %.c Makefile | $(BUILD_DIR) 
	$(CC) -c $(CFLAGS) -Wa,-a,-ad,-alms=$(BUILD_DIR)/$(notdir $(<:.c=.lst)) $< -o $@
 
$(BUILD_DIR)/%.o: %.s Makefile | $(BUILD_DIR)
	$(AS) -c $(CFLAGS) $< -o $@
 
$(BUILD_DIR)/$(TARGET).elf: $(OBJECTS) Makefile
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@
	$(SZ) $@
 
$(BUILD_DIR)/%.hex: $(BUILD_DIR)/%.elf | $(BUILD_DIR)
	$(HEX) $< $@
	
$(BUILD_DIR)/%.bin: $(BUILD_DIR)/%.elf | $(BUILD_DIR)
	$(BIN) $< $@	
	
$(BUILD_DIR):
	mkdir $@		
 
#######################################
# clean up
#######################################
clean:
	-rm -fR $(BUILD_DIR)
  
#######################################
# dependencies
#######################################
-include $(wildcard $(BUILD_DIR)/*.d)
 
# *** EOF ***