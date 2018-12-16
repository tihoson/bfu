#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>

int main() {
	char *myfifo = "/gpfs/home/aparahin/lab06/3/myfifo";
        mkfifo(myfifo, 0666);
	sigset_t set;
	sigemptyset(&set);
	sigaddset(&set, SIGUSR1);
	sigaddset(&set, SIGUSR2);
	sigprocmask(SIG_BLOCK, &set, NULL); 
        
	printf("%d\n", getpid());
	int fd = open(myfifo, O_WRONLY);
	char *bufer = (char*)malloc(100);
	while (1) {
		int signal;
		sigwait(&set, &signal);
		if (signal == SIGUSR1) {
			printf("ENTER THE MESSAGE:\n");
			fgets(bufer, 100, stdin);
			write(fd, bufer, 100);
		}
		if (signal == SIGUSR2) {
			printf("I'm done\n");
			break;
		}
	}
	free(bufer);	
	close(fd);
	unlink(myfifo);
	return 0;
}	 
