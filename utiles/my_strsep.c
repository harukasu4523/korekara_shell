#include<string.h>
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>

#define ARRAYMAX 50

// if string the far left is "|" what to do this function.
char str[] = "abcd  aaa | ssssefg";

char *put_in_array(char *str, char c, int *offset)
{
	int len = 0, i, j;
	cnt->array_cnt = 0;
	char buf[PATH_MAX];

	i = *offset;
	printf("%d \n", i);
	while(str[i++])
	{
		if (str[i] == c)
			break;
	}
	buf = malloc(i + 1);
	buf[i] = '\0';
	j = -1;
	while (++j < i)
		buf[j] = str[j + *offset];
	*offset += i;
	while(str[i++] == c)
		*offset += 1;
	return (buf);
}

char **my_strsep(char *str, char c)
{
	size_t len;
	int i = -1, cnt = 0, offset;
	char *buf[ARRAMAX] = {};
	int array_cnt;

	len = strlen(str);
	while (++i < len)
	{
		if(str[i] == c)
			array_cnt++;
	}
	array_cnt++;
	i = -1;
	offset = 0;
	while (++i < array_cnt)
	{
		buf[i] = put_in_array(str, c, &offset);
		printf("buf[%d] = %s\n", i, buf[i]);
	}
	return(buf);
}

void free_array(char ***array)
{
	int i = 0;

	while(i++ < 3)
	{
		free(**array);
		**array = NULL;
	}
	free(*array);
}

int main(void)
{
	char **array;

	array = my_strsep(str, '|', &cnt);
	int i = -1;
	while (++i < 2)
		printf("%s\n",array[i]);
	free_array(&array);
	return (0);
}
