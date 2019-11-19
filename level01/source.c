#include <string.h>
#include <stdio.h>

char a_user_name[256] = {0};

int verify_user_name()
{
	puts("verifying username....\n");
	return (memcmp(a_user_name, "dat_wil", 7));
}

int verify_user_pass(char *var)
{
	return (memcmp(var, "admin", 5));
}

int main()
{
	char var[16] = {0};
	int result;

	puts("********* ADMIN LOGIN PROMPT *********");

	printf("Enter Username: ");

	fgets(a_user_name, 256, stdin);

	result = verify_user_name();

	if (result != 0) {
		puts("nope, incorrect username...\n");
		return (1);
	} else {

		puts("Enter Password: ");

		fgets(var, 100, stdin);
		
		result = verify_user_pass(var);

		if (result != 0) {
			if (result != 0) {
				;
			}
		} else {
			puts("nope, incorrect password...\n");
			return (1);
		}
	}
	return (0);
}




