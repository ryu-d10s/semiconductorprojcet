# Lightweight SNN IP Core for Vitis HLS

Spiking Neural Network (SNN) IP core implementation for Xilinx Zynq-7000 FPGAs using Vitis HLS.

## 📁 Project Structure

```
light_snn/
├── snn_ip.h              # IP core header file
├── snn_ip.cpp            # IP core implementation
├── snn_weights.h         # Neural network weights (auto-generated)
├── testbench.cpp         # C testbench
├── run_hls.tcl           # Vitis HLS synthesis script
├── export_weights.py     # Weight extraction script
├── lightweight_snn.pth   # PyTorch trained model
└── README.md             # This file
```

## 🔧 Requirements

- Vitis HLS 2020.2 or later
- Python 3.x with PyTorch (for weight extraction)
- Target Device: Xilinx Zynq-7020 (xc7z020clg400-1)

## 🚀 Quick Start

### 1. Extract Weights from PyTorch Model

```bash
python3 export_weights.py
```

This will generate `snn_weights.h` containing all network weights.

### 2. Run C Simulation (Recommended First Step)

```bash
# Method 1: Using TCL script
vitis_hls -f csim.tcl

# Method 2: Using Makefile
make csim

# Method 3: Using shell script
./run_csim.sh
```

This will verify the functionality with 9 test patterns. See [CSIM_README.md](CSIM_README.md) for detailed guide.

### 3. Run Full HLS Synthesis

```bash
# Run C synthesis and export IP
vitis_hls run_hls.tcl

# Or using Makefile
make hls
```

This will:
- Run C simulation
- Perform C synthesis
- Export RTL as IP catalog

### 4. Check Results

Reports are generated in:
```
snn_ip_project/solution1/syn/report/
```

IP package exported to:
```
snn_ip_project/solution1/impl/ip/
```

## 📊 Network Architecture

| Layer | Type | Input | Output | Kernel | Stride |
|-------|------|-------|--------|--------|--------|
| Conv1 | Conv2D + MaxPool | 64×64×1 | 31×31×16 | 3×3 | 1 |
| Conv2 | Conv2D + MaxPool | 31×31×16 | 14×14×32 | 3×3 | 1 |
| Conv3 | Conv2D + MaxPool | 14×14×32 | 6×6×64 | 3×3 | 1 |
| FC1 | Fully Connected | 2304 | 256 | - | - |
| FC2 | Fully Connected | 256 | 10 | - | - |

**Total Parameters:** 1,074,320

## 🧠 SNN Features

### LIF Neuron Model
- **Threshold:** 1.0
- **Decay:** 0.9
- **Reset Potential:** 0.0
- **Timesteps:** 10

### Spike-based Computation
- Each layer uses Leaky Integrate-and-Fire (LIF) neurons
- Spike trains propagate through the network
- Output determined by spike count over timesteps

## 💻 IP Interface

### AXI4-Lite Interface

```cpp
void snn_ip(
    pixel_t image[64][64],    // Input: 64×64 grayscale image (0-255)
    int* output_class,        // Output: Predicted class (0-9)
    bool* done                // Output: Processing complete flag
);
```

### Interface Signals
- `image`: Input image buffer (AXI4-Lite)
- `output_class`: Classification result (AXI4-Lite)
- `done`: Completion flag (AXI4-Lite)

## ⚙️ HLS Optimizations

### Pipeline Directives
- Loop pipelining with II=1 for throughput
- Function inlining for LIF neurons

### Array Partitioning
- Output spike counters completely partitioned
- Internal buffers optimized for memory bandwidth

### Resource Usage
See synthesis report for:
- BRAM utilization
- DSP48 usage
- LUT and FF consumption
- Clock frequency achieved

## 🧪 Testbench

The testbench includes 5 test cases:

1. **Random input** - Random pixel values
2. **All zeros** - Black image
3. **All max (255)** - White image
4. **Checkerboard** - Alternating pattern
5. **Gradient** - Smooth gradient pattern

Run testbench:
```bash
cd snn_ip_project/solution1/csim/build
./csim.exe
```

## 📈 Performance Metrics

### Clock Configuration
- **Target Clock:** 100 MHz (10ns period)
- **Device:** xc7z020clg400-1

### Expected Metrics
- **Latency:** ~10M cycles (10 timesteps × network computation)
- **Throughput:** ~100 inferences/second @ 100MHz
- **BRAM:** ~40-60% (weights storage)
- **DSP48:** ~50-80% (MAC operations)

## 🔍 Key Implementation Details

### Memory Organization
- Static buffers for layer outputs
- Membrane potential storage for each neuron
- Weights loaded from generated header file

### Fixed-Point Support
```cpp
typedef ap_fixed<16,6> fixed_t;  // 16-bit total, 6-bit integer
```

Define `__SYNTHESIS__` to use `ap_fixed` instead of `float`.

### Weight File Format
```c
// Conv layer weights
const float features_0_weight[16][1][3][3] = { ... };

// FC layer weights
const float classifier_0_weight[256][4096] = { ... };
```

## 📝 Customization

### Modify Network Parameters

Edit `snn_ip.h`:
```cpp
#define NUM_TIMESTEPS 10     // Number of timesteps
#define THRESHOLD 1.0f       // LIF threshold
#define DECAY 0.9f           // Membrane decay
```

### Change Target Device

Edit `run_hls.tcl`:
```tcl
set_part {xc7z020clg400-1}
```

### Adjust Clock Frequency

Edit `run_hls.tcl`:
```tcl
create_clock -period 10 -name default  # 10ns = 100MHz
```

## 🐛 Troubleshooting

### Synthesis Fails
- Check weight file is generated correctly
- Verify all source files are present
- Review synthesis log for errors

### Timing Not Met
- Reduce clock frequency in TCL script
- Add more pipeline pragmas
- Partition large arrays

### Resource Overflow
- Reduce internal buffer sizes
- Use more aggressive array partitioning
- Consider fixed-point arithmetic

## 📚 References

- [Vitis HLS User Guide](https://docs.xilinx.com/r/en-US/ug1399-vitis-hls)
- [AXI4-Lite Interface](https://docs.xilinx.com/r/en-US/ug1399-vitis-hls/AXI4-Lite-Slave-Interface)
- [HLS Optimization Techniques](https://docs.xilinx.com/r/en-US/ug1399-vitis-hls/HLS-Pragmas)

## 📄 License

This project is provided as-is for educational and research purposes.

## 🤝 Contributing

Feel free to submit issues or pull requests for improvements.
