#include "../Include/minishell.h"
#include <assert.h>

int	g_exit_code = 0;

static char	**test_tree(t_tree *tree, char **input, t_envp *envp);

static char	**test_pipe(t_tree *tree, char **input, t_envp *envp)
{
	t_pipe	*pipe;

	pipe = (t_pipe *) tree;
	input = test_tree(pipe->left, input, envp);
	assert(ft_strncmp(*input, "|", ft_strlen(*input)) == 0);
	input++;
	input = test_tree(pipe->right, input, envp);
	return (input);
}

static char	**test_delim(t_tree *tree, char **input, t_envp *envp)
{
	t_delim	*delim;

	delim = (t_delim *) tree;
	input = test_tree(delim->right, input, envp);
	assert(ft_strncmp(*input, "<<", ft_strlen(*input)) == 0);
	input++;
	assert(ft_strncmp(*input, delim->delim, ft_strlen(delim->delim)) == 0);
	input++;
	return (input);
}

static char	**test_redir(t_tree *tree, char **input, t_envp *envp)
{
	t_redir	*redir;

	redir = (t_redir *) tree;
	input = test_tree(redir->right, input, envp);
	if (**input == '<' && ft_strlen(*input) == 1)
		assert(redir->mode == O_RDONLY);
	else if (**input == '>' && ft_strlen(*input) == 1)
		assert(redir->mode == (O_WRONLY | O_CREAT));
	else if (ft_strncmp(*input, ">>", ft_strlen(*input)) == 0)
		assert(redir->mode == (O_WRONLY | O_CREAT | O_APPEND));
	input++;
	if (redir->file == NULL)
		assert(redir->file == *input);
	else
		assert(ft_strncmp(*input, redir->file, ft_strlen(redir->file)) == 0);
	input++;
	return (input);
}

static char	**test_cmd(t_tree *tree, char **input, t_envp *envp)
{
	char	**arr;
	t_cmd	*cmd;
	int		i;
	int		arr_size;

	cmd = (t_cmd *) tree;
	arr = split_input(*input, envp);
	assert(ft_strncmp(arr[0], cmd->cmd, ft_strlen(cmd->cmd)) == 0);
	input++;
	arr_size = 0;
	while (arr[arr_size] != NULL)
		arr_size++;
	i = 0;
	while (i < arr_size)
	{
		assert(ft_strncmp(arr[i], cmd->opt[i], ft_strlen(cmd->opt[i])) == 0);
		i++;
	}
	clear_arr(arr);
	return (input);
}

static char	**test_tree(t_tree *tree, char **input, t_envp *envp)
{
	if (tree == NULL)
		return (NULL);
	else if (tree->type == PIPE)
		return (test_pipe(tree, input, envp));
	else if (tree->type == DELIM)
		return (test_delim(tree, input, envp));
	else if (tree->type == REDIR)
		return (test_redir(tree, input, envp));
	else if (tree->type == CMD)
		return (test_cmd(tree, input, envp));
	return (NULL);
}

int	main(int argc, char **argv, char **env)
{
	t_tree	*tree;
	t_tree	*tree_cpy;
	t_envp	*envp;

	(void) argc;
	(void) argv;
	envp = arr_to_lst(env);
	// Test "ls -l" input
	tree = tokenisation("ls -l", envp);
	tree_cpy = tree;
	char	*input[1] = {"ls -l"};
	test_tree(tree_cpy, input, envp);
	clear_tree(tree);

	// Test "cat < infile" input
	tree = tokenisation("cat < infile", envp);
	tree_cpy = tree;
	char	*input2[3] = {"cat", "<", "infile"};
	test_tree(tree_cpy, input2, envp);
	clear_tree(tree);

	// Test "cat < "" input
	tree = tokenisation("cat < """, envp);
	tree_cpy = tree;
	char	*input3[3] = {"cat", "<", NULL};
	test_tree(tree_cpy, input3, envp);
	clear_tree(tree);

	// Test "cat > outfile" input
	tree = tokenisation("cat > outfile", envp);
	tree_cpy = tree;
	char	*input4[3] = {"cat", ">", "outfile"};
	test_tree(tree_cpy, input4, envp);
	clear_tree(tree);

	// Test "cat | grep 'dlkjfj dshfh'" input
	tree = tokenisation("cat | grep 'dlkjfj dshfh'", envp);
	tree_cpy = tree;
	char	*input5[3] = {"cat", "|", "grep 'dlkjfj dshfh'"};
	test_tree(tree_cpy, input5, envp);
	clear_tree(tree);

	// Test "cat | grep 'dlkjfj dshfh' | wc -l" input
	tree = tokenisation("cat | grep 'dlkjfj dshfh' | wc -l", envp);
	tree_cpy = tree;
	char	*input6[5] = {"cat", "|", "grep 'dlkjfj dshfh'", "|", "wc -l"};
	test_tree(tree_cpy, input6, envp);
	clear_tree(tree);
	
	// Test "cat < infile | grep 'dlkjfj dshfh' | wc -l > outfile" input
	tree = tokenisation("cat < infile | grep 'dlkjfj dshfh' | wc -l > outfile", envp);
	tree_cpy = tree;
	char	*input7[9] = {"cat", "<", "infile", "|", "grep 'dlkjfj dshfh'", "|", "wc -l", ">", "outfile"};
	test_tree(tree_cpy, input7, envp);
	clear_tree(tree);

	// Test "cat << delim" input
	tree = tokenisation("cat << delim", envp);
	tree_cpy = tree;
	char	*input8[3] = {"cat", "<<", "delim"};
	test_tree(tree_cpy, input8, envp);
	clear_tree(tree);

	// Test "cat >> outfile" input
	tree = tokenisation("cat >> outfile", envp);
	tree_cpy = tree;
	char	*input9[3] = {"cat", ">>", "outfile"};
	test_tree(tree_cpy, input9, envp);
	clear_tree(tree);
	
	// Test "(cat infile) | wc -l" input
	tree = tokenisation("(cat infile) | wc -l", envp);
	tree_cpy = tree;
	char	*input10[3] = {"cat infile", "|", "wc -l"};
	test_tree(tree_cpy, input10, envp);
	clear_tree(tree);

	// Test "< infile cat" input
	tree = tokenisation("< infile cat", envp);
	tree_cpy = tree;
	char	*input11[3] = {"cat", "<", "infile"};
	test_tree(tree_cpy, input11, envp);
	clear_tree(tree);

	clear_envp(envp);
}
