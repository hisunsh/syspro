#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "storecreate.h"

int main(int argc, char *argv[]) {
	int fd;
	struct coffee rec;
	if (argc < 2) {
		fprintf(stderr, "How to use: %s file\n", argv[0]);
		exit(1);
	}

	if ((fd = open(argv[1], O_WRONLY | O_CREAT | O_EXCL, 0640)) == -1) {
		perror(argv[1]);
		exit(2);
	}
	
	printf("%-5s %-7s %-7s %-9s %-5s\n", "id", "name", "category", "expired date", "stock");

	while (scanf("%d %s %s %d %d", &rec.id, rec.name, rec.category, &rec.expired_date, &rec.stock) == 5) {		lseek(fd, (rec.id - START_ID) * sizeof(rec), SEEK_SET);
		write(fd, (char *) &rec, sizeof(rec));
	}

	close(fd);
	exit(0);
}
