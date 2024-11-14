#include "../Include/minishell.h"
#include <assert.h>

static void	test_tree(t_tree *tree, char **input);

static void	test_pipe(t_tree *tree, char **input)
{
	t_pipe	*pipe;

	pipe = (t_pipe *) tree;
	test_tree((t_tree *) pipe->left, input);
	assert(ft_strncmp(*input, "|", ft_strlen(*input)) == 0);
	input++;
	test_tree((t_tree *) pipe->right, input);
}

static void	test_delim(t_tree *tree, char **input)
{
	t_delim	*delim;

	delim = (t_delim *) tree;
	test_tree((t_tree *) delim->right, input);
	assert(ft_strncmp(*input, "<<", ft_strlen(*input)) == 0);
	input++;
	assert(ft_strncmp(*input, delim->delim, ft_strlen(delim->delim)) == 0);
	input++;
}

static void	test_redir(t_tree *tree, char **input)
{
	t_redir	*redir;

	redir = (t_redir *) tree;
	test_tree((t_tree *) redir->right, input);
	if (**input == '<')
		assert(redir->mode == O_RDONLY);
	else if (**input == '>')
		assert(redir->mode == (O_WRONLY | O_CREAT));
	else if (ft_strncmp(*input, ">>", ft_strlen(*input)) == 0)
		assert(redir->mode == (O_WRONLY | O_CREAT | O_APPEND));
	input++;
	assert(ft_strncmp(*input, redir->file, ft_strlen(redir->file)));
	input++;
}

static void	test_cmd(t_tree *tree, char **input)
{
	char	**arr;
	t_cmd	*cmd;
	int		i;
	int		arr_size;

	cmd = (t_cmd *) tree;
	arr = split_input(*input);
	assert(ft_strncmp(*input, cmd->cmd, ft_strlen(cmd->cmd)) == 0);
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
}

static void	test_tree(t_tree *tree, char **input)
{
	if (tree == NULL)
		return ;
	else if (tree->type == PIPE)
		test_pipe(tree, input);
	else if (tree->type == DELIM)
		test_delim(tree, input);	
	else if (tree->type == REDIR)
		test_redir(tree, input);
	else if (tree->type == CMD)
		test_cmd(tree, input);
}

int	main(void)
{
	t_tree	*tree;
	t_tree	*tree_cpy;

	// Test "ls -l" input
	tree = tokenisation("ls -l");
	tree_cpy = tree;
	char	*input[1] = {"ls -l"};
	test_tree(tree_cpy, input);
	clear_tree(tree);

	// Test "cat < infile" input
	tree = tokenisation("cat < infile");
	tree_cpy = tree;
	char	*input2[3] = {"cat", "<", "infile"};
	test_tree(tree_cpy, input2);
	clear_tree(tree);

	// Test "cat < "" input
	tree = tokenisation("cat < """);
	tree_cpy = tree;
	char	*input3[3] = {"cat", "<", ""};
	test_tree(tree_cpy, input3);
	clear_tree(tree);

	// Test "cat > outfile" input
	tree = tokenisation("cat > outfile");
	tree_cpy = tree;
	char	*input4[3] = {"cat", ">", "outfile"};
	test_tree(tree_cpy, input4);
	clear_tree(tree);

	// Test "cat | grep 'dlkjfj dshfh'" input
	tree = tokenisation("cat | grep 'dlkjfj dshfh'");
	tree_cpy = tree;
	char	*input5[3] = {"cat", "|", "grep 'dlkjfj dshfh'"};
	test_tree(tree_cpy, input5);
	clear_tree(tree);

	// Test "cat | grep 'dlkjfj dshfh' | wc -l" input
	tree = tokenisation("cat | grep 'dlkjfj dshfh' | wc -l");
	tree_cpy = tree;
	char	*input6[5] = {"cat", "|", "grep 'dlkjfj dshfh'", "|", "wc -l"};
	test_tree(tree_cpy, input6);
	clear_tree(tree);
	
	// Test "cat < infile | grep 'dlkjfj dshfh' | wc -l > outfile" input
	tree = tokenisation("cat < infile | grep 'dlkjfj dshfh' | wc -l > outfile");
	tree_cpy = tree;
	char	*input7[9] = {"cat", "<", "infile", "|", "grep 'dlkjfj dshfh'", "|", "wc -l", ">", "outfile"};
	test_tree(tree_cpy, input7);
	clear_tree(tree);
}
