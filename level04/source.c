#include <stdio.h>
#include <stdint.h>
#include <signal.h>
#include <unistd.h>
#include <sys/ptrace.h>
#include <sys/wait.h>
#include <sys/prctl.h> // note : only on linux

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

void			prog_timeout()
{
	//	interrupt(0x80) with 0x1 as parameter == sys_exit
}

void			enable_timeout_cons()
{
	signal(SIGALRM, &prog_timeout); // SIGALRM = 14
	alarm(60);
}

int				main(void)
{
	pid_t		pid; //					esp + 0xac
	int			ptret; //				esp + 0xa8
	int			status; //				esp + 0xa0
	char		buff[0x80]; //			esp + 0x20
	int			*st; //					esp + 0x1c

	pid = fork();
	if (pid == 0) // child
	{
		prctl(1, 1);
		ptrace(0, 0, 0, 0); // 0 = PTRACE_TRACEME
		puts("Give me some shellcode, k");
		gets(buff);
	}
	else // 
	{
		while (1) // ~main+160 
		{
			st = &status;
			wait(st);
			//status = *st;
			if ((__WTERMSIG(status) == 0) // (status & 0x7f)
			{
				puts("child is exiting...");
				break;
			}
			if (__WIFSIGNALED(status) != 0) // (((status && 0x7f) + 1) >> 1) > 0
			{
				puts("child is exiting...");
				break;
			}
			ptret = ptrace(3, pid, 44, 0); // 3 = PTRACE_PEEKUSER
			if (ptret == 0xb)
			{
				puts("no exec() for you");
				kill(pid, SIGKILL);
			}
		}
	}
	return (0);
}
