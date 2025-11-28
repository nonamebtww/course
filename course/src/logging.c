#include <stdio.h>

void log_error(const char* message) {
    FILE* file = fopen("error.log", "a+");

    if (!file) {
        return;
    }

    fprintf(file, "ERROR: %s\n", message);
    fclose(file);

    printf("%s\n", message);
}
