#include "../Include/minishell.h"

int	g_exit_code = 1;

static void	get_full_str(t_cmd *cmd, t_envp *envp)
{
	int		i;

	i = 0;
	cmd->cmd = remove_quotes(cmd->cmd, envp);
	while (cmd->opt[i] != NULL)
	{
		cmd->opt[i] = remove_quotes(cmd->opt[i], envp);
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
	get_full_str(cmd, envp);
	printf("cmd: %s\nopt: %s\n", cmd->cmd, cmd->opt[0]);
	clear_tree(tree);

	tree = tokenisation("$?dksajfklj", envp);
	cmd = (t_cmd *) tree;
	get_full_str(cmd, envp);
	printf("cmd: %s\nopt: %s\n", cmd->cmd, cmd->opt[0]);
	clear_tree(tree);

	tree = tokenisation("$PWD", envp);
	cmd = (t_cmd *) tree;
	get_full_str(cmd, envp);
	printf("cmd: %s\nopt: %s\n", cmd->cmd, cmd->opt[0]);
	clear_tree(tree);

	tree = tokenisation("$PWDdkajfklj", envp);
	cmd = (t_cmd *) tree;
	get_full_str(cmd, envp);
	printf("cmd: %s\nopt: %s\n", cmd->cmd, cmd->opt[0]);
	clear_tree(tree);

	tree = tokenisation("'kldsajfkl adsjf $PWDdkajfklj'", envp);
	cmd = (t_cmd *) tree;
	get_full_str(cmd, envp);
	printf("cmd: %s\nopt: %s\n", cmd->cmd, cmd->opt[0]);
	clear_tree(tree);

	tree = tokenisation("'kldsajfkl adsjf $PWDdkajfklj kdljaflk'", envp);
	cmd = (t_cmd *) tree;
	get_full_str(cmd, envp);
	printf("cmd: %s\nopt: %s\n", cmd->cmd, cmd->opt[0]);
	clear_tree(tree);

	tree = tokenisation("'kldsajfkl adsjf $?dkajfklj kdljaflk'", envp);
	cmd = (t_cmd *) tree;
	get_full_str(cmd, envp);
	printf("cmd: %s\nopt: %s\n", cmd->cmd, cmd->opt[0]);
	clear_tree(tree);

	tree = tokenisation("'kldsajfkl adsjf \\$?dkajfklj kdljaflk'", envp);
	cmd = (t_cmd *) tree;
	get_full_str(cmd, envp);
	printf("cmd: %s\nopt: %s\n", cmd->cmd, cmd->opt[0]);
	clear_tree(tree);

	tree = tokenisation("\"kldsajfkl adsjf $?dkajfklj $PWD kdljaflk\"", envp);
	cmd = (t_cmd *) tree;
	get_full_str(cmd, envp);
	printf("cmd: %s\nopt: %s\n", cmd->cmd, cmd->opt[0]);
	clear_tree(tree);

	tree = tokenisation("\"$SHLVL kldsajfkl $PWDadsjf $?dkajfklj $PWD kdljaflk\"", envp);
	cmd = (t_cmd *) tree;
	get_full_str(cmd, envp);
	printf("cmd: %s\nopt: %s\n", cmd->cmd, cmd->opt[0]);
	clear_tree(tree);

	tree = tokenisation("\"'$USER'\"", envp);
	cmd = (t_cmd *) tree;
	get_full_str(cmd, envp);
	printf("cmd: %s\nopt: %s\n", cmd->cmd, cmd->opt[0]);
	clear_tree(tree);

	tree = tokenisation("\"ksdljf daskfj kjdf '$USER'\"", envp);
	cmd = (t_cmd *) tree;
	get_full_str(cmd, envp);
	printf("cmd: %s\nopt: %s\n", cmd->cmd, cmd->opt[0]);
	clear_tree(tree);

	tree = tokenisation("\"ksdljf daskfj kjdf $USER\"", envp);
	cmd = (t_cmd *) tree;
	get_full_str(cmd, envp);
	printf("cmd: %s\nopt: %s\n", cmd->cmd, cmd->opt[0]);
	clear_tree(tree);

	tree = tokenisation("jdsflkjdjs\"ksdljf daskfj kjdf $USER\"sldkjjds", envp);
	cmd = (t_cmd *) tree;
	get_full_str(cmd, envp);
	printf("cmd: %s\nopt: %s\n", cmd->cmd, cmd->opt[0]);
	clear_tree(tree);

	tree = tokenisation("jdsflkjdjs'ksdljf daskfj kjdf $USER'sldkjjds", envp);
	cmd = (t_cmd *) tree;
	get_full_str(cmd, envp);
	printf("cmd: %s\nopt: %s\n", cmd->cmd, cmd->opt[0]);
	clear_tree(tree);

	tree = tokenisation("jdsflkjdjs'ksdljf daskfj kjdf $USERdksj'sldkjjds", envp);
	cmd = (t_cmd *) tree;
	get_full_str(cmd, envp);
	printf("cmd: %s\nopt: %s\n", cmd->cmd, cmd->opt[0]);
	clear_tree(tree);

	tree = tokenisation("echo kjdf\"$USER\"nice", envp);
	cmd = (t_cmd *) tree;
	get_full_str(cmd, envp);
	printf("cmd: %s\nopt1: %s\nopt2: %s\n", cmd->cmd, cmd->opt[0], cmd->opt[1]);
	clear_tree(tree);

	clear_envp(envp);
}
