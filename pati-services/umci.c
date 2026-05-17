// Uluslararası Mobil Cihaz ID Generator - Comments by mehmetdemir-tr
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#define VERSIYON "Pati 2.1"

int main() {
    FILE *fp;
    FILE *fpointer;
    char mac[20];
    char alphabet[] = "abcdefghijklmnopqrstuvwxyz0123456789";
    char word[5];
    unsigned char rastgele[4];

    fpointer = fopen("/dev/urandom", "rb");
    if (fpointer == NULL) {
        perror("urandom acilamadi");
        return -1;
    }
    fread(rastgele, 1, 4, fpointer);
    fclose(fpointer);

    for (int i = 0; i < 4; i++) {
        word[i] = alphabet[rastgele[i] % 36];
    }
    word[4] = '\0';
    // printf("Rastgele word: %s\n", word);

    fp = fopen("/sys/class/net/eth0/address", "r");
    if (fp == NULL) {
        perror("Mac Adresi yok?");
        return -1;
    }
    if (fgets(mac, sizeof(mac), fp) != NULL) {
        // printf("MAC Adresi: %s\n", mac);
    }

char mac_kisim[12];
strncpy(mac_kisim, mac, 11);
mac_kisim[11] = '\0';


int sol = 0, sag = 10;
while (sol < sag) {
    char tmp = mac_kisim[sol];
    mac_kisim[sol] = mac_kisim[sag];
    mac_kisim[sag] = tmp;
    sol++;
    sag--;
}
char umci[50];
snprintf(umci, sizeof(umci), "UI-%s-%s-Pati2.1-Pineapple", word, mac_kisim);
// printf("%s\n", umci);

if (access("/etc/device.umci", F_OK) == 0) {
    FILE* fl = fopen("/etc/device.umci", "r");
    if (fl == NULL) { perror("umci okunamadi"); fclose(fp); return -1; }
    char umcio[50];
    size_t okunan = fread(umcio, 1, 49, fl);
    umcio[okunan] = '\0';
    printf("Uluslararasi Mobil Cihaz ID: %s\n", umcio);
    fclose(fl);
} else {
    FILE* fl = fopen("/etc/device.umci", "w");
    if (fl == NULL) { perror("umci yazilamadi"); fclose(fp); return -1; }
    fprintf(fl, "%s\n", umci);
    fclose(fl);
}


    return 0;
}