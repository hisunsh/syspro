#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#define BUFFER_SIZE 1024

int main(int argc, char *argv[]) {
	if (argc == 1) { // not have argc
		printf("[Shell] ");
	}

	int pipefd[2];
	pid_t pid1, pid2;
	char *command1, *command2;
	char input[BUFFER_SIZE];

	fgets(input, BUFFER_SIZE, stdin);
	input[strcspn(input, "\n")] = '\0'; // remove newline character

	// parse the input to split the commands
	if (strchr(input, '|') != NULL) {
		command1 = strtok(input, "| ");
		command2 = strtok(NULL, "| ");
	}
	else {
		printf("No pipe '|' found in input\n");
		return 1;
	}

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
		close(pipefd[0]); // close the read end of the pipe
		dup2(pipefd[1], STDOUT_FILENO); // redirect stdout to the pipe
		close(pipefd[1]); // close the original write end of the pipe
		
		// execute the first command
		execlp(command1, command1, NULL);
		perror("execlp failed for command1");
		exit(1);
	}

	// fork the second child process
	pid2 = fork();
	if (pid2 < 0) {
		perror("fork failed");
		return 1;
	}

	if (pid2 == 0) { //second child process
		close(pipefd[1]); // close the write end of the pipe
		dup2(pipefd[0], STDIN_FILENO); // redirect stdin from the pipe
		close(pipefd[0]); // close the original read end of the pipe

		// execute the second command
		execlp(command2, command2, NULL);
		perror("execlp failed for command2");
		exit(1);
	}

	// parents process
	close(pipefd[0]); // close reading
	close(pipefd[1]); // close writting

	// wait for child process to terminate
	wait(NULL);
	wait(NULL);

	return 0;
}
