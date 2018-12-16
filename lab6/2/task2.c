#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define INPUT_FILE  "input.txt"
#define OUTPUT_FILE "output.txt"
#define STR_SIZE	100

int cmp(const void *a, const void *b) {
	return strcmp(*(char**)a, *(char**)b);
}

int getData(char ***strings) {
	FILE *input = fopen(INPUT_FILE, "r");
	if (input == NULL) {
		printf("Failed to open "INPUT_FILE"\n");
		exit(-1);
	}
	int n = 0;
	*strings = malloc(sizeof(char*));
	char *buffer = malloc(STR_SIZE * sizeof(char));
	while (fgets(buffer, STR_SIZE, input)) {
		*strings = realloc(*strings, sizeof(char*) * (n + 1));
		(*strings)[n] = (char*)malloc(STR_SIZE * sizeof(char));
		strcpy((*strings)[n++], buffer);
	}
	fclose(input);
	free(buffer);
	return n;
}

void slave(char **strings, int n) {
	FILE *output = fopen(OUTPUT_FILE, "w");
	if (output == NULL) {
		printf("Failed to open "OUTPUT_FILE"\n");
		exit(-1);
        }
	int i;
	qsort(strings, n, sizeof(char*) , cmp);	
	for (i = 0; i < n; ++i)
		fprintf(output, "%s", strings[i]);
	fclose(output);
}

void clear(char ***strings, int n) {
	int i;
	for (i = 0; i < n; ++i)
		free((*strings)[i]);
	free(*strings);
}

int main() {
	char **strings;
	int n = getData(&strings);
	if (n == 0) {
		printf("File is empty\n");
		return 0;
	}
	pid_t master = fork();
	if (!master)
		slave(strings, n);	
	else {
		int status;
		int block = 2;
		while (1) {
			puts("Hey buddy");
			usleep(500000);
			puts("I think you've got the wrong door");
			usleep(500000);
			printf("The WINDOWS club's %d blocks down\n", block++);
                        usleep(1000000);
                        puts("ok.");
			usleep(1000000);
			if (waitpid(master, &status, WNOHANG)) {
				puts("WELCOME TO THE CLUB, BUDDY");
				break;
			}
		}
	}
	clear(&strings, n);		
	return 0;
}
