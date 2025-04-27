#include <iostream>
using namespace std;

void generateBinaryStrings(int n, string str) {
	if (n == 0) {
		cout << str << endl;
		return;
	}
	generateBinaryStrings(n - 1, str + "0");
	generateBinaryStrings(n - 1, str + "1");
}
//Ví dụ n=3
//Đầu tiên gọi hàm generateBinaryStrings lần 1 với str là khoảng trống 
//Sau đó kiểm tra xem n có bằng 0 không, nếu bằng ta in str ra và kết thúc
//Còn nếu không bằng thì ta gọi tiép hàm generateBinaryStrings với n - 1, và + thêm ký tự 0,
//Gọi generateBinaryStrings(2, "0")
//Lần 1 : Thêm 0 vào chuỗi, gọi tiếp generateBinaryStrings(1, "00").
//Gọi generateBinaryStrings(1, "00")
//Lần 1 : Thêm 0 vào chuỗi, gọi tiếp generateBinaryStrings(0, "000").
//Vì n == 0, chương trình in ra "000".
//Lần 2 : Thêm 1 vào chuỗi, gọi tiếp generateBinaryStrings(0, "001").
//Vì n == 0, chương trình in ra "001".
//Sau đó, quay lại và tiếp tục với bước trước.
//Quay lại generateBinaryStrings(2, ""), tiếp tục với lần thứ hai :
//Gọi generateBinaryStrings(2, "1")
//Lần 1 : Thêm 0 vào chuỗi, gọi tiếp generateBinaryStrings(1, "10").
//Gọi generateBinaryStrings(1, "10")
//Lần 1 : Thêm 0 vào chuỗi, gọi tiếp generateBinaryStrings(0, "100").
//Vì n == 0, chương trình in ra "100".
//Lần 2 : Thêm 1 vào chuỗi, gọi tiếp generateBinaryStrings(0, "101").
//Vì n == 0, chương trình in ra "101".
//Quay lại generateBinaryStrings(3, ""), tiếp tục với lần thứ hai :
//Gọi generateBinaryStrings(2, "1")
//Thêm 0 vào chuỗi, gọi tiếp generateBinaryStrings(1, "10")
//Gọi generateBinaryStrings(1, "11")
//Gọi generateBinaryStrings(1, "10")
//Lần 1 : Gọi generateBinaryStrings(0, "100")
//Vì n == 0, chương trình in ra "100".
//Lần 2 : Gọi generateBinaryStrings(0, "101")
//Vì n == 0, chương trình in ra "101".
//Gọi generateBinaryStrings(1, "11")
//Lần 1 : Gọi generateBinaryStrings(0, "110")
//Vì n == 0, chương trình in ra "110".
//Lần 2 : Gọi generateBinaryStrings(0, "111")
//Vì n == 0, chương trình in ra "111".


int main() {
	int n;
	cin >> n;
	generateBinaryStrings(n, "");
	return 0;
}