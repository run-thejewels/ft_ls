/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleann <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 12:24:00 by jleann            #+#    #+#             */
/*   Updated: 2019/10/09 12:24:03 by jleann           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arg_parser.h"
#include <stdint.h>
#include <dirent.h>
#include <sys/stat.h>
#include <stdio.h>
#include <ft_ls.h>
#include <libft.h>
#include <errno.h>

int				is_print_dir(t_list *lst)
{
	t_list_node	*cur;
	t_filedata	*tmp;
	char		res;

	res = 0;
	cur = lst->begin;
	while (cur)
	{
		tmp = cur->content;
		if (tmp->premissions & (uint32_t)S_IFDIR)
		{
			res = 1;
			break ;
		}
		cur = cur->next;
	}
	return (lst->len > 1 && res);
}

void			free_fileslst(t_list *flist)
{
	t_list_node	*cur;
	t_list_node	*tmp;
	t_filedata	*content;

	cur = flist->begin;
	while (cur)
	{
		content = cur->content;
		tmp = cur->next;
		free(content->name);
		free(content->path);
		free(content);
		free(cur);
		cur = tmp;
	}
	free(flist);
}

void			fill_data(t_filedata *dst, struct stat *buff,
					char *name, char *path)
{
	dst->name = ft_strdup(name);
	dst->group_id = buff->st_gid;
	dst->user_id = buff->st_uid;
	dst->premissions = buff->st_mode;
	dst->size = buff->st_size;
	dst->blocks = buff->st_blocks;
	dst->h_links = buff->st_nlink;
	dst->path = ft_strdup(path);
}

struct timespec	get_time(struct stat *buff, uint32_t flags)
{
	if (flags & F_ATIME)
		return (buff->st_atimespec);
	else if (flags & F_MTIME)
		return (buff->st_mtimespec);
	else if (flags & F_CTIME)
		return (buff->st_ctimespec);
	return (buff->st_mtimespec);
}

t_list_node		*create_filenode(char *path, char *name,
							uint32_t flags, char fatal)
{
	struct stat		buff;
	char			*tmp_str;
	t_list_node		*res;

	tmp_str = path[0] ? create_path(path, name) : name;
	if (lstat(tmp_str, &buff) == -1)
	{
		raise_error("Cannot read file!!!\n", fatal);
		return (NULL);
	}
	res = ft_memalloc(sizeof(t_list_node));
	res->content_size = sizeof(t_filedata);
	res->content = malloc(sizeof(t_filedata));
	ft_bzero(res->content, sizeof(t_filedata));
	fill_data(res->content, &buff, name, tmp_str);
	((t_filedata *)(res->content))->cur_time = get_time(&buff, flags);
	if (tmp_str != name)
		free(tmp_str);
	return (res);
}
