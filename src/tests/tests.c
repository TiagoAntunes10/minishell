#include "../../Include/minishell.h"
#include <assert.h>

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
	test_tree((t_tree *) delim->cmd, input);
	assert(ft_strncmp(*input, "<<", ft_strlen(*input)) == 0);
	input++;
	assert(ft_strncmp(*input, delim->delim, ft_strlen(delim->delim)) == 0);
	input++;
}

static void	test_redir(t_tree *tree, char **input)
{
	t_redir	*redir;

	redir = (t_redir *) tree;
	test_tree((t_tree *) redir->cmd, input);
	if (**input == '<')
		assert(redir->mode == O_RDONLY);
	else if (**input == '>')
		assert(redir->mode == O_WRONLY | O_CREAT);
	else if (ft_strncmp(*input, ">>", ft_strlen(*input)) == 0)
		assert(redir->mode == O_WRONLY | O_CREAT | O_APPEND);
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
		assert(ft_strncmp(arr[i], cmd->opt[i], ft_strlen(cmd->opt[i++])) == 0);
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
	t_tokens	*tokens_lst;
	t_tokens	*tokens_cpy;

	// Test "ls -l" input
	tokens_lst = tokenisation("ls -l");
	assert(ft_strncmp(tokens_lst->cmd, "ls", 2) == 0);
	assert(ft_strncmp(tokens_lst->options[0], "ls", 2) == 0);
	assert(ft_strncmp(tokens_lst->options[1], "-l", 2) == 0);
	clear_lst(tokens_lst);

	// Test "cat < infile" input
	tokens_lst = tokenisation("cat < infile");
	assert(ft_strncmp(tokens_lst->cmd, "cat", 3) == 0);
	assert(ft_strncmp(tokens_lst->options[0], "cat", 3) == 0);
	assert(tokens_lst->options[1] == NULL);
	assert(ft_strncmp(tokens_lst->infile, "infile", 6) == 0);
	clear_lst(tokens_lst);

	// Test "cat < """ input
	tokens_lst = tokenisation("cat < """);
	assert(ft_strncmp(tokens_lst->cmd, "cat", 3) == 0);
	assert(ft_strncmp(tokens_lst->options[0], "cat", 3) == 0);
	assert(tokens_lst->options[1] == NULL);
	assert(tokens_lst->infile == NULL);
	clear_lst(tokens_lst);

	// Test "cat > outfile" input
	tokens_lst = tokenisation("cat > outfile");
	assert(ft_strncmp(tokens_lst->cmd, "cat", 3) == 0);
	assert(ft_strncmp(tokens_lst->options[0], "cat", 3) == 0);
	assert(tokens_lst->options[1] == NULL);
	assert(ft_strncmp(tokens_lst->outfile, "outfile", 7) == 0);
	clear_lst(tokens_lst);

	// Test "cat | grep 'dlkjfj dshfh'" input
	tokens_lst = tokenisation("cat | grep 'dlkjfj dshfh'");
	tokens_cpy = tokens_lst;
	assert(ft_strncmp(tokens_cpy->cmd, "cat", 3) == 0);
	assert(ft_strncmp(tokens_cpy->options[0], "cat", 3) == 0);
	assert(tokens_cpy->options[1] == NULL);
	tokens_cpy = tokens_cpy->next;
	assert(ft_strncmp(tokens_cpy->cmd, "grep", 4) == 0);
	assert(ft_strncmp(tokens_cpy->options[0], "grep", 4) == 0);
	assert(ft_strncmp(tokens_cpy->options[1], "dlkjfj dshfh", 12) == 0);
	assert(tokens_cpy->options[2] == NULL);
	clear_lst(tokens_lst);

	// Test "cat | grep 'dlkjfj dshfh' | wc -l" input
	tokens_lst = tokenisation("cat | grep 'dlkjfj dshfh' | wc -l");
	tokens_cpy = tokens_lst;
	assert(ft_strncmp(tokens_cpy->cmd, "cat", 3) == 0);
	assert(ft_strncmp(tokens_cpy->options[0], "cat", 3) == 0);
	assert(tokens_cpy->options[1] == NULL);
	tokens_cpy = tokens_cpy->next;
	assert(ft_strncmp(tokens_cpy->cmd, "grep", 4) == 0);
	assert(ft_strncmp(tokens_cpy->options[0], "grep", 4) == 0);
	assert(ft_strncmp(tokens_cpy->options[1], "dlkjfj dshfh", 12) == 0);
	assert(tokens_cpy->options[2] == NULL);
	tokens_cpy = tokens_cpy->next;
	assert(ft_strncmp(tokens_cpy->cmd, "wc", 2) == 0);
	assert(ft_strncmp(tokens_cpy->options[0], "wc", 2) == 0);
	assert(ft_strncmp(tokens_cpy->options[1], "-l", 2) == 0);
	assert(tokens_cpy->options[2] == NULL);
	clear_lst(tokens_lst);
	
	// Test "cat < infile | grep 'dlkjfj dshfh' | wc -l > outfile" input
	tokens_lst = tokenisation("cat < infile | grep 'dlkjfj dshfh' | wc -l > outfile");
	tokens_cpy = tokens_lst;
	assert(ft_strncmp(tokens_cpy->cmd, "cat", 3) == 0);
	assert(ft_strncmp(tokens_cpy->options[0], "cat", 3) == 0);
	assert(tokens_cpy->options[1] == NULL);
	assert(ft_strncmp(tokens_lst->infile, "infile", 6) == 0);
	tokens_cpy = tokens_cpy->next;
	assert(ft_strncmp(tokens_cpy->cmd, "grep", 4) == 0);
	assert(ft_strncmp(tokens_cpy->options[0], "grep", 4) == 0);
	assert(ft_strncmp(tokens_cpy->options[1], "dlkjfj dshfh", 12) == 0);
	assert(tokens_cpy->options[2] == NULL);
	tokens_cpy = tokens_cpy->next;
	assert(ft_strncmp(tokens_cpy->cmd, "wc", 2) == 0);
	assert(ft_strncmp(tokens_cpy->options[0], "wc", 2) == 0);
	assert(ft_strncmp(tokens_cpy->options[1], "-l", 2) == 0);
	assert(tokens_cpy->options[2] == NULL);
	assert(ft_strncmp(tokens_cpy->outfile, "outfile", 7) == 0);
	clear_lst(tokens_lst);
}
