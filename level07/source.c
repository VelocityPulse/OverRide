#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

void			clear_stdin()
{
	char	c;
	while (1)
	{
		c = getchar();
		if (c == '\n' || c == -1)
			break ;
	}
	return ;
}

uint32_t		get_unum()
{
	uint32_t	lol;

	fflush(stdout);
	scanf("%u", &lol);
	clear_stdin();
	return (lol);
}

int				read_number(uint32_t *table)
{
	uint32_t	index;

	printf(" Index: ");
	index = get_unum();
	printf(" Number at data[%u] is %u\n", index, table[index]);
	return (0);
}

int				store_number(uint32_t *table)
{
	int			index = 0; // ebp - 0xc
	int			number = 0; // ebp - 0x10

	printf(" Number: ");
	number = get_unum();
	printf(" Index: ");
	index = get_unum();

	// the buisness with 0xaaaaaaab is actually olympic level gymnastics
	// from to compiler to get a "index % 3"

	// 0 : 0 - 0 jump taken
	// 1 : 1 - 0 jump NOT taken
	// 2 : 2 - 0 jump NOT taken 
	// 3 : 3 - 3 jump taken
	// 4 : 4 - 3 jump NOT taken
	// 5 : 5 - 3 jump NOT taken
	// 6 : 6 - 6 jump taken
	// 7 : 7 - 6 jump NOT taken
	// 8 : 8 - 6 jump NOT taken
	// 8 : 9 - 9 jump taken

	if ((index % 3) == 0 || (number >> 24) == 0xb7)
	{
		puts(" *** ERROR! ***");
		puts("   This index is reserved for wil!");
		puts(" *** ERROR! ***");
		return (1);
	}
	table[index] = number;
	return (0);
}

int				main(int argc, char **argv, char **envp)
{
	int			canary = 0;		// esp + 0x1cc | gs:0x14 | we don't know its actual value
	char		buff[20];		// esp + 0x1b8 | filled with zeroes at start of main
	uint32_t	v;				// esp + 0x1b4 | zeroed at start of main
	uint32_t	bbuff[100];		// esp + 0x24 | filled with zeroes at start of main
	char		**av = argv;	// esp + 0x1c | ebp + 0xc
	char		**ep = envp;	// esp + 0x18 | ebp + 0x10
	int			l;				// esp + 0x14

	while (*av != NULL)
	{
		memset(*av, 0, strlen(*av));
		av++;
	}
	while (*ep != NULL)
	{
		memset(*ep, 0, strlen(*ep));
		ep++;
	}
	puts('-' <repeats 52 times>, "\n  Welcome to wil's crappy number storage service!   \n",
			'-' <repeats 52 times>, "\n Commands:", ' ' <repeats 31 times>...);
	while (1)
	{
		printf("Input command: ");
		v = 1;
		fgets(buff, 20,.stdin);
		buff[strlen(buff) - 1] = 0; // this does not make much sense
		if (strncmp(buff, "store", 5))
		{
			store_number(bbuff);
		}
		else if (strncmp(buff, "read", 4))
		{
			read_number(bbuff);
		}
		else if (strncmp(buff, "quit", 4))
		{
			break;
		}
	}
	return (0);
}
