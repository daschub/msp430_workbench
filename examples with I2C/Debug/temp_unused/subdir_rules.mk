################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
temp_unused/functions.obj: ../temp_unused/functions.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: MSP430 Compiler'
	"C:/ti/ccsv8/tools/compiler/ti-cgt-msp430_18.1.5.LTS/bin/cl430" -vmspx --data_model=restricted --use_hw_mpy=F5 --advice:power="all" --define=__MSP430F5529__ -g --printf_support=full --diag_suppress=169 --diag_suppress=179 --diag_suppress=515 --diag_suppress=2580 --diag_warning=225 --diag_wrap=off --display_error_number --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU23 --silicon_errata=CPU40 --preproc_with_compile --preproc_dependency="temp_unused/functions.d_raw" --obj_directory="temp_unused" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


