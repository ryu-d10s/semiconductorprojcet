# HLS C Simulation Guide

Complete guide for running Vitis HLS C Simulation of the SNN IP Core.

## 📋 Prerequisites

### Required Files
- ✅ [snn_ip.h](snn_ip.h) - IP header file
- ✅ [snn_ip.cpp](snn_ip.cpp) - IP implementation
- ✅ [snn_weights.h](snn_weights.h) - Network weights (auto-generated)
- ✅ [testbench.cpp](testbench.cpp) - Test harness
- ✅ [csim.tcl](csim.tcl) - C simulation script

### Software
- **Vitis HLS** 2020.2 or later
- Ensure `vitis_hls` is in your PATH

### Verify Setup
```bash
# Check if Vitis HLS is available
which vitis_hls

# Check all required files exist
ls -lh snn_ip.h snn_ip.cpp snn_weights.h testbench.cpp csim.tcl
```

## 🚀 Quick Start

### Method 1: Using TCL Script (Recommended)

```bash
# Run C simulation
vitis_hls -f csim.tcl
```

### Method 2: Using Makefile

```bash
# If Makefile exists
make csim
```

### Method 3: Manual Execution

```bash
# Start Vitis HLS GUI
vitis_hls

# In Vitis HLS Tcl console:
source csim.tcl
```

## 📊 Test Cases

The testbench includes 9 comprehensive test patterns:

| Test # | Pattern | Description |
|--------|---------|-------------|
| 1 | Black Image | All pixels = 0 |
| 2 | White Image | All pixels = 255 |
| 3 | Vertical Stripes | 8-pixel wide vertical stripes |
| 4 | Horizontal Stripes | 8-pixel wide horizontal stripes |
| 5 | Checkerboard | 8×8 checkerboard pattern |
| 6 | Diagonal Gradient | Smooth diagonal gradient |
| 7 | Circle | Filled circle in center |
| 8 | Cross | Horizontal + vertical cross |
| 9 | Random Noise | Random pixel values |

### Test Pattern Examples

```
Black (Test 1):        White (Test 2):        Vertical Stripes (Test 3):
                       ████████████████       █       █       █       █
                       ████████████████       █       █       █       █
                       ████████████████       █       █       █       █
                       ████████████████       █       █       █       █

Checkerboard (Test 5): Circle (Test 7):       Cross (Test 8):
█ █ █ █ █ █ █ █                                       ████
 █ █ █ █ █ █ █                ████                    ████
█ █ █ █ █ █ █ █              ██████              ████████████████
 █ █ █ █ █ █ █              ████████                  ████
█ █ █ █ █ █ █ █              ██████                   ████
```

## 📝 Expected Output

### Successful Run

```
=============================================
  SNN IP Core - C Simulation Testbench
=============================================
Network Configuration:
  Input size: 64x64
  Output classes: 10
  Timesteps: 10
  LIF threshold: 1
  LIF decay: 0.9
=============================================

[Test 1] All-zero input (black image)
  Preview (top-left 16x16):



  ...
  Running SNN inference...
  Done: true
  Predicted class: 3
  [PASS]

[Test 2] All-max input (white image)
  Preview (top-left 16x16):
  ████████████████
  ████████████████
  ...
  Running SNN inference...
  Done: true
  Predicted class: 7
  [PASS]

...

=============================================
  Test Summary
=============================================
Total tests: 9
Passed: 9
Failed: 0
Success rate: 100%
=============================================

✓ ALL TESTS PASSED!

INFO: [SIM 2] *************** CSIM finish ***************
```

### Simulation Statistics

After completion, you'll see:
- **Execution time**: Time taken for C simulation
- **Function calls**: Number of `snn_ip()` calls (9)
- **Return value**: 0 (success) or 1 (failure)

## 📂 Output Files Location

After running C simulation:

```
snn_ip_project/
└── solution1/
    └── csim/
        ├── build/           # Compiled testbench
        │   └── csim.exe     # Executable
        ├── report/          # Simulation report
        │   └── snn_ip_csim.log
        └── wrap_pc/         # HLS wrappers
```

### View Detailed Log

```bash
cat snn_ip_project/solution1/csim/report/snn_ip_csim.log
```

## 🐛 Troubleshooting

### Problem 1: `snn_weights.h` Not Found

**Error:**
```
fatal error: snn_weights.h: No such file or directory
```

**Solution:**
```bash
# Generate weights file
python3 export_weights.py

# Verify it exists
ls -lh snn_weights.h
```

---

### Problem 2: Compilation Errors

**Error:**
```
undefined reference to 'sqrt'
```

**Solution:**
Update [csim.tcl](csim.tcl) to include math library:
```tcl
add_files -tb testbench.cpp -cflags "-std=c++11 -I. -lm"
```

---

### Problem 3: Simulation Hangs

**Symptoms:**
- No output for long time
- Process seems stuck

**Reasons:**
- Network computation is very slow in C simulation
- Large weight file takes time to load

**Solutions:**

1. **Reduce timesteps temporarily** in [snn_ip.h](snn_ip.h):
   ```cpp
   #define NUM_TIMESTEPS 2  // Instead of 10
   ```

2. **Run fewer tests** - Edit [testbench.cpp](testbench.cpp) to comment out some tests

3. **Check system resources:**
   ```bash
   top  # Monitor CPU/memory usage
   ```

4. **Enable debug output** - Add prints in snn_ip.cpp to see progress

---

### Problem 4: Test Failures

**Error:**
```
[Test X] Pattern Name
  Done: true
  Predicted class: -1
  [FAIL] Invalid output class: -1
```

**Debug Steps:**

1. **Check if network runs:**
   ```cpp
   // In snn_ip.cpp, add debug prints
   cout << "Timestep: " << t << endl;
   ```

2. **Verify weights loaded:**
   ```bash
   # Check weight file size
   ls -lh snn_weights.h
   # Should be ~15MB
   ```

3. **Test with simpler input:**
   - Comment out complex tests
   - Run only Test 1 (all zeros)

4. **Check output initialization:**
   ```cpp
   // In testbench, verify:
   int output_class = -1;  // Should be initialized
   bool done = false;
   ```

---

### Problem 5: Memory Issues

**Error:**
```
Segmentation fault
Out of memory
```

**Solutions:**

1. **Increase stack size:**
   ```bash
   ulimit -s unlimited
   vitis_hls -f csim.tcl
   ```

2. **Use heap allocation:**
   In [testbench.cpp](testbench.cpp):
   ```cpp
   // Change from:
   static pixel_t test_image[IMAGE_SIZE][IMAGE_SIZE];

   // To:
   pixel_t (*test_image)[IMAGE_SIZE] = new pixel_t[IMAGE_SIZE][IMAGE_SIZE];
   // ... use test_image
   delete[] test_image;
   ```

---

### Problem 6: Wrong Results

**Symptoms:**
- Tests pass but results seem incorrect
- All tests predict same class

**Debug:**

1. **Print intermediate values:**
   ```cpp
   // In snn_ip.cpp
   cout << "Conv1 output: " << conv1_out[0][0][0] << endl;
   cout << "Spike count: " << output_spikes[0] << endl;
   ```

2. **Verify LIF neuron:**
   ```cpp
   // Test LIF function separately
   float mem = 0.0f;
   float spike = lif_neuron(1.5f, &mem);
   cout << "Spike: " << spike << " Mem: " << mem << endl;
   ```

3. **Check normalization:**
   ```cpp
   // Input should be 0.0-1.0
   input_float[i][j][0] = (float)image[i][j] / 255.0f;
   ```

---

### Problem 7: Long Compilation Time

**Issue:**
- C compilation takes very long (>30 minutes)

**Reasons:**
- Large weight file (15MB)
- Complex nested loops

**Solutions:**

1. **Use precompiled headers** (advanced)

2. **Reduce optimization level:**
   ```tcl
   # In csim.tcl
   add_files snn_ip.cpp -cflags "-O1"  # Instead of -O3
   ```

3. **First-time only:**
   - Subsequent runs are faster (cached)

---

## 🔍 Debugging Tips

### Enable Verbose Output

```bash
# Run with verbose mode
vitis_hls -f csim.tcl -l csim.log 2>&1 | tee console.log
```

### Add Debug Prints

In [snn_ip.cpp](snn_ip.cpp):

```cpp
void snn_ip(...) {
    #ifndef __SYNTHESIS__
    cout << "Starting SNN inference..." << endl;
    #endif

    // ... your code

    #ifndef __SYNTHESIS__
    cout << "Completed timestep " << t << endl;
    #endif
}
```

### Check Array Bounds

```cpp
// Add assertions
#include <cassert>

assert(output_class >= 0 && output_class < NUM_CLASSES);
assert(done == true);
```

### Profile Performance

```bash
# Time the simulation
time vitis_hls -f csim.tcl
```

## ✅ Verification Checklist

Before considering C simulation successful:

- [ ] All 9 tests pass
- [ ] `done` flag is always `true`
- [ ] Output class is always 0-9
- [ ] No segmentation faults
- [ ] No compiler warnings
- [ ] Simulation completes in reasonable time (<30 min)
- [ ] Results are reproducible (run twice, same results)

## 📈 Performance Expectations

### Typical Timings

| Metric | Expected Value |
|--------|----------------|
| Compilation time (first run) | 2-5 minutes |
| Compilation time (subsequent) | 10-30 seconds |
| Per-test execution | 1-3 minutes |
| Total simulation time | 10-30 minutes |

**Note:** C simulation is slow because:
- No hardware acceleration
- Software emulation of all layers
- 10 timesteps per inference
- 9 complete inferences

### Speed Optimization

To speed up for debugging:

1. **Reduce timesteps:**
   ```cpp
   #define NUM_TIMESTEPS 2  // Temporary
   ```

2. **Run fewer tests:**
   ```cpp
   // Comment out tests 3-9 temporarily
   ```

3. **Use simpler network** (if available)

## 🎯 Next Steps

After C simulation passes:

1. ✅ **C Simulation** ← You are here
2. ⬜ **C Synthesis** - Generate RTL
   ```bash
   vitis_hls run_hls.tcl
   ```

3. ⬜ **C/RTL Co-simulation** - Verify RTL matches C
   ```bash
   # Uncomment cosim in run_hls.tcl
   ```

4. ⬜ **Export IP** - Package for Vivado
   ```bash
   # Already in run_hls.tcl
   ```

5. ⬜ **Vivado Integration** - Use in block design

## 📚 Additional Resources

- [Vitis HLS C Simulation](https://docs.xilinx.com/r/en-US/ug1399-vitis-hls/Running-C-Simulation)
- [Debugging HLS Designs](https://docs.xilinx.com/r/en-US/ug1399-vitis-hls/Debugging-C-Code)
- [Testbench Best Practices](https://docs.xilinx.com/r/en-US/ug1399-vitis-hls/Writing-a-Test-Bench)

## 💡 Tips

1. **First time takes longest** - Subsequent runs are much faster
2. **Use fixed random seed** - Ensures reproducible results (already done: `srand(42)`)
3. **Start simple** - If issues, comment out complex tests first
4. **Monitor resources** - Use `top` or `htop` to watch CPU/memory
5. **Save logs** - Redirect output to file for analysis later

---

## Quick Reference Commands

```bash
# Full C simulation
vitis_hls -f csim.tcl

# With logging
vitis_hls -f csim.tcl 2>&1 | tee csim.log

# Check if project exists
ls -ld snn_ip_project/

# View simulation results
cat snn_ip_project/solution1/csim/report/snn_ip_csim.log

# Clean and re-run
rm -rf snn_ip_project/
vitis_hls -f csim.tcl

# Run with Makefile
make csim
```

Good luck with your C simulation! 🚀
