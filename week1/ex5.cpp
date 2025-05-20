#include <iostream>
using namespace std;
bool issorted(int* arr, int n) { //Hàm kiểm tra xem mảng đã được sắp xếp chưa 
	if (n == 1 || n == 0) { // Nếu như không có phần tử nào hoặc chỉ có 1 phần tử thì mặc định đã được sắp xếp
		return true;
	}
	if (arr[0] > arr[1]) { // Kiểm tra xem nếu có bất kỳ một cặp phần tử nào mà phần tử trước lớn hơn phần tử sau thì trả về false ngay 
		return false;
	}
	return issorted(arr + 1, n - 1); //Gọi lại hàm với vị trí trong mảng tiếp theo 
}
int main() {
	int n;
	cin >> n;
	int* arr = new int[n]; 
	for (int i = 0; i < n; i++) {
		cin >> arr[i];
	}
	if (issorted(arr, n))
		cout << "The array is sorted.\n";
	else
		cout << "The array is NOT sorted.\n";
	delete[]arr;
	return 0;
}