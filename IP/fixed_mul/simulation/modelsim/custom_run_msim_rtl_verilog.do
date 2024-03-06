transcript on
if {[file exists rtl_work]} {
	vdel -lib rtl_work -all
}
vlib rtl_work
vmap work rtl_work

vlog -vlog01compat -work work +incdir+D:/DSD_coursework/mul {D:/DSD_coursework/mul/lpm_1.v}
vlog -vlog01compat -work work +incdir+D:/DSD_coursework/mul/db {D:/DSD_coursework/mul/db/mult_b8n.v}

vlog -vlog01compat -work work +incdir+D:/DSD_coursework/mul {D:/DSD_coursework/mul/testbench_1.v}

vsim -t 1ps -L altera_ver -L lpm_ver -L sgate_ver -L altera_mf_ver -L altera_lnsim_ver -L cyclonev_ver -L cyclonev_hssi_ver -L cyclonev_pcie_hip_ver -L rtl_work -L work -voptargs="+acc"  tb

add wave *
view structure
view signals
run -all
