/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleann <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 12:24:00 by jleann            #+#    #+#             */
/*   Updated: 2019/10/09 12:24:03 by jleann           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include <ntsid.h>
# include "arg_parser.h"
# include "sys/stat.h"

typedef struct		s_filedata
{
	mode_t			premissions;
	uid_t			user_id;
	gid_t			group_id;
	off_t			size;
	quad_t			blocks;
	char			*name;
	char			*u_name;
	char			*g_name;
	char			*l_name;
	char			*p_str;
	char			*t_name;
	char			*path;
	nlink_t			h_links;
	struct timespec	cur_time;
}					t_filedata;

typedef struct		s_par
{
	quad_t			bl;
	uint32_t		p_par;
	uint32_t		h_par;
	uint32_t		u_par;
	uint32_t		g_par;
	uint32_t		s_par;
}					t_par;

int					ft_ls(t_argdata *args);
char				*create_path(char *l, char *r);
void				raise_error(const char *msg, char fatal);
void				sort_files(t_list *files_list, uint32_t flags);
void				print_file(t_filedata *file, uint32_t flags);
void				print_files(t_list *files_list, uint32_t flags);
void				ft_ls_recursive(char *path, t_filedata *file,
							uint32_t flags, char fatal);
int					is_print_dir(t_list *lst);
void				free_fileslst(t_list *flist);
t_list_node			*create_filenode(char *path, char *name,
						uint32_t flags, char fatal);

#endif
