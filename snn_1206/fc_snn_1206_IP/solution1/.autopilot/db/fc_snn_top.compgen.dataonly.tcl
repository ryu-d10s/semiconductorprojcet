# This script segment is generated automatically by AutoPilot

set axilite_register_dict [dict create]
set port_CTRL {
ap_start { }
ap_done { }
ap_ready { }
ap_idle { }
n_steps { 
	dir I
	width 32
	depth 1
	mode ap_none
	offset 16
	offset_end 23
}
clear_state { 
	dir I
	width 1
	depth 1
	mode ap_none
	offset 24
	offset_end 31
}
}
dict set axilite_register_dict CTRL $port_CTRL


