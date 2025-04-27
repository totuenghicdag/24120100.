#include "function.h"
#include <cstring>
int main(int argc, char* argv[]) {
	const char* algorithm = nullptr;
	const char* inputFile = nullptr;
	const char* outputFile = nullptr;
	int n = 0;
	int* arr = nullptr;
	for (int i = 1; i < argc; i++) {
		if (strcmp(argv[i], "-a") == 0 && i + 1 < argc) {
			algorithm = argv[i + 1];
			i++;
		}
		else if (strcmp(argv[i], "-i") == 0 && i + 1 < argc) {
			inputFile = argv[i + 1];
			i++;
		}
		else if (strcmp(argv[i], "-o") == 0 && i + 1 < argc) {
			outputFile = argv[i + 1];
			i++;
		}
		else {
			cout << "Tham so khong hop le: " << argv[i] << endl;
		}
	}
	if (algorithm == nullptr || inputFile == nullptr || outputFile == nullptr) {
		cout << "Thieu tham so." << endl;
		return 1;
	}
	cout << "chuan bi doc file";
	readfile(inputFile, n, arr);
	cout << "da doc file";
	if (arr == nullptr) {
		cout << "Loi khi doc file, arr rong." << endl;
		return 1;
	}
	cout << endl;
	if (strcmp(algorithm, "insertion-sort") == 0) {
		cout << "Thuat toan ho tro: " << algorithm << endl;
		insertionsort(arr, n);
		writeoutput(outputFile, n, arr);
	}
	else if (strcmp(algorithm, "selection-sort") == 0) {
		cout << "Thuat toan ho tro: " << algorithm << endl;
		selectionsort(arr, 0, n);
		writeoutput(outputFile, n, arr);
	}
	else if (strcmp(algorithm, "bubble-sort") == 0) {
		cout << "Thuat toan ho tro: " << algorithm << endl;
		bubble_sort(arr, n);
		writeoutput(outputFile, n, arr);
	}
	else if (strcmp(algorithm, "shaker-sort") == 0) {
		cout << "Thuat toan ho tro: " << algorithm << endl;
		shaker_sort(arr, n);
		writeoutput(outputFile, n, arr);
	}
	else if (strcmp(algorithm, "shell-sort") == 0) {
		cout << "Thuat toan ho tro: " << algorithm << endl;
		shell_sort(arr, n);
		writeoutput(outputFile, n, arr);
	}
	else if (strcmp(algorithm, "heap-sort") == 0) {
		cout << "Thuat toan ho tro: " << algorithm << endl;
		heapsort(arr, n);
		writeoutput(outputFile, n, arr);
	}
	else if (strcmp(algorithm, "merge-sort") == 0) {
		cout << "Thuat toan ho tro: " << algorithm << endl;
		mergesort(arr, 0, n - 1);
		writeoutput(outputFile, n, arr);
	}
	else if (strcmp(algorithm, "quick-sort") == 0) {
		cout << "Thuat toan ho tro: " << algorithm << endl;
		quickSort(arr, 0, n - 1);
		writeoutput(outputFile, n, arr);
	}
	else if (strcmp(algorithm, "counting-sort") == 0) {
		cout << "Thuat toan ho tro: " << algorithm << endl;
		countingSort(arr, n);
		writeoutput(outputFile, n, arr);
	}
	else if (strcmp(algorithm, "radix-sort") == 0) {
		cout << "Thuat toan ho tro: " << algorithm << endl;
		radixSort(arr, n);
		writeoutput(outputFile, n, arr);
	}
	else if (strcmp(algorithm, "flash-sort") == 0) {
		cout << "Thuat toan ho tro: " << algorithm << endl;
		flashSort(arr, n);
		writeoutput(outputFile, n, arr);
	}
	else {
		cout << "Thuat toan khong duoc ho tro: " << algorithm << endl;
		return 0;
	}
	cout << endl;
	delete[] arr;
	return 0;
}