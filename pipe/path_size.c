#include <stdio.h>
#include <limits.h>


int main(void)
{
	int i = PATH_MAX;
	printf("PATHMAX = %d\n ARGMAX = %d\n",i, _POSIX_ARG_MAX);
}
