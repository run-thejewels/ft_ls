/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleann <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 12:24:00 by jleann            #+#    #+#             */
/*   Updated: 2019/10/09 12:24:03 by jleann           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_ARG_PARSER_H
# define FT_LS_ARG_PARSER_H

# include "ft_list.h"
# include <unistd.h>
# define F_RECURSIVE 1U
# define F_REVERSE 2U
# define F_L 8U
# define F_ALL 16U
# define OF_PRINT_DIR 32U
# define F_SIZE 64U
# define F_MTIME 128U
# define F_ATIME 256U
# define F_CTIME 512U

typedef struct		s_argdata
{
	t_list			*dirs;
	unsigned		flags;
}					t_argdata;

t_argdata			*arg_parser(int argc, char **argv);
#endif
