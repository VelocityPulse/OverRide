#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() 
{

	char str[100]; //	$esp + 0x28
	int a; //			$esp + 0x8c

	fgets(str, 100, stdin);
	a = 0;

	while (strlen(str) > a)
	{
		if (str[a] > 0x40 && str[a] <= 0x5a) {
			// main+103
			str[a] = str[a] ^ 0x20;
			// main+133
		}
		a++;
	}

	printf(str);
	exit(0);
}


