#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <termios.h>
#include <dirent.h>
#include <stdlib.h>
#include <libgen.h>
#include <sys/reboot.h>
#include <sys/wait.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <fcntl.h>

int main(void) {
    while (1) {
        printf("pati@tr> ");
        fflush(stdout);
        char girdi[256];
        fgets(girdi, 256, stdin);
        girdi[strcspn(girdi, "\n")] = 0;
        char *argv[64];
        int argc = 0;
        char *token = strtok(girdi, " ");
        while (token && argc < 63) {
            argv[argc++] = token;
            token = strtok(NULL, " ");
        }
        argv[argc] = NULL;
        if (argc == 0) {
            continue;
        }

        if (strcmp(argv[0], "pati") == 0) {
            printf("Miyavv!\n");
        }
        else if (strcmp(argv[0], "miyav") == 0) {
            pid_t pid = fork();
            if (pid == 0) {
                char *args[] = {"/lib/paticommands/miyav", argv[1], NULL};
                execv("/lib/paticommands/miyav", args);
                perror("miyav baslatilmadi");
                exit(EXIT_FAILURE);
            } else if (pid > 0) {
                wait(NULL);
            } else {
                perror("fork basarisiz");
            }
        }
        else if (strcmp(argv[0], "temizle") == 0) {
            for (int i = 0; i < 50; i++) {
                printf("\n");
            }
            printf("Ekran Gumletildi!\n");
        }
        else if (strcmp(argv[0], "ls") == 0) {
            pid_t pid = fork();
            if (pid == 0) {
                char *args[] = {"/lib/paticommands/ls", argv[1], NULL};
                execv("/lib/paticommands/ls", args);
                perror("ls baslatilmadi");
                exit(EXIT_FAILURE);
            } else if (pid > 0) {
                wait(NULL);
            } else {
                perror("fork basarisiz");
            }
        }
        else if (strcmp(argv[0], "yapimci") == 0) {
            printf("Pati-2.1 by Mehmet Demir. Kod adi: Ananas (Pineapple)\n");
        }
        else if (strcmp(argv[0], "touch") == 0) {
            if (argv[1] == NULL) {
                printf("Kullanim: touch <dosya_adi>\n");
                continue;
            }
            int fd = creat(argv[1], 0644);
            if (fd != -1) {
                printf("Dosya olusturuldu: %s\n", argv[1]);
                close(fd);
                sync();
            } else {
                perror("touch hatasi");
            }
        }
        else if (strcmp(argv[0], "cikis") == 0) {
            sync();
            reboot(RB_POWER_OFF);
        }
        else if (strcmp(argv[0], "cat") == 0) {
            pid_t pid = fork();
            if (pid == 0) {
                char *args[] = {"/lib/paticommands/cat", argv[1], NULL};
                execv("/lib/paticommands/cat", args);
                perror("cat baslatilmadi");
                exit(EXIT_FAILURE);
            } else if (pid > 0) {
                wait(NULL);
            } else {
                perror("fork basarisiz");
            }
        }
        else if (strcmp(argv[0], "mamakabi") == 0) {
            pid_t pid = fork();
            if (pid == 0) {
                char *args[] = {"/lib/paticommands/mamakabi", argv[1], NULL};
                execv("/lib/paticommands/mamakabi", args);
                perror("mamakabi baslatilmadi");
                exit(EXIT_FAILURE);
            } else if (pid > 0) {
                wait(NULL);
            } else {
                perror("fork basarisiz");
            }
        }
        else if (strcmp(argv[0], "libreturks") == 0) {
            printf("\nYaHnI oLaN vArMi?\n");
        }
        else if (strcmp(argv[0], "psc") == 0) {
             char *psc_args[3] = {"/pcg-startup/psc", NULL, NULL};
            if (argv[1] != NULL) {
                psc_args[1] = argv[1];
                psc_args[2] = NULL;
            }
            pid_t psc_pid = fork();
            if (psc_pid == 0) {
                execv("/pcg-startup/psc", psc_args);
                perror("psc baslatilmadi");
                exit(EXIT_FAILURE);
            } else if (psc_pid > 0) {
                wait(NULL);
            } else {
                perror("fork basarisiz");
            }
        }
        else if (strcmp(argv[0], "2048") == 0) {
            pid_t two_pid = fork();
            if (two_pid == 0) {
                setenv("TERMINFO", "/usr/lib/terminfo", 1);
                setenv("TERM", "xterm", 1);
                char *args[] = {"/lib/paticommands/2048", NULL};
                execv("/lib/paticommands/2048", args);
            } else if (two_pid > 0) {
                wait(NULL);
                system("reset");
            } else {
                printf("fork hatasi!\n");
            }
        }
        else if (strcmp(argv[0], "grafik") == 0) {
            pid_t tri_pid = fork();
            if (tri_pid == 0) {
                char *args[] = {"/lib/paticommands/grafik", NULL};
                execv("/lib/paticommands/grafik", args);
                perror("execv hatasi");
                exit(1);
            } else if (tri_pid < 0) {
                printf("fork hatasi!\n");
            }
        }
        else if (strcmp(argv[0], "karabas") == 0) {
            pid_t pid = fork();
            if (pid == 0) {
                char *args[] = {"/lib/paticommands/karabas", NULL};
                execv("/lib/paticommands/karabas", args);
                perror("karabas baslatilmadi");
                exit(EXIT_FAILURE);
            } else if (pid > 0) {
                wait(NULL);
            } else {
                perror("fork basarisiz");
            }
        }
        else if (strcmp(argv[0], "yardim") == 0) {
            printf("\nKomutlar:\n");
            printf("  pati     = Supriz komutu\n");
            printf("  uname    = Sistem bilgisi\n");
            printf("  cat      = Dosya okur\n");
            printf("  temizle  = Ekrani temizler\n");
            printf("  ls       = Klasorleri listeler\n");
            printf("  mamakabi = RAM bilgisi\n");
            printf("  psc      = Guvenlik kontrol sistemi\n");
            printf("  2048     = Oyun zamanii!\n");
            printf("  karabas  = Calisan processleri listeler\n");
            printf("  miyav = miyav <adres> (ping)\n");
            printf("  libreturks  = ahem...\n");
            printf("  touch = dosya olusturur\n");
            printf("  patifetch = sistem bilgisi\n");
            printf("  vi       = Editor\n");
            printf("  cikis    = Sistemi kapat\n\n");
        }
        else if (strcmp(argv[0], "patifetch") == 0) {
            pid_t fetch_pid = fork();
            if (fetch_pid == 0) {
                char *args[] = {"/lib/paticommands/patifetch", NULL};
                execv("/lib/paticommands/patifetch", args);
                perror("pati-fetch baslatilmadi");
                exit(EXIT_FAILURE);
            } else if (fetch_pid > 0) {
                wait(NULL);
            } else {
                perror("fork basarisiz");
            }
        }
        else if (strcmp(argv[0], "vi") == 0) {
            pid_t pid = fork();
            if (pid == 0) {
                char *args[] = {"/lib/paticommands/vi", argv[1], NULL};
                execv("/lib/paticommands/vi", args);
                perror("vi calismadi");
                exit(EXIT_FAILURE);
            } else if (pid > 0) {
                wait(NULL);
            }
        }
        else {
            pid_t pid = fork();
            if (pid == 0) {
                execvp(argv[0], argv);
                printf("%s komutu bulunamadi, bi' yardim komutuna bak istersen..\n", argv[0]);
                exit(127);
            } else if (pid > 0) {
                wait(NULL);
            }
        }
    }
}
