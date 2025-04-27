#include <iostream>
using namespace std;
// Hàm tìm phần tử nhỏ nhất trong mảng đã xoay
int minelement(int arr[], int n, int low, int high) {
	low = 0;
	high = n - 1;
	// Tiến hành tìm kiếm nhị phân
	while (low < high) {
		int mid = low + (high - low) / 2;
		// Nếu phần tử giữa lớn hơn phần tử cuối, thì phần tử nhỏ nhất nằm ở bên phải
		if (arr[mid] > arr[high]) {
			low = mid + 1;// Di chuyển chỉ số low lên
		}
		else {
			high = mid;// Nếu không, phần tử nhỏ nhất nằm trong nửa trái
		}
	}
	// Khi vòng lặp kết thúc, low sẽ trỏ đến phần tử nhỏ nhất
	return arr[low];
}
int main() {
	int n;
	cin >> n;
	int arr[100];
	for (int i = 0; i < n; i++) {
		cin >> arr[i];
	}
	cout << minelement(arr, n, 0, n - 1);
	return 0;
}