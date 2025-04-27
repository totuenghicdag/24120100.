#include <iostream>
using namespace std;
const int N = 8; //Kích thước của bàn cờ
int board[N][N] = { 0 }; //Ban đầu gán tất cả là 0 (tức có nghĩa là chưa có quân hậu
int solutions = 0; //Biến lưu số lượng giải pháp
bool isSafe(int row, int col) {

	for (int i = 0; i < row; i++)
	{
		if (board[i][col] == 1) //Kiểm tra coi ở cột đó đã có quân hậu chưa 
			return false; 
		if (col - (row - i) >= 0 && board[i][col - (row - i)] == 1) //Kiểm tra dườnd chéo trái 
			return false; 
		if (col + (row - i) < N && board[i][col + (row - i)] == 1) //Kiểm tra đường chéo phải
			return false; 
	}
	return true; //Nếu không bị vướng vào các điều kiện trên thì trả về true 
}
void solveNQueens(int row)
{
	if (row == N){ //nếu đã đặt các quân hậu hợp lệ cho các hàng
		solutions++; // tăng biến solution hợp lệ 
		return;
	}
	    for (int col = 0; col < N; col++){

		    if (isSafe(row, col)) // Kiểm tra vị trí đó có an toàn không
		{
			board[row][col] = 1; // nếu an toàn thì đặt quân hậu tại đó
			solveNQueens(row + 1); //tiếp tục gọi hàm cho hàng tiếp theo 
			board[row][col] = 0; //Sau khi quay lại, gỡ bỏ quân hậu để thử các lựa chọn khác
		}
	}
 }
 int main()
 {
	 solveNQueens(0);
	 cout << solutions << endl;
	 return 0;
 }