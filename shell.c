#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <termios.h>

int main() {
    printf("pati@tr> ");
    fflush(stdout);
    char girdi[256];
    scanf("%s", girdi);

    if (strcmp(girdi, "pati") == 0) {
        printf("Miyavv!");
    }
}