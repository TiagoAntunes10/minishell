#include "../Include/minishell.h"

// TODO: Make tests
int	main(int argc, char **argv, char *env)
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
