#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <signal.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>
#define BUF_SIZE 2048

FILE* out;
int cs;

void caught(int sig) {
	puts("Done. Good bye");
	fclose(out);
	close(cs);
	exit(0);
}

int main() {
	printf("Hello! I'm %d\n", getpid());
	struct sockaddr_in local;
	inet_aton("127.0.0.1", &local.sin_addr);
	local.sin_port = htons(3000);
	local.sin_family = AF_INET;
	int s = socket(AF_INET, SOCK_STREAM, 0);
	if (s == -1) {
                fputs("socket error", stdout);
                return -1;
        }
	int bd = bind(s,(struct sockaddr*)&local, sizeof(local));
	if (bd == -1) {
		fputs("bind error", stdout);
		return -1;
	}
	listen(s, 10);
	char buf[BUF_SIZE];
	out = fopen("ans", "a+");
	if (!out) {
		fputs("fopen", stdout);
		return -1;
	}
	signal(SIGUSR1, caught);

	while (1) {
		
		cs = accept(s, NULL , NULL);

		if (read(cs, buf, BUFSIZ)) {
			printf("%s\n", buf);
			fprintf(out, "%s\n", buf);
		}
	}	
	return 0;
}
