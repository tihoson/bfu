#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define BUF_SIZE 20971520

int main() {
	static char buf[BUF_SIZE];
	int i;
	srand(time(NULL));
	for (i = 0; i < BUF_SIZE; i++)
		buf[i] = 'a' + rand() % ('z' - 'a' + 1);
	int out = open("out", O_WRONLY | O_CREAT);
	if (out == -1) {
		fputs("open error", stdout);
		return -1;
	}
	write(out, buf, BUF_SIZE);
	close(out);
	return 0;
}
	
