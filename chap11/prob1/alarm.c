#include <stdio.h>
#include <unistd.h>

unsigned int alarm(unsigned int sec);

int main() {
	alarm(5);
	printf("Loop start\n");
	short i = 0;
	while (1) {
		sleep(1);
		i++;
		printf("%d second\n", i);
	}
	printf("end\n");
}
