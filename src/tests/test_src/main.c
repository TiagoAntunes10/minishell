#include "../includes/macro.h"

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
		(void)!write(2, str++, 1);
}

int is_builtin(char *str)
{
	char **builtins = (char *[]){"exit", "cd", "pwd", "echo", "env", "export", "unset",  NULL};
	int i = -1;
	while (builtins[++i])
		if (str && !ft_strcmp(builtins[i], str))
			return (1);
	return (0);
}

int b_exit(t_cmd *cmd, t_envp *envp)
{
	int ext = 0;
	if (cmd->opt[0] && !cmd->opt[1])
	{
		clear_envp(envp);
		ft_free(&cmd->cmd);
		ft_freematrix(cmd->opt);
		free(cmd);
		return (printf("exit\n"), exit(0), 1);
	}
	else if (cmd->opt[1])
	{
		ext = ft_atoi(cmd->opt[1]);
		clear_envp(envp);
		ft_free(&cmd->cmd);
		ft_freematrix(cmd->opt);
		free(cmd);
		return (printf("exit\n"), exit(ext), 1);
	}
	return (1);
}

int builtin(t_cmd *cmd, t_envp *envp)
{
	char **builtins = (char *[]){"exit", "cd", "pwd", "echo", "env", "export", "unset",  NULL};
	t_builtin_fn bt_fn = {b_exit, ft_cd, ft_pwd, ft_echo, ft_env, ft_export, ft_unset, NULL};
	int i = -1;
	while (builtins[++i])
		if (cmd->cmd && !ft_strcmp(builtins[i], cmd->cmd))
			return (bt_fn[i](cmd, envp));
	return (0);
}

char *ft_path(char *str)
{
	char **path = ft_split_mult(getenv("PATH"), ":");
	if (!path)
		return (NULL);
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

int exec(t_cmd *cmd, t_envp *envp, char **ev)
{
	char **env = lst_to_arr(envp);
	char *path;
	if (is_builtin(cmd->cmd))
		return (builtin(cmd, envp));
	int pid = fork();
	path = ft_path(cmd->cmd);
	if (-1 == pid)
		return (err("ERROR\n"), 1);
	if (!pid)
	{
		signal_child();
		execve(path, cmd->opt, env);
		err("ERROR\n");
		exit(1);
	}
	ft_freematrix(env);
	free(path);
	int status;
	waitpid(pid, &status, 0);
	return (WIFEXITED(status) && WEXITSTATUS(status));
}

int main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	char *input;
	t_cmd *cmd;
	t_envp	*ev;
	char prompt[7000000] = {RED "testshell->" RST};
	cmd = ft_calloc(1, sizeof(t_cmd));
	ev = arr_to_lst(envp);
	input = readline(prompt);
	while (input)
	{
		signal_parent();
		add_history(input);
		cmd->opt = ft_split_mult(input, " \t");
		if (!(cmd->cmd = ft_strdup(cmd->opt[0])))
			continue ;
		exec(cmd, ev, envp);
		ft_free(&cmd->cmd);
		ft_freematrix(cmd->opt);
		ft_free(&input);
		input = readline(prompt);
	}
	clear_envp(ev);
	ft_free(&cmd->cmd);
	free(cmd);
	rl_clear_history();
	printf("exit\n");
	return (0);
}
