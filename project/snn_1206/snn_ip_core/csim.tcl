############################################################
# Vitis HLS C Simulation TCL Script
# For SNN IP Core Functional Verification
############################################################

puts "=========================================="
puts "SNN IP Core - C Simulation"
puts "=========================================="

# Create project if it doesn't exist, otherwise open it
set project_exists [file exists snn_ip_project]

if {$project_exists} {
    puts "Opening existing project..."
    open_project snn_ip_project
} else {
    puts "Creating new project..."
    open_project -reset snn_ip_project

    # Set top function
    set_top snn_ip

    # Add design files
    puts "Adding design files..."
    add_files snn_ip.cpp -cflags "-std=c++11 -I."
    add_files snn_ip.h -cflags "-std=c++11 -I."
    add_files snn_weights.h -cflags "-std=c++11 -I."

    # Add testbench files
    puts "Adding testbench files..."
    add_files -tb testbench.cpp -cflags "-std=c++11 -I."
}

# Create or open solution
set solution_exists [file exists snn_ip_project/solution1]

if {$solution_exists} {
    puts "Opening existing solution..."
    open_solution solution1
} else {
    puts "Creating new solution..."
    open_solution -reset solution1

    # Set target device (Zynq-7020)
    set_part {xc7z020clg400-1}

    # Set clock period (10ns = 100MHz)
    create_clock -period 10 -name default
}

############################################################
# Run C Simulation
############################################################
puts ""
puts "=========================================="
puts "Running C Simulation..."
puts "=========================================="
puts "This may take several minutes..."
puts ""

# Run C simulation with clean build
# Options:
#   -clean: Clean previous build
#   -argv: Pass arguments to testbench (if needed)
csim_design -clean

puts ""
puts "=========================================="
puts "C Simulation Complete!"
puts "=========================================="
puts ""
puts "Check the output above for test results."
puts ""
puts "Simulation artifacts are in:"
puts "  snn_ip_project/solution1/csim/"
puts ""

# Don't exit automatically so user can see the results
# exit
