#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ptrace.h>

int auth(char *login, unsigned int u)
{
	int len; //	ebp - 0xc
	int b; //	ebp - 0x10
	int c; //	ebp - 0x14

	login[strcspn(login, "\n")] = 0;
	len = strnlen(login, 32);

	if (len <= 5)
		return (1);

	if (ptrace(0, 0, 1, 0) == 0xffffffff) {
		puts("\033[32m.---------------------------.");
		puts("\033[31m| !! TAMPERING DETECTED !!  |");
		puts("\033[32m'---------------------------'");
		return (1);
	}

	b = (login[3] ^ 0x1337) & 0x5eeded;
	c = 0;

	while (c < len)
	{
		if (login[c] <= 0x1f)
			return (1);
		// not sure :
		b += (login[c] ^ b) - (((((login[c] ^ b) - 
			((login[c] ^ b) * 0x88233b2b)) >> 1) + 1) >> 10) * 0x539;
		// b += eax
		++c;
	}

	if (u != b)
		return (1);
	return (0);
}


int main()
{

	char login[32]; //	esp + 0x2c
	unsigned int u; //	esp + 0x28

	puts("***********************************");
	puts("*\t\tlevel06\t\t  *");
	puts("***********************************");

	printf("-> Enter Login: ");

	fgets(login, 32, stdin);

	puts("***********************************");
	puts("***** NEW ACCOUNT DETECTED ********");
	puts("***********************************");

	printf("-> Enter Serial: ");

	scanf("%u", &u);

	if (auth(login, u) == 0) {
		puts("Authenticated!");
		system("/bin/sh");
		return 0;
	} else {
	//	__stack_chk_fail();
	}
	return (1);
}
