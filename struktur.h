// struktur.h
#ifndef STRUKTUR_H
#define STRUKTUR_H

#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <stdbool.h>

// ================= STRUKTUR DATA =================
typedef struct {
    char username[50];
    char password[50];
    int is_premium; // 0 = Basic, 1 = Premium
    float saldo;
} User;

typedef struct {
    int id;
    char artis[50];
    char judul[50];
    char lirik[500];
    int tahun;
    int is_premium; // 0 = Basic, 1 = Premium
} Lirik;

typedef struct {
    char pelapor[50];
    char judul_lagu[50];
    char laporan[200];
} Laporan;

// ================= DEKLARASI FUNGSI GLOBAL =================
void menu_utama();
void login_admin();
void menu_admin();
void manajemen_lirik();
void tambah_lirik();
void edit_lirik();
void hapus_lirik();
void cari_lirik_admin();
void lihat_laporan_admin();

// Fitur 1 & 2: Rasya
void register_user();
void login_user();
void menu_user(User u);

// Fitur 3: Ahid
void topup_saldo(User *u);
void upgrade_premium(User *u);
void update_user_file(User u);

// Fitur 4: Rafi
void daftar_lirik(User u);

// Fitur 5: Fazza
void pencarian_lirik(User u);

// Fitur 6: Almas
void detail_lirik(User u);

// Fitur 7: Rama
void laporkan_lirik(User u);

#endif