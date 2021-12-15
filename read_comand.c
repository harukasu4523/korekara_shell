#include<unistd.h>
#include<stdio.h>
#include<sys/wait.h>
#include<stdlib.h>
#include<string.h>

enum { MAXLINE = 256, MAXARGS = 45};

typedef struct s_cnt
{
	int		comand;
	int		path;
}			t_cnt;

int main(void)
{
	char	buf[MAXLINE];
	char *args[MAXARGS];
	pid_t	pid;
	int		status;
	char *str1, *token;

	printf("%%");
	while (fgets(buf, MAXLINE, stdin) != NULL)
	{
		if (buf[strlen(buf) - 1] == '\n')
			buf[strlen(buf) - 1] = 0;
		/*analyz buf*/
		str1 = strdup(buf);
		int args_num = 0;
		for (int j = 0; ;j++, str1 = NULL)
		{
			token = strtok(str1, " ");
			if(token == NULL)
				break;
			args[j] = token;
			args_num += 1;
		}
		free(str1);
		args[args_num] = NULL;

		if ((pid = fork()) < 0)
		{
			perror("fork error");
		}
		else if (pid == 0)/*children side*/
		{
			execvp(args[0], &args[0]);
			printf("couldn't execute: %s", buf);
			exit(127);
		}

		/*parent side*/
		if ((pid = waitpid(pid, &status, 0)) < 0)
			perror("waitpid error");
		for (int i = 0; i < args_num; i++)
			args[i] = NULL;
		printf("%%");

	}
	exit(0);
}
