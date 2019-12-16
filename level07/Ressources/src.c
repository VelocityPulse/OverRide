#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void clear_stdin()
{
	int a;
	do {
	 	a = getchar();
	} while (a != '\n' || a != 0xff);
}

unsigned int get_unum()
{
	unsigned int a = 0;

	fflush(stdout);
	scanf("%u", &a);
	clear_stdin();
	return a;
}

int read_number(char *tab)
{
	int index = 0; //	ebp - 0xc

	printf(" Index: ");
	index = get_unum();
	printf(" Number at data[%u] is %u\n", index, tab[index << 2]);
	return 0;
}

int store_number(char *tab)
{
	unsigned int index; //		ebp - 0xc
	unsigned int number; //		ebp - 0x10

	printf(" Number: ");
	number = get_unum();
	printf(" Index: ");
	index = get_unum();

	if (index % 3 == 0 || number >> 24 == 0xb7) {
		puts(" *** ERROR! ***");
		puts("   This index is reserved for wil!");
		puts(" *** ERROR! ***");
		return (1);
	}
	tab[index << 2] = number;
	return (0);
}

int main(int argc, char **argv, char **envp)
{
	char input[20] = {0}; //	esp+0x1b8
	int failed = 0; //			esp+0x1b4
	char tab[400]; //			esp+0x24
	char **a1 = argv; //		esp+0x1c
	char **e1 = envp; //		esp+0x18

	memset(tab, 0, 0x64);

	while (*a1) {
		memset(*a1, 0, strlen(*a1));
		a1 += 1;
	}
	while (*e1) {
		memset(*e1, 0, strlen(*e1));
		e1 += 1;
	}

	puts("----------------------------------------------------\n"
			"Welcome to wil\'s crappy number storage service!\n"
			"----------------------------------------------------\n"
			" Commands:\n"
			"    store - store a number into the data storage\n"
			"    read  - read a number from the data storage\n"
			"    quit  - exit the program\n"
			"----------------------------------------------------\n"
			"   wil has reserved some storage :>\n"
			"----------------------------------------------------\n");

	while (1) {
		printf("Input command: ");
		fgets(input, 20, stdin);
		input[strlen(input) - 1] = 0;

		if (strncmp(input, "store", 0x5) == 0) {
			failed = store_number((char *)tab);
		}
		else if (strncmp(input, "read", 0x4) == 0) {
			failed = read_number((char *)tab);
		}
		else if (strncmp(input, "quit", 0x4) == 0) {
			return 0;
		}

		if (failed != 0) {
			printf(" Failed to do %s command\n", input);
		} else {
			printf(" Completed %s command successfully\n", input);
		}

		((int*)input)[0] = 0;
		((int*)input)[1] = 0;
		((int*)input)[2] = 0;
		((int*)input)[3] = 0;
		((int*)input)[4] = 0;
	}
}












