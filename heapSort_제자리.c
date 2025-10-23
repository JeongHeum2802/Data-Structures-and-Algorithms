#include <stdio.h>
#include <stdlib.h>

void downHeap(int* heap, int n, int v); // downHeap
void inplaceHeapSort(int* heap, int n); // 제자리 힙 정렬
void buildHeap(int* heap, int n); // 배열을 상향식으로 힙화

int main() {
	int arr[101];
	int n = 10;

	for (int i = 1; i <= n; i++)
		scanf("%d", &arr[i]);

	inplaceHeapSort(arr, n);
	
	for (int i = 1; i <= n; i++)
		printf(" %d", arr[i]);
	
	return 0;
}

// 제자리 힙 정렬
void inplaceHeapSort(int* heap, int n) {
	buildHeap(heap, n);
	for (int i = n; i > 1; i--) {
		int temp = heap[i];
		heap[i] = heap[1];
		heap[1] = temp;

		n--;
		downHeap(heap, n, 1);
	}
}

// 상향식 힙 생성
void buildHeap(int* heap, int n) {
	for (int i = n / 2; i >= 1; i--)
		downHeap(heap, n, i);
}

// downHeap
void downHeap(int* heap, int n, int v) {
	int left = v * 2;
	int right = v * 2 + 1;
	if (left > n) return;

	int bigger = left;
	if (right <= n && heap[right] > heap[bigger])
		bigger = right;

	if (heap[v] >= heap[bigger]) return;

	int temp = heap[bigger];
	heap[bigger] = heap[v];
	heap[v] = temp;

	downHeap(heap, n, bigger);
}

