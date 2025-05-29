#include <iostream>
using namespace std;

int LinearSearch(int arr[], int key, int n) {
	for (int i = 0; i < n; i++) { //Duyet het tat ca cac phan tu trong mang
		if (arr[i] == key) { //Khi bat gap vi tri = key
			return i; // Ham tra ve key
		}
	}
}

int main() {
    int n;
	cin >> n;
	int arr[100];
	for (int i = 0; i < n; i++) {
		cin >> arr[i];
	}
	int key;
	cin >> key;
	cout << LinearSearch(arr, key, n);
	return 0;
}