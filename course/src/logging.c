#include <stdio.h>

#include "../headers/models.h"

void log_error(const char* message) {
    FILE* file = fopen("error.log", "a+");

    if (!file) {
        return;
    }

    fprintf(file, "ERROR: %s\n", message);
    fclose(file);

    printf("%s\n", message);
}

int show_interval(MapEntry* entities, size_t size) {
    for (size_t i = 0; i < size; i++) {
        printf("%lf | %lf\n", entities[i].key, entities[i].value);
    }

    return 0;
}

int save_interval(MapEntry* entities, size_t size) {
    FILE* file = fopen("interval.txt", "w");
   
    if (!file) {
        log_error("Failed to open interval.log for appending.");
        return -1;
    }

	for (size_t i = 0; i < size; i++) {
        fprintf(file, "%lf | %lf\n", entities[i].key, entities[i].value);
    }

    fclose(file);
    return 0;
}