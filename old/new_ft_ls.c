//
// Created by Jasper Leann on 07/10/2019.
//

#include <sys/stat.h>
#include <dirent.h>
#include "arg_parser.h"
#include "ft_ls.h"
#include <stdio.h>

void	recursive_shit(t_filedata *cur_dir, char *path);
int	ls_iterative(t_list_node *node, char *path);


char *create_path(char *l, char *r)
{
	size_t l1, l2;
	l1 = strlen(l);
	l2 = strlen(r);
	char *res = malloc(l1 + l2 + 2);
	memcpy(res, l, l1);
	res[l1] = '/';
	memcpy(res + l1 + 1, r, l2);
	res[l1 + l2 + 1] = 0;
	return (res);
}


void	fill_data(t_filedata *d, struct stat *data)
{
	d->size = data->st_size;
	d->group_id = data->st_gid;
	d->user_id = data->st_uid;
	d->premissions = data->st_mode;
}

int	get_files_data(t_list *files_list, t_list *target_list)
{
	t_list_node	*cur;
	t_filedata	tmp;
	struct stat buff;

	cur = target_list->begin;
	while (cur)
	{
		if (lstat(cur->content, &buff) == -1)
			return (-1);
		tmp.name = cur->content;
		fill_data(&tmp, &buff);
		ft_lstaddend(files_list, ft_lstnew_node(&tmp, sizeof(t_filedata)));
		cur = cur->next;
	}
	return (0);
}

t_list	*get_files_in_dir(char *path)
{
	DIR *dir = opendir(path);

	struct dirent *res;
	struct stat buff;

	char *tmp;
	t_list	*files_in_dir;
	t_filedata	tmpf;

	files_in_dir = ft_lstinit();

	while ((res = readdir(dir)))
	{
		tmp = create_path(path, res->d_name);
		if (lstat(tmp, &buff) == -1)
			printf("%s", tmp);
		tmpf.name = res->d_name;
		fill_data(&tmpf, &buff);
		ft_lstaddend(files_in_dir, ft_lstnew_node(&tmp, sizeof(t_filedata)));
	}
	return (files_in_dir);

}

void	print_file(t_filedata	*cur_file)
{
	printf("%s ", cur_file->name);
}

void	print_dirname(t_filedata *data)
{
	printf("%s:/\n", data->name);
}

int	ls_iterative(t_list_node *node, char *path)
{
	t_filedata	*cur_file;

	cur_file = node->content;
	if (S_ISDIR(cur_file->premissions))
	{
		print_dirname(cur_file);
		recursive_shit(cur_file, path);
	}
	else
		print_file(cur_file);
	return (0);
}

void	recursive_shit(t_filedata *cur_dir, char *path)
{
	t_list *init_dirs;
	t_list	*files_data;


	char *tmp_path = create_path(path, cur_dir->name);
	init_dirs = get_files_in_dir(tmp_path);
	files_data = ft_lstinit();

	get_files_data(files_data, init_dirs);
	t_list_node	*cur;

	cur = files_data->begin;
	while (cur)
	{
		ls_iterative(cur, path);
		cur = cur->next;
	}
}



int	ft_ls(t_argdata *args)
{
	t_list *init_dirs;
	t_list	*files_data;

	init_dirs = args->dirs;
	files_data = ft_lstinit();

	get_files_data(files_data, init_dirs);
	t_list_node	*cur;

	cur = files_data->begin;
	while (cur)
	{
		ls_iterative(cur, "");
		cur = cur->next;
	}
	return (0);
}
