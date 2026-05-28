// rafi.c
#include "struktur.h"

void daftar_lirik(User u) {
    FILE *f = fopen("lirik.dat", "rb");
    if (f == NULL) { printf("Belum ada lirik.\n"); return; }

    int count = 0;
    Lirik temp;
    while (fread(&temp, sizeof(Lirik), 1, f) == 1) count++;
    fclose(f);

    Lirik *list = (Lirik *)malloc(count * sizeof(Lirik));
    f = fopen("lirik.dat", "rb");
    fread(list, sizeof(Lirik), count, f);
    fclose(f);

    int sort_pilih;
    printf("\nUrutkan berdasarkan:\n1. Judul (A-Z)\n2. Tahun Rilis\nPilihan: ");
    scanf("%d", &sort_pilih); getchar();

    // Bubble Sort
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            bool swap = false;
            if (sort_pilih == 1) {
                if (strcmp(list[j].judul, list[j+1].judul) > 0) swap = true;
            } else if (sort_pilih == 2) {
                if (list[j].tahun > list[j+1].tahun) swap = true;
            }

            if (swap) {
                Lirik temp_swap = list[j];
                list[j] = list[j+1];
                list[j+1] = temp_swap;
            }
        }
    }

    printf("\n--- DAFTAR LIRIK ---\n");
    for (int i = 0; i < count; i++) {
        printf("ID: %d | Judul: %s | Artis: %s | Tahun: %d | Status: %s\n", 
            list[i].id, list[i].judul, list[i].artis, list[i].tahun, list[i].is_premium ? "Premium" : "Basic");
    }

    free(list);
}