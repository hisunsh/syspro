#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
	printf("Parent Process Start\n");
	if (fork() == 0) {
		execl("/bin/echo", "echo", "hello", NULL);
		fprintf(stderr, "First One Fail");
		exit(1);
	}

	printf("Parent Process End\n");
}
