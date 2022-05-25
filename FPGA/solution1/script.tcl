############################################################
## This file is generated automatically by Vivado HLS.
## Please DO NOT edit it.
## Copyright (C) 1986-2019 Xilinx, Inc. All Rights Reserved.
############################################################
open_project FPGA
add_files FPGA/.settings/utils.hpp
add_files FPGA/.settings/mutual_info.hpp
add_files FPGA/.settings/mutual_info.cpp
add_files FPGA/.settings/histogram.h
add_files FPGA/.settings/entropy.h
add_files -tb FPGA/.settings/testbench.cpp -cflags "-Wno-unknown-pragmas" -csimflags "-Wno-unknown-pragmas"
open_solution "solution1"
set_part {xczu7ev-ffvc1156-2-e}
create_clock -period 10 -name default
#source "./FPGA/solution1/directives.tcl"
csim_design -clean
csynth_design
cosim_design
export_design -format ip_catalog
