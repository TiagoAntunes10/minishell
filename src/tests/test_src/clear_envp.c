#include "macro.h"

void	clear_envp(t_envp *envp)
{
	t_envp	*envp_cpy;

	envp_cpy = envp->next;
	while (envp != NULL)
	{
		if (envp->key != NULL)
			free(envp->key);
		if (envp->value != NULL)
			free(envp->value);
		envp_cpy = envp->next;
		free(envp);
		envp = envp_cpy;
	}
}

void	*safe_alloc(unsigned int size, unsigned int type, t_envp *envp)
{
	void	*var;

	var = malloc(size * type);
	if (var == NULL)
		return (NULL);
	ft_bzero(var, size * type);
	return (var);
}
