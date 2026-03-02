#include <iostream>
using namespace std;

int FindMin(int A[], int n, int &index) {
    int min = A[0];
    index = 0;
    for (int i = 1; i < n; i++) {
        if (A[i] < min) {
            min = A[i];
            index = i;
        }
    }
    return min;
}

int main() {
    int A[8] = {1, 1, 2, 3, 5, 8, 13, 21};
    int index;
    int minValue = FindMin(A, 8, index);

    cout << "Nilai minimum: " << minValue << endl;
    cout << "Indeks: " << index << endl;

    return 0;
}

/*
        <============ ANALISIS KOMPLEKSITAS ============>

Pseudocode:
1. min ← A[0]                → Cost = 1
2. for i ← 1 to n-1 do       → Cost = n-1
3.   if A[i] < min then      → Cost = n-1 (perbandingan)
4.     min ← A[i]            → Cost ≤ n-1 (hanya jika kondisi benar)
5. return min                → Cost = 1

Tabel Cost (Best Case vs Worst Case):
-------------------------------------------------
Langkah        | Cost Best Case | Cost Worst Case
-------------------------------------------------
Inisialisasi   |       1        |       1
Loop           |     n-1        |     n-1
Perbandingan   |     n-1        |     n-1
Assignment     |       0        |     n-1
Return         |       1        |       1
-------------------------------------------------
Total Tmin(n)  = 2 + (n-1) + (n-1) = 2n             -> O(n)
Total Tmax(n)  = 2 + (n-1) + (n-1) + (n-1) = 3n - 1 -> O(n)
-------------------------------------------------

Eksekusi Manual Alogritma Findmin 
Array A = [1, 1, 2, 3, 5, 8, 13, 21]
Ukuran n = 8

iterasi (i) | nilai A[i] | kondisi (A[i] < min) | nilai min | index min
-----------------------------------------------------------------------
    0       |     1      |         -            |     1     |    0
    1       |     1      |    1 < 1 -> false    |     1     |    0
    2       |     2      |    2 < 1 -> false    |     1     |    0
    3       |     3      |    3 < 1 -> false    |     1     |    0
    4       |     5      |    5 < 1 -> false    |     1     |    0
    5       |     8      |    8 < 1 -> false    |     1     |    0
    6       |    13      |   13 < 1 -> false    |     1     |    0
    7       |    21      |   21 < 1 -> false    |     1     |    0

Nilai minimum: 1
Indeks: 0

Big-O:
- Best Case  : O(n)
- Worst Case : O(n)

Kesimpulan:
Algoritma FindMin memiliki kompleksitas linear O(n), pada best case ataupun worst case.
*/