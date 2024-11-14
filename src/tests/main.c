#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "libft/includes/libft.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <signal.h>
#include <assert.h>

void	handle_child(int signum)
{
	if (signum == SIGINT)
		printf("ignored");
}

void	handle_parent(int signum)
{
	if (signum != SIGINT)
		return ;
	rl_replace_line("", 0);
	write(1, "\n", 1);
	rl_on_new_line();
	rl_redisplay();
}

char	*cat_path(char *tpath,char *path, char *name)
{
	tpath = ft_stpcpy(tpath, path);
	tpath = ft_stpcpy(tpath, "/");
	tpath = ft_stpcpy(tpath, name);
	return (tpath);

}
void ft_free(void *p)
{
	void **ptr = p;
	if (*ptr)
	{
		free(*ptr);
		*ptr = NULL;
	}
}

void err(char *str)
{
	while (*str)
		write(2, str++, 1);
}

int is_builtin(char *str)
{
	char **builtins = (char *[]){"exit", "cd", NULL};
	int i = -1;

	while (builtins[++i])
		if (str && !ft_strcmp(builtins[i], str))
			return (1);
	return (0);
}

int ft_argc(char **argv)
{
	int i = 0;
	while (argv[i])
		i++;
	return (i);
}

int b_exit(int ac, char **av)
{
	if (ac == 1)
		return (exit(0), 1);
	else if (ac >= 2)
		return (exit(ft_atoi(av[1])), 1);
	return (1);
}

int b_cd(int ac, char **av)
{
	(void)ac;
	struct stat stats;
	if (access(av[1], F_OK) && access(av[1], X_OK))
			return (ft_putstr_fd("cd: Error no permission", 2), 2);
	if (av[1] && av[2])
		return (ft_putstr_fd("cd: Error too many args", 2), 2);
	stat(av[1], &stats);
	if (S_ISDIR(stats.st_mode))
	{
		if (chdir(av[1]) == -1)
			return (ft_putstr_fd("cd: Error could not change directory", 2), 127);
	}
	else
		return (ft_putstr_fd("cd: Error is not a directory", 2), 2);
	return (0);
}

int builtin(char *str, char **av)
{
	char **builtins = (char *[]){"exit", "cd", NULL};
	int (*builtin_fn[])(int, char **) = { b_exit, b_cd, NULL};
	int i = -1;
	int ac = ft_argc(av);
	while (builtins[++i])
		if (str && !ft_strcmp(builtins[i], str))
			return (builtin_fn[i](ac, av));
	return (0);
}

char *ft_path(char *str)
{
	char **path = ft_split_mult(getenv("PATH"), ":");
	int i = -1;
	while (path[++i])
	{
		char *res = ft_calloc(ft_strlen(path[i]) + ft_strlen(str) + 2, 1);
		if (!res)
			return (NULL);
		cat_path(res, path[i], str);
		struct stat buffer = {0};
		if (stat(res, &buffer) == 0)
		{
			ft_freematrix(path);
			return (res);
		}
		ft_free(&res);
	}
	ft_freematrix(path);
	return (ft_strdup(str));
}

int exec(char **av, char **ev)
{
	if (is_builtin(av[0]))
		return (builtin(av[0], av));
	int pid = fork();
	if (-1 == pid)
		return (err("ERROR\n"), 1);
	if (!pid)
	{
		execve(ft_path(av[0]), av, ev);
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, handle_child);
		err("ERROR\n");
		exit(1);
	}
	int status;
	waitpid(pid, &status, 0);
	return (WIFEXITED(status) && WEXITSTATUS(status));
}

int main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	char *input;
	char **av;
	char *user = getenv("USER");
	char pwd[512] = {0};
	getcwd(pwd, 512);
	char prompt[1024] = {0};
	ft_stpcpy(ft_stpcpy(ft_stpcpy(ft_stpcpy(prompt, user), "@"), pwd), " $ ");
	input = readline(prompt);
	while (input)
	{
		signal(SIGINT, handle_parent);
		signal(SIGQUIT, SIG_IGN);
		add_history(input);
		av = ft_split_mult(input, " \n\t");
		exec(av, envp);
		ft_freematrix(av);
		ft_free(&input);
		ft_bzero(prompt, 1024);
		getcwd(pwd, 512);
		ft_stpcpy(ft_stpcpy(ft_stpcpy(ft_stpcpy(prompt, user), "@"), pwd), " $ ");
		input = readline(prompt);
	}
	rl_clear_history();
	printf("exit\n");
	return 0;
}
