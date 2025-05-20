#include <iostream>
using namespace std;

void insertionsort(int arr[], int n) {
    for (int i = 1; i < n; i++) { 
        int key = arr[i];
        int pos = i - 1;
        while (pos >= 0 && key < arr[pos]) {
            arr[pos + 1] = arr[pos];
            --pos;
        }
        arr[pos + 1] = key;
    }
}

void findtriplet(int arr[], int n) {
    for (int i = 0; i < n - 2; i++) {  // i chỉ đi đến n-3 để còn đủ 3 phần tử
        // Tránh trùng lặp cho phần tử đầu tiên
        if (i > 0 && arr[i] == arr[i - 1]) {
            continue;  // Nếu phần tử đầu tiên trùng với phần tử trước đó, bỏ qua
        }

        int firstelement = arr[i];
        int left = i + 1;
        int right = n - 1;
        while (left < right) {
            int sum = firstelement + arr[left] + arr[right];
            if (sum == 0) {
                cout << "[" << firstelement << "," << arr[left] << "," << arr[right] << "]" << endl;

                // Di chuyển các con trỏ để tránh trùng lặp
                while (left < right && arr[left] == arr[left + 1]) {
                    left++;
                }
                while (left < right && arr[right] == arr[right - 1]) {
                    right--;
                }

                left++;
                right--;
            }
            else if (sum < 0) {
                left++;
            }
            else {
                right--;
            }
        }
    }
}

int main() {
    int arr[6] = { -1, 0, 1, 2, -1, -4 };
    int n = 6;
    insertionsort(arr, n);  // Sắp xếp mảng
    findtriplet(arr, n);    // Tìm các bộ ba có tổng bằng 0
    return 0;
}