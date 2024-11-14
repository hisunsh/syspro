#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
	int pid1, pid2, child, status;

	printf("[%d] Parent Process Start \n", getpid());
	pid1 = fork();

	if (pid1 == 0) {
		printf("[%d] Child Process[1] Start \n", getpid());
		sleep(1);
		printf("[%d] Child Process[1] End \n", getpid());
		exit(1);
	}

	pid2 = fork();
	if (pid2 == 0) {
		printf("[%d] Child Process #2 Start \n", getpid());
		sleep(2);
		printf("[%d] Child Process #2 End \n", getpid());
		exit(2);
	}

	child = waitpid(pid1, &status, 0);
	printf("[%d] Child Process #1 %d End \n", getpid(), child);
	printf("\tEnd Code %d\n", status>>8);
}
