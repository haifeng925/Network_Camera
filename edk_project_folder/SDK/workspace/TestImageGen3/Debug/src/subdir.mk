################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/camera_tools.c \
../src/helloworld.c \
../src/network_tools.c \
../src/platform.c 

LD_SRCS += \
../src/lscript.ld 

OBJS += \
./src/camera_tools.o \
./src/helloworld.o \
./src/network_tools.o \
./src/platform.o 

C_DEPS += \
./src/camera_tools.d \
./src/helloworld.d \
./src/network_tools.d \
./src/platform.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo Building file: $<
	@echo Invoking: MicroBlaze gcc compiler
	mb-gcc -Wall -O0 -g3 -c -fmessage-length=0 -Wl,--no-relax -I../../TestImageGen3_bsp/microblaze_0/include -mxl-barrel-shift -mxl-pattern-compare -mcpu=v8.40.b -mno-xl-soft-mul -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo Finished building: $<
	@echo ' '

