#include <iostream>
#include <limits.h>
using namespace std;
// Hàm tìm phần tử lớn nhất trong mảng
int findmax(int arr[], int n) {
	int max = INT_MIN;
	for (int i = 0; i < n; i++) {
		if (arr[i] > max) {
			max = arr[i];
		}
	}
	return max;
}
// Hàm kiểm tra xem có thể vận chuyển tất cả các phần tử với công suất tối đa là 'mid' trong số 'days' ngày hay không
bool canShip(int weight[], int n, int mid, int days) {
	int sum = 0;
	int day = 1;
	// Duyệt qua mảng trọng lượng
	for (int i = 0; i < n; i++) {
		if (sum + weight[i] > mid) {// Nếu tổng trọng lượng trong ngày vượt quá công suất tối đa
			day++; // Chuyển sang ngày tiếp theo
			sum = weight[i]; // Bắt đầu tính trọng lượng từ phần tử hiện tại
		}
		else {
			sum += weight[i]; // Cộng trọng lượng hiện tại vào tổng
		}

		if (day > days) { // Nếu số ngày vượt quá số ngày cho phép
			return false; // Không thể vận chuyển trong số ngày cho phé
		}
	}

	return true; // Nếu có thể vận chuyển trong số ngày cho phép
}
int shipcapacity(int weight[], int n, int days) {
	int left = findmax(weight, n);// Công suất tối thiểu là trọng lượng lớn nhất trong mảng
	int right = 0;
	// Tổng trọng lượng tất cả các phần tử trong mảng để xác định công suất tối đa
	for (int i = 0; i < n; i++) {
		right += weight[i];
	}
	// Sử dụng Binary Search để tìm công suất tối thiểu của tàu
	while (left < right) {
		int mid = left + (right - left) / 2;

		if (canShip(weight, n, mid, days)) {
			right = mid;  // Nếu có thể, giảm phạm vi tìm kiếm về phía bên trái
		}
		else {
			left = mid + 1;  // Nếu không thể, tăng phạm vi tìm kiếm về phía bên phải
		}
	}

	return left;
}
int main() {
	int n, days;
	cin >> n;
	int weight[100];
	for (int i = 0; i < n; i++) {
		cin >> weight[i];
	}
	cin >> days;
	cout << shipcapacity(weight, n, days);
	return 0;
}