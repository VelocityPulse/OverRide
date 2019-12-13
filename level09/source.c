#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

struct data {
	char message[140];
	char user[40];
	int value;

} typedef s_data;

void secret_backdoor()
{
	char a[128];

	fgets(a, 128, stdin);
	system(a);
}

void set_msg(s_data *a)
{
	char buff[1024]; //			rbp - 0x400
	s_data *param = a; //		rbp - 0x408

	memset(buff, 0, 1024);
	puts(">: Msg @Unix-Dude");

	printf(">>: ");
	fgets(buff, 1024, stdin);
	
	strncpy(a->message, buff, a->value);
}

void set_username(s_data *a)
{
	int i; //			rbp - 0x4
	char tab[128]; //	rbp - 0x90
	s_data *param = a;

	memset(&tab, 0, 128);
	puts(">: Enter your username");
	printf(">>: ");
	fgets(tab, 128, stdin);

	i = 0;
	while (i < 40 && tab[i] != 0) {
		a->user[i] = tab[i];
		i++;
	}

	printf(">: Welcome, %s", a->user);
}

void handle_msg()
{
	s_data a;
	memset(a.user, 0, 32);
	a.value = 0x8c;
	set_username(&a);
	set_msg(&a);
	puts(">: Msg sent!");
}

int main()
{
	puts("--------------------------------------------\n"
			"|   ~Welcome to l33t-m$n ~    v1337        |\n"
			"--------------------------------------------");
	handle_msg();
	return 0;
}













