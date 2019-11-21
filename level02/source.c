#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
	char a[100] = {0}; // rbp - 0x70
	char b[48] = {0}; // rbp - 0xa0
	char c[112] = {0}; // rbp - 0x110
	int var;

	FILE *fd;

	if ((fd = fopen("/home/users/level03/.pass", "r")) == 0)
	{
		fwrite("ERROR: failed to open password file\n", 1, 24, stderr);
		exit(1);
	}
	
	var = fread(b, 1, 41, fd);

	b[strcspn(b, "\n")] = 0;

	if (var == 0x29) {// 41
		fwrite("ERROR: failed to read password file\n", 1, 24, stderr);
		fwrite("ERROR: failed to read password file\n", 1, 24, stderr);
		exit(1);
	}

	fclose(fd);

	puts("===== [ Secure Access System v1.0 ] =====");
	puts("/***************************************\\");
	puts("| You must login to access this system. |");
	puts("\\**************************************/");

	printf("--[ Username: ");
	fgets(a, 100, stdin);
	a[strcspn(a, "\n")] = 0;

	printf("--[ Password: ");
	fgets(c, 100, stdin);
	c[strcspn(c, "\n")] = 0;

	puts("*****************************************");

	if (strncmp(b, c, 41) == 0) {
		printf("Greetings, %s!\n", a); // main+620
		system("/bin/sh");
		return (0);
	}

	printf(a); // main+654
	puts(" does not have access!"); // main+664
	exit(1);
}



