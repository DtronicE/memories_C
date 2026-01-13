// logger.c
#include <stdio.h>
#include <time.h>

void log_event(const char* event) {
    FILE* f = fopen("events.log", "a");
    if (!f) return;
    time_t now = time(NULL);
    fprintf(f, "%s - %s\n", ctime(&now), event);
    fclose(f);
}
