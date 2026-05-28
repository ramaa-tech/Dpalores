// fazza.c
#include "struktur.h"

void pencarian_lirik(User u) {
    FILE *f = fopen("lirik.dat", "rb");
    Lirik temp;
    char keyword[50];
    int pilihan;
    bool ketemu = false;

    if (f == NULL) { printf("Belum ada lirik.\n"); return; }

    printf("\nCari berdasarkan:\n1. Judul\n2. Artis\nPilihan: ");
    scanf("%d", &pilihan); getchar();
    printf("Masukkan kata kunci: "); 
    fgets(keyword, sizeof(keyword), stdin); keyword[strcspn(keyword, "\n")] = 0;

    printf("\n--- Hasil Pencarian ---\n");
    while (fread(&temp, sizeof(Lirik), 1, f) == 1) {
        if (pilihan == 1 && strstr(temp.judul, keyword) != NULL) {
            printf("ID: %d | Judul: %s | Artis: %s\n", temp.id, temp.judul, temp.artis);
            ketemu = true;
        } else if (pilihan == 2 && strstr(temp.artis, keyword) != NULL) {
            printf("ID: %d | Judul: %s | Artis: %s\n", temp.id, temp.judul, temp.artis);
            ketemu = true;
        }
    }
    fclose(f);11
    if (!ketemu) printf("Pencarian tidak ditemukan.\n");
}