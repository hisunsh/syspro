#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#define MAX_LINES 10
#define MAX_LENGTH 100

char savedText[MAX_LINES][MAX_LENGTH];

int readFile(const char *filename) {
	int fd = open(filename, O_RDONLY);

	if (fd == -1) {
		perror("Opening File Error");
		exit(1);
	}

	char buf;
	int line = 0, column = 0;

	while (read(fd, &buf, 1) > 0) {
		if (buf == '\n') {
			savedText[line][column] = '\0';
			line++;
			column = 0;
		}

		else {
			savedText[line][column] = buf;
			column++;
		}

		if (line >= MAX_LINES) {
			break;
		}
	}

	savedText[line][column] = '\0';
	close(fd);

	return line;
}

void printLine(int line) {
	if (line >= 0 && line < MAX_LINES && strlen(savedText[line]) > 0) {
		printf("%s\n", savedText[line]);
	}

	else {
		printf("This is Wrong Line Number.\n");
	}
}

void processInput(int input, int totalLines) {
	for (int i = 0; i < 2; i++) {
		printLine(i);
	}
}

int main(int argc, char *argv[]) {
	const char *filename = argv[1];

	int totalLines = readFile(filename);
	
	int input = 2;

	processInput(input, totalLines);

	return 0;
}
