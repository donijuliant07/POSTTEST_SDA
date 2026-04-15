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
    Layanan* next;
};

void tukarData(Layanan* a, Layanan* b) {
    int tempId = a->id;
    string tempNama = a->namaHewan;
    string tempJenis = a->jenisPerawatan;
    int tempHarga = a->harga;

    a->id = b->id;
    a->namaHewan = b->namaHewan;
    a->jenisPerawatan = b->jenisPerawatan;
    a->harga = b->harga;

    b->id = tempId;
    b->namaHewan = tempNama;
    b->jenisPerawatan = tempJenis;
    b->harga = tempHarga;
}

void linearSearchNama(Layanan* arr, int n, string target) {
    bool found = false;
    cout << "\n<=== Hasil Pencarian Linear Search ===>\n";
    for (int i = 0; i < n; i++) {
        cout << "Iterasi " << i + 1 << " | Mengecek Nama: " << (arr + i)->namaHewan << "\n";
        if ((arr + i)->namaHewan == target) {
            cout << " -> DITEMUKAN: ID " << (arr + i)->id << " | Pasien: " << (arr + i)->namaHewan
                << " | Perawatan: " << (arr + i)->jenisPerawatan << " | Biaya: Rp" << (arr + i)->harga << "\n\n";
            found = true;
        }
    }
    if (!found) cout << " -> Pasien bernama '" << target << "' tidak ditemukan.\n";
}

void sortByID(Layanan* arr, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if ((arr + j)->id > (arr + j + 1)->id) {
                tukarData((arr + j), (arr + j + 1));
            }
        }
    }
}

void fibonacciSearchID(Layanan* arr, int n, int target) {
    if (n == 0) return;
    sortByID(arr, n);
    cout << "\n[Sistem] Data diurutkan berdasarkan ID untuk Fibonacci Search.\n";

    int fibMMm2 = 0;
    int fibMMm1 = 1;
    int fibM = fibMMm2 + fibMMm1;

    while (fibM < n) {
        fibMMm2 = fibMMm1;
        fibMMm1 = fibM;
        fibM = fibMMm2 + fibMMm1;
    }

    int offset = -1;
    int iterasi = 1;

    cout << "<=== Proses Iterasi Fibonacci Search ===>\n";
    while (fibM > 1) {
        int i = min(offset + fibMMm2, n - 1);
        cout << "Iterasi " << iterasi++ << " | Mengecek Index " << i << " (ID: " << (arr + i)->id << ")\n";

        if ((arr + i)->id < target) {
            cout << " -> ID lebih kecil. Buang area kiri, geser ke KANAN.\n";
            fibM = fibMMm1;
            fibMMm1 = fibMMm2;
            fibMMm2 = fibM - fibMMm1;
            offset = i;
        } else if ((arr + i)->id > target) {
            cout << " -> ID lebih besar. Buang area kanan, geser ke KIRI.\n";
            fibM = fibMMm2;
            fibMMm1 = fibMMm1 - fibMMm2;
            fibMMm2 = fibM - fibMMm1;
        } else {
            cout << " -> TARGET DITEMUKAN!\n\n";
            cout << "ID: " << (arr + i)->id << " | Pasien: " << (arr + i)->namaHewan
                << " | Perawatan: " << (arr + i)->jenisPerawatan << " | Biaya: Rp" << (arr + i)->harga << "\n";
            return;
        }
    }

    if (fibMMm1 && offset + 1 < n && (arr + offset + 1)->id == target) {
        cout << "Iterasi Terakhir | Mengecek Index " << offset + 1 << "\n";
        cout << " -> TARGET DITEMUKAN!\n\n";
        cout << "ID: " << (arr + offset + 1)->id << " | Pasien: " << (arr + offset + 1)->namaHewan
            << " | Perawatan: " << (arr + offset + 1)->jenisPerawatan << " | Biaya: Rp" << (arr + offset + 1)->harga << "\n";
        return;
    }

    cout << "\n[!] Data Layanan dengan ID '" << target << "' tidak ditemukan.\n";
}

void bubbleSortNama(Layanan* arr, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if ((arr + j)->namaHewan > (arr + j + 1)->namaHewan) {
                tukarData((arr + j), (arr + j + 1));
            }
        }
    }
    cout << "\n<=== Data berhasil diurutkan berdasarkan Nama Pasien (A-Z) ===>\n";
}

bool isQueueEmpty(Layanan* front) {
    return front == NULL;
}

void enqueue(Layanan*& front, Layanan*& rear, Layanan dataBaru) {
    Layanan* newNode = new Layanan;
    newNode->id = dataBaru.id;
    newNode->namaHewan = dataBaru.namaHewan;
    newNode->jenisPerawatan = dataBaru.jenisPerawatan;
    newNode->harga = dataBaru.harga;
    newNode->next = NULL;

    if (front == NULL) {
        front = newNode;
        rear = newNode;
    } else {
        rear->next = newNode;
        rear = newNode;
    }
    cout << "Pasien " << dataBaru.namaHewan << " berhasil masuk ke antrian pemeriksaan!\n";
}

void tampilAntrian(Layanan* front) {
    cout << "\n<=== Daftar Antrian Pemeriksaan (Front ke Rear) ===>\n";
    if (isQueueEmpty(front)) {
        cout << "Antrian pemeriksaan kosong.\n";
        return;
    }
    cout << left << setw(5) << "ID" << setw(15) << "Nama Pasien" << setw(20) << "Jenis Perawatan" << "Harga\n";
    Layanan* temp = front;
    while (temp != NULL) {
        cout << left << setw(5) << temp->id
            << setw(15) << temp->namaHewan
            << setw(20) << temp->jenisPerawatan
            << "Rp" << temp->harga << "\n";
        temp = temp->next;
    }
}

void push(Layanan*& top, Layanan dataBaru) {
    Layanan* newNode = new Layanan;
    newNode->id = dataBaru.id;
    newNode->namaHewan = dataBaru.namaHewan;
    newNode->jenisPerawatan = dataBaru.jenisPerawatan;
    newNode->harga = dataBaru.harga;
    newNode->next = top;
    top = newNode;
    cout << "[Riwayat] Tindakan pasien " << dataBaru.namaHewan << " berhasil dicatat.\n";
}

void pop(Layanan*& top) {
    if (top == NULL) {
        cout << "Stack underflow! Tidak ada riwayat yang bisa dibatalkan.\n";
        return;
    }
    Layanan* temp = top;
    top = top->next;
    cout << "Riwayat tindakan untuk pasien '" << temp->namaHewan << "' telah dibatalkan (dihapus).\n";
    delete temp;
}

void tampilRiwayat(Layanan* top) {
    cout << "\n<=== Riwayat Tindakan Medis (Terbaru ke Terlama) ===>\n";
    if (top == NULL) {
        cout << "Riwayat tindakan masih kosong.\n";
        return;
    }
    cout << left << setw(5) << "ID" << setw(15) << "Nama Pasien" << setw(20) << "Jenis Perawatan" << "Harga\n";
    Layanan* temp = top;
    while (temp != NULL) {
        cout << left << setw(5) << temp->id
            << setw(15) << temp->namaHewan
            << setw(20) << temp->jenisPerawatan
            << "Rp" << temp->harga << "\n";
        temp = temp->next;
    }
}

void panggilPasien(Layanan*& front, Layanan*& rear, Layanan*& top) {
    if (isQueueEmpty(front)) {
        cout << "Queue underflow! Tidak ada pasien di antrian.\n";
        return;
    }

    Layanan* temp = front;
    front = front->next;

    if (front == NULL) {
        rear = NULL;
    }

    cout << "\n>>> DOKTER MEMANGGIL PASIEN <<<\n";
    cout << "Memeriksa Pasien ID: " << temp->id << " | Nama: " << temp->namaHewan << "\n";

    push(top, *temp);
    delete temp;
}

void peekAntrianDanRiwayat(Layanan* front, Layanan* top) {
    cout << "\n<=== Informasi Terdepan & Terakhir (PEEK) ===>\n";
    cout << "[Pasien Terdepan Antrian]: ";
    if (front == NULL) {
        cout << "KOSONG\n";
    } else {
        cout << "ID " << front->id << " - " << front->namaHewan << " (Menunggu giliran)\n";
    }

    cout << "[Tindakan Terakhir Riwayat]: ";
    if (top == NULL) {
        cout << "KOSONG\n";
    } else {
        cout << "ID " << top->id << " - " << top->namaHewan << " (Telah diperiksa)\n";
    }
}

void tampilData(Layanan* arr, int n) {
    cout << "\n<=== Database Layanan Pasien Klinik ===>\n";
    if (n == 0) {
        cout << "Data masih kosong.\n";
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

void tambahData(Layanan* arr, int& n) {
    cout << "\n<=== Tambah Data Database Klinik ===>\n";
    cout << "Masukkan ID Layanan (Angka): ";
    cin >> (arr + n)->id;
    cin.ignore();
    cout << "Masukkan Nama Pasien (Hewan): ";
    getline(cin, (arr + n)->namaHewan);
    cout << "Masukkan Jenis Perawatan (Grooming/Vaksin/dll): ";
    getline(cin, (arr + n)->jenisPerawatan);
    cout << "Masukkan Biaya: ";
    cin >> (arr + n)->harga;
    (arr + n)->next = NULL;
    n++;
    cout << "Data berhasil ditambahkan ke database!\n";
}

int main() {
    Layanan dataKlinik[100];
    Layanan* ptrData = dataKlinik;

    Layanan* queueFront = NULL;
    Layanan* queueRear = NULL;
    Layanan* stackTop = NULL;

    int jumlahData = 0;
    int pilihan;

    while (true) {
        system("cls");

        cout << "|===============================================|\n";
        cout << "|       KLINIK VETCARE & PET SPA BY DONI        |\n";
        cout << "|===============================================|\n";
        cout << "| DATABASE PASIEN:                              |\n";
        cout << "| 1. Tampil Database Layanan                    |\n";
        cout << "| 2. Tambah Database Baru                       |\n";
        cout << "| 3. Cari Pasien by Nama (Linear Search)        |\n";
        cout << "| 4. Cari Pasien by ID (Fibonacci Search)       |\n";
        cout << "| 5. Urutkan Database by Nama (Bubble Sort)     |\n";
        cout << "|-----------------------------------------------|\n";
        cout << "| MANAJEMEN ANTRIAN (QUEUE) & RIWAYAT (STACK):  |\n";
        cout << "| 6. Masukkan Pasien ke Antrian (Enqueue)       |\n";
        cout << "| 7. Tampil Antrian Pemeriksaan                 |\n";
        cout << "| 8. Panggil Pasien Pemeriksaan (Dequeue & Push)|\n";
        cout << "| 9. Tampil Riwayat Tindakan Medis (Stack)      |\n";
        cout << "| 10.Batalkan Riwayat Terakhir (Pop Stack)      |\n";
        cout << "| 11.Intip Pasien Depan & Riwayat (Peek)        |\n";
        cout << "|-----------------------------------------------|\n";
        cout << "| 0. Keluar                                     |\n";
        cout << "|===============================================|\n";
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
                tampilData(ptrData, jumlahData);
                break;
            case 2:
                tambahData(ptrData, jumlahData);
                break;
            case 3: {
                if (jumlahData == 0) { cout << "Data kosong!\n"; break; }
                string cariNama;
                cout << "\nMasukkan Nama Pasien yang dicari: ";
                cin.ignore();
                getline(cin, cariNama);
                linearSearchNama(ptrData, jumlahData, cariNama);
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
                    fibonacciSearchID(ptrData, jumlahData, cariID);
                }
                break;
            }
            case 5:
                if (jumlahData == 0) { cout << "Data kosong!\n"; break; }
                bubbleSortNama(ptrData, jumlahData);
                tampilData(ptrData, jumlahData);
                break;
            case 6: {
                Layanan pasienAntri;
                cout << "\n<=== Registrasi Antrian Pasien Baru ===>\n";
                cout << "Masukkan ID Antrian (Angka): ";
                cin >> pasienAntri.id;
                cin.ignore();
                cout << "Masukkan Nama Pasien (Hewan): ";
                getline(cin, pasienAntri.namaHewan);
                cout << "Masukkan Keluhan/Perawatan: ";
                getline(cin, pasienAntri.jenisPerawatan);
                cout << "Masukkan Estimasi Biaya: ";
                cin >> pasienAntri.harga;
                enqueue(queueFront, queueRear, pasienAntri);
                break;
            }
            case 7:
                tampilAntrian(queueFront);
                break;
            case 8:
                panggilPasien(queueFront, queueRear, stackTop);
                break;
            case 9:
                tampilRiwayat(stackTop);
                break;
            case 10:
                pop(stackTop);
                break;
            case 11:
                peekAntrianDanRiwayat(queueFront, stackTop);
                break;
            default:
                cout << "Pilihan tidak valid! Silakan coba lagi.\n";
        }
        cout << "\n";
        system("pause");
    }
    return 0;
}