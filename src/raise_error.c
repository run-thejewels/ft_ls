#include "ft_printf.h"
#include <stdlib.h>

void	raise_error(const char *msg, char fatal)
{
	ft_dprintf(2, msg);
	if (fatal)
		exit(1);
}