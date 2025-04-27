#include <iostream>
using namespace std;
// Hàm tìm kiếm tuyến tính với cách sử dụng Sentinel
int sentinelLinearSearch(int arr[], int n, int key) {
	int lastelement = arr[n - 1];
	arr[n - 1] = key;
	int i = 0;
	// Tìm kiếm key trong mảng, duyệt qua các phần tử cho đến khi gặp key hoặc đạt đến phần tử cuối
	while (arr[i] != key) {
		i++;
	}
	// Kiểm tra nếu không tìm thấy key (i sẽ bằng n-1 và phần tử cuối không phải key)
	if (i == n - 1 && arr[n - 1] != key) {
		return -1;
	}
	return i; // Trả về chỉ số của phần tử key trong mảng
}
int main() {
	int n;
	cin >> n;
	int a[100];
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}
	int key;
	cin >> key;
	cout << sentinelLinearSearch(a, n, key);
	return 0;
}