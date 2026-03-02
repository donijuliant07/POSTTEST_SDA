#include <iostream>
using namespace std;

void reverseArray(int* arr, int n) {
    int* start = arr;         
    int* end = arr + n - 1;    

    while (start < end) {
        int temp = *start;
        *start = *end;
        *end = temp;

        start++;  
        end--;  
    }
}

int main() {
    const int n = 7;
    int arr[n] = {2, 3, 5, 7, 11, 13, 17};

    
    cout << "Array sebelum dibalik:\n";
    int* p = arr; 
    for (int i = 0; i < n; i++) {
        cout << "Nilai: " << *(p+i) << ", Alamat: " << (p+i) << endl;
    }

    
    reverseArray(arr, n);

    // Tampilkan array sesudah dibalik
    cout << "\nArray sesudah dibalik:\n";
    for (int i = 0; i < n; i++) {
        cout << "Nilai: " << *(p+i) << ", Alamat: " << (p+i) << endl;
    }

    return 0;
}