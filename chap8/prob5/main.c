#include <stdio.h>
#include <unistd.h>

int main() {
	printf("My Process Number: [%d] \n", getpid());
	printf("My Parents Process Number: [%d] \n", getppid());
}
