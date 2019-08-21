#ifndef FT_LS_ARG_PARSER_H
# define FT_LS_ARG_PARSER_H

# include "ft_list.h"
# include <unistd.h>
# define F_RECURSIVE 1U
# define F_REVERSE 2U
# define F_TIME 4U
# define F_L 8U
# define F_ALL 16U


typedef struct		s_argdata
{
	t_list			*dirs;
	unsigned        flags;
}                    t_argdata;

t_argdata           *arg_parser(int argc, char **argv);
#endif
