#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	printf("PATH of current dir is\n%s\n", getcwd(NULL, 4096));
	printf("PWD env is\n%s\n", getenv("PWD"));
	chdir(getenv("HOME"));
	char *home = getcwd(NULL, 4096);
	printf("current directory is\n%s\n", home);
	printf("PWD when not set is\n%s\n", getenv("PWD"));
	setenv("PWD", home, 1);
	printf("PWD after set is\n%s\n", getenv("PWD"));
	return (0);
}
