
#include "ft_printf.h"
#include "arg_parser.h"
#include "ft_ls.h"


int main(int argc, char **argv)
{
	t_argdata *res = arg_parser(argc, argv);

	ft_ls(res);
}
