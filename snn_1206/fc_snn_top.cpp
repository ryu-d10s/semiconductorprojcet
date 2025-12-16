// fc_snn_top.cpp
#include <hls_stream.h>
#include <ap_axi_sdata.h>
#include <ap_int.h>
#include "weights.h"

// 32-bit AXI4-Stream word (no side channels)
typedef ap_axiu<32, 0, 0, 0> axis32_t;

// FEAT must be a multiple of 32 because we pack spikes into 32-bit words.
#if (FEAT % 32) != 0
#error "FEAT must be a multiple of 32."
#endif

static const int WORDS_PER_STEP = FEAT / 32;

void fc_snn_top(
    hls::stream<axis32_t> &in_stream,
    hls::stream<axis32_t> &out_stream,
    int n_steps,
    bool clear_state
) {
#pragma HLS INTERFACE axis port=in_stream
#pragma HLS INTERFACE axis port=out_stream

#pragma HLS INTERFACE s_axilite port=n_steps     bundle=CTRL
#pragma HLS INTERFACE s_axilite port=clear_state bundle=CTRL
#pragma HLS INTERFACE s_axilite port=return      bundle=CTRL

    // Persistent membrane state (kept across calls unless explicitly cleared)
    static q32_t v_mem[NCLASS];
#pragma HLS ARRAY_PARTITION variable=v_mem complete dim=1

    // Optional state clear (useful between independent inferences)
    if (clear_state) {
        for (int c = 0; c < NCLASS; c++) {
#pragma HLS UNROLL
            v_mem[c] = 0;
        }
    }

    // Run for n_steps timesteps
    for (int t = 0; t < n_steps; t++) {

        // Accumulator for this timestep: sum of weights for active spikes
        q32_t acc[NCLASS];
#pragma HLS ARRAY_PARTITION variable=acc complete dim=1

        // Initialize accumulators
        for (int c = 0; c < NCLASS; c++) {
#pragma HLS UNROLL
            acc[c] = 0;
        }

        // Read packed spikes: FEAT bits == WORDS_PER_STEP 32-bit words
        axis32_t x;
        ap_uint<32> bits = 0;

        // Iterate over all feature bits in the timestep
        for (int i = 0; i < FEAT; i++) {
#pragma HLS PIPELINE II=1

            // Every 32 features, read a new AXIS word
            if ((i & 31) == 0) {
                x = in_stream.read();
                bits = (ap_uint<32>)x.data;
            }

            // If spike bit is 1, add weights for all classes
            if (bits[i & 31]) {
                for (int c = 0; c < NCLASS; c++) {
#pragma HLS UNROLL
                    acc[c] += (q32_t)W_FC[c][i];
                }
            }
        }

        // Integrate-and-fire (no leak), soft reset on spike
        ap_uint<32> out_mask = 0;

        for (int c = 0; c < NCLASS; c++) {
#pragma HLS UNROLL
            v_mem[c] += acc[c];

            if (v_mem[c] >= TH_LAST_Q) {
                out_mask[c] = 1;
                v_mem[c] -= TH_LAST_Q;  // Soft reset
            }
        }

        // Write one 32-bit output word per timestep
        axis32_t y;
        y.data = out_mask;
        y.keep = 0xF;
        y.strb = 0xF;
        y.last = (t == (n_steps - 1)) ? 1 : 0; // TLAST at end of inference only

        out_stream.write(y);
    }
}
