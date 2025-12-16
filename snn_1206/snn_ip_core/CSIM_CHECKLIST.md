# C Simulation Quick Checklist

Quick reference for running HLS C Simulation.

## ✅ Pre-Run Checklist

### Files Required
- [ ] `snn_ip.h` exists
- [ ] `snn_ip.cpp` exists
- [ ] `snn_weights.h` exists (15MB)
- [ ] `testbench.cpp` exists
- [ ] `csim.tcl` exists

### Software
- [ ] Vitis HLS installed
- [ ] `vitis_hls` in PATH

### Quick Check Commands
```bash
# Check all files
ls -lh snn_ip.h snn_ip.cpp snn_weights.h testbench.cpp csim.tcl

# Check Vitis HLS
which vitis_hls

# Generate weights if needed
python3 export_weights.py
```

## 🚀 Run C Simulation

### Choose ONE method:

**Method 1: Direct TCL**
```bash
vitis_hls -f csim.tcl
```

**Method 2: Makefile**
```bash
make csim
```

**Method 3: Shell Script**
```bash
./run_csim.sh
```

## 📊 Expected Results

### Console Output Should Show:
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
  ...
  Done: true
  Predicted class: X
  [PASS]

...

[Test 9] Random noise pattern
  ...
  [PASS]

=============================================
  Test Summary
=============================================
Total tests: 9
Passed: 9
Failed: 0
Success rate: 100%
=============================================

✓ ALL TESTS PASSED!
```

## ✅ Post-Run Verification

### Check These:
- [ ] All 9 tests passed
- [ ] No compilation errors
- [ ] No segmentation faults
- [ ] Output saved to `csim_run.log`
- [ ] Project created: `snn_ip_project/`

### View Results
```bash
# View log
cat csim_run.log

# View HLS report
cat snn_ip_project/solution1/csim/report/snn_ip_csim.log

# Check project structure
tree snn_ip_project/solution1/csim/
```

## ⚠️ Common Issues

### Issue: `snn_weights.h` not found
**Solution:**
```bash
python3 export_weights.py
```

### Issue: Compilation errors
**Solution:**
- Check C++ version: needs C++11
- Verify all files present
- Clean and rebuild: `rm -rf snn_ip_project/`

### Issue: Takes too long (>1 hour)
**Temporary fix:**
Edit `snn_ip.h`:
```cpp
#define NUM_TIMESTEPS 2  // Reduce from 10
```

### Issue: Tests fail
**Debug:**
- Check weight file size (should be ~15MB)
- Verify network structure
- Add debug prints in `snn_ip.cpp`

## 🎯 Expected Timing

| Phase | Time |
|-------|------|
| First compilation | 2-5 min |
| Test execution | 10-30 min |
| Total | 15-35 min |

**Note:** First run is slower. Subsequent runs are faster.

## 📝 Quick Debug

If tests fail, try this minimal test:

```cpp
// In testbench.cpp main():
// Comment out tests 2-9, keep only test 1

// Run again
vitis_hls -f csim.tcl
```

## ✨ Success Criteria

- [x] Compilation successful
- [x] 9/9 tests passed
- [x] `done = true` for all tests
- [x] Output class in range [0-9]
- [x] No crashes
- [x] Reproducible results

## 🔄 Next Steps After CSIM Passes

1. ✅ **C Simulation** ← You completed this!
2. ⬜ **C Synthesis**
   ```bash
   vitis_hls run_hls.tcl
   ```
3. ⬜ **Check Reports**
   ```bash
   cat snn_ip_project/solution1/syn/report/snn_ip_csynth.rpt
   ```
4. ⬜ **Export IP**
5. ⬜ **Vivado Integration**

## 📚 More Help

See [CSIM_README.md](CSIM_README.md) for:
- Detailed troubleshooting
- Performance tuning
- Debug techniques
- Full documentation

---

## Quick Command Reference

```bash
# Full workflow
python3 export_weights.py    # Generate weights
vitis_hls -f csim.tcl         # Run C sim
make hls                      # Run synthesis

# Clean restart
rm -rf snn_ip_project/
rm csim_run.log
vitis_hls -f csim.tcl

# View results
grep -A 5 "Test Summary" csim_run.log
tail -20 csim_run.log
```

Good luck! 🚀
