#include "heap.h"

void make(heap* my_heap, size_t key_size, size_t val_size, fType compare) {
	my_heap->size = 1;
	my_heap->cur = 1;
	my_heap->key_size = key_size;
	my_heap->val_size = val_size;
	my_heap->compare = compare;
	my_heap->elements = (pair*)malloc(sizeof(pair));
	my_heap->elements[0].key = malloc(my_heap->key_size);
	my_heap->elements[0].val = malloc(my_heap->val_size);
}

void swap(pair* a, pair* b) {
	pair t = *a; 
	*a = *b;
	*b = t;
}

void lift(heap* my_heap, int v) {
	while (v > 1 && my_heap->compare(my_heap->elements[v].key, my_heap->elements[v / 2].key) > 0) {
		swap(&(my_heap->elements[v]), &(my_heap->elements[v / 2]));
		v /= 2;
	}
}

void sift(heap* my_heap, int v) {
	while (2 * v < my_heap->cur) {
		int p = 2 * v;
		if (p < my_heap->cur && my_heap->compare(my_heap->elements[p + 1].key, my_heap->elements[p].key) > 0)
			++p;
		if (my_heap->compare(my_heap->elements[v].key, my_heap->elements[p].key) > 0)
			break;
		swap(&(my_heap->elements[v]), &(my_heap->elements[p]));
		v = p;
	}
}

pair extract_max(heap* my_heap) {
	memmove(my_heap->elements[0].key, my_heap->elements[1].key, my_heap->key_size);
	memmove(my_heap->elements[0].val, my_heap->elements[1].val, my_heap->val_size);
	--my_heap->cur;
	memmove(my_heap->elements[1].key, my_heap->elements[my_heap->cur].key, my_heap->key_size);
	memmove(my_heap->elements[1].val, my_heap->elements[my_heap->cur].val, my_heap->val_size);
	sift(my_heap, 1);
	return my_heap->elements[0];
}

void change_key(heap* my_heap, void* key, void* new_key) {
	int i;
	for (i = 1; i < my_heap->cur; ++i) {
		if (my_heap->compare(my_heap->elements[i].key, key) == 0) {
			memcpy(my_heap->elements[i].key, new_key, my_heap->key_size);
			sift(my_heap, i);
			lift(my_heap, i);
			return;
		}
	}
	fprintf(stdout, "Error, no such element\n");
}

void clear(heap* my_heap) {
	int i;
	for (i = 0; i < my_heap->size; ++i) {
		free(my_heap->elements[i].key);
		free(my_heap->elements[i].val);
	}
	free(my_heap->elements);
}

void add(heap* my_heap, void* key, void* val) {
	if (my_heap->cur == my_heap->size) {
		my_heap->elements = (pair*)realloc(my_heap->elements, sizeof(pair) * my_heap->size * 2);
		int i;
		for (i = my_heap->cur; i < my_heap->size * 2; ++i) {
			my_heap->elements[i].key = malloc(my_heap->key_size);
			my_heap->elements[i].val = malloc(my_heap->val_size);
		}
		my_heap->size *= 2;
	}
	memcpy(my_heap->elements[my_heap->cur].key, key, my_heap->key_size);
	memcpy(my_heap->elements[my_heap->cur].val, val, my_heap->val_size);
	lift(my_heap, my_heap->cur);
	my_heap->cur++;
}	

void heap_sort(void* a, size_t data_size, int n, fType compare) {
	heap my_heap;
	make(&my_heap, data_size, data_size, compare);
	int i;
	for (i = 0; i < n; ++i)
		add(&my_heap, a + i * data_size, a + i * data_size);
	for (i = 0; i < n; ++i) {
		pair ans = extract_max(&my_heap);
		memmove(a + i * data_size, ans.key, data_size);
	}
	clear(&my_heap);
}
