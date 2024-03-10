# TCL File Generated by Component Editor 18.1
# Mon Mar 11 03:56:44 CST 2024
# DO NOT MODIFY


# 
# cordicMulti "cordicMulti" v1.0
#  2024.03.11.03:56:44
# 
# 

# 
# request TCL package from ACDS 16.1
# 
package require -exact qsys 16.1


# 
# module cordicMulti
# 
set_module_property DESCRIPTION ""
set_module_property NAME cordicMulti
set_module_property VERSION 1.0
set_module_property INTERNAL false
set_module_property OPAQUE_ADDRESS_MAP true
set_module_property AUTHOR ""
set_module_property DISPLAY_NAME cordicMulti
set_module_property INSTANTIATE_IN_SYSTEM_MODULE true
set_module_property EDITABLE true
set_module_property REPORT_TO_TALKBACK false
set_module_property ALLOW_GREYBOX_GENERATION false
set_module_property REPORT_HIERARCHY false


# 
# file sets
# 
add_fileset QUARTUS_SYNTH QUARTUS_SYNTH "" ""
set_fileset_property QUARTUS_SYNTH TOP_LEVEL CORDIC
set_fileset_property QUARTUS_SYNTH ENABLE_RELATIVE_INCLUDE_PATHS false
set_fileset_property QUARTUS_SYNTH ENABLE_FILE_OVERWRITE_MODE false
add_fileset_file CORDIC.v VERILOG PATH IP/CORDIC/CORDIC.v TOP_LEVEL_FILE


# 
# parameters
# 
add_parameter M INTEGER 22
set_parameter_property M DEFAULT_VALUE 22
set_parameter_property M DISPLAY_NAME M
set_parameter_property M TYPE INTEGER
set_parameter_property M UNITS None
set_parameter_property M ALLOWED_RANGES -2147483648:2147483647
set_parameter_property M HDL_PARAMETER true
add_parameter W INTEGER 32
set_parameter_property W DEFAULT_VALUE 32
set_parameter_property W DISPLAY_NAME W
set_parameter_property W TYPE INTEGER
set_parameter_property W UNITS None
set_parameter_property W ALLOWED_RANGES -2147483648:2147483647
set_parameter_property W HDL_PARAMETER true
add_parameter FixedW INTEGER 27 ""
set_parameter_property FixedW DEFAULT_VALUE 27
set_parameter_property FixedW DISPLAY_NAME FixedW
set_parameter_property FixedW TYPE INTEGER
set_parameter_property FixedW UNITS None
set_parameter_property FixedW ALLOWED_RANGES -2147483648:2147483647
set_parameter_property FixedW DESCRIPTION ""
set_parameter_property FixedW HDL_PARAMETER true
add_parameter EXONENT_BITS INTEGER 8
set_parameter_property EXONENT_BITS DEFAULT_VALUE 8
set_parameter_property EXONENT_BITS DISPLAY_NAME EXONENT_BITS
set_parameter_property EXONENT_BITS TYPE INTEGER
set_parameter_property EXONENT_BITS UNITS None
set_parameter_property EXONENT_BITS ALLOWED_RANGES -2147483648:2147483647
set_parameter_property EXONENT_BITS HDL_PARAMETER true
add_parameter MANTISSA_BITS INTEGER 23
set_parameter_property MANTISSA_BITS DEFAULT_VALUE 23
set_parameter_property MANTISSA_BITS DISPLAY_NAME MANTISSA_BITS
set_parameter_property MANTISSA_BITS TYPE INTEGER
set_parameter_property MANTISSA_BITS UNITS None
set_parameter_property MANTISSA_BITS ALLOWED_RANGES -2147483648:2147483647
set_parameter_property MANTISSA_BITS HDL_PARAMETER true
add_parameter INTEGER_BITS INTEGER 2
set_parameter_property INTEGER_BITS DEFAULT_VALUE 2
set_parameter_property INTEGER_BITS DISPLAY_NAME INTEGER_BITS
set_parameter_property INTEGER_BITS TYPE INTEGER
set_parameter_property INTEGER_BITS UNITS None
set_parameter_property INTEGER_BITS ALLOWED_RANGES -2147483648:2147483647
set_parameter_property INTEGER_BITS HDL_PARAMETER true
add_parameter FRACTION_BITS INTEGER 25 ""
set_parameter_property FRACTION_BITS DEFAULT_VALUE 25
set_parameter_property FRACTION_BITS DISPLAY_NAME FRACTION_BITS
set_parameter_property FRACTION_BITS TYPE INTEGER
set_parameter_property FRACTION_BITS UNITS None
set_parameter_property FRACTION_BITS ALLOWED_RANGES -2147483648:2147483647
set_parameter_property FRACTION_BITS DESCRIPTION ""
set_parameter_property FRACTION_BITS HDL_PARAMETER true


# 
# display items
# 


# 
# connection point nios_custom_instruction_slave_1
# 
add_interface nios_custom_instruction_slave_1 nios_custom_instruction end
set_interface_property nios_custom_instruction_slave_1 clockCycle 5
set_interface_property nios_custom_instruction_slave_1 operands 1
set_interface_property nios_custom_instruction_slave_1 ENABLED true
set_interface_property nios_custom_instruction_slave_1 EXPORT_OF ""
set_interface_property nios_custom_instruction_slave_1 PORT_NAME_MAP ""
set_interface_property nios_custom_instruction_slave_1 CMSIS_SVD_VARIABLES ""
set_interface_property nios_custom_instruction_slave_1 SVD_ADDRESS_GROUP ""

add_interface_port nios_custom_instruction_slave_1 dataa dataa Input W
add_interface_port nios_custom_instruction_slave_1 rst reset Input 1
add_interface_port nios_custom_instruction_slave_1 result result Output W
add_interface_port nios_custom_instruction_slave_1 clk clk Input 1

