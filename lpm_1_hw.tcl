# TCL File Generated by Component Editor 18.1
# Sat Feb 17 01:08:16 CST 2024
# DO NOT MODIFY


# 
# lpm_1 "lpm_1" v1.0
#  2024.02.17.01:08:16
# 
# 

# 
# request TCL package from ACDS 16.1
# 
package require -exact qsys 16.1


# 
# module lpm_1
# 
set_module_property DESCRIPTION ""
set_module_property NAME lpm_1
set_module_property VERSION 1.0
set_module_property INTERNAL false
set_module_property OPAQUE_ADDRESS_MAP true
set_module_property AUTHOR ""
set_module_property DISPLAY_NAME lpm_1
set_module_property INSTANTIATE_IN_SYSTEM_MODULE true
set_module_property EDITABLE true
set_module_property REPORT_TO_TALKBACK false
set_module_property ALLOW_GREYBOX_GENERATION false
set_module_property REPORT_HIERARCHY false


# 
# file sets
# 
add_fileset QUARTUS_SYNTH QUARTUS_SYNTH "" ""
set_fileset_property QUARTUS_SYNTH TOP_LEVEL lpm
set_fileset_property QUARTUS_SYNTH ENABLE_RELATIVE_INCLUDE_PATHS false
set_fileset_property QUARTUS_SYNTH ENABLE_FILE_OVERWRITE_MODE false
add_fileset_file lpm_1.v VERILOG PATH ip/IP/fixed_mul/lpm_1.v TOP_LEVEL_FILE


# 
# parameters
# 


# 
# display items
# 

