#include <iostream>
#include <limits.h>
using namespace std;

// Hàm tìm độ dài của dãy con nhỏ nhất có tổng >= target
int minimalsubarray(int arr[], int target, int n) {
	int low = 0;
	int sum = 0;
	int minlength = INT_MAX;// Khởi tạo độ dài dãy con nhỏ nhất là vô cùng lớn (INT_MAX)
	// Duyệt qua mảng, high sẽ là chỉ số của phần tử cuối cùng trong cửa sổ
	for (int high = 0; high < n; high++) {
		// Mở rộng cửa sổ bằng cách cộng giá trị arr[high] vào tổn
		if (sum < target) {
			sum += arr[high];
		}
		// Khi tổng lớn hơn hoặc bằng target, cố gắng thu hẹp cửa sổ từ phía bên trái
		while (sum >= target) {
			// Thu hẹp cửa sổ bằng cách loại bỏ phần tử ở vị trí low
			sum -= arr[low];
			if (high - low + 1 < minlength) {
				minlength = high - low + 1;
			}
			low++;
		}
	}
	return minlength;
}
int main() {
	int n;
	cin >> n;
	int target;
	cin >> target;
	int arr[100];
	for (int i = 0; i < n; i++) {
		cin >> arr[i];
	}
	cout << minimalsubarray(arr, target, n);
	return 0;
}