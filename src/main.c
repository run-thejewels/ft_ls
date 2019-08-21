
#include "ft_printf.h"
#include "arg_parser.h"

int main(int argc, char **argv)
{
	t_argdata *res = arg_parser(argc, argv);
	t_list_node *cur = res->dirs->begin;
	while (cur)
	{
		ft_printf("%s\n", cur->content);
		cur = cur->next;
	}
	//not_ft_ls("/home/fellum", 0);
}
