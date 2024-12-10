#include "../includes/macro.h"
#include <readline/readline.h>

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

int is_builtin(char *name)
{
	char	**bt;
	int		i;

	bt = (char (*[])){"exit", "cd", "pwd", "echo", "env", "export",
		"unset", NULL};
	i = -1;
	while (bt[++i])
		if (name && !ft_strncmp(bt[i], name, ft_strlen(name)))
			return (1);
	return (0);
}

int ft_exit(t_cmd *cmd, t_envp *envp)
{
	int ext = 0;
	if (cmd->opt[0] && !cmd->opt[1])
	{
		rl_clear_history();
		clear_envp(envp);
		ft_free(&cmd->cmd);
		ft_freematrix(cmd->opt);
		free(cmd);
		return (printf("exit\n"), exit(0), 1);
	}
	else if (cmd->opt[1])
	{
		ext = ft_atoi(cmd->opt[1]);
		rl_clear_history();
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
	int		i;
	int		(**bt_func)(t_cmd *, t_envp *);
	char	**bt_name;

	bt_name = (char (*[])){"exit", "cd", "pwd",
		"echo", "env", "export", "unset", NULL};
	bt_func = (int (*[])(t_cmd *, t_envp *)){ft_exit, ft_cd, ft_pwd, ft_echo,
		ft_env, ft_export, ft_unset, NULL};
	i = -1;
	while (bt_name[++i])
		if (cmd->cmd && !ft_strcmp(bt_name[i], cmd->cmd))
			return (bt_func[i](cmd, envp));
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
	char **env;
	char *path;
	if (is_builtin(cmd->cmd))
		return (builtin(cmd, envp));
	env = lst_to_arr(envp);
	signal_child();
	int pid = fork();
	path = ft_path(cmd->cmd);
	if (-1 == pid)
		return (err("ERROR\n"), 1);
	if (!pid)
	{
		execve(path, cmd->opt, env);
		ft_free(&path);
		ft_freematrix(env);
		err("ERROR\n");
		exit(1);
	}
	ft_freematrix(env);
	free(path);
	int status;
	waitpid(pid, &status, 0);
	signal_parent();
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
		cmd->cmd = ft_strdup(cmd->opt[0]);
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
