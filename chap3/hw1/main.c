#include <stdio.h>
#include "copy.h"

char line[MAXLINE];
char longest[MAXLINE];

int main() {
	int len;
	int max;
	max = 0;

	int count = 0;
	while(count < 5) {
		if (gets(line) != NULL) {
			len = strlen(line);
		}

		if (len > max) {
			max = len;
			copy(line, longest);
		}

		count++;
	}

	if (max > 0) {
		printf("%s \n", longest);
	}

	return 0;
}
