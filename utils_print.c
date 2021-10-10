#include "minishell.h"

int	msg_error(void)
{
	printf("%s\n", strerror(errno));
	return (errno);
}

int	msg_mallocfail(void)
{
	printf("Cannot allocate memory.\n");
	exit (12);
}
