################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Card.cpp \
../src/Deck.cpp \
../src/Lab13.cpp \
../src/TerminalPlayer.cpp 

OBJS += \
./src/Card.o \
./src/Deck.o \
./src/Lab13.o \
./src/TerminalPlayer.o 

CPP_DEPS += \
./src/Card.d \
./src/Deck.d \
./src/Lab13.d \
./src/TerminalPlayer.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


