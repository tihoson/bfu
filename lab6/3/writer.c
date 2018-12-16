#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

#define BUF_SIZE 2048

int main() {
	int fd;
	char *myfifo = "/gpfs/home/aparahin/lab06/3/myfifo";
	char buf[BUF_SIZE];
	fd = open(myfifo, O_RDONLY);
	while (1) {
		int ln = read(fd, buf, BUF_SIZE);
		if (ln == 0) {
			printf("Good bye?..\n");
			break;
		}
		int i;
		for (i = 0; i < 10; ++i)
			printf("%s", buf);
	}
	close(fd);
	return 0;
}	
