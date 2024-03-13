transcript on
if {[file exists rtl_work]} {
	vdel -lib rtl_work -all
}
vlib rtl_work
vmap work rtl_work

vlog -vlog01compat -work work +incdir+C:/Users/linmo/Desktop/DSD/test/system_template_de1_soc/IP/CORDIC {C:/Users/linmo/Desktop/DSD/test/system_template_de1_soc/IP/CORDIC/CORDIC.v}
vlog -vlog01compat -work work +incdir+C:/Users/linmo/Desktop/DSD/test/system_template_de1_soc/IP/fp_sub {C:/Users/linmo/Desktop/DSD/test/system_template_de1_soc/IP/fp_sub/fp_subtractor.v}
vlog -vlog01compat -work work +incdir+C:/Users/linmo/Desktop/DSD/test/system_template_de1_soc/IP/fp_mul {C:/Users/linmo/Desktop/DSD/test/system_template_de1_soc/IP/fp_mul/fp_multiplier.v}
vlog -vlog01compat -work work +incdir+C:/Users/linmo/Desktop/DSD/test/system_template_de1_soc/IP/fp_add {C:/Users/linmo/Desktop/DSD/test/system_template_de1_soc/IP/fp_add/fp_adder.v}
vlog -vlog01compat -work work +incdir+C:/Users/linmo/Desktop/DSD/test/system_template_de1_soc/IP/FX {C:/Users/linmo/Desktop/DSD/test/system_template_de1_soc/IP/FX/FX.v}
vlog -vlog01compat -work work +incdir+C:/Users/linmo/Desktop/DSD/test/system_template_de1_soc/IP/FX/db {C:/Users/linmo/Desktop/DSD/test/system_template_de1_soc/IP/FX/db/mult_6ct.v}

vlog -vlog01compat -work work +incdir+C:/Users/linmo/Desktop/DSD/test/system_template_de1_soc/IP/FX {C:/Users/linmo/Desktop/DSD/test/system_template_de1_soc/IP/FX/testbench_1.v}

vsim -t 1ps -L altera_ver -L lpm_ver -L sgate_ver -L altera_mf_ver -L altera_lnsim_ver -L cyclonev_ver -L cyclonev_hssi_ver -L cyclonev_pcie_hip_ver -L rtl_work -L work -voptargs="+acc"  tb

add wave *
view structure
view signals
run -all
