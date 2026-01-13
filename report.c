// stats.c
static int alloc_count = 0, free_count = 0, write_count = 0, read_count = 0;

void record_alloc() { alloc_count++; }
void record_free() { free_count++; }
void record_write() { write_count++; }
void record_read() { read_count++; }

void print_stats() {
    printf("Stats: alloc=%d, free=%d, write=%d, read=%d\n",
           alloc_count, free_count, write_count, read_count);
}
