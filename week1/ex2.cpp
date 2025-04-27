#include <iostream>
using namespace std;

int factorial(int n) { //Hàm đệ quy tìm giai thừa của một số 
	if (n == 0 || n == 1) { //Đúng định nghĩa của giai thừa, giai thừa của 0 là 1
		return 1;
	}
	else {
		return factorial(n - 1) * n; //Nếu khác 2 số 0 và 1, ta sẽ trả về số đó nhân với giai thừa của phần tử bé hơn
	}
}
// Cho ví dụ: n=5
// Khi hàm factorial được gọi lần 1, nó sẽ trả về: factorial(4)*5
// Khi hàm factorial được gọi lần 2, nó sẽ trả về: factorial(3)*4*5
// Khi hàm factorial được gọi lần 3, nó sẽ trả về: factorial(2)*3*4*5
// Khi hàm factorial được gọi lần 4, nó sẽ trả về: factorial(2)*2*3*4*5
// Khi hàm factorial được gọi lần 5, nó sẽ trả về: factorial(1)*1*2*3*4*5 = 1*2*3*4*5= 120 
int main() {
	int n;
	cin >> n;
	int res = factorial(n);
	cout << res;
}