#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>

void quickSort(int *arr, int l, int r);
int partition(int* arr, int l, int mid, int r);
void swap(int* a, int* b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}

int main() {
	int arr[101];
	int n;

	scanf("%d", &n);
	for (int i = 0; i < n; i++)
		scanf("%d", &arr[i]);

	quickSort(arr, 0, n - 1);

	for (int i = 0; i < n; i++)
		printf(" %d", arr[i]);
	printf("\n");
	
	return 0;
}


void quickSort(int* arr, int l, int r) {
	if (l < r) {
		int mid = (l + r) / 2;
		int pivot = partition(arr, l, mid, r);
		
		quickSort(arr, l, pivot - 1);
		quickSort(arr, pivot + 1, r);
	}
}

// mid를 pivot으로 구간을 나눔
int partition(int *arr, int l, int mid, int r) {
	swap(&arr[mid], &arr[r]);
	int pivot = arr[r];

	int i = l;
	int j = r - 1;

	while (i <= j) {
		while (i <= j && arr[i] <= pivot)
			i++;

		while (i <= j && arr[j] >= pivot)
			j--;

		if (i < j)
			swap(&arr[i], &arr[j]);
	}

	swap(&arr[i], &arr[r]);
	return i;
}
