#include <iostream>
#include <string>
#include <iomanip>
#include <algorithm> 
#include <cstdlib> 

using namespace std;


struct Layanan {
    int id;
    string namaHewan;
    string jenisPerawatan;
    int harga;
};


void tukarData(Layanan* a, Layanan* b) {
    Layanan temp = *a;
    *a = *b;
    *b = temp;
}

void tampilData(Layanan* arr, int n) {
    cout << "\n<=== Daftar Antrian VetCare & Pet Spa By Doni ===>\n";
    if (n == 0) {
        cout << "Data antrian masih kosong.\n";
        return;
    }
    cout << left << setw(5) << "ID" << setw(15) << "Nama Pasien" << setw(20) << "Jenis Perawatan" << "Harga\n";
    for (int i = 0; i < n; i++) {
        
        cout << left << setw(5) << (arr + i)->id
            << setw(15) << (arr + i)->namaHewan
            << setw(20) << (arr + i)->jenisPerawatan
            << "Rp" << (arr + i)->harga << "\n";
    }
}


void tambahData(Layanan* arr, int &n) {
    cout << "\n<=== Tambah Pasien Baru ===>\n";
    cout << "Masukkan ID Layanan (Angka): ";
    cin >> (arr + n)->id;
    cin.ignore();
    cout << "Masukkan Nama Pasien (Hewan): ";
    getline(cin, (arr + n)->namaHewan);
    cout << "Masukkan Jenis Perawatan (Grooming/Vaksin/Steril/dll): ";
    getline(cin, (arr + n)->jenisPerawatan);
    cout << "Masukkan Biaya: ";
    cin >> (arr + n)->harga;
    n++;
    cout << "Data pasien berhasil ditambahkan!\n";
}


void linearSearchNama(Layanan* arr, int n, string target) {
    bool found = false;
    cout << "\n<=== Hasil Pencarian Linear Search ===>\n";
    for (int i = 0; i < n; i++) {
        if ((arr + i)->namaHewan == target) {
            cout << "Ditemukan: ID " << (arr + i)->id << " | Pasien: " << (arr + i)->namaHewan 
                << " | Perawatan: " << (arr + i)->jenisPerawatan << " | Biaya: Rp" << (arr + i)->harga << "\n";
            found = true;
        }
    }
    if (!found) cout << "Pasien bernama '" << target << "' tidak ditemukan.\n";
}


void sortByID(Layanan* arr, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if ((arr + j)->id > (arr + j + 1)->id) {
                
                tukarData(&(arr[j]), &(arr[j + 1]));
            }
        }
    }
}

// Fibonacci Search cari berdasarkan ID Layanan
void fibonacciSearchID(Layanan* arr, int n, int target) {
    if (n == 0) return;
    
    // Fibonacci Search butuh data yang urut. Kita urutkan ID-nya dulu.
    sortByID(arr, n);
    cout << "\n[Sistem] Data otomatis diurutkan berdasarkan ID untuk Fibonacci Search.\n";

    // --- TAHAP 1: INISIALISASI DERET FIBONACCI ---
    // Kita butuh 3 angka Fibonacci berurutan untuk menentukan ukuran pembagian area.
    int fibMMm2 = 0;   // F(m-2) -> Nantinya jadi penentu ukuran area kiri
    int fibMMm1 = 1;   // F(m-1) -> Nantinya jadi penentu ukuran area kanan
    int fibM = fibMMm2 + fibMMm1;  // F(m) -> Total ukuran area pencarian saat ini

    // Looping untuk mencari angka Fibonacci (Fm) yang ukurannya
    // lebih besar atau sama dengan jumlah data (n).
    // Tujuannya agar seluruh array bisa tercakup dalam rentang pencarian awal.
    while (fibM < n) {
        fibMMm2 = fibMMm1;
        fibMMm1 = fibM;
        fibM = fibMMm2 + fibMMm1;
    }

    // offset adalah penanda indeks yang sudah 'dieleminasi' (dibuang) dari pencarian.
    // Awalnya -1 karena belum ada data yang dibuang (kita mulai dari paling kiri array).
    int offset = -1; 
    int iterasi = 1;

    cout << "<=== Proses Iterasi Fibonacci Search ===>\n";
    
    // --- TAHAP 2: PROSES ITERASI (PEMBAGIAN AREA) ---
    // Looping pencarian akan terus berjalan selama area masih bisa dibagi (Fm > 1)
    while (fibM > 1) {
        // Menentukan index 'i' yang akan dicek pada iterasi ini. 
        // Rumusnya: batas offset ditambah lompatan sejauh F(m-2).
        // min() digunakan agar jika lompatan melebihi ukuran array, 
        // kita mentok di index terakhir (n - 1) supaya tidak error "out of bounds".
        int i = min(offset + fibMMm2, n - 1);
        
        cout << "Iterasi " << iterasi++ << " | Mengecek Index " << i << " (ID: " << (arr + i)->id << ")\n";

        // KONDISI A: Jika ID di index saat ini LEBIH KECIL dari target
        if ((arr + i)->id < target) {
            cout << " -> ID lebih kecil. Buang area kiri, geser pencarian ke KANAN.\n";
            // Penjelasan Logika: Karena target ada di kanan, area kiri sebesar F(m-2) kita buang.
            // Sisa area pencarian sekarang ukurannya adalah F(m-1).
            // Maka, deret Fibonacci diturunkan 1 tingkat ke bawah:
            fibM = fibMMm1;           // Fm turun jadi Fm-1
            fibMMm1 = fibMMm2;        // Fm-1 turun jadi Fm-2
            fibMMm2 = fibM - fibMMm1; // Fm-2 disesuaikan untuk iterasi berikutnya
            
            // Batas offset digeser maju ke titik 'i' karena semua data dari 
            // kiri sampai index 'i' sudah pasti lebih kecil dari target (telah dieleminasi).
            offset = i;
        } 
        // KONDISI B: Jika ID di index saat ini LEBIH BESAR dari target
        else if ((arr + i)->id > target) {
            cout << " -> ID lebih besar. Buang area kanan, geser pencarian ke KIRI.\n";
            // Penjelasan Logika: Karena target ada di kiri, area kanan sebesar F(m-1) kita buang.
            // Sisa area pencarian sekarang ukurannya lebih kecil, yaitu F(m-2).
            // Maka, deret Fibonacci langsung diturunkan 2 tingkat ke bawah:
            fibM = fibMMm2;              // Fm langsung turun jadi Fm-2
            fibMMm1 = fibMMm1 - fibMMm2; // Hitung mundur nilai Fm-1 yang baru
            fibMMm2 = fibM - fibMMm1;    // Hitung mundur nilai Fm-2 yang baru
            
            // offset TIDAK BERUBAH karena batas kiri area pencarian kita masih sama.
        } 
        // KONDISI C: Jika ID COCOK dengan target
        else {
            cout << " -> Target ditemukan pada iterasi ini!\n";
            cout << "\n=== Hasil Pencarian ===\n";
            cout << "ID: " << (arr + i)->id << " | Pasien: " << (arr + i)->namaHewan 
                << " | Perawatan: " << (arr + i)->jenisPerawatan << " | Biaya: Rp" << (arr + i)->harga << "\n";
            return; // Langsung keluar dari fungsi karena data sudah ketemu
        }
    }

    // --- TAHAP 3: CEK SISA ELEMEN TERAKHIR ---
    // Kasus khusus: Jika setelah looping di atas target belum ketemu, 
    // tapi nilai fibMMm1 masih 1, artinya masih tersisa 1 elemen terakhir 
    // di sebelah kanan offset yang belum dicek. Kita cek secara manual.
    if (fibMMm1 && offset + 1 < n && (arr + offset + 1)->id == target) {
        cout << "Iterasi Terakhir | Mengecek Index " << offset + 1 << "\n";
        cout << " -> Target ditemukan!\n";
        cout << "\n<=== Hasil Pencarian ===>\n";
        cout << "ID: " << (arr + offset + 1)->id << " | Pasien: " << (arr + offset + 1)->namaHewan 
            << " | Perawatan: " << (arr + offset + 1)->jenisPerawatan << " | Biaya: Rp" << (arr + offset + 1)->harga << "\n";
        return;
    }

    // Jika sampai baris ini dieksekusi, berarti seluruh area sudah dicari dan kosong.
    cout << "\n[!] Data Layanan dengan ID '" << target << "' tidak ditemukan.\n";
}


void bubbleSortNama(Layanan* arr, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if ((arr + j)->namaHewan > (arr + j + 1)->namaHewan) {
                tukarData(&(arr[j]), &(arr[j + 1]));
            }
        }
    }
    cout << "\n<=== Data berhasil diurutkan berdasarkan Nama Pasien (A-Z) ===>\n";
}


void selectionSortHarga(Layanan* arr, int n) {
    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < n; j++) {
            if ((arr + j)->harga < (arr + min_idx)->harga) {
                min_idx = j;
            }
        }
        if (min_idx != i) {
            tukarData(&(arr[i]), &(arr[min_idx]));
        }
    }
    cout << "\n<== Data berhasil diurutkan berdasarkan Biaya (Termurah - Termahal) ===>\n";
}

// Program Utama
int main() {
    Layanan dataKlinik[100];
    int jumlahData = 0;
    int pilihan;

    while (true) {
        system("cls");

        cout << "|==============================================|\n";
        cout << "|       KLINIK VETCARE & PET SPA BY DONI       |\n";
        cout << "|==============================================|\n";
        cout << "|1. Tampil Semua Antrian                       |\n";
        cout << "|2. Tambah Pasien Baru                         |\n";
        cout << "|3. Cari Pasien by Nama (Linear Search)        |\n";
        cout << "|4. Cari Antrian by ID (Fibonacci Search)      |\n";
        cout << "|5. Urutkan by Nama A-Z (Bubble Sort)          |\n";
        cout << "|6. Urutkan by Biaya Termurah (Selection Sort) |\n";
        cout << "|0. Keluar                                     |\n";
        cout << "|==============================================|\n";
        cout << "Pilih Menu: ";
        
        if (!(cin >> pilihan)) { 
            cout << "Input harus berupa angka!\n";
            cin.clear(); 
            cin.ignore(1000, '\n'); 
            system("pause");
            continue;
        }

        if (pilihan == 0) {
            cout << "\nTerima kasih telah menggunakan sistem VetCare by Doni!\n";
            break;
        }

        switch (pilihan) {
            case 1:
                tampilData(dataKlinik, jumlahData);
                break;
            case 2:
                tambahData(dataKlinik, jumlahData);
                break;
            case 3: {
                if (jumlahData == 0) { cout << "Data kosong!\n"; break; }
                string cariNama;
                cout << "\nMasukkan Nama Pasien yang dicari: ";
                cin.ignore();
                getline(cin, cariNama);
                linearSearchNama(dataKlinik, jumlahData, cariNama);
                break;
            }
            case 4: {
                if (jumlahData == 0) { cout << "Data kosong!\n"; break; }
                int cariID;
                cout << "\nMasukkan ID Antrian yang dicari: ";
                if (!(cin >> cariID)) {
                    cout << "ID harus berupa angka!\n";
                    cin.clear(); cin.ignore(1000, '\n');
                } else {
                    fibonacciSearchID(dataKlinik, jumlahData, cariID);
                }
                break;
            }
            case 5:
                if (jumlahData == 0) { cout << "Data kosong!\n"; break; }
                bubbleSortNama(dataKlinik, jumlahData);
                tampilData(dataKlinik, jumlahData);
                break;
            case 6:
                if (jumlahData == 0) { cout << "Data kosong!\n"; break; }
                selectionSortHarga(dataKlinik, jumlahData);
                tampilData(dataKlinik, jumlahData);
                break;
            default:
                cout << "Pilihan tidak valid! Silakan coba lagi.\n";
        }
        
        cout << "\n";
        system("pause");
    }
    return 0;
}