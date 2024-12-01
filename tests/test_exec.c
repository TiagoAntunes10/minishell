#include "../Include/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_tree	*tree;
	t_envp	*envp_lst;

	(void) argc;
	(void) argv;
	envp_lst = arr_to_lst(envp);
	// Test "ls -l" input
	tree = tokenisation("ls -l", envp_lst);
	execution(tree, -1, envp_lst);
	clear_tree(tree);

	// Test "cat < infile" input
	tree = tokenisation("cat < infile", envp_lst);
	execution(tree, -1, envp_lst);
	clear_tree(tree);

	// Test "cat < "" input
	tree = tokenisation("cat < """, envp_lst);
	execution(tree, -1, envp_lst);
	clear_tree(tree);

	// Test "cat > outfile" input
	tree = tokenisation("cat > outfile", envp_lst);
	execution(tree, -1, envp_lst);
	clear_tree(tree);

	// Test "cat | grep 'dlkjfj dshfh'" input
	tree = tokenisation("cat | grep 'dlkjfj dshfh'", envp_lst);
	execution(tree, -1, envp_lst);
	clear_tree(tree);

	// Test "cat | grep 'dlkjfj dshfh' | wc -l" input
	tree = tokenisation("cat | grep 'dlkjfj dshfh' | wc -l", envp_lst);
	execution(tree, -1, envp_lst);
	clear_tree(tree);
	
	// Test "cat < infile | grep 'dlkjfj dshfh' | wc -l > outfile" input
	tree = tokenisation("cat < infile | grep 'dlkjfj dshfh' | wc -l > outfile", envp_lst);
	execution(tree, -1, envp_lst);
	clear_tree(tree);

	// Test "cat << delim" input
	tree = tokenisation("cat << delim", envp_lst);
	execution(tree, -1, envp_lst);
	clear_tree(tree);

	// Test "cat >> outfile" input
	tree = tokenisation("cat >> outfile", envp_lst);
	execution(tree, -1, envp_lst);
	clear_tree(tree);
	
	// Test "(cat infile) | wc -l" input
	tree = tokenisation("(cat infile) | wc -l", envp_lst);
	execution(tree, -1, envp_lst);
	clear_tree(tree);
}
