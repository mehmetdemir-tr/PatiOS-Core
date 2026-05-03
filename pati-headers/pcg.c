#include "pcg.h"

int pcg_read(const char *dosya_yolu, const char *key, char *buf, size_t buf_sz) {
    FILE *f = fopen(dosya_yolu, "r");
    if (!f) return -1;

    char satir[512];
    while (fgets(satir, sizeof(satir), f)) {
        char *k = strtok(satir, " =\n");
        if (!k) continue;
        if (strcmp(k, key) == 0) {
            char *v = strtok(NULL, " =\n");
            if (v) {
                strncpy(buf, v, buf_sz - 1);
                buf[buf_sz - 1] = '\0';
                fclose(f);
                return 0;
            }
        }
    }
    fclose(f);
    return -1;
}
