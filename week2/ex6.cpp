#include <iostream>
using namespace std;
// Hàm kiểm tra xem có một cặp số trong mảng có tổng bằng target hay không
bool checkequal(int arr[], int low, int high, int n, int target) {
    low = 0;
    high = n - 1;
    // Duyệt mảng với hai con trỏ, low và high
    while (low < high) {
        int sum = arr[low] + arr[high];// Tính tổng của hai phần tử tại vị trí low và high
        if (sum == target) {
            return true;//Trả về true nếu tìm thấy
        }
        else if (sum < target) {
            low++;// Tăng con trỏ low lên để tìm tổng lớn hơn
        }
        else {
            high--;// Giảm con trỏ high xuống để tìm tổng nhỏ hơ
        }
    }
    return false;// Trả về false nếu không tìm thấy cặp có tổng bằng target
}
int main() {
    int n;
    cin >> n;
    int arr[100];
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    int target;
    cin >> target;
    if (checkequal(arr, 0, n - 1, n, target)) {
        cout << "YES";
    }
    else {
        cout << "NO";
    }
}