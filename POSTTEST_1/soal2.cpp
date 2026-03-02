#include <iostream>
#include <string>
using namespace std;

struct Mahasiswa {
    string nama;
    string nim;
    float ipk;
};

int main() {
    const int jumlah = 5;
    Mahasiswa mhs[jumlah];

    cout << "Input data 5 mahasiswa:\n";
    for (int i = 0; i < jumlah; i++) {
        cout << "Mahasiswa ke-" << i+1 << endl;
        cout << "Nama : ";
        cin >> mhs[i].nama; 
        cout << "NIM  : ";
        cin >> mhs[i].nim;
        cout << "IPK  : ";
        cin >> mhs[i].ipk;
        cout << endl;
    }
    
    int idxMax = 0;
    float maxIpk = mhs[0].ipk;
    for (int i = 1; i < jumlah; i++) {
        if (mhs[i].ipk > maxIpk) {
            maxIpk = mhs[i].ipk;
            idxMax = i;
        }
    }

    // Tampilkan hasil
    cout << "\nMahasiswa dengan IPK tertinggi:\n";
    cout << "Nama : " << mhs[idxMax].nama << endl;
    cout << "NIM  : " << mhs[idxMax].nim << endl;
    cout << "IPK  : " << mhs[idxMax].ipk << endl;

    return 0;
}