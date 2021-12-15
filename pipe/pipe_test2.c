#include<unistd.h>
#include<sys/wait.h>

char *cmd1[] = {"cat", "pipe_test2.c", NULL};
char *cmd2[] = {"head", NULL};
char *cmd3[] = {"grep", "char", NULL};
char **cmds[] = {cmd1, cmd2, cmd3};

int cmd_n = 3;

void dopipes(i)
{
	pid_t ret;
	int pp[2] = {};

	if (i == cmd_n - 1)
	{
		//if it's on the far left, just execvp
		execvp (cmds[0][0], cmds[0]);
	}
	else 
	{
		// if it's not the far left, pipe and fork, and parent executes, child recurses
		pipe(pp);
		ret = fork();

		if (ret == 0)
		{
			//if it's a child process, dup2 the pipe to stdout, recurse with dopipes(i + 1)
			//and on the next fork, the parent excutes the i + 1th command from the right
			close(pp[0]);
			dup2(pp[1], 1);
			close(pp[1]);

			dopipes(i + 1);
		}
		else 
		{
			//if it's a parent process, dup2 to stdin,
			//and excutes ith command from the right
			close(pp[1]);
			dup2(pp[0], 0);
			close(pp[0]);

			execvp(cmds[cmd_n - i - 1][0], cmds[cmd_n - i - 1]);
		}
	}
}

int main (void)
{
	pid_t ret;

	ret = fork();
	if(ret == 0)
		dopipes(0);
	else
		wait(NULL);
	
	return (0);
}
