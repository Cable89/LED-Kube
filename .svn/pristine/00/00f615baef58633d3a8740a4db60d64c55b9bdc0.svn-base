################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL := cmd.exe
RM := rm -rf

USER_OBJS :=

LIBS := 
PROJ := 

O_SRCS := 
C_SRCS := 
S_SRCS := 
S_UPPER_SRCS := 
OBJ_SRCS := 
ASM_SRCS := 
PREPROCESSING_SRCS := 
OBJS := 
OBJS_AS_ARGS := 
C_DEPS := 
C_DEPS_AS_ARGS := 
EXECUTABLES := 
OUTPUT_FILE_PATH :=
OUTPUT_FILE_PATH_AS_ARGS :=
AVR_APP_PATH :=$$$AVR_APP_PATH$$$
QUOTE := "
ADDITIONAL_DEPENDENCIES:=
OUTPUT_FILE_DEP:=
LIB_DEP:=

# Every subdirectory with source files must be described here
SUBDIRS := 


# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS +=  \
../draw.c \
../effect.c \
../font.c \
../main.c \
../snake.c \
../usb.c


PREPROCESSING_SRCS += 


ASM_SRCS += 


OBJS +=  \
draw.o \
effect.o \
font.o \
main.o \
snake.o \
usb.o

OBJS_AS_ARGS +=  \
draw.o \
effect.o \
font.o \
main.o \
snake.o \
usb.o

C_DEPS +=  \
draw.d \
effect.d \
font.d \
main.d \
snake.d \
usb.d

C_DEPS_AS_ARGS +=  \
draw.d \
effect.d \
font.d \
main.d \
snake.d \
usb.d

OUTPUT_FILE_PATH +=Led_Cube-10x10x10-Red-v-0-1-4.elf

OUTPUT_FILE_PATH_AS_ARGS +=Led_Cube-10x10x10-Red-v-0-1-4.elf

ADDITIONAL_DEPENDENCIES:=

OUTPUT_FILE_DEP:= ./makedep.mk

LIB_DEP+= 

# AVR32/GNU C Compiler













./%.o: .././%.c
	@echo Building file: $<
	@echo Invoking: AVR/GNU C Compiler : 3.4.2
	$(QUOTE)C:\Program Files (x86)\Atmel\Atmel Toolchain\AVR8 GCC\Native\3.4.2.939\avr8-gnu-toolchain\bin\avr-gcc.exe$(QUOTE)  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -Wall -mmcu=at90usb1287 -c -std=gnu99 -MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)"   -o "$@" "$<"
	@echo Finished building: $<
	



# AVR32/GNU Preprocessing Assembler



# AVR32/GNU Assembler




ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: $(OUTPUT_FILE_PATH) $(ADDITIONAL_DEPENDENCIES)

$(OUTPUT_FILE_PATH): $(OBJS) $(USER_OBJS) $(OUTPUT_FILE_DEP) $(LIB_DEP)
	@echo Building target: $@
	@echo Invoking: AVR/GNU Linker : 3.4.2
	$(QUOTE)C:\Program Files (x86)\Atmel\Atmel Toolchain\AVR8 GCC\Native\3.4.2.939\avr8-gnu-toolchain\bin\avr-gcc.exe$(QUOTE) -o$(OUTPUT_FILE_PATH_AS_ARGS) $(OBJS_AS_ARGS) $(USER_OBJS) $(LIBS) -Wl,-Map="Led_Cube-10x10x10-Red-v-0-1-4.map" -Wl,--start-group -Wl,-lm  -Wl,--end-group -Wl,--gc-sections -mmcu=at90usb1287 
	@echo Finished building target: $@
	"C:\Program Files (x86)\Atmel\Atmel Toolchain\AVR8 GCC\Native\3.4.2.939\avr8-gnu-toolchain\bin\avr-objcopy.exe" -O ihex -R .eeprom -R .fuse -R .lock -R .signature  "Led_Cube-10x10x10-Red-v-0-1-4.elf" "Led_Cube-10x10x10-Red-v-0-1-4.hex"
	"C:\Program Files (x86)\Atmel\Atmel Toolchain\AVR8 GCC\Native\3.4.2.939\avr8-gnu-toolchain\bin\avr-objcopy.exe" -j .eeprom  --set-section-flags=.eeprom=alloc,load --change-section-lma .eeprom=0  --no-change-warnings -O ihex "Led_Cube-10x10x10-Red-v-0-1-4.elf" "Led_Cube-10x10x10-Red-v-0-1-4.eep" || exit 0
	"C:\Program Files (x86)\Atmel\Atmel Toolchain\AVR8 GCC\Native\3.4.2.939\avr8-gnu-toolchain\bin\avr-objdump.exe" -h -S "Led_Cube-10x10x10-Red-v-0-1-4.elf" > "Led_Cube-10x10x10-Red-v-0-1-4.lss"
	"C:\Program Files (x86)\Atmel\Atmel Toolchain\AVR8 GCC\Native\3.4.2.939\avr8-gnu-toolchain\bin\avr-objcopy.exe" -O srec -R .eeprom -R .fuse -R .lock -R .signature  "Led_Cube-10x10x10-Red-v-0-1-4.elf" "Led_Cube-10x10x10-Red-v-0-1-4.srec"
	"C:\Program Files (x86)\Atmel\Atmel Toolchain\AVR8 GCC\Native\3.4.2.939\avr8-gnu-toolchain\bin\avr-size.exe" "Led_Cube-10x10x10-Red-v-0-1-4.elf"
	
	





# Other Targets
clean:
	-$(RM) $(OBJS_AS_ARGS) $(EXECUTABLES)  
	-$(RM) $(C_DEPS_AS_ARGS)   
	rm -rf "Led_Cube-10x10x10-Red-v-0-1-4.elf" "Led_Cube-10x10x10-Red-v-0-1-4.a" "Led_Cube-10x10x10-Red-v-0-1-4.hex" "Led_Cube-10x10x10-Red-v-0-1-4.lss" "Led_Cube-10x10x10-Red-v-0-1-4.eep" "Led_Cube-10x10x10-Red-v-0-1-4.map" "Led_Cube-10x10x10-Red-v-0-1-4.srec"
	