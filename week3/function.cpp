#include "function.h"
void readfile(const char filename[], int& n, int*& arr) {
	ifstream inputfile(filename);
	if (!inputfile.is_open()) {
		cout << "LOI MO FILE INPUT";
		return;
	}
	else {
		inputfile >> n;
		arr = new int[n];
		for (int i = 0; i < n; i++) {
			inputfile >> arr[i];
		}
		cout << n << " ";
		cout << "\n";
		cout << "Mang da doc: ";
		for (int i = 0; i < n; i++) {
			cout << arr[i] << " ";
		}
		inputfile.close();
	}
}
int findmin(int* arr, int low, int n) {
	int min = low;
	for (int i = low + 1; i < n; i++) {
		if (arr[i] < arr[min]) {
			min = i;
		}
	}
	return min;
}
void swap(int* arr, int i, int j) {
	int temp = arr[i];
	arr[i] = arr[j];
	arr[j] = temp;
}
void selectionsort(int* arr, int low, int n) {
	for (int i = low; i < n; i++) {
		int key = findmin(arr, i, n);
		swap(arr, i, key);
	}
}
void insertionsort(int* arr, int& n) {
	for (int i = 1; i < n; i++) {
		int key = arr[i];
		int pos = i - 1;
		while (pos >= 0 && arr[pos] > key) {
			arr[pos + 1] = arr[pos];
			--pos;
		}
		arr[pos + 1] = key;
	}
}
void bubble_sort(int* arr, int n) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n - i - 1; j++) {
			if (arr[j] > arr[j + 1]) {
				swap(arr, j, j + 1);
			}
		}
	}
}
void heapify(int* arr, int n, int i) {
	int largest = i;
	int left = 2 * i + 1;
	int right = 2 * i + 2;
	if (left < n && arr[left] > arr[largest]) {
		largest = left;
	}
	if (right < n && arr[right]>arr[largest]) {
		largest = right;
	}
	if (largest != i) {
		swap(arr, largest, i);
		heapify(arr, n, largest);
	}
}
void heapsort(int* arr, int n) {
	for (int i = (n / 2) - 1; i >= 0; i--) {
		heapify(arr, n, i);
	}
	cout << endl;
	for (int i = n - 1; i > 0; i--) {
		swap(arr, i, 0);
		heapify(arr, i, 0);
	}
}
void shell_sort(int* arr, int n) {
	for (int interval = n / 2; interval > 0; interval /= 2) {
		for (int i = interval; i < n; i++) {
			int j = i;
			int value = arr[i];
			for (j = i; j >= interval && arr[j - interval] > value; j -= interval) {
				arr[j] = arr[j - interval];
			}
			arr[j] = value;
		}
	}
}
void shaker_sort(int* arr, int n) {
	int left = 0, right = n - 1, k = 0;
	while (left < right) {
		for (int i = left; i < right; i++) {
			if (arr[i] > arr[i + 1]) {
				swap(arr[i], arr[i + 1]);
				k = i;
			}
		}
		right = k;
		for (int i = right; i > left; i--) {
			if (arr[i] < arr[i - 1]) {
				swap(arr[i], arr[i - 1]);
				k = i;
			}
		}
		left = k;
	}
}
int findmax(int* arr, int n) {
	int max = INT_MIN;
	for (int i = 0; i < n; i++) {
		if (arr[i] > max) {
			max = arr[i];
		}
	}
	return max;
}

void flashSort(int* arr, int n) {
	if (n <= 1) {
		return;
	}
	int minVal = arr[0], maxVal = arr[0];
	for (int i = 1; i < n; ++i) {
		if (arr[i] < minVal) minVal = arr[i];
		if (arr[i] > maxVal) maxVal = arr[i];
	}
	if (minVal == maxVal) {
		return;
	}
	const int m = int(0.42 * n);
	int* L = new int[m]();

	for (int i = 0; i < n; ++i) {
		int k = int((double)(m - 1) * (arr[i] - minVal) / (maxVal - minVal));
		L[k]++;
	}

	for (int i = 1; i < m; ++i) {
		L[i] += L[i - 1];
	}

	int count = 0;
	int i = 0;
	while (count < n - 1) {
		int k = int((double)(m - 1) * (arr[i] - minVal) / (maxVal - minVal));
		while (i >= L[k]) {
			i++;
			k = int((double)(m - 1) * (arr[i] - minVal) / (maxVal - minVal));
		}
		int flash = arr[i];
		while (i < L[k]) {
			k = int((double)(m - 1) * (flash - minVal) / (maxVal - minVal));
			int hold = arr[L[k] - 1];
			arr[L[k] - 1] = flash;
			flash = hold;
			L[k]--;
			count++;
		}
	}
	for (int i = 1; i < n; ++i) {
		int key = arr[i];
		int j = i - 1;
		while (j >= 0 && arr[j] > key) {
			arr[j + 1] = arr[j];
			j--;
		}
		arr[j + 1] = key;
	}
	delete[] L;
}
void merge(int* arr, int left, int mid, int right) {
	int n1 = mid - left + 1;
	int n2 = right - mid;

	int* L = new int[n1];
	int* R = new int[n2];

	for (int i = 0; i < n1; ++i) {
		L[i] = arr[left + i];
	}
	for (int j = 0; j < n2; ++j) {
		R[j] = arr[mid + 1 + j];
	}

	int i = 0, j = 0, k = left;
	while (i < n1 && j < n2) {
		if (L[i] <= R[j]) {
			arr[k++] = L[i++];
		}
		else {
			arr[k++] = R[j++];
		}
	}
	while (i < n1) {
		arr[k++] = L[i++];
	}

	while (j < n2) {
		arr[k++] = R[j++];
	}

	delete[] L;
	delete[] R;
}
void mergesort(int* arr, int left, int right) {
	if (left < right) {
		int mid = left + (right - left) / 2;
		mergesort(arr, left, mid);
		mergesort(arr, mid + 1, right);
		merge(arr, left, mid, right);
	}
}
int partition(int* arr, int low, int high) {
	int randomIndex = low + rand() % (high - low + 1);
	swap(arr[randomIndex], arr[high]);

	int pivot = arr[high];
	int i = low - 1;
	for (int j = low; j < high; j++) {
		if (arr[j] < pivot) {
			i++;
			swap(arr[i], arr[j]);
		}
	}
	swap(arr[i + 1], arr[high]);
	return i + 1;
}
void quickSort(int* arr, int low, int high) {
	while (low < high) {
		int pivotIndex = partition(arr, low, high);
		if (pivotIndex - low < high - pivotIndex) {
			quickSort(arr, low, pivotIndex - 1);
			low = pivotIndex + 1;
		}
		else {
			quickSort(arr, pivotIndex + 1, high);
			high = pivotIndex - 1;
		}
	}
}
void countingSort(int* arr, int n) {
	if (n <= 0) return;
	int maxVal = arr[0];
	for (int i = 1; i < n; i++) {
		if (arr[i] > maxVal) {
			maxVal = arr[i];
		}
	}
	int* output = new int[n];
	int* count = new int[maxVal + 1]();
	for (int i = 0; i < n; i++) {
		count[arr[i]]++;
	}
	for (int i = 1; i <= maxVal; i++) {
		count[i] += count[i - 1];
	}
	for (int i = n - 1; i >= 0; i--) {
		output[count[arr[i]] - 1] = arr[i];
		count[arr[i]]--;
	}
	for (int i = 0; i < n; i++) {
		arr[i] = output[i];
	}
	delete[] output;
	delete[] count;
}
void radixSort(int* arr, int n) {
	if (n <= 0) return;
	int maxNum = findmax(arr, n);
	for (int exp = 1; maxNum / exp > 0; exp *= 10) {
		countingSort(arr, n);
	}
}

void writeoutput(const char filename[], int& n, int* arr) {
	ofstream outputfile(filename);
	if (!outputfile.is_open()) {
		cout << "Loi mo file output";
		return;
	}
	else {
		outputfile << n << "\n";
		for (int i = 0; i < n; i++) {
			outputfile << arr[i] << " ";
		}
		cout << "\n";
		cout << n << " ";
		cout << "\n";
		cout << "Mang da ghi: ";
		for (int i = 0; i < n; i++) {
			cout << arr[i] << " ";
		}
		outputfile.close();
	}
}
