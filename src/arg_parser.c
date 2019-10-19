#include "arg_parser.h"
#include "ft_list.h"
#include "ft_string.h"
#include <stdio.h>

static unsigned            get_basic_flag(char c)
{

	if (c == 'l')
		return (F_L);
	else if (c == 'r')
		return (F_REVERSE);
	else if (c == 'R')
		return (F_RECURSIVE);
	else if (c == 'a')
		return (F_ALL);
	else if (c == 'c')
		return (F_MTIME);
	else if (c == 'T')
		return (F_SIZE);
	else if (c == 't')
		return (F_MTIME);
	else if (c == 'u')
		return (F_ATIME);
	else if (c == 'U')
		return (F_CTIME);
	return (0);
}

static void	raise_error(const char *msg, int code, const char opt)
{
	if (opt)
		dprintf(2, msg, opt);
	else
		dprintf(2, "%s", msg);
	exit(code);
}

static unsigned            get_flags(char *str)
{
	unsigned    res;
	unsigned    tmp;
	size_t		cur;

	cur = 0;
	res = 0;
	while (str[cur] != '\0')
	{
		if (!(tmp = get_basic_flag(str[cur])))
			raise_error("ls: illegal option -- %c\n", 2,
					str[cur]);
		res |= tmp;
		cur++;
	}
	return (res);
}

t_argdata           *arg_parser(int argc, char **argv)
{
	t_argdata   *res;
	int         cur_arg;

	res = malloc(sizeof(t_argdata));
	res->dirs = ft_lstinit();
	res->flags = 0;
	cur_arg = 1;
	while (cur_arg < argc)
	{
		if (argv[cur_arg][0] == '-')
			res->flags |= get_flags(argv[cur_arg] + 1);
		else
			ft_lstaddend(res->dirs, ft_lstnew_node(argv[cur_arg],
					ft_strlen(argv[cur_arg]) + 1));
		cur_arg++;
	}
	if (res->dirs->len == 0)
		ft_lstaddend(res->dirs, ft_lstnew_node(".", 2));
	return (res);
}
