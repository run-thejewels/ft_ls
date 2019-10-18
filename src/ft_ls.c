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

#include "arg_parser.h"
#include <stdint.h>
#include <dirent.h>
#include <sys/stat.h>
#include <stdio.h>
#include <ft_ls.h>
#include <libft.h>
#include <errno.h>

char		*create_path(char *l, char *r);
void		raise_error(const char *msg, char fatal);
void		sort_files(t_list *files_list, uint32_t flags);

int			is_dirs_in_lst(t_list *lst)
{
	t_list_node	*cur;
	t_filedata	*tmp;

	cur = lst->begin;
	while (cur)
	{
		tmp = cur->content;
		if (tmp->premissions & (uint32_t)S_IFDIR)
			return (1);
		cur = cur->next;
	}
	return (0);
}

int			is_print_dir(t_list *lst)
{
	return (lst->len > 1 && is_dirs_in_lst(lst));
}

void		print_file(t_filedata *file, uint32_t flags);
void		print_files(t_list *files_list, uint32_t flags);

void		free_fileslst(t_list *flist)
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
		free(content);
		free(cur);
		cur = tmp;
	}
	free(flist);
}

void		fill_data(t_filedata *dst, struct stat *buff, char *name, char *path)
{
	dst->name = ft_strdup(name);
	dst->group_id = buff->st_gid;
	dst->user_id = buff->st_uid;
	dst->premissions = buff->st_mode;
	dst->size = buff->st_size;
	dst->blocks = buff->st_blocks;
	dst->h_links = buff->st_nlink;
	dst->atime = buff->st_atimespec;
	dst->mtime = buff->st_mtimespec;
	dst->ctime = buff->st_ctimespec;
	dst->path = path;
}

t_list_node	*create_filenode(char *path, char *name)
{
	struct stat		buff;
	char			*tmp_str;
	t_list_node		*res;

	tmp_str = path[0] ? create_path(path, name) : name;
	if (lstat(tmp_str, &buff) == -1)
	{
		raise_error("Cannot read file!!!\n", 0);
		return (NULL);
	}
	//if (tmp_str != name)
	//	free(tmp_str);
	res = ft_memalloc(sizeof(t_list_node));
	res->content_size = sizeof(t_filedata);
	res->content = malloc(sizeof(t_filedata));
	fill_data(res->content, &buff, name, tmp_str);
	return (res);
}

t_list		*get_files_in_dir(char *path, uint32_t flags)
{
	DIR				*dir;
	struct dirent	*cur_file;
	t_list			*files_list;
	t_list_node		*tmp_node;

	if (!(dir = opendir(path)))
	{
		raise_error("Cannot open dir!!!\n", 0);
		return (NULL);
	}
	files_list = ft_lstinit();
	while ((cur_file = readdir(dir)))
	{
		if ((cur_file->d_name[0] != '.' || flags & F_ALL) &&
			(tmp_node = create_filenode(path, cur_file->d_name)))
			ft_lstadd(files_list, tmp_node);
	}
	if (errno != 0)
	{
		raise_error("Cant read file from dir for some reason\n", 0);
		errno = 0;
	}
	closedir(dir);
	return (files_list);
}

t_list		*get_files_by_name(t_list *filenames)
{
	t_list		*res;
	t_list_node	*cur_fname;

	res = ft_lstinit();
	cur_fname = filenames->begin;
	while (cur_fname)
	{
		ft_lstadd(res, create_filenode("", cur_fname->content));
		cur_fname = cur_fname->next;
	}
	return (res);
}

void		ft_ls_recursive(char *path, t_filedata *file, uint32_t flags)
{
	t_list		*files;
	char		*path_to_dir;
	t_list_node	*cur_file;
	t_filedata	*tmp;

	path_to_dir = path[0] ? create_path(path, file->name) : file->name;
	files = get_files_in_dir(path_to_dir, flags);
	if (files)
	{
		sort_files(files, flags);
//        if (flags & OF_PRINT_DIR)
            printf("%s:\n", path_to_dir);
		print_files(files, flags);
		cur_file = files->begin;
		while (cur_file)
		{
			tmp = cur_file->content;
			if (flags & F_RECURSIVE && tmp->premissions & (uint32_t)S_IFDIR &&
				ft_strcmp(tmp->name, ".") && ft_strcmp(tmp->name, ".."))
			{
				//printf("\n\n%s:\n", path_to_dir);
				ft_ls_recursive(path_to_dir, tmp, flags);
			}
			cur_file = cur_file->next;
		}
		free_fileslst(files);
	}
	if (path_to_dir != file->name)
		free(path_to_dir);
}

int			ft_ls(t_argdata *args)
{
	t_list			*files;
	t_list_node		*cur_file_name;
	t_filedata		*tmp;

	files = get_files_by_name(args->dirs);
	args->flags |= is_print_dir(files) ? OF_PRINT_DIR : 0;
	sort_files(files, args->flags);
	cur_file_name = files->begin;
	while (cur_file_name)
	{
		tmp = cur_file_name->content;
		if (!(tmp->premissions & (uint32_t)S_IFDIR))
			print_file(tmp, args->flags);
		else
		{
			//if (args->flags & OF_PRINT_DIR)
			//	printf("%s:\n", tmp->name);
			ft_ls_recursive("", tmp, args->flags);
		}
		cur_file_name = cur_file_name->next;
	}
	free_fileslst(files);
	return (errno ? 1 : 0);
}
