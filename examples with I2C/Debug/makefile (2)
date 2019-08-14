################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

CG_TOOL_ROOT := C:/ti/ccsv8/tools/compiler/ti-cgt-msp430_18.1.5.LTS

GEN_OPTS__FLAG := 
GEN_CMDS__FLAG := 

ORDERED_OBJS += \
"./main.obj" \
"./sources/catchUnwantedInterrupts.obj" \
"./sources/clock.obj" \
"./sources/concole.obj" \
"./sources/functions.obj" \
"./sources/handler.obj" \
"./sources/i2c.obj" \
"./sources/rtc.obj" \
"./sources/timer.obj" \
"./sources/uart.obj" \
"../lnk_msp430f5529.cmd" \
$(GEN_CMDS__FLAG) \
-llibmath.a \
-llibc.a \

-include ../makefile.init

RM := DEL /F
RMDIR := RMDIR /S/Q

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include headers/subdir_vars.mk
-include sources/subdir_vars.mk
-include subdir_rules.mk
-include headers/subdir_rules.mk
-include sources/subdir_rules.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C55_DEPS)),)
-include $(C55_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(S67_DEPS)),)
-include $(S67_DEPS)
endif
ifneq ($(strip $(S62_DEPS)),)
-include $(S62_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(OPT_DEPS)),)
-include $(OPT_DEPS)
endif
ifneq ($(strip $(C??_DEPS)),)
-include $(C??_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(S??_DEPS)),)
-include $(S??_DEPS)
endif
ifneq ($(strip $(C64_DEPS)),)
-include $(C64_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(S64_DEPS)),)
-include $(S64_DEPS)
endif
ifneq ($(strip $(INO_DEPS)),)
-include $(INO_DEPS)
endif
ifneq ($(strip $(CLA_DEPS)),)
-include $(CLA_DEPS)
endif
ifneq ($(strip $(S55_DEPS)),)
-include $(S55_DEPS)
endif
ifneq ($(strip $(SV7A_DEPS)),)
-include $(SV7A_DEPS)
endif
ifneq ($(strip $(C62_DEPS)),)
-include $(C62_DEPS)
endif
ifneq ($(strip $(C67_DEPS)),)
-include $(C67_DEPS)
endif
ifneq ($(strip $(PDE_DEPS)),)
-include $(PDE_DEPS)
endif
ifneq ($(strip $(K_DEPS)),)
-include $(K_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C43_DEPS)),)
-include $(C43_DEPS)
endif
ifneq ($(strip $(S43_DEPS)),)
-include $(S43_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(SA_DEPS)),)
-include $(SA_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXE_OUTPUTS += \
Uebung9_I2C.out \

EXE_OUTPUTS__QUOTED += \
"Uebung9_I2C.out" \

BIN_OUTPUTS += \
Uebung9_I2C.hex \

BIN_OUTPUTS__QUOTED += \
"Uebung9_I2C.hex" \


# All Target
all: $(OBJS) $(CMD_SRCS) $(GEN_CMDS)
	@$(MAKE) --no-print-directory -Onone "Uebung9_I2C.out"

# Tool invocations
Uebung9_I2C.out: $(OBJS) $(CMD_SRCS) $(GEN_CMDS)
	@echo 'Building target: "$@"'
	@echo 'Invoking: MSP430 Linker'
	"C:/ti/ccsv8/tools/compiler/ti-cgt-msp430_18.1.5.LTS/bin/cl430" -vmspx --data_model=restricted --use_hw_mpy=F5 --advice:power="all" --define=__MSP430F5529__ -g --printf_support=full --diag_suppress=169 --diag_suppress=2170 --diag_suppress=179 --diag_suppress=515 --diag_suppress=2580 --diag_warning=225 --diag_wrap=off --display_error_number --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU23 --silicon_errata=CPU40 -z -m"Uebung9_I2C.map" --heap_size=160 --stack_size=160 --cinit_hold_wdt=on -i"C:/ti/ccsv8/ccs_base/msp430/include" -i"C:/ti/ccsv8/ccs_base/msp430/lib/5xx_6xx_FRxx" -i"C:/ti/ccsv8/tools/compiler/ti-cgt-msp430_18.1.5.LTS/lib" -i"C:/ti/ccsv8/tools/compiler/ti-cgt-msp430_18.1.5.LTS/include" --reread_libs --diag_wrap=off --display_error_number --warn_sections --xml_link_info="Uebung9_I2C_linkInfo.xml" --use_hw_mpy=F5 --rom_model -o "Uebung9_I2C.out" $(ORDERED_OBJS)
	@echo 'Finished building target: "$@"'
	@echo ' '

Uebung9_I2C.hex: $(EXE_OUTPUTS)
	@echo 'Building files: $(strip $(EXE_OUTPUTS__QUOTED))'
	@echo 'Invoking: MSP430 Hex Utility'
	"C:/ti/ccsv8/tools/compiler/ti-cgt-msp430_18.1.5.LTS/bin/hex430" --memwidth=8 --romwidth=8 -o "Uebung9_I2C.hex" $(EXE_OUTPUTS__QUOTED)
	@echo 'Finished building: $(strip $(EXE_OUTPUTS__QUOTED))'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(BIN_OUTPUTS__QUOTED)$(EXE_OUTPUTS__QUOTED)
	-$(RM) "main.obj" "sources\catchUnwantedInterrupts.obj" "sources\clock.obj" "sources\concole.obj" "sources\functions.obj" "sources\handler.obj" "sources\i2c.obj" "sources\rtc.obj" "sources\timer.obj" "sources\uart.obj" 
	-$(RM) "main.d" "sources\catchUnwantedInterrupts.d" "sources\clock.d" "sources\concole.d" "sources\functions.d" "sources\handler.d" "sources\i2c.d" "sources\rtc.d" "sources\timer.d" "sources\uart.d" 
	-@echo 'Finished clean'
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

