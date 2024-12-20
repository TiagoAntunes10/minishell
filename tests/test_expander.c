#include "../Include/minishell.h"

int	g_exit_code = 1;

static void check_str_lit(t_cmd *cmd)
{
	char	*str;
	int		i;

	if (*(cmd->cmd) == '\'' || *(cmd->cmd) == '"')
	{
		str = ft_substr(cmd->cmd, 1, ft_strlen(cmd->cmd) - 2);
		free(cmd->cmd);
		cmd->cmd = ft_substr(str, 0, ft_strlen(str));
		free(str);
	}
	i = 0;
	while (cmd->opt[i] != NULL)
	{
		if (*(cmd->opt[i]) == '\'' || *(cmd->opt[i]) == '"')
		{
			str = ft_substr(cmd->opt[i], 1, ft_strlen(cmd->opt[i]) - 2);
			free(cmd->opt[i]);
			cmd->opt[i] = ft_substr(str, 0, ft_strlen(str));
			free(str);
		}
		i++;
	}
}

int	main(int argc, char **argv, char **env)
{
	t_tree	*tree;
	t_envp	*envp;
	t_cmd	*cmd;

	(void) argc;
	(void) argv;
	envp = arr_to_lst(env);

	tree = tokenisation("$?", envp);
	cmd = (t_cmd *) tree;
	check_dolla(cmd, envp);
	check_str_lit(cmd);
	printf("cmd: %s\nopt: %s\n", cmd->cmd, cmd->opt[0]);
	clear_tree(tree);

	tree = tokenisation("$?dksajfklj", envp);
	cmd = (t_cmd *) tree;
	check_dolla(cmd, envp);
	check_str_lit(cmd);
	printf("cmd: %s\nopt: %s\n", cmd->cmd, cmd->opt[0]);
	clear_tree(tree);

	tree = tokenisation("$PWD", envp);
	cmd = (t_cmd *) tree;
	check_dolla(cmd, envp);
	check_str_lit(cmd);
	printf("cmd: %s\nopt: %s\n", cmd->cmd, cmd->opt[0]);
	clear_tree(tree);

	tree = tokenisation("$PWDdkajfklj", envp);
	cmd = (t_cmd *) tree;
	check_dolla(cmd, envp);
	check_str_lit(cmd);
	printf("cmd: %s\nopt: %s\n", cmd->cmd, cmd->opt[0]);
	clear_tree(tree);

	tree = tokenisation("'kldsajfkl adsjf $PWDdkajfklj'", envp);
	cmd = (t_cmd *) tree;
	check_dolla(cmd, envp);
	check_str_lit(cmd);
	printf("cmd: %s\nopt: %s\n", cmd->cmd, cmd->opt[0]);
	clear_tree(tree);

	tree = tokenisation("'kldsajfkl adsjf $PWDdkajfklj kdljaflk'", envp);
	cmd = (t_cmd *) tree;
	check_dolla(cmd, envp);
	check_str_lit(cmd);
	printf("cmd: %s\nopt: %s\n", cmd->cmd, cmd->opt[0]);
	clear_tree(tree);

	tree = tokenisation("'kldsajfkl adsjf $?dkajfklj kdljaflk'", envp);
	cmd = (t_cmd *) tree;
	check_dolla(cmd, envp);
	check_str_lit(cmd);
	printf("cmd: %s\nopt: %s\n", cmd->cmd, cmd->opt[0]);
	clear_tree(tree);

	tree = tokenisation("'kldsajfkl adsjf \\$?dkajfklj kdljaflk'", envp);
	cmd = (t_cmd *) tree;
	check_dolla(cmd, envp);
	check_str_lit(cmd);
	printf("cmd: %s\nopt: %s\n", cmd->cmd, cmd->opt[0]);
	clear_tree(tree);

	tree = tokenisation("\"kldsajfkl adsjf $?dkajfklj $PWD kdljaflk\"", envp);
	cmd = (t_cmd *) tree;
	check_dolla(cmd, envp);
	check_str_lit(cmd);
	printf("cmd: %s\nopt: %s\n", cmd->cmd, cmd->opt[0]);
	clear_tree(tree);

	tree = tokenisation("\"$SHLVL kldsajfkl $PWDadsjf $?dkajfklj $PWD kdljaflk\"", envp);
	cmd = (t_cmd *) tree;
	check_dolla(cmd, envp);
	check_str_lit(cmd);
	printf("cmd: %s\nopt: %s\n", cmd->cmd, cmd->opt[0]);
	clear_tree(tree);

	clear_envp(envp);
}
