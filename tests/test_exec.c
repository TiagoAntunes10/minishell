#include "../Include/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_tree	*tree;
	t_envp	*envp_lst;

	(void) argc;
	(void) argv;
	envp_lst = arr_to_lst(envp);
	
	// // Test "ls -l" input
	// tree = tokenisation("ls -l", envp_lst);
	// execution(tree, -1, envp_lst);
	// clear_tree(tree);

	// // Test "cat < infile" input
	// tree = tokenisation("cat < infile", envp_lst);
	// execution(tree, -1, envp_lst);
	// clear_tree(tree);

	// // Test "cat < """ input
	// tree = tokenisation("cat < """, envp_lst);
	// execution(tree, -1, envp_lst);
	// clear_tree(tree);

	// // Test "cat infile > outfile" input
	// tree = tokenisation("cat infile > outfile", envp_lst);
	// execution(tree, -1, envp_lst);
	// clear_tree(tree);

	// // Test "cat < infile > outfile" input
	// tree = tokenisation("cat < infile > outfile", envp_lst);
	// execution(tree, -1, envp_lst);
	// clear_tree(tree);

	// // Test "cat infile | grep 'lk'" input
	// tree = tokenisation("cat infile | grep 'lk'", envp_lst);
	// execution(tree, -1, envp_lst);
	// clear_tree(tree);

	// // Test "cat test_exec.c | grep 'void' | wc -l" input
	// tree = tokenisation("cat test_exec.c | grep 'void' | wc -l", envp_lst);
	// execution(tree, -1, envp_lst);
	// clear_tree(tree);

	// TODO: Understand why this has still reachable leaks
	// // Test "cat < infile | grep 'lk' | wc -l > outfile" input
	// tree = tokenisation("cat < infile | grep 'lk' | wc -l > outfile", envp_lst);
	// execution(tree, -1, envp_lst);
	// clear_tree(tree);

	// Test "cat << delim" input
	tree = tokenisation("cat << delim", envp_lst);
	execution(tree, -1, envp_lst);
	clear_tree(tree);

	// Test "cat < infile >> outfile" input
	// tree = tokenisation("cat < infile >> outfile", envp_lst);
	// execution(tree, -1, envp_lst);
	// clear_tree(tree);

	// // Test "(cat infile) | wc -l" input
	// tree = tokenisation("(cat infile) | wc -l", envp_lst);
	// execution(tree, -1, envp_lst);
	// clear_tree(tree);

	// // Test "cat infile | cat infile | ls -l" input
	// tree = tokenisation("cat infile | cat infile | ls -l", envp_lst);
	// execution(tree, -1, envp_lst);
	// clear_tree(tree);
	clear_envp(envp_lst);
}
