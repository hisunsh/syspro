#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>

int main(int argc, char *argv[]) {
	int child, pid, status;

	pid = fork();

	if (pid == 0) {
		execvp(argv[1], &argv[1]);
		fprintf(stderr, "%s:Running Error\n", argv[1]);
	}
	else {
		child = wait(&status);
		printf("[%d] Child Process %d End \n", getpid(), pid);
		printf("\tEnd Code %d \n", status>>8);
	}
}
