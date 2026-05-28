// main.c
#include "struktur.h"

int main() {
    menu_utama();
    return 0;
}

void menu_utama() {
    int pilihan;
    do {
        printf("\n====================================\n");
        printf("        APLIKASI DPAROLES           \n");
        printf("====================================\n");
        printf("1. Login Admin\n");
        printf("2. Registrasi User\n");
        printf("3. Login User\n");
        printf("0. Keluar\n");
        printf("Pilihan: ");
        scanf("%d", &pilihan);
        getchar();

        switch (pilihan) {
            case 1: login_admin(); break;
            case 2: register_user(); break;
            case 3: login_user(); break;
            case 0: printf("Terima kasih telah menggunakan DParoles.\n"); break;
            default: printf("Pilihan tidak valid!\n");
        }
    } while (pilihan != 0);
}

void menu_user(User u) {
    int pilihan;
    do {
        printf("\n--- MENU USER ---\n");
        printf("Halo, %s (Status: %s) | Saldo: Rp%.2f\n", 
            u.username, u.is_premium ? "Premium" : "Basic", u.saldo);
        printf("1. Top-Up Saldo\n");
        printf("2. Upgrade Premium\n");
        printf("3. Daftar Lirik (Sorting)\n");
        printf("4. Cari Lirik\n");
        printf("5. Detail Lirik & Baca Lirik\n");
        printf("6. Laporkan Lirik\n");
        printf("0. Logout\n");
        printf("Pilihan: ");
        scanf("%d", &pilihan);
        getchar();

        switch (pilihan) {
            case 1: topup_saldo(&u); break; 
            case 2: upgrade_premium(&u); break;
            case 3: daftar_lirik(u); break;
            case 4: pencarian_lirik(u); break;
            case 5: detail_lirik(u); break;
            case 6: laporkan_lirik(u); break;
            case 0: printf("Logout...\n"); break;
            default: printf("Pilihan salah.\n");
        }
    } while (pilihan != 0);
}