#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <sys/reboot.h>
#include <signal.h>
#include <time.h>

int main(int argc, char *argv[]) {
    if (argc > 1 && strcmp(argv[1], "-debug") == 0) {
        debug_mode = 1;
    }
    else {
        int debug_mode = 0;
    }
    
    if (debug_mode) {
        time_t now = time(NULL);
        printf("[DEBUG] PSC basladi | PID: %d | Saat: %s", getpid(), ctime(&now));
    }
    
    DIR* proc = opendir("/proc");
    if (proc == NULL) {
        perror("[PSC] HATA: /proc acilamadi");
        exit(EXIT_FAILURE);
    }
    
    struct dirent* entry;
    int mauvyd_found = 0;
    int virus_killed_count = 0;
    
    char *karaliste[] = {
        "xmrig", "mirai", "tsunami", "reptile", 
        "azazel", "bdvl", "kinsing", "sysrv", NULL
    };
    
    while ((entry = readdir(proc)) != NULL) {
        if (entry->d_name[0] >= '0' && entry->d_name[0] <= '9') {
            char yol[512];
            snprintf(yol, sizeof(yol), "/proc/%s/cmdline", entry->d_name);
            
            FILE* f = fopen(yol, "r");
            if (f == NULL) continue;
            
            char icerik[512] = {0};
            size_t n = fread(icerik, 1, sizeof(icerik) - 1, f);
            fclose(f);
            
            if (n == 0) continue;

            if (strcmp(entry->d_name, "1") == 0) {
                if (strstr(icerik, "mauvyd") != NULL || strstr(icerik, "init") != NULL) {
                    mauvyd_found = 1;
                }
            }

            for (int i = 0; karaliste[i] != NULL; i++) {
                if (strstr(icerik, karaliste[i]) != NULL) {
                    if (atoi(entry->d_name) == getpid()) continue;

                    printf("[PSC] UYARI: Zararli bulundu: %s (PID:%s) - kapatiliyor!\n", 
                           karaliste[i], entry->d_name);
                    
                    kill(atoi(entry->d_name), SIGKILL);
                    virus_killed_count++;
                }
            }
        }
    }
    closedir(proc);
    
    printf("-------------------------------------\n");
    printf("            Virus Kontrolu...        \n");
    printf("-------------------------------------\n");
    if (virus_killed_count == 0) {
        printf("[PSC] Temiz: Zararli bulunmadi.\n");
    } else {
        printf("[PSC] %d zararli process sonlandirildi!\n", virus_killed_count);
    }
    
    printf("-------------------------------------\n");
    printf("     Sistem Yoneticisi Kontrolu...   \n");
    printf("-------------------------------------\n");
    if (mauvyd_found) {
        printf("[PSC] Mauvyd calisiyor\n");
    } else {
        printf("[PSC] HATA: Mauvyd bulunamadi! Kod:NF1\n");
        if (!debug_mode) reboot(RB_POWER_OFF);
    }

    printf("-------------------------------------\n");
    printf("      Cihaz Kimligi Kontrolu...      \n");
    printf("-------------------------------------\n");
    if (access("/etc/device.umci", F_OK) == 0) {
        printf("[PSC] Cihaz kimligi tanimlandi.\n");
    } else {
        printf("[PSC] UYARI: Cihaz kimligi gecersiz! Kod:NF2\n");
    }

    printf("-------------------------------------\n");
    printf("          Istemci Kontrolu...        \n");
    printf("-------------------------------------\n");
    if (access("/bin/shell", F_OK) == 0) {
        printf("[PSC] Ana istemci bulundu.\n");
    } else {
        printf("[PSC] HATA: Ana istemci bulunamadi! Kod:NF3\n");
        if (!debug_mode) reboot(RB_POWER_OFF);
    }

    printf("-------------------------------------\n");
    printf("[PSC] Guvenlik kontrolu tamamlandi.\n");
    printf("-------------------------------------\n");

    return 0;
}