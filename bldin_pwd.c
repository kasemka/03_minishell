#include "minishell.h"

int bldin_pwd(void)
{
	// char *pwd;
	char *buf;
	size_t size;

	size = 4096;
	buf = malloc(size * sizeof(char));
	if (buf == NULL)
		return (msg_error());
	printf("%s\n", getcwd(buf, size));
	free(buf);
	return (0);
}
