#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void clear_stdin()
{
	int c;

	while (1) {
		c = getchar();
		if (c == '\n')
			return;
		if (c == 0xff)
			return;
	}
}

void get_unum()
{
	int a;
	fflush(stdout);

	scanf("%u", &a);
	clear_stdin();
}

void decrypt(int a)
{
	char str[17];
	int c;
	int len;
	int i;

	((int *)str)[0] = 0x757c7d51;
	((int *)str)[1] = 0x67667360;
	((int *)str)[2] = 0x7b66737e;
	((int *)str)[3] = 0x33617c7d;
	str[16] = 0;

	c = 0xffffffff;

	len = strnlen((char*)str, c); //	ebp - 0x24
	i = 0; //							ebp - 0x28

	while (i < len) 
	{
		str[i] = (char)a ^ str[i];
		i++;
	}

	if (strcmp("Congratulations!", str) == 0) {
		system("/bin/sh");
	} else {
		puts("\nInvalid Password");
	}
}

void test(int a, int b)
{

	a = b - a;
	if (a < 0x15)
	{
		a = a << 2;
		goto *(void *)(&&END + a);
	}
	else {
		decrypt(b); return;
		decrypt(b); return;
		decrypt(b); return;
		decrypt(b); return;
		decrypt(b); return;
		decrypt(b); return;
		decrypt(b); return;
		decrypt(b); return;
		decrypt(b); return;
		decrypt(b); return;
		decrypt(b); return;
		decrypt(b); return;
		decrypt(b); return;
		decrypt(b); return;
		decrypt(b); return;
		decrypt(b); return;
		decrypt(b); return;
	}
	END:
	decrypt(rand());
	return;
}


int main()
{
	int var1;

	srand(time(NULL));

	puts("***********************************");
	puts("*\t\tlevel03\t\t**");
	puts("***********************************");

	printf("Password:");

	scanf("%d", &var1);
	
	test(var1, 0x1337d00d); // 322 424 845

	return 0;
}










