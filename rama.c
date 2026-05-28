// rama.c
#include "struktur.h"

void laporkan_lirik(User u) {
    FILE *f = fopen("laporan.dat", "ab");
    Laporan lap;

    strcpy(lap.pelapor, u.username);
    printf("\nMasukkan Judul Lagu yang salah: "); fgets(lap.judul_lagu, sizeof(lap.judul_lagu), stdin); lap.judul_lagu[strcspn(lap.judul_lagu, "\n")] = 0;
    printf("Deskripsikan kesalahan lirik: "); fgets(lap.laporan, sizeof(lap.laporan), stdin); lap.laporan[strcspn(lap.laporan, "\n")] = 0;

    fwrite(&lap, sizeof(Laporan), 1, f);
    fclose(f);
    printf("Laporan berhasil dikirim ke Admin.\n");
}

// ================= FITUR BACKEND ADMIN =================
void login_admin() {
    char user[50], pass[50];
    int percobaan = 0;
    bool sukses = false;

    while (percobaan < 3 && !sukses) {
        printf("\n--- LOGIN ADMIN ---\n");
        printf("Username: "); fgets(user, sizeof(user), stdin); user[strcspn(user, "\n")] = 0;
        printf("Password: "); fgets(pass, sizeof(pass), stdin); pass[strcspn(pass, "\n")] = 0;

        if (strcmp(user, "admin") == 0 && strcmp(pass, "admin") == 0) {
            sukses = true;
            printf("Login Sukses!\n");
            menu_admin();
        } else {
            percobaan++;
            printf("Login Gagal! Sisa percobaan: %d\n", 3 - percobaan);
        }
    }
}

void menu_admin() {
    int pilihan;
    do {
        printf("\n--- MENU ADMIN ---\n");
        printf("1. Manajemen Lirik\n");
        printf("2. Laporan User\n");
        printf("0. Logout\n");
        printf("Pilihan: ");
        scanf("%d", &pilihan);
        getchar();

        switch (pilihan) {
            case 1: manajemen_lirik(); break;
            case 2: lihat_laporan_admin(); break;
            case 0: printf("Logout berhasil.\n"); break;
            default: printf("Pilihan tidak valid!\n");
        }
    } while (pilihan != 0);
}

void manajemen_lirik() {
    int pilihan;
    do {
        printf("\n-- Manajemen Lirik --\n");
        printf("1. Tambah Lirik\n");
        printf("2. Edit Lirik\n");
        printf("3. Hapus Lirik\n");
        printf("4. Cari & Lihat Lirik\n");
        printf("0. Kembali\n");
        printf("Pilihan: ");
        scanf("%d", &pilihan);
        getchar();

        switch (pilihan) {
            case 1: tambah_lirik(); break;
            case 2: edit_lirik(); break;
            case 3: hapus_lirik; break;
            case 4: cari_lirik_admin(); break;
            case 0: break;
            default: printf("Pilihan tidak valid.\n");
        }
    } while (pilihan != 0);
}

void tambah_lirik() {
    FILE *f = fopen("lirik.dat", "ab");
    Lirik baru;

    printf("\nMasukkan ID Lagu: "); scanf("%d", &baru.id); getchar();
    printf("Masukkan Artis: "); fgets(baru.artis, sizeof(baru.artis), stdin); baru.artis[strcspn(baru.artis, "\n")] = 0;
    printf("Masukkan Judul: "); fgets(baru.judul, sizeof(baru.judul), stdin); baru.judul[strcspn(baru.judul, "\n")] = 0;
    printf("Masukkan Lirik: "); fgets(baru.lirik, sizeof(baru.lirik), stdin); baru.lirik[strcspn(baru.lirik, "\n")] = 0;
    printf("Masukkan Tahun Rilis: "); scanf("%d", &baru.tahun);
    printf("Status (0=Basic, 1=Premium): "); scanf("%d", &baru.is_premium); getchar();

    fwrite(&baru, sizeof(Lirik), 1, f);
    fclose(f);
    printf("Lirik berhasil ditambahkan!\n");
}

void edit_lirik() {
    FILE *f = fopen("lirik.dat", "rb");
    FILE *ftemp = fopen("temp.dat", "wb");
    Lirik temp;
    int id_cari;
    bool ketemu = false;

    if (f == NULL) { printf("Belum ada data lirik.\n"); return; }

    printf("\nMasukkan ID Lirik yang akan diedit: ");
    scanf("%d", &id_cari); getchar();

    while (fread(&temp, sizeof(Lirik), 1, f) == 1) {
        if (temp.id == id_cari) {
            ketemu = true;
            printf("Artis Baru: "); fgets(temp.artis, sizeof(temp.artis), stdin); temp.artis[strcspn(temp.artis, "\n")] = 0;
            printf("Judul Baru: "); fgets(temp.judul, sizeof(temp.judul), stdin); temp.judul[strcspn(temp.judul, "\n")] = 0;
            printf("Lirik Baru: "); fgets(temp.lirik, sizeof(temp.lirik), stdin); temp.lirik[strcspn(temp.lirik, "\n")] = 0;
            printf("Tahun Rilis Baru: "); scanf("%d", &temp.tahun);
            printf("Status Baru (0=Basic, 1=Premium): "); scanf("%d", &temp.is_premium); getchar();
        }
        fwrite(&temp, sizeof(Lirik), 1, ftemp);
    }
    fclose(f); fclose(ftemp);

    remove("lirik.dat");
    rename("temp.dat", "lirik.dat");

    if (ketemu) printf("Lirik berhasil diedit!\n");
    else printf("ID tidak ditemukan.\n");
}

void hapus_lirik() {
    FILE *f = fopen("lirik.dat", "rb");
    FILE *ftemp = fopen("temp.dat", "wb");
    Lirik temp;
    int id_cari;
    bool ketemu = false;

    if (f == NULL) return;

    printf("\nMasukkan ID Lirik yang akan dihapus: ");
    scanf("%d", &id_cari); getchar();

    while (fread(&temp, sizeof(Lirik), 1, f) == 1) {
        if (temp.id != id_cari) {
            fwrite(&temp, sizeof(Lirik), 1, ftemp);
        } else {
            ketemu = true;
        }
    }
    fclose(f); fclose(ftemp);

    remove("lirik.dat");
    rename("temp.dat", "lirik.dat");

    if (ketemu) printf("Lirik berhasil dihapus!\n");
    else printf("ID tidak ditemukan.\n");
}

void cari_lirik_admin() {
    FILE *f = fopen("lirik.dat", "rb");
    Lirik temp;
    char keyword[50];
    bool ketemu = false;

    if (f == NULL) { printf("Data lirik kosong.\n"); return; }

    printf("\nMasukkan Judul/Artis yang dicari: ");
    fgets(keyword, sizeof(keyword), stdin); keyword[strcspn(keyword, "\n")] = 0;

    while (fread(&temp, sizeof(Lirik), 1, f) == 1) {
        if (strstr(temp.judul, keyword) != NULL || strstr(temp.artis, keyword) != NULL) {
            printf("\nID: %d | Judul: %s | Artis: %s | Tahun: %d | Status: %s\n", 
                temp.id, temp.judul, temp.artis, temp.tahun, temp.is_premium ? "Premium" : "Basic");
            printf("Lirik:\n%s\n", temp.lirik);
            ketemu = true;
        }
    }
    fclose(f);
    if (!ketemu) printf("Lirik tidak ditemukan.\n");
}

void lihat_laporan_admin() {
    FILE *f = fopen("laporan.dat", "rb");
    Laporan temp;
    
    if (f == NULL) { printf("Tidak ada laporan user.\n"); return; }

    printf("\n--- LAPORAN USER ---\n");
    while (fread(&temp, sizeof(Laporan), 1, f) == 1) {
        printf("Pelapor: %s | Lagu: %s\nLaporan: %s\n\n", temp.pelapor, temp.judul_lagu, temp.laporan);
    }
    fclose(f);
}