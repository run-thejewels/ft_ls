#include "arg_parser.h"


#include <stdint.h>
#include <dirent.h>
#include <sys/stat.h>


#include <stdio.h>
#include <ft_ls.h>
#include <libft.h>
#include <errno.h>


char 		*create_path(char *l, char *r);
void		raise_error(const char *msg, char fatal);

void		fill_data(t_filedata *dst, struct stat *buff, char *name)
{
	dst->name = ft_strdup(name);
	dst->group_id = buff->st_gid;
	dst->user_id = buff->st_uid;
	dst->premissions = buff->st_mode;
	dst->size = buff->st_size;
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
	res = ft_memalloc(sizeof(t_list_node));
	res->content_size = sizeof(t_filedata);
	res->content = malloc(sizeof(t_filedata));
	fill_data(res->content, &buff, name);
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
		if ((tmp_node = create_filenode(path, cur_file->d_name)))
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

void		print_file(t_filedata *file)
{
	printf("%s\n", file->name);
}

void		print_files(t_list *files_list)
{
	t_list_node	*cur;

	cur = files_list->begin;
	while (cur)
	{
		print_file(cur->content);
		cur = cur->next;
	}
}


t_list		*get_files_by_name(t_list *filenames)
{
	t_list	*res;
	t_list_node	*cur_fname;

	res = ft_lstinit();
	cur_fname = filenames->begin;
	while (cur_fname)
	{
		ft_lstadd(res, create_filenode("",cur_fname->content));
		cur_fname = cur_fname->next;
	}
	return (res);
}

int 		ft_ls(t_argdata	*args)
{
	t_list	*files;
	t_list_node	*cur_file_name;
	t_filedata	*tmp;

	files = get_files_by_name(args->dirs);
	cur_file_name = files->begin;
	while (cur_file_name)
	{
		tmp = cur_file_name->content;
		if (!(tmp->premissions & S_IFDIR))
			print_file(tmp);
		else
		{
			files = get_files_in_dir(tmp->name, args->flags);
			if (args->dirs->len > 1 || args->flags & F_RECURSIVE)
				printf("%s:\n", tmp->name);
			print_files(files);
		}
		cur_file_name = cur_file_name->next;
	}
	return (0);
}