#include "minishell.h"

int bldin_pwd(void)
{
	char *pwd;
	char *buf;
	size_t size;

	size = 4096;
	buf = malloc(size * sizeof(char));
	if (buf == NULL)
		return (msg_error());
	pwd = getcwd(buf, size);
	if (pwd == NULL)
		return (msg_error());
	printf("%s\n", pwd);
	free(buf);
	return (0);
}
