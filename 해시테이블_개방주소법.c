#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>

// 개방주소법 ( key는 1 이상의 정수 )
typedef struct Node {
	int key;
	int ele;
	int active;
} Node;

typedef struct Hash {
	Node* table;
	int q; // 이중 해싱 q
	int M;
} Hash;

// 해시함수
void initHash(Hash* hash, int M);
int hashF(int k, int M);

// 조사 함수
int linerSearch(int idx); // 선형조사
int doubleSearch(int idx); // 2차조사
int doubleHashF(int k, int q); // 이중해싱

// 기능 함수
void insertItem(Hash* hash,	int key, int ele);
int deleteItem(Hash* hash, int key);
int searchItem(Hash* hash, int key);
void printHash(Hash* hash);

int main() {
	int M;
	scanf("%d", &M);
	
	Hash hash;
	initHash(&hash, M);

	char cmd;
	scanf(" %c", &cmd);
	while (cmd != 'e') {
		if (cmd == 'i') {
			int key, ele;
			scanf("%d %d", &key, &ele);
			insertItem(&hash, key, ele);
		}
		else if (cmd == 's') {
			int key;
			scanf("%d", &key);
			int ele = searchItem(&hash, key);
			if (ele != -1)
				printf("%d\n", ele);
		}
		else if (cmd == 'd') {
			int key;
			scanf("%d", &key);
			int ele = deleteItem(&hash, key);
			if (ele != -1)
				printf("%d\n", ele);
		}
		else if (cmd == 'p') {
			printHash(&hash);
			printf("\n");
		}

		scanf(" %c", &cmd);
	}
	
	return 0;
}

// 해시함수
void initHash(Hash* hash, int M) {
	hash->M = M;
	hash->table = (Node*)malloc(sizeof(Node) * (M));

	for (int i = 0; i < M; i++) {
		hash->table[i].active = 0;
		hash->table[i].ele = 0;
		hash->table[i].key = 0;
	}

	// M보다 작은 소수를 찾아 q에 저장
	for (int i = M - 1; i > 1; i--) {
		int flag = 0;
		for (int j = 2; j < i; j++)
			if (i % j == 0) {
				flag = 1;
				break;
			}
		if (flag == 0) {
			hash->q = i;
			break;
		}
	}
}
int hashF(int k, int M) {
	return k % M;
}
int doubleHashF(int k, int q) {
	return q - (k % q);
}

// 조사 함수
int linerSearch(int idx) {
	return idx;
}
int doubleSearch(int idx) {
	return idx * idx;
}
int doubleHashing(int idx, int k, int q) {
	return doubleHashF(k, q) * idx;
}

// 기능 함수
void insertItem(Hash* hash, int key, int ele) {
	int v = hashF(key, hash->M);

	for (int i = 0; i < hash->M; i++) {
		int idx = (v + doubleHashing(i, key, hash->q)) % hash->M;
		if (hash->table[idx].active == 0 || hash->table[idx].key == 0) { // 공간이 비어있거나 비활성화
			hash->table[idx].key = key;
			hash->table[idx].ele = ele;
			hash->table[idx].active = 1;
			return;
		}
	}
	printf("cant insert\n");
	return;
}
int deleteItem(Hash* hash, int key) {
	int v = hashF(key, hash->M);

	for (int i = 0; i < hash->M; i++) {
		int idx = (v + doubleHashing(i, key, hash->q)) % hash->M;
		if (hash->table[idx].key == 0) {
			printf("No Search Key\n");
			return -1;
		}
		else if (hash->table[idx].key == key) { // 찾음
			hash->table[idx].active = 0;
			return hash->table[idx].ele;
		}
	}

	printf("Cant Search Key\n");
	return -1;
}
int searchItem(Hash* hash, int key) {
	int v = hashF(key, hash->M);

	for (int i = 0; i < hash->M; i++) {
		int idx = (v + doubleHashing(i, key, hash->q)) % hash->M;
		if (hash->table[idx].key == 0) {
			printf("No Search Key\n");
			return -1;
		}
		else if (hash->table[idx].key == key) { // 찾음
			return hash->table[idx].ele;
		}
	}
	printf("Cant Search Key\n");
	return -1;
}
void printHash(Hash* hash) {
	for (int i = 0; i < hash->M; i++)
		if (hash->table[i].active == 1)
			printf("%d (%d , %d)\n", i, hash->table[i].key, hash->table[i].ele);
}
