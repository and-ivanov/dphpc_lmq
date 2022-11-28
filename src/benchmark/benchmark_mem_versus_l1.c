#include <snrt.h>
#include "printf.h"

#include "lmq.h"
#include "benchmark.h"

int main() {
    uint32_t core_idx = snrt_global_core_idx();

    // only run on 1 core
    if (core_idx != 0) return 1;

    // memory
    float* memory_x = allocate(size, sizeof(float));
    float* memory_target = allocate(size, sizeof(float));
    float* memory_target_from_l1 = allocate(size, sizeof(float));
    
    for (int i = 0; i < size; i++) {
        memory_x[i] = (float)i - 20.0;
    }
    
    // copy
    size_t _start_ = read_csr(mcycle);
    for (size_t i = 0; i < size; i++) {
        memory_target[i] = memory_x[i];
    }
    size_t _end_ = read_csr(mcycle);

    printf("copy_memory_to_memory, size: %d: %lu cycles\n", size, _end_ - _start_);

    float* memory_l1 = snrt_l1alloc(size * sizeof(float));
    size_t start_l1 = read_csr(mcycle);
    for (size_t i = 0; i < size; i++) {
        memory_target_from_l1[i] = memory_x[i];
    }
    size_t end_l1  = read_csr(mcycle);
    
    printf("copy_l1_to_memory, size: %d: %lu cycles\n", size, end_l1 - start_l1);

    verify_vector(memory_target, memory_x, size);
    verify_vector(memory_target, memory_target_from_l1, size);
 
    return 0;
}

