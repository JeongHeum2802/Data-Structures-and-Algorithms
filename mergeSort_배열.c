#include <stdio.h>
#include <stdlib.h>

void mergeSort(int *B, int* arr, int l, int r);
void merge(int *B, int* arr, int l, int mid, int r);

int main() {
	int arr[100];
	int B[100];
	int n;

	// 입력
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
		scanf("%d", &arr[i]);

	// mergeSort
	mergeSort(B, arr, 0, n-1);
	
	// 출력
	for (int i = 0; i < n; i++)
		printf(" %d", arr[i]);

	return 0;
}

// mergeSort
void mergeSort(int* B, int* arr, int l, int r) {
	if (l < r) {
		int mid = (l + r) / 2;
		mergeSort(B, arr, l, mid);
		mergeSort(B, arr, mid + 1, r);

		merge(B, arr, l, mid, r);
	}
}

// l~mid , mid+1 ~ r 로 나뉘어진 배열을 병합
void merge(int* B, int* arr, int l, int mid, int r) {
	int i = l;
	int j = mid + 1;
	int k = l;

	while (i <= mid && j <= r) {
		if (arr[i] <= arr[j]) {
			B[k++] = arr[i++];
		}
		else {
			B[k++] = arr[j++];
		}
	}

	while (i <= mid) {
		B[k++] = arr[i++];
	}

	while(j <= r) {
		B[k++] = arr[j++];
	}

	for (int p = l; p <= r; p++)
		arr[p] = B[p];
}
