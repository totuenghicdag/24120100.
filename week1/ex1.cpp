#include <iostream>
using namespace std;

int fibonacci(int n) {
    if (n < 0) {
        return -1;
    }
    else if (n == 0 || n == 1) {
        return n;
    }
    else {
        return fibonacci(n - 1) + fibonacci(n - 2);
    }
}
//Ví dụ như khi gọi n=5
//Ta sẽ cho i chạy đến 4
// i=0, ta trả về n tức là trả về 0
// 0
// i=1, ta trả về n tức là trả về 1
// 0 1
// i=2, ta trả về fibonacci(1) + fibonacci(0) = 1+0=1;
// 0 1 1 
// i=3, ta trả về fibonacci(2) + fibonacci(1)= fibonacci(1) + fibonacci(0) + fibonacci(1)=1+0+1=2;
// 0 1 1 2 
// i=4, ta trả về fibonacci(3) + fibonacci(2)= fibonacci(1) + fibonacci(0) + fibonacci(1) + fibonacci(1) + fibonacci(0)=1+0+1+1+0=3;
// 0 1 1 2 3
int main() {
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cout << fibonacci(i) << " ";
    }
    return 0;
}