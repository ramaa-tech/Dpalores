// rasya.c
#include "struktur.h"

void register_user() {
    FILE *f = fopen("users.dat", "ab");
    User u;

    printf("\n--- REGISTRASI USER ---\n");
    printf("Username: "); fgets(u.username, sizeof(u.username), stdin); u.username[strcspn(u.username, "\n")] = 0;
    printf("Password: "); fgets(u.password, sizeof(u.password), stdin); u.password[strcspn(u.password, "\n")] = 0;
    u.is_premium = 0;
    u.saldo = 0.0;

    fwrite(&u, sizeof(User), 1, f);
    fclose(f);
    printf("Registrasi Berhasil! Silakan Login.\n");
}

void login_user() {
    User u, temp;
    bool sukses = false;
    FILE *f;

    printf("\n--- LOGIN USER ---\n");
    // Menggunakan For Loop (3x Kesempatan)
    for (int i = 0; i < 3; i++) {
        printf("Username: "); fgets(u.username, sizeof(u.username), stdin); u.username[strcspn(u.username, "\n")] = 0;
        printf("Password: "); fgets(u.password, sizeof(u.password), stdin); u.password[strcspn(u.password, "\n")] = 0;

        f = fopen("users.dat", "rb");
        if (f != NULL) {
            while (fread(&temp, sizeof(User), 1, f) == 1) {
                if (strcmp(temp.username, u.username) == 0 && strcmp(temp.password, u.password) == 0) {
                    sukses = true;
                    u = temp;
                    break;
                }
            }
            fclose(f);
        }

        if (sukses) {
            printf("Login Sukses!\n");
            menu_user(u);
            return;
        } else {
            printf("Login Gagal! Sisa percobaan: %d\n", 2 - i);
        }
    }
}