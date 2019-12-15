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

	FILE *file_fd_log; //			rbp - 0x88
	FILE *file_fd_src; //			rbp - 0x80

	int fd_backup = 0xffffffff; //	rbp - 0x78
	unsigned char fd_dest = 0xff; //		rbp - 0x71
	char backup_name[112]; //				rbp - 0x70

	if (ac != 2) {
		printf("Usage: %s filename\n", *argv);
	}
	file_fd_log = fopen("./backups/.log", "w");
	if (file_fd_log == 0) {
		printf("ERROR: Failed to open %s\n", "./backups/.log");
		exit(1);
	}

	log_wrapper(file_fd_log, "Starting back up: ", av[2]);

	if ((file_fd_src = fopen(av[2], "r")) == 0) {
		printf("ERROR: Failed to open %s\n", av[2]);
		exit(1);
	}

	strcpy(backup_name, "./backups/");

	x = 0xffffffffffffffff;

	strncat(backup_name, av[2], strlen(backup_name) - 99);

	if ((fd_backup = open(backup_name, 0)) != 0) {
		printf("ERROR: Failed to open %s%s\n", "./backups/", av[2]);
		exit(1);
	}

	while ((fd_dest = fgetc(file_fd_src)) != 0xff) {
		write(fd_backup, &fd_dest, 1);
	}
	
	log_wrapper(file_fd_log, "Finished back up ", av[2]);

	fclose(file_fd_src);
	close(fd_backup);
	return 0;
}
