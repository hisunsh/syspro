#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>

int main() {
	int pipefd[2];
	pid_t pid;
	char buffer[50];

	// create pipe
	if (pipe(pipefd) == -1) {
		perror("pipe failed");
		return 1;
	}

	// create process
	pid = fork();

	if (pid < 0) {
		perror("fork failed");
		return 1;
	}
	else if (pid == 0) { // child process
		close(pipefd[0]); // close reading
		snprintf(buffer, sizeof(buffer), "Hello from PID %d", getpid());
		write(pipefd[1], buffer, strlen(buffer) + 1); // write to the pipe
		close(pipefd[1]);
	}
	else { // parent process
		close(pipefd[1]); // close writting
		read(pipefd[0], buffer, sizeof(buffer)); // reading on pipe
		printf("Send: [%d] %s\n", getpid(), buffer);
		printf("Recv: [%d] %s\n", getpid(), buffer);
		close(pipefd[0]);
	}

	return 0;
}
