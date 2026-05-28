// ahid.c
#include "struktur.h"

void update_user_file(User u) {
    FILE *f = fopen("users.dat", "rb");
    FILE *ftemp = fopen("temp_u.dat", "wb");
    User temp;

    while (fread(&temp, sizeof(User), 1, f) == 1) {
        if (strcmp(temp.username, u.username) == 0) {
            fwrite(&u, sizeof(User), 1, ftemp);
        } else {
            fwrite(&temp, sizeof(User), 1, ftemp);
        }
    }
    fclose(f); fclose(ftemp);
    remove("users.dat");
    rename("temp_u.dat", "users.dat");
}

void topup_saldo(User *u) {
    float nominal;
    printf("\nMasukkan nominal top-up: ");
    scanf("%f", &nominal); getchar();
    
    u->saldo += nominal;
    update_user_file(*u);
    printf("Top-up berhasil! Saldo anda sekarang: Rp%.2f\n", u->saldo);
}

void upgrade_premium(User *u) {
    if (u->is_premium == 1) {
        printf("\nAkun Anda sudah Premium!\n");
        return;
    }
    
    if (u->saldo >= 50000) {
        u->saldo -= 50000;
        u->is_premium = 1;
        update_user_file(*u);
        printf("\nSelamat! Akun Anda kini menjadi Premium.\n");
    } else {
        printf("\nSaldo tidak mencukupi. Harga Premium Rp50000. Saldo Anda: Rp%.2f\n", u->saldo);
    }
}