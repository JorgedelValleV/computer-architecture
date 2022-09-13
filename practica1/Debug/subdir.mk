################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../arit-ent.c \
../arit-float.c \
../caracteres.c \
../casting.c \
../enteros.c \
../flotante.c \
../tipos-estru.c 

S_UPPER_SRCS += \
../main.S 

OBJS += \
./arit-ent.o \
./arit-float.o \
./caracteres.o \
./casting.o \
./enteros.o \
./flotante.o \
./main.o \
./tipos-estru.o 

C_DEPS += \
./arit-ent.d \
./arit-float.d \
./caracteres.d \
./casting.d \
./enteros.d \
./flotante.d \
./tipos-estru.d 

S_UPPER_DEPS += \
./main.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Sourcery Windows GCC C Compiler'
	arm-none-eabi-gcc -O0 -Wall -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -mapcs-frame -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -mcpu=arm7tdmi -g3 -gdwarf-2 -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

%.o: ../%.S
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Sourcery Windows GCC Assembler'
	arm-none-eabi-gcc -x assembler-with-cpp -Wall -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -mcpu=arm7tdmi -g3 -gdwarf-2 -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


