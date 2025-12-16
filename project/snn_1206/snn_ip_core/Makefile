############################################################
# Makefile for SNN IP Core
# Vitis HLS Project Build Automation
############################################################

# Project settings
PROJECT_NAME = snn_ip_project
TOP_FUNCTION = snn_ip
SOLUTION = solution1

# Vitis HLS settings
VITIS_HLS = vitis_hls
VIVADO = vivado

# Source files
SOURCES = snn_ip.cpp snn_ip.h snn_weights.h
TESTBENCH = testbench.cpp
TCL_SCRIPT = run_hls.tcl

# Python settings
PYTHON = python3
WEIGHT_SCRIPT = export_weights.py
MODEL_FILE = lightweight_snn.pth
WEIGHT_HEADER = snn_weights.h

# Directories
REPORT_DIR = $(PROJECT_NAME)/$(SOLUTION)/syn/report
IP_DIR = $(PROJECT_NAME)/$(SOLUTION)/impl/ip
CSIM_DIR = $(PROJECT_NAME)/$(SOLUTION)/csim/build

# Colors for output
BLUE = \033[0;34m
GREEN = \033[0;32m
YELLOW = \033[0;33m
RED = \033[0;31m
NC = \033[0m # No Color

############################################################
# Targets
############################################################

.PHONY: all clean weights hls csim csynth export help check view_report

# Default target
all: weights hls

# Extract weights from PyTorch model
weights:
	@echo "$(BLUE)=========================================$(NC)"
	@echo "$(BLUE)Extracting weights from PyTorch model...$(NC)"
	@echo "$(BLUE)=========================================$(NC)"
	@if [ ! -f $(MODEL_FILE) ]; then \
		echo "$(RED)Error: Model file $(MODEL_FILE) not found!$(NC)"; \
		exit 1; \
	fi
	$(PYTHON) $(WEIGHT_SCRIPT)
	@echo "$(GREEN)✓ Weight extraction complete!$(NC)"

# Run full HLS flow (C sim + synthesis + export)
hls: check
	@echo "$(BLUE)=========================================$(NC)"
	@echo "$(BLUE)Running Vitis HLS synthesis...$(NC)"
	@echo "$(BLUE)=========================================$(NC)"
	$(VITIS_HLS) $(TCL_SCRIPT)
	@echo "$(GREEN)✓ HLS synthesis complete!$(NC)"
	@$(MAKE) summary

# Run C simulation only
csim: check
	@echo "$(BLUE)=========================================$(NC)"
	@echo "$(BLUE)Running C simulation...$(NC)"
	@echo "$(BLUE)=========================================$(NC)"
	@echo "$(YELLOW)This may take 10-30 minutes...$(NC)"
	$(VITIS_HLS) -f csim.tcl 2>&1 | tee csim_run.log
	@echo "$(GREEN)✓ C simulation complete!$(NC)"
	@echo "$(YELLOW)Log saved to: csim_run.log$(NC)"

# Run C synthesis only
csynth: check
	@echo "$(BLUE)=========================================$(NC)"
	@echo "$(BLUE)Running C synthesis...$(NC)"
	@echo "$(BLUE)=========================================$(NC)"
	$(VITIS_HLS) -f csynth_only.tcl
	@echo "$(GREEN)✓ C synthesis complete!$(NC)"

# Export IP only
export: check
	@echo "$(BLUE)=========================================$(NC)"
	@echo "$(BLUE)Exporting IP...$(NC)"
	@echo "$(BLUE)=========================================$(NC)"
	$(VITIS_HLS) -f export_only.tcl
	@echo "$(GREEN)✓ IP export complete!$(NC)"

# Check prerequisites
check:
	@echo "$(YELLOW)Checking prerequisites...$(NC)"
	@if [ ! -f $(WEIGHT_HEADER) ]; then \
		echo "$(RED)Error: $(WEIGHT_HEADER) not found!$(NC)"; \
		echo "$(YELLOW)Run 'make weights' first$(NC)"; \
		exit 1; \
	fi
	@for file in $(SOURCES) $(TESTBENCH); do \
		if [ ! -f $$file ]; then \
			echo "$(RED)Error: $$file not found!$(NC)"; \
			exit 1; \
		fi \
	done
	@echo "$(GREEN)✓ All prerequisites OK$(NC)"

# View synthesis report
view_report:
	@if [ -f $(REPORT_DIR)/$(TOP_FUNCTION)_csynth.rpt ]; then \
		cat $(REPORT_DIR)/$(TOP_FUNCTION)_csynth.rpt; \
	else \
		echo "$(RED)Error: Report not found. Run synthesis first.$(NC)"; \
	fi

# Summary of results
summary:
	@echo ""
	@echo "$(GREEN)=========================================$(NC)"
	@echo "$(GREEN)Build Summary$(NC)"
	@echo "$(GREEN)=========================================$(NC)"
	@echo "$(YELLOW)Project:$(NC) $(PROJECT_NAME)"
	@echo "$(YELLOW)Top Function:$(NC) $(TOP_FUNCTION)"
	@echo ""
	@echo "$(YELLOW)Generated Files:$(NC)"
	@if [ -d $(REPORT_DIR) ]; then \
		echo "  Reports:  $(REPORT_DIR)/"; \
	fi
	@if [ -d $(IP_DIR) ]; then \
		echo "  IP Core:  $(IP_DIR)/"; \
	fi
	@echo ""
	@if [ -f $(REPORT_DIR)/$(TOP_FUNCTION)_csynth.rpt ]; then \
		echo "$(YELLOW)Key Metrics (from synthesis report):$(NC)"; \
		grep -A 2 "Latency" $(REPORT_DIR)/$(TOP_FUNCTION)_csynth.rpt 2>/dev/null || true; \
		echo ""; \
		grep -A 10 "Utilization Estimates" $(REPORT_DIR)/$(TOP_FUNCTION)_csynth.rpt 2>/dev/null || true; \
	fi
	@echo "$(GREEN)=========================================$(NC)"

# Clean build artifacts
clean:
	@echo "$(YELLOW)Cleaning build artifacts...$(NC)"
	rm -rf $(PROJECT_NAME)
	rm -f vitis_hls.log
	rm -f *.log
	@echo "$(GREEN)✓ Clean complete$(NC)"

# Clean everything including generated weights
distclean: clean
	@echo "$(YELLOW)Cleaning all generated files...$(NC)"
	rm -f $(WEIGHT_HEADER)
	@echo "$(GREEN)✓ Deep clean complete$(NC)"

# Help
help:
	@echo "$(BLUE)=========================================$(NC)"
	@echo "$(BLUE)SNN IP Core Makefile$(NC)"
	@echo "$(BLUE)=========================================$(NC)"
	@echo ""
	@echo "$(YELLOW)Available targets:$(NC)"
	@echo "  $(GREEN)all$(NC)          - Extract weights and run HLS (default)"
	@echo "  $(GREEN)weights$(NC)      - Extract weights from PyTorch model"
	@echo "  $(GREEN)hls$(NC)          - Run full HLS flow (csim + synthesis + export)"
	@echo "  $(GREEN)csim$(NC)         - Run C simulation only"
	@echo "  $(GREEN)csynth$(NC)       - Run C synthesis only"
	@echo "  $(GREEN)export$(NC)       - Export IP only"
	@echo "  $(GREEN)view_report$(NC)  - Display synthesis report"
	@echo "  $(GREEN)summary$(NC)      - Show build summary"
	@echo "  $(GREEN)check$(NC)        - Check prerequisites"
	@echo "  $(GREEN)clean$(NC)        - Remove build artifacts"
	@echo "  $(GREEN)distclean$(NC)    - Remove all generated files"
	@echo "  $(GREEN)help$(NC)         - Show this help message"
	@echo ""
	@echo "$(YELLOW)Examples:$(NC)"
	@echo "  make weights      # Extract weights only"
	@echo "  make hls          # Run full HLS synthesis"
	@echo "  make csim         # Test with C simulation"
	@echo "  make clean        # Clean project"
	@echo ""

# Create simplified TCL scripts for individual steps
csim_only.tcl:
	@echo "open_project $(PROJECT_NAME)" > $@
	@echo "set_top $(TOP_FUNCTION)" >> $@
	@echo "add_files snn_ip.cpp" >> $@
	@echo "add_files -tb testbench.cpp" >> $@
	@echo "open_solution $(SOLUTION)" >> $@
	@echo "csim_design" >> $@
	@echo "exit" >> $@

csynth_only.tcl:
	@echo "open_project $(PROJECT_NAME)" > $@
	@echo "set_top $(TOP_FUNCTION)" >> $@
	@echo "open_solution $(SOLUTION)" >> $@
	@echo "csynth_design" >> $@
	@echo "exit" >> $@

export_only.tcl:
	@echo "open_project $(PROJECT_NAME)" > $@
	@echo "open_solution $(SOLUTION)" >> $@
	@echo "export_design -rtl verilog -format ip_catalog" >> $@
	@echo "exit" >> $@
