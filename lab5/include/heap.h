#ifndef heap_h
#define heap_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int (*fType)(void*, void*);

typedef struct pair {
	void* val;
	void* key;
} pair;

typedef struct heap {
	int size;
	int cur;
	size_t key_size;
	size_t val_size;
	fType compare;
	pair* elements;
} heap;

void make(heap* my_heap, size_t key_size, size_t val_size, fType compare);
pair extract_max(heap* my_heap);
void change_key(heap* my_heap, void* key, void* new_key);
void clear(heap* my_heap);
void add(heap* my_heap, void* key, void* val);
void heap_sort(void* a, size_t data_size, int n, fType compare);

#endif 
