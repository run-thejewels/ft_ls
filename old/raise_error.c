#include "ft_printf.h"
#include <stdlib.h>

void	raise_error(const char *msg, int code, const char opt)
{
	if (opt)
		ft_dprintf(2, msg, opt);
	else
		ft_dprintf(2, msg);
	exit(code);
}