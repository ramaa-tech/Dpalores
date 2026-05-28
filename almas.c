// almas.c
#include "struktur.h"

void detail_lirik(User u) {
    FILE *f = fopen("lirik.dat", "rb");
    Lirik temp;
    int id_cari;
    bool ketemu = false;

    if (f == NULL) return;

    printf("\nMasukkan ID Lagu yang ingin dibaca: ");
    scanf("%d", &id_cari); getchar();

    while (fread(&temp, sizeof(Lirik), 1, f) == 1) {
        if (temp.id == id_cari) {
            ketemu = true;
            // Pengecekan Akses Premium/Basic
            if (temp.is_premium == 1 && u.is_premium == 0) {
                printf("\n[AKSES DITOLAK] Lagu ini eksklusif untuk akun Premium.\n");
            } else {
                printf("\n===================================\n");
                printf("Judul : %s\nArtis : %s\n", temp.judul, temp.artis);
                printf("===================================\n");
                printf("%s\n", temp.lirik);
                printf("===================================\n");
            }
            break;
        }
    }
    fclose(f);
    if (!ketemu) printf("ID Lagu tidak ditemukan.\n");
}