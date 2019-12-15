#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

void			clear_stdin() // note : this is called by get_unum which is never used
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

uint32_t		get_unum() // note : this is never used
{
	uint32_t	lol;

	fflush(stdout);
	scanf("%u", &lol);
	clear_stdin();
	return (lol);
}

void			prog_timeout() // note : this is never used
{
//	interrupt(0x80) with 0x1 as parameter == sys_exit
}

void			decrypt(int key)
{
	char		buff[17] = 0x757c7d51 + 0x67667360 + 0x7b66737e + 0x33617c7d + 0x0; // ebp-0x1d
	int			len; //		ebp-0x24
	int			i; //		ebp-0x28

	len = strlen(buff); // inline
	i = 0;
	while (i < len)
	{
		buff[i] = buff[i] ^ (int8_t)key;
		i++;
	}
	if (!strncmp("Congratulations!", buff, 17)) // inline
	{
		system("/bin/sh");
	}
	else
	{
		puts("\nInvalid Password");
	}
}

void			test(int a, int b)
{
	int			c;

	c = b - a;
	
	switch (c)
	{
		case 1:
			decrypt(c); break;
		case 2:
			decrypt(c); break;
		case 3:
			decrypt(c); break;
		case 4:
			decrypt(c); break;
		case 5:
			decrypt(c); break;
		case 6:
			decrypt(c); break;
		case 7:
			decrypt(c); break;
		case 8:
			decrypt(c); break;
		case 9:
			decrypt(c); break;
		case 10:
			decrypt(c); break;
		case 12:
			decrypt(c); break;
		case 13:
			decrypt(c); break;
		case 14:
			decrypt(c); break;
		case 15:
			decrypt(c); break;
		case 16:
			decrypt(c); break;
		default:
			decrypt(rand()); break;
	}
}

int				main(void)
{
	int			i;

	puts("************************************");
	puts("*\t\tlevel03\t\t**");
	puts("************************************");
	printf("Password:");
	scanf("%d", &i);
	test(i, 0x1337d00d);
	return (0);
}
