#include <stdio.h>
#include <stdlib.h>

#define MEMORY_SIZE 1024   // total memory size
#define BLOCK_SIZE 64      // size of each block

int memory[MEMORY_SIZE];   // simulated memory
int used[MEMORY_SIZE / BLOCK_SIZE]; // track block usage

// allocate memory block
int allocate() {
    for (int i = 0; i < MEMORY_SIZE / BLOCK_SIZE; i++) {
        if (used[i] == 0) {
            used[i] = 1;
            printf("Allocated block %d\n", i);
            return i;
        }
    }
    printf("No free blocks available!\n");
    return -1;
}

// free memory block
void free_block(int block) {
    if (block >= 0 && block < MEMORY_SIZE / BLOCK_SIZE) {
        used[block] = 0;
        printf("Freed block %d\n", block);
    }
}

int main() {
    int b1 = allocate();
    int b2 = allocate();
    free_block(b1);
    int b3 = allocate();
    return 0;
}
