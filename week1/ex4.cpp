#include <iostream>
using namespace std;
void towerOfHanoi(int n, char from_rod, char to_rod, char aux_rod) {
	if (n == 1) {
		cout << "";
		cout << "Move disk 1 from " << from_rod << " to " << to_rod << endl; //Dòng này kiểm tra nếu chỉ còn một đĩa (n == 1), thì di chuyển đĩa đó 
//từ from_rod đến to_rod và in ra thông báo. Sau đó, thoát khỏi hàm vì không còn đĩa nào để di chuyển nữa.
	    return;
	}
	towerOfHanoi(n - 1, from_rod, aux_rod, to_rod);//Dòng này gọi đệ quy để di chuyển n-1 đĩa từ thanh ban đầu (from_rod) đến thanh phụ (aux_rod) bằng thanh đích (to_rod) làm trung gian.
//Điều này chuẩn bị cho việc di chuyển đĩa lớn hơn (đĩa n).
	cout << "Move disk " << n << " from " << from_rod << " to " << to_rod << endl;
	towerOfHanoi(n - 1, aux_rod, to_rod, from_rod);////Dòng này tiếp tục gọi đệ quy để di chuyển n - 1 đĩa từ thanh phụ(aux_rod) sang thanh đích(to_rod), sử dụng thanh ban đầu(from_rod) làm trung gian.
}
int main() {
	int n;
	cin >> n;
	towerOfHanoi(n, 'A', 'C', 'B');
	return 0;
}