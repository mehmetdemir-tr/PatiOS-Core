#include "pcg.h"

int pcg_read(const char *file_path, const char *key, char *buf, size_t buf_size) {
    FILE *f = fopen(file_path, "r");
    if (!f) return -1;

    char line[512];
    while (fgets(line, sizeof(line), f)) {
        char *k = strtok(line, " =\n");
        if (!k) continue;
        if (strcmp(k, key) == 0) {
            char *v = strtok(NULL, " =\n");
            if (v) {
                strncpy(buf, v, buf_size - 1);
                buf[buf_size - 1] = '\0';
                fclose(f);
                return 0;
            }
        }
    }
    fclose(f);
    return -1;
}
