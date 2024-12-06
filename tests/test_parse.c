#include "../Include/minishell.h"
#include <assert.h>

static char	**test_tree(t_tree *tree, char **input);

static char	**test_pipe(t_tree *tree, char **input)
{
	t_pipe	*pipe;

	pipe = (t_pipe *) tree;
	input = test_tree(pipe->left, input);
	assert(ft_strncmp(*input, "|", ft_strlen(*input)) == 0);
	input++;
	input = test_tree(pipe->right, input);
	return (input);
}

static char	**test_delim(t_tree *tree, char **input)
{
	t_delim	*delim;

	delim = (t_delim *) tree;
	input = test_tree(delim->right, input);
	assert(ft_strncmp(*input, "<<", ft_strlen(*input)) == 0);
	input++;
	assert(ft_strncmp(*input, delim->delim, ft_strlen(delim->delim)) == 0);
	input++;
	return (input);
}

static char	**test_redir(t_tree *tree, char **input)
{
	t_redir	*redir;

	redir = (t_redir *) tree;
	input = test_tree(redir->right, input);
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

static char	**test_cmd(t_tree *tree, char **input)
{
	char	**arr;
	t_cmd	*cmd;
	int		i;
	int		arr_size;

	cmd = (t_cmd *) tree;
	arr = split_input(*input);
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

static char	**test_tree(t_tree *tree, char **input)
{
	if (tree == NULL)
		return (NULL);
	else if (tree->type == PIPE)
		return (test_pipe(tree, input));
	else if (tree->type == DELIM)
		return (test_delim(tree, input));
	else if (tree->type == REDIR)
		return (test_redir(tree, input));
	else if (tree->type == CMD)
		return (test_cmd(tree, input));
	return (NULL);
}

int	main(int argc, char **argv, char **envp)
{
	t_tree	*tree;
	t_tree	*tree_cpy;
	t_envp	*envp_lst;

	(void) argc;
	(void) argv;
	envp_lst = arr_to_lst(envp);
	// Test "ls -l" input
	tree = tokenisation("ls -l", envp_lst);
	tree_cpy = tree;
	char	*input[1] = {"ls -l"};
	test_tree(tree_cpy, input);
	clear_tree(tree);

	// Test "cat < infile" input
	tree = tokenisation("cat < infile", envp_lst);
	tree_cpy = tree;
	char	*input2[3] = {"cat", "<", "infile"};
	test_tree(tree_cpy, input2);
	clear_tree(tree);

	// Test "cat < "" input
	tree = tokenisation("cat < """, envp_lst);
	tree_cpy = tree;
	char	*input3[3] = {"cat", "<", NULL};
	test_tree(tree_cpy, input3);
	clear_tree(tree);

	// Test "cat > outfile" input
	tree = tokenisation("cat > outfile", envp_lst);
	tree_cpy = tree;
	char	*input4[3] = {"cat", ">", "outfile"};
	test_tree(tree_cpy, input4);
	clear_tree(tree);

	// Test "cat | grep 'dlkjfj dshfh'" input
	tree = tokenisation("cat | grep 'dlkjfj dshfh'", envp_lst);
	tree_cpy = tree;
	char	*input5[3] = {"cat", "|", "grep 'dlkjfj dshfh'"};
	test_tree(tree_cpy, input5);
	clear_tree(tree);

	// Test "cat | grep 'dlkjfj dshfh' | wc -l" input
	tree = tokenisation("cat | grep 'dlkjfj dshfh' | wc -l", envp_lst);
	tree_cpy = tree;
	char	*input6[5] = {"cat", "|", "grep 'dlkjfj dshfh'", "|", "wc -l"};
	test_tree(tree_cpy, input6);
	clear_tree(tree);
	
	// Test "cat < infile | grep 'dlkjfj dshfh' | wc -l > outfile" input
	tree = tokenisation("cat < infile | grep 'dlkjfj dshfh' | wc -l > outfile", envp_lst);
	tree_cpy = tree;
	char	*input7[9] = {"cat", "<", "infile", "|", "grep 'dlkjfj dshfh'", "|", "wc -l", ">", "outfile"};
	test_tree(tree_cpy, input7);
	clear_tree(tree);

	// Test "cat << delim" input
	tree = tokenisation("cat << delim", envp_lst);
	tree_cpy = tree;
	char	*input8[3] = {"cat", "<<", "delim"};
	test_tree(tree_cpy, input8);
	clear_tree(tree);

	// Test "cat >> outfile" input
	tree = tokenisation("cat >> outfile", envp_lst);
	tree_cpy = tree;
	char	*input9[3] = {"cat", ">>", "outfile"};
	test_tree(tree_cpy, input9);
	clear_tree(tree);
	
	// Test "(cat infile) | wc -l" input
	tree = tokenisation("(cat infile) | wc -l", envp_lst);
	tree_cpy = tree;
	char	*input10[3] = {"cat infile", "|", "wc -l"};
	test_tree(tree_cpy, input10);
	clear_tree(tree);
}
