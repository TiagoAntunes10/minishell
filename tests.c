#include "Include/minishell.h"
#include <assert.h>

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
