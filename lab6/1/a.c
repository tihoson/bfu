#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#define BUF_SIZE 20971520

int main() {
	FILE* out = fopen("out", "w");
	if (!out) {
		fputs("fopen error", stdout);
		return -1;
	}
	srand(time(NULL));
	int i;
	for (i = 0; i < BUF_SIZE; i++) {
		char c = 'a' +  rand() % ('z' - 'a' + 1);
		fprintf(out, "%c", c);
	}
	fclose(out);
	return 0;
}
	
