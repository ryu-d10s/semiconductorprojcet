/*
 * SNN IP Core Testbench
 * Comprehensive test with various input patterns
 */

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include "snn_ip.h"

using namespace std;

// Helper function to create test patterns
void create_vertical_stripes(pixel_t image[IMAGE_SIZE][IMAGE_SIZE], int stripe_width) {
    for (int i = 0; i < IMAGE_SIZE; i++) {
        for (int j = 0; j < IMAGE_SIZE; j++) {
            image[i][j] = ((j / stripe_width) % 2) ? 255 : 0;
        }
    }
}

void create_horizontal_stripes(pixel_t image[IMAGE_SIZE][IMAGE_SIZE], int stripe_width) {
    for (int i = 0; i < IMAGE_SIZE; i++) {
        for (int j = 0; j < IMAGE_SIZE; j++) {
            image[i][j] = ((i / stripe_width) % 2) ? 255 : 0;
        }
    }
}

void create_diagonal_pattern(pixel_t image[IMAGE_SIZE][IMAGE_SIZE]) {
    for (int i = 0; i < IMAGE_SIZE; i++) {
        for (int j = 0; j < IMAGE_SIZE; j++) {
            image[i][j] = (unsigned char)((i + j) * 255 / (2 * IMAGE_SIZE));
        }
    }
}

void create_circle_pattern(pixel_t image[IMAGE_SIZE][IMAGE_SIZE]) {
    int center_x = IMAGE_SIZE / 2;
    int center_y = IMAGE_SIZE / 2;
    int radius = IMAGE_SIZE / 4;

    for (int i = 0; i < IMAGE_SIZE; i++) {
        for (int j = 0; j < IMAGE_SIZE; j++) {
            int dx = j - center_x;
            int dy = i - center_y;
            int dist = (int)sqrt((double)(dx*dx + dy*dy));
            image[i][j] = (dist < radius) ? 255 : 0;
        }
    }
}

void create_cross_pattern(pixel_t image[IMAGE_SIZE][IMAGE_SIZE]) {
    int center = IMAGE_SIZE / 2;
    int thickness = IMAGE_SIZE / 8;

    for (int i = 0; i < IMAGE_SIZE; i++) {
        for (int j = 0; j < IMAGE_SIZE; j++) {
            bool horizontal = (i >= center - thickness) && (i < center + thickness);
            bool vertical = (j >= center - thickness) && (j < center + thickness);
            image[i][j] = (horizontal || vertical) ? 255 : 0;
        }
    }
}

void create_checkerboard(pixel_t image[IMAGE_SIZE][IMAGE_SIZE], int square_size) {
    for (int i = 0; i < IMAGE_SIZE; i++) {
        for (int j = 0; j < IMAGE_SIZE; j++) {
            int row_block = i / square_size;
            int col_block = j / square_size;
            image[i][j] = ((row_block + col_block) % 2) ? 255 : 0;
        }
    }
}

void print_image_preview(pixel_t image[IMAGE_SIZE][IMAGE_SIZE], int preview_size = 16) {
    cout << "  Preview (top-left " << preview_size << "x" << preview_size << "):" << endl;
    for (int i = 0; i < preview_size; i++) {
        cout << "  ";
        for (int j = 0; j < preview_size; j++) {
            if (image[i][j] > 200) cout << "�뻽";
            else if (image[i][j] > 150) cout << "�뼋";
            else if (image[i][j] > 100) cout << "�뼊";
            else if (image[i][j] > 50) cout << "�뼇";
            else cout << " ";
        }
        cout << endl;
    }
}

// Test runner function
bool run_test(const char* test_name, pixel_t image[IMAGE_SIZE][IMAGE_SIZE], int test_num) {
    cout << "\n[Test " << test_num << "] " << test_name << endl;
    print_image_preview(image);

    int output_class = -1;
    bool done = false;

    cout << "  Running SNN inference..." << endl;
    snn_ip(image, &output_class, &done);

    cout << "  Done: " << (done ? "true" : "false") << endl;
    cout << "  Predicted class: " << output_class << endl;

    if (!done) {
        cout << "  [FAIL] Processing not completed!" << endl;
        return false;
    }

    if (output_class < 0 || output_class >= NUM_CLASSES) {
        cout << "  [FAIL] Invalid output class: " << output_class << endl;
        return false;
    }

    cout << "  [PASS] Test completed successfully!" << endl;
    return true;
}

int main() {
    cout << "=============================================" << endl;
    cout << "  SNN IP Core - C Simulation Testbench" << endl;
    cout << "=============================================" << endl;
    cout << "Network Configuration:" << endl;
    cout << "  Input size: " << IMAGE_SIZE << "x" << IMAGE_SIZE << endl;
    cout << "  Output classes: " << NUM_CLASSES << endl;
    cout << "  Timesteps: " << NUM_TIMESTEPS << endl;
    cout << "  LIF threshold: " << THRESHOLD << endl;
    cout << "  LIF decay: " << DECAY << endl;
    cout << "=============================================" << endl;

    // Allocate input image
    static pixel_t test_image[IMAGE_SIZE][IMAGE_SIZE];
    int total_tests = 0;
    int passed_tests = 0;

    // Initialize random seed (fixed for reproducibility)
    srand(42);

    // Test 1: All zeros (black image)
    total_tests++;
    cout << "\n[Test " << total_tests << "] All-zero input (black image)" << endl;
    for (int i = 0; i < IMAGE_SIZE; i++) {
        for (int j = 0; j < IMAGE_SIZE; j++) {
            test_image[i][j] = 0;
        }
    }
    print_image_preview(test_image);

    int output_class = -1;
    bool done = false;
    cout << "  Running SNN inference..." << endl;
    snn_ip(test_image, &output_class, &done);
    cout << "  Done: " << (done ? "true" : "false") << endl;
    cout << "  Predicted class: " << output_class << endl;

    if (done && output_class >= 0 && output_class < NUM_CLASSES) {
        cout << "  [PASS]" << endl;
        passed_tests++;
    } else {
        cout << "  [FAIL]" << endl;
    }

    // Test 2: All max (white image)
    total_tests++;
    cout << "\n[Test " << total_tests << "] All-max input (white image)" << endl;
    for (int i = 0; i < IMAGE_SIZE; i++) {
        for (int j = 0; j < IMAGE_SIZE; j++) {
            test_image[i][j] = 255;
        }
    }
    print_image_preview(test_image);

    output_class = -1;
    done = false;
    cout << "  Running SNN inference..." << endl;
    snn_ip(test_image, &output_class, &done);
    cout << "  Done: " << (done ? "true" : "false") << endl;
    cout << "  Predicted class: " << output_class << endl;

    if (done && output_class >= 0 && output_class < NUM_CLASSES) {
        cout << "  [PASS]" << endl;
        passed_tests++;
    } else {
        cout << "  [FAIL]" << endl;
    }

    // Test 3: Vertical stripes
    total_tests++;
    cout << "\n[Test " << total_tests << "] Vertical stripes pattern" << endl;
    create_vertical_stripes(test_image, 8);
    print_image_preview(test_image);

    output_class = -1;
    done = false;
    cout << "  Running SNN inference..." << endl;
    snn_ip(test_image, &output_class, &done);
    cout << "  Done: " << (done ? "true" : "false") << endl;
    cout << "  Predicted class: " << output_class << endl;

    if (done && output_class >= 0 && output_class < NUM_CLASSES) {
        cout << "  [PASS]" << endl;
        passed_tests++;
    } else {
        cout << "  [FAIL]" << endl;
    }

    // Test 4: Horizontal stripes
    total_tests++;
    cout << "\n[Test " << total_tests << "] Horizontal stripes pattern" << endl;
    create_horizontal_stripes(test_image, 8);
    print_image_preview(test_image);

    output_class = -1;
    done = false;
    cout << "  Running SNN inference..." << endl;
    snn_ip(test_image, &output_class, &done);
    cout << "  Done: " << (done ? "true" : "false") << endl;
    cout << "  Predicted class: " << output_class << endl;

    if (done && output_class >= 0 && output_class < NUM_CLASSES) {
        cout << "  [PASS]" << endl;
        passed_tests++;
    } else {
        cout << "  [FAIL]" << endl;
    }

    // Test 5: Checkerboard
    total_tests++;
    cout << "\n[Test " << total_tests << "] Checkerboard pattern" << endl;
    create_checkerboard(test_image, 8);
    print_image_preview(test_image);

    output_class = -1;
    done = false;
    cout << "  Running SNN inference..." << endl;
    snn_ip(test_image, &output_class, &done);
    cout << "  Done: " << (done ? "true" : "false") << endl;
    cout << "  Predicted class: " << output_class << endl;

    if (done && output_class >= 0 && output_class < NUM_CLASSES) {
        cout << "  [PASS]" << endl;
        passed_tests++;
    } else {
        cout << "  [FAIL]" << endl;
    }

    // Test 6: Diagonal gradient
    total_tests++;
    cout << "\n[Test " << total_tests << "] Diagonal gradient pattern" << endl;
    create_diagonal_pattern(test_image);
    print_image_preview(test_image);

    output_class = -1;
    done = false;
    cout << "  Running SNN inference..." << endl;
    snn_ip(test_image, &output_class, &done);
    cout << "  Done: " << (done ? "true" : "false") << endl;
    cout << "  Predicted class: " << output_class << endl;

    if (done && output_class >= 0 && output_class < NUM_CLASSES) {
        cout << "  [PASS]" << endl;
        passed_tests++;
    } else {
        cout << "  [FAIL]" << endl;
    }

    // Test 7: Circle pattern
    total_tests++;
    cout << "\n[Test " << total_tests << "] Circle pattern" << endl;
    create_circle_pattern(test_image);
    print_image_preview(test_image);

    output_class = -1;
    done = false;
    cout << "  Running SNN inference..." << endl;
    snn_ip(test_image, &output_class, &done);
    cout << "  Done: " << (done ? "true" : "false") << endl;
    cout << "  Predicted class: " << output_class << endl;

    if (done && output_class >= 0 && output_class < NUM_CLASSES) {
        cout << "  [PASS]" << endl;
        passed_tests++;
    } else {
        cout << "  [FAIL]" << endl;
    }

    // Test 8: Cross pattern
    total_tests++;
    cout << "\n[Test " << total_tests << "] Cross pattern" << endl;
    create_cross_pattern(test_image);
    print_image_preview(test_image);

    output_class = -1;
    done = false;
    cout << "  Running SNN inference..." << endl;
    snn_ip(test_image, &output_class, &done);
    cout << "  Done: " << (done ? "true" : "false") << endl;
    cout << "  Predicted class: " << output_class << endl;

    if (done && output_class >= 0 && output_class < NUM_CLASSES) {
        cout << "  [PASS]" << endl;
        passed_tests++;
    } else {
        cout << "  [FAIL]" << endl;
    }

    // Test 9: Random image
    total_tests++;
    cout << "\n[Test " << total_tests << "] Random noise pattern" << endl;
    for (int i = 0; i < IMAGE_SIZE; i++) {
        for (int j = 0; j < IMAGE_SIZE; j++) {
            test_image[i][j] = rand() % 256;
        }
    }
    print_image_preview(test_image);

    output_class = -1;
    done = false;
    cout << "  Running SNN inference..." << endl;
    snn_ip(test_image, &output_class, &done);
    cout << "  Done: " << (done ? "true" : "false") << endl;
    cout << "  Predicted class: " << output_class << endl;

    if (done && output_class >= 0 && output_class < NUM_CLASSES) {
        cout << "  [PASS]" << endl;
        passed_tests++;
    } else {
        cout << "  [FAIL]" << endl;
    }

    // Summary
    cout << "\n=============================================" << endl;
    cout << "  Test Summary" << endl;
    cout << "=============================================" << endl;
    cout << "Total tests: " << total_tests << endl;
    cout << "Passed: " << passed_tests << endl;
    cout << "Failed: " << (total_tests - passed_tests) << endl;
    cout << "Success rate: " << (100.0 * passed_tests / total_tests) << "%" << endl;
    cout << "=============================================" << endl;

    if (passed_tests == total_tests) {
        cout << "\n�쐯 ALL TESTS PASSED!" << endl;
        return 0;
    } else {
        cout << "\n�쐵 SOME TESTS FAILED!" << endl;
        return 1;
    }
}
