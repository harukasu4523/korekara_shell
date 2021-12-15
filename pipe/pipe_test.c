#include<unistd.h>
#include<stdio.h>
#include<signal.h>
#include<stdlib.h>
#include<string.h>

#define READ (0)
#define WRITE (1)


/**
 * *fd_r = file descriptor for reading
 * *fd_w = file descriptor for writting
**/

int popen2(int *fd_r, int *fd_w){
	//conecting pipe for kid to parent
	int pipe_child2parent[2];

	//conecting pipe for parent to kid
	int pipe_parent2child[2];

	//process ID
	int pid;

	//pipe generation
	if(pipe(pipe_child2parent) < 0){
		//pipe generation failur
		perror("popen2");
		return (1);
	}

	//pipe generarion
	if(pipe(pipe_parent2child) < 0){
		//pipe generarion failur
		perror("popen2");

		// close the pipe opened  above and then exit
		close(pipe_child2parent[READ]);
		close(pipe_child2parent[WRITE]);
		return (1);
	}
	//fork
	if ((pid = fork()) < 0){
		// fork failur
		perror("popen2");

		// close the pipe opened above and then exit
		close(pipe_child2parent[READ]);
		close(pipe_child2parent[WRITE]);

		close(pipe_parent2child[READ]);
		close(pipe_parent2child[WRITE]);
		return (1);
	}

	// child process
	if (pid == 0){
		// in the case of a child process, there can be no writing from the parent to the child, so close it.
		close(pipe_parent2child[WRITE]);
		// and there can be no reading from the child to the parent, so close it
		close (pipe_child2parent[READ]);

		// assign parent to child output as stdin
		dup2(pipe_parent2child[READ], 0);
		// assign child to parent input as stdout
		dup2(pipe_child2parent[WRITE], 1);

		// the assigned file descriptor is closed
		close(pipe_parent2child[READ]);
		close(pipe_child2parent[WRITE]);

		//the child process start the program here and doesn't return
		if (execl("./test1", "./test1", NULL) < 0){
			perror("popen2");
			close(pipe_parent2child[READ]);
			close(pipe_child2parent[WRITE]);
			return 1;
		}
	}

	// doesn't child process(parent process)
	close(pipe_parent2child[READ]);
	close(pipe_child2parent[WRITE]);

	*fd_r = pipe_child2parent[READ];
	*fd_w = pipe_parent2child[WRITE];
	return (pid);
}

int main(int argc, char *argv[]){
	int fd_r = fileno(stdin);
	int fd_w = fileno(stdout);

	if (argc < 2){
		printf("Usage: %s <message>\n", argv[0]);
		return (1);
	}

	popen2(&fd_r, &fd_w);

//	*fd_r = pipe_child2parent[READ];
//	*fd_w = pipe_parent2child[WRITE];

	write(fd_w, argv[1], strlen(argv[1]));

	char buf[255];
	int size = read(fd_r, buf, 255);
	if (size == -1){
		perror("error");
		return (1);
	}

	printf("test2: ");
	fwrite(buf, 1, size, stdout);
	printf("\n");
	return (0);
}
