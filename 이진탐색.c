#include <stdio.h>
#include <stdlib.h>

int findElement(int* arr, int n, int key);
int rFE(int* arr, int l, int r, int key);

int main() {
	int arr[101];
	int n;

	scanf("%d", &n);
	for (int i = 0; i < n; i++)
		scanf("%d", &arr[i]);


	return 0;
}

int findElement(int* arr, int n, int key) {
	return rFE(arr, 0, n - 1, key);
}

int rFE(int* arr, int l, int r, int key) {
	if (l > r) return -1; // 값이 없으면 1 반환

	int mid = (l + r) / 2;
	if (arr[mid] == key)
		return arr[mid];
	else if (key < arr[mid])
		return rFE(arr, l, mid - 1, key);
	else
		return rFE(arr, mid + 1, r, key);
}
