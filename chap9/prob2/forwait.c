#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
	int pid, child, status;

	printf("[%d] Parent Process Start \n", getpid());
	pid = fork();

	if (pid == 0) {
		printf("[%d] Child Process Start \n", getpid());
		exit(1);
	}

	child = wait(&status);
	printf("[%d] Child Process %d End \n", getpid(), child);
	printf("\tEnd Code %d\n", status>>8);
}
