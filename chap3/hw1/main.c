#include <stdio.h>
#include <string.h>
#include "copy.h"

#define MAXLINE 100
#define MAXSTRINGS 5

char line[MAXLINE];
char longest[MAXLINE];
char sentences[MAXSTRINGS][MAXLINE];

int main() {
	int len;
	int max;
	max = 0;

	int count = 0;
	while(count < MAXSTRINGS) {
		if (fgets(line, MAXLINE, stdin) != NULL) {
			line[strcspn(line, "\n")] = 0;
			len = strlen(line);
			strcpy(sentences[count], line);
			count++;
		}
	}

	for (int i = 0; i < MAXSTRINGS; i++) {
		for (int j = i + 1; j < MAXSTRINGS; j++) {
			if (strlen(sentences[i]) < strlen(sentences[j])) {
				char temp[MAXLINE];
				strcpy(temp, sentences[i]);
				strcpy(sentences[i], sentences[j]);
				strcpy(sentences[j], temp);
			}
		}
	}


	for (int i = 0; i < MAXSTRINGS; i++) {
			printf("%s\n", sentences[i]);
		}

	return 0;
}
