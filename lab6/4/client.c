#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>
#define BUF_SIZE 2048

int main(int argc, char *argv[]) {
	if (argc < 2) {
		puts("Enter the DNS");
		return -1;
	}
	struct hostent *h;
	h  = gethostbyname(argv[1]);
	if (!h) {
		fputs("gethostbyname error", stdout);
		return -1;
	}

	struct sockaddr_in local;
	inet_aton("127.0.0.1", &local.sin_addr);
	local.sin_port = htons(3000);
	local.sin_family = AF_INET;
	int s = socket(AF_INET, SOCK_STREAM, 0);
	if (s == -1) {
		fputs("socket error", stdout);
		return -1;
	}
	
	if (connect(s, (struct sockaddr*)&local, sizeof(local)) == -1) {
		fputs("connect error", stdout);
		return -1;
        }
		
	int i = 0;
	char buf[BUF_SIZE];
	memset(buf, 0, BUF_SIZE);
	strcat(buf, "DNS: ");
	strcat(buf, argv[1]);
	strcat(buf, "\n");

	while (h->h_addr_list[i]) {
		struct in_addr *tmp = (struct in_addr*)h->h_addr_list[i];
		strcat(buf, inet_ntoa(*tmp));
		buf[strlen(buf)] = '\n';
		i++;
	}
	write(s, buf, BUF_SIZE);
	close(s);
	return 0;	
}
