#include <stdlib.h>
#include <stdio.h>

int main(void)
{
	char	*env;

	env = getenv("PATH");
	if (env == NULL)
	{
		printf("did not work\n");
		return (0);
	}
	printf("Worked: %s\n", env);
}
