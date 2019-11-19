#include <stdio.h>
#include <stdlib.h>

int main ()
{

	int a;

	puts("***********************************");
	puts("* \t     -Level00 -\t\t  *");
	puts("***********************************");

	printf("Password:");

	scanf("%d", &a);

	if (a == 0x149c) // 5276
	{
		puts("\nAuthenticated!");
		system("/bin/sh");
	}
	else 
	{
		puts("\nInvalid Password!");
	}
	return 1;
}
