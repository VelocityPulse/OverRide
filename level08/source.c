#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

void log_wrapper(FILE *log, char *str, char *param)
{
	FILE *logg = log; //		rbp - 0x118
	char *strr = str; //		rbp - 0x120
	char *paramm = param; //	rbp - 0x128

	char tab[254]; //				rbp - 0x110

	strcpy((char *)tab, strr);
	snprintf(tab + strlen(tab), 254 - strlen(tab), param);
	
	tab[strcspn(tab, "\n")] = 0;

	fprintf(log, "LOG: %s\n", "Starting back up: AAA");
}

int main(int argc, char **argv)
{
	long int x; //			rbp - 0xa8
	char **av = argv; //	rbp - 0xa0
	int ac = argc; //		rbp - 0x94

	FILE *log; //			rbp - 0x88
	FILE *param; //			rbp - 0x80

	int fd = 0xffffffff; //	rbp - 0x78
	unsigned char b = 0xff; //		rbp - 0x71
	char a[112]; //				rbp - 0x70

	if (ac != 2) {
		printf("Usage: %s filename\n", *argv);
	}
	log = fopen("./backups/.log", "w");
	if (log == 0) {
		printf("ERROR: Failed to open %s\n", "./backups/.log");
		exit(1);
	}

	log_wrapper(log, "Starting back up: ", av[2]);

	if ((param = fopen(av[2], "r")) == 0) {
		printf("ERROR: Failed to open %s\n", av[2]);
		exit(1);
	}

	strcpy(a, "./backups/");

	x = 0xffffffffffffffff;

	strncat(a, av[2], strlen(a) - 99);

	if ((fd = open(a, 0)) != 0) {
		printf("ERROR: Failed to open %s%s\n", "./backups/", av[2]);
		exit(1);
	}


	while ((b = fgetc(param)) != 0xff) {
		write(fd, &b, 1);
	}
	
	log_wrapper(log, "Finished back up ", av[2]);

	fclose(param);
	close(fd);

	return 0;
}
