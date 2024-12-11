#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#define BUFFER_SIZE 100

int main() {
	int pipefd[2];
	pid_t pid1, pid2;

	printf("parent process start\n");

	// create pipe
	if (pipe(pipefd) == -1) {
		perror("pipe failed");
		return 1;
	}

	// generate first child process
	pid1 = fork();
	if (pid1 < 0) {
		perror("fork failed");
		return 1;
	}

	if (pid1 == 0) { // first child process
		close(pipefd[0]); // close reading
		char input[BUFFER_SIZE];
		printf("input string: ");
		fgets(input, BUFFER_SIZE, stdin);

		// remove newline characters
		input[strcspn(input, "\n")] = '\0';

		// writting string on the pipe
		write(pipefd[1], input, strlen(input) + 1);
		close(pipefd[1]); // close writting
		exit(0);
	}

	// generate second child process
	pid2 = fork();
	if (pid2 < 0) {
		perror("fork failed");
		return 1;
	}

	if (pid2 == 0) { // second child process
		close(pipefd[1]); // close writting
		char buffer[BUFFER_SIZE];

		// reading string on the pipe
		read(pipefd[0], buffer, BUFFER_SIZE);
		close(pipefd[0]); // close reading

		// convert lowercase letters to uppercase
		for (int i = 0; buffer[i] != '\0'; i++) {
			buffer[i] = toupper(buffer[i]);
		}

		printf("%s\n", buffer);
		exit(0);
	}

	// parents process
	close(pipefd[0]); // close reading
	close(pipefd[1]); // close writting

	// wait for child process to terminate
	wait(NULL);
	wait(NULL);

	return 0;
}
