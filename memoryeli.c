#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MEMORY_SIZE 1024   // total memory size in bytes
#define BLOCK_SIZE 64      // size of each block in bytes
#define TOTAL_BLOCKS (MEMORY_SIZE / BLOCK_SIZE)

// simulated memory
unsigned char memory[MEMORY_SIZE];

// block usage table
// 0 = free, 1 = used
int used[TOTAL_BLOCKS];

// initialize memory system
void init_memory() {
    memset(memory, 0, MEMORY_SIZE);
    memset(used, 0, sizeof(used));
    printf("Memory initialized (%d bytes, %d blocks)\n",
           MEMORY_SIZE, TOTAL_BLOCKS);
}

// display memory usage
void display_memory() {
    printf("Memory blocks: ");
    for (int i = 0; i < TOTAL_BLOCKS; i++) {
        printf("[%d]", used[i]);
    }
    printf("\n");
}

// allocate memory by size (bytes)
int allocate(int size) {
    if (size <= 0) {
        printf("Invalid allocation size!\n");
        return -1;
    }

    int required_blocks =
        (size + BLOCK_SIZE - 1) / BLOCK_SIZE;

    int count = 0;
    int start = -1;

    for (int i = 0; i < TOTAL_BLOCKS; i++) {
        if (used[i] == 0) {
            if (count == 0)
                start = i;
            count++;

            if (count == required_blocks) {
                for (int j = start; j < start + required_blocks; j++)
                    used[j] = 1;

                printf("Allocated %d bytes (%d blocks) starting at block %d\n",
                       size, required_blocks, start);
                return start;
            }
        } else {
            count = 0;
        }
    }

    printf("Allocation failed: not enough contiguous blocks\n");
    return -1;
}

// free allocated blocks
void free_blocks(int start_block, int size) {
    if (start_block < 0 || start_block >= TOTAL_BLOCKS) {
        printf("Invalid block index!\n");
        return;
    }

    int blocks =
        (size + BLOCK_SIZE - 1) / BLOCK_SIZE;

    for (int i = start_block; i < start_block + blocks; i++) {
        if (i >= TOTAL_BLOCKS) break;

        if (used[i] == 0) {
            printf("Warning: block %d already free\n", i);
        } else {
            used[i] = 0;
        }
    }

    printf("Freed %d bytes (%d blocks) from block %d\n",
           size, blocks, start_block);
}

// main test
int main() {
    init_memory();
    display_memory();

    int a = allocate(100);   // 2 blocks
    display_memory();

    int b = allocate(200);   // 4 blocks
    display_memory();

    free_blocks(a, 100);
    display_memory();

    int c = allocate(64);    // 1 block
    display_memory();

    return 0;
}
