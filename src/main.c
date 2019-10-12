
#include "arg_parser.h"
#include "ft_ls.h"

void	free_args(t_argdata *data)
{
	t_list_node	*cur;
	t_list_node	*tmp;

	cur = data->dirs->begin;
	free(data->dirs);
	free(data);
	while (cur)
	{
		tmp = cur->next;
		free(cur->content);
		free(cur);
		cur = tmp;
	}
}

int main(int argc, char **argv)
{
	t_argdata *res = arg_parser(argc, argv);
	int ret;

	ret = ft_ls(res);
	free_args(res);
	return (ret);
}
