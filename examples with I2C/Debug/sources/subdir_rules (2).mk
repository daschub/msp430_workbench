################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
sources/catchUnwantedInterrupts.obj: ../sources/catchUnwantedInterrupts.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: MSP430 Compiler'
	"C:/ti/ccsv8/tools/compiler/ti-cgt-msp430_18.1.5.LTS/bin/cl430" -vmspx --data_model=restricted --use_hw_mpy=F5 --include_path="C:/ti/ccsv8/ccs_base/msp430/include" --include_path="Q:/Praktikum/Praktikum - Mikrocontroller/Workspace/Uebung9_I2C" --include_path="C:/ti/ccsv8/tools/compiler/ti-cgt-msp430_18.1.5.LTS/include" --advice:power="all" --define=__MSP430F5529__ -g --printf_support=full --diag_suppress=169 --diag_suppress=2170 --diag_suppress=179 --diag_suppress=515 --diag_suppress=2580 --diag_warning=225 --diag_wrap=off --display_error_number --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU23 --silicon_errata=CPU40 --preproc_with_compile --preproc_dependency="sources/catchUnwantedInterrupts.d_raw" --obj_directory="sources" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

sources/clock.obj: ../sources/clock.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: MSP430 Compiler'
	"C:/ti/ccsv8/tools/compiler/ti-cgt-msp430_18.1.5.LTS/bin/cl430" -vmspx --data_model=restricted --use_hw_mpy=F5 --include_path="C:/ti/ccsv8/ccs_base/msp430/include" --include_path="Q:/Praktikum/Praktikum - Mikrocontroller/Workspace/Uebung9_I2C" --include_path="C:/ti/ccsv8/tools/compiler/ti-cgt-msp430_18.1.5.LTS/include" --advice:power="all" --define=__MSP430F5529__ -g --printf_support=full --diag_suppress=169 --diag_suppress=2170 --diag_suppress=179 --diag_suppress=515 --diag_suppress=2580 --diag_warning=225 --diag_wrap=off --display_error_number --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU23 --silicon_errata=CPU40 --preproc_with_compile --preproc_dependency="sources/clock.d_raw" --obj_directory="sources" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

sources/concole.obj: ../sources/concole.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: MSP430 Compiler'
	"C:/ti/ccsv8/tools/compiler/ti-cgt-msp430_18.1.5.LTS/bin/cl430" -vmspx --data_model=restricted --use_hw_mpy=F5 --include_path="C:/ti/ccsv8/ccs_base/msp430/include" --include_path="Q:/Praktikum/Praktikum - Mikrocontroller/Workspace/Uebung9_I2C" --include_path="C:/ti/ccsv8/tools/compiler/ti-cgt-msp430_18.1.5.LTS/include" --advice:power="all" --define=__MSP430F5529__ -g --printf_support=full --diag_suppress=169 --diag_suppress=2170 --diag_suppress=179 --diag_suppress=515 --diag_suppress=2580 --diag_warning=225 --diag_wrap=off --display_error_number --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU23 --silicon_errata=CPU40 --preproc_with_compile --preproc_dependency="sources/concole.d_raw" --obj_directory="sources" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

sources/functions.obj: ../sources/functions.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: MSP430 Compiler'
	"C:/ti/ccsv8/tools/compiler/ti-cgt-msp430_18.1.5.LTS/bin/cl430" -vmspx --data_model=restricted --use_hw_mpy=F5 --include_path="C:/ti/ccsv8/ccs_base/msp430/include" --include_path="Q:/Praktikum/Praktikum - Mikrocontroller/Workspace/Uebung9_I2C" --include_path="C:/ti/ccsv8/tools/compiler/ti-cgt-msp430_18.1.5.LTS/include" --advice:power="all" --define=__MSP430F5529__ -g --printf_support=full --diag_suppress=169 --diag_suppress=2170 --diag_suppress=179 --diag_suppress=515 --diag_suppress=2580 --diag_warning=225 --diag_wrap=off --display_error_number --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU23 --silicon_errata=CPU40 --preproc_with_compile --preproc_dependency="sources/functions.d_raw" --obj_directory="sources" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

sources/handler.obj: ../sources/handler.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: MSP430 Compiler'
	"C:/ti/ccsv8/tools/compiler/ti-cgt-msp430_18.1.5.LTS/bin/cl430" -vmspx --data_model=restricted --use_hw_mpy=F5 --include_path="C:/ti/ccsv8/ccs_base/msp430/include" --include_path="Q:/Praktikum/Praktikum - Mikrocontroller/Workspace/Uebung9_I2C" --include_path="C:/ti/ccsv8/tools/compiler/ti-cgt-msp430_18.1.5.LTS/include" --advice:power="all" --define=__MSP430F5529__ -g --printf_support=full --diag_suppress=169 --diag_suppress=2170 --diag_suppress=179 --diag_suppress=515 --diag_suppress=2580 --diag_warning=225 --diag_wrap=off --display_error_number --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU23 --silicon_errata=CPU40 --preproc_with_compile --preproc_dependency="sources/handler.d_raw" --obj_directory="sources" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

sources/i2c.obj: ../sources/i2c.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: MSP430 Compiler'
	"C:/ti/ccsv8/tools/compiler/ti-cgt-msp430_18.1.5.LTS/bin/cl430" -vmspx --data_model=restricted --use_hw_mpy=F5 --include_path="C:/ti/ccsv8/ccs_base/msp430/include" --include_path="Q:/Praktikum/Praktikum - Mikrocontroller/Workspace/Uebung9_I2C" --include_path="C:/ti/ccsv8/tools/compiler/ti-cgt-msp430_18.1.5.LTS/include" --advice:power="all" --define=__MSP430F5529__ -g --printf_support=full --diag_suppress=169 --diag_suppress=2170 --diag_suppress=179 --diag_suppress=515 --diag_suppress=2580 --diag_warning=225 --diag_wrap=off --display_error_number --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU23 --silicon_errata=CPU40 --preproc_with_compile --preproc_dependency="sources/i2c.d_raw" --obj_directory="sources" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

sources/rtc.obj: ../sources/rtc.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: MSP430 Compiler'
	"C:/ti/ccsv8/tools/compiler/ti-cgt-msp430_18.1.5.LTS/bin/cl430" -vmspx --data_model=restricted --use_hw_mpy=F5 --include_path="C:/ti/ccsv8/ccs_base/msp430/include" --include_path="Q:/Praktikum/Praktikum - Mikrocontroller/Workspace/Uebung9_I2C" --include_path="C:/ti/ccsv8/tools/compiler/ti-cgt-msp430_18.1.5.LTS/include" --advice:power="all" --define=__MSP430F5529__ -g --printf_support=full --diag_suppress=169 --diag_suppress=2170 --diag_suppress=179 --diag_suppress=515 --diag_suppress=2580 --diag_warning=225 --diag_wrap=off --display_error_number --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU23 --silicon_errata=CPU40 --preproc_with_compile --preproc_dependency="sources/rtc.d_raw" --obj_directory="sources" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

sources/timer.obj: ../sources/timer.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: MSP430 Compiler'
	"C:/ti/ccsv8/tools/compiler/ti-cgt-msp430_18.1.5.LTS/bin/cl430" -vmspx --data_model=restricted --use_hw_mpy=F5 --include_path="C:/ti/ccsv8/ccs_base/msp430/include" --include_path="Q:/Praktikum/Praktikum - Mikrocontroller/Workspace/Uebung9_I2C" --include_path="C:/ti/ccsv8/tools/compiler/ti-cgt-msp430_18.1.5.LTS/include" --advice:power="all" --define=__MSP430F5529__ -g --printf_support=full --diag_suppress=169 --diag_suppress=2170 --diag_suppress=179 --diag_suppress=515 --diag_suppress=2580 --diag_warning=225 --diag_wrap=off --display_error_number --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU23 --silicon_errata=CPU40 --preproc_with_compile --preproc_dependency="sources/timer.d_raw" --obj_directory="sources" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

sources/uart.obj: ../sources/uart.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: MSP430 Compiler'
	"C:/ti/ccsv8/tools/compiler/ti-cgt-msp430_18.1.5.LTS/bin/cl430" -vmspx --data_model=restricted --use_hw_mpy=F5 --include_path="C:/ti/ccsv8/ccs_base/msp430/include" --include_path="Q:/Praktikum/Praktikum - Mikrocontroller/Workspace/Uebung9_I2C" --include_path="C:/ti/ccsv8/tools/compiler/ti-cgt-msp430_18.1.5.LTS/include" --advice:power="all" --define=__MSP430F5529__ -g --printf_support=full --diag_suppress=169 --diag_suppress=2170 --diag_suppress=179 --diag_suppress=515 --diag_suppress=2580 --diag_warning=225 --diag_wrap=off --display_error_number --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU23 --silicon_errata=CPU40 --preproc_with_compile --preproc_dependency="sources/uart.d_raw" --obj_directory="sources" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


