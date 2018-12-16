#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "heap.h"

int compare(void* a, void* b) {   
	int* x = (int*)a;
	int* y = (int*)b; 
	return *x > *y ? 1 : (*x < *y ? - 1 : 0);
}

void print(heap* my_heap) {
	while (my_heap->cur > 1) {
		pair ans = extract_max(my_heap);
		int* a = (int*)ans.key;
		int* b = (int*)ans.val;
		printf("MAX KEY:%d -> %d\n", *a, *b);
	}
}

int main() {
	int val, key;
	heap my_heap;
	make(&my_heap, sizeof(val), sizeof(key), compare);
	while (scanf("%d %d", &key, &val) > 0) 
		add(&my_heap, &key, &val);
	print(&my_heap);
	clear(&my_heap);
	return 0;
}
