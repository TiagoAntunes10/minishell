#include "../Include/minishell.h"

int	g_exit_code = 1;

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
	printf("cmd: %s\nopt: %s\n", cmd->cmd, cmd->opt[0]);
	clear_tree(tree);

	tree = tokenisation("$?dksajfklj", envp);
	cmd = (t_cmd *) tree;
	check_dolla(cmd, envp);
	printf("cmd: %s\nopt: %s\n", cmd->cmd, cmd->opt[0]);
	clear_tree(tree);

	tree = tokenisation("$PWD", envp);
	cmd = (t_cmd *) tree;
	check_dolla(cmd, envp);
	printf("cmd: %s\nopt: %s\n", cmd->cmd, cmd->opt[0]);
	clear_tree(tree);

	tree = tokenisation("$PWDdkajfklj", envp);
	cmd = (t_cmd *) tree;
	check_dolla(cmd, envp);
	printf("cmd: %s\nopt: %s\n", cmd->cmd, cmd->opt[0]);
	clear_tree(tree);

	tree = tokenisation("'kldsajfkl adsjf $PWDdkajfklj'", envp);
	cmd = (t_cmd *) tree;
	check_dolla(cmd, envp);
	printf("cmd: %s\nopt: %s\n", cmd->cmd, cmd->opt[0]);
	clear_tree(tree);

	tree = tokenisation("'kldsajfkl adsjf $PWDdkajfklj kdljaflk'", envp);
	cmd = (t_cmd *) tree;
	check_dolla(cmd, envp);
	printf("cmd: %s\nopt: %s\n", cmd->cmd, cmd->opt[0]);
	clear_tree(tree);

	tree = tokenisation("'kldsajfkl adsjf $?dkajfklj kdljaflk'", envp);
	cmd = (t_cmd *) tree;
	check_dolla(cmd, envp);
	printf("cmd: %s\nopt: %s\n", cmd->cmd, cmd->opt[0]);
	clear_tree(tree);

	tree = tokenisation("'kldsajfkl adsjf \\$?dkajfklj kdljaflk'", envp);
	cmd = (t_cmd *) tree;
	check_dolla(cmd, envp);
	printf("cmd: %s\nopt: %s\n", cmd->cmd, cmd->opt[0]);
	clear_tree(tree);

	tree = tokenisation("'kldsajfkl adsjf $?dkajfklj $PWD kdljaflk'", envp);
	cmd = (t_cmd *) tree;
	check_dolla(cmd, envp);
	printf("cmd: %s\nopt: %s\n", cmd->cmd, cmd->opt[0]);
	clear_tree(tree);

	tree = tokenisation("'$SHLVL kldsajfkl $PWDadsjf $?dkajfklj $PWD kdljaflk'", envp);
	cmd = (t_cmd *) tree;
	check_dolla(cmd, envp);
	printf("cmd: %s\nopt: %s\n", cmd->cmd, cmd->opt[0]);
	clear_tree(tree);

	clear_envp(envp);
}
