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

void		print_file(t_filedata *file, uint32_t flags)
{
	//TODO: IMPLEMENT CORRECTLY
	flags++;
	printf("%s\n", file->name);
}

void		print_files(t_list *files_list, uint32_t flags)
{
	//TODO: IMPLEMENT CORRECTLY
	t_list_node	*cur;
	flags++;
	cur = files_list->begin;
	while (cur)
	{
		printf("%s\n", ((t_filedata *)(cur->content))->name);
		cur = cur->next;
	}
}

void        swap_nodes(t_list *lst, t_list_node *l, t_list_node *r)
{

    if (l->prev)
        l->prev->next = r;
    else
        lst->begin = r;
    if (r->next)
        r->next->prev = l;
    else
        lst->end = l;
    l->next = r->next;
    r->next = l;
    r->prev = l ->prev;
    l->prev = r;
}
int         time_sort(t_filedata *a, t_filedata *b)
{

}

int         size_sort(t_filedata *a, t_filedata *b)
{
    return ((int)(b->size - a->size));
}

int         name_sort(t_filedata *a, t_filedata *b)
{
    return(ft_strcmp(a->name, b->name));
}

void		lst_sort(t_list *files_list,int (*f)(void *, void *), char rev)
{
    t_list_node *tmp;
    t_list_node *pmt;

    tmp = files_list->end;
    while (tmp) {
        pmt = files_list->begin;
        while (pmt->next) {
            if (f(pmt->content, pmt->next->content) * (rev ? -1 : 1) > 0)
                swap_nodes(files_list, pmt, pmt->next);
            else
                pmt = pmt->next;
        }
        tmp = tmp->prev;
    }
}
void        sort_files(t_list *files_list, uint32_t flags)
{
    lst_sort(files_list, name_sort, flags & F_REVERSE);
//    if (flags & F_TIME)
//        lst_sort(files_list, time_sort, flags & F_REVERSE);
    if (flags & F_TIME)
        lst_sort(files_list, size_sort, flags & F_REVERSE);
}

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
	if (tmp_str != name)
		free(tmp_str);
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

void		ft_ls_recursive(char *path, t_filedata *file, uint32_t flags)
{
	t_list	*files;
	char	*path_to_dir;
	t_list_node	*cur_file;
	t_filedata	*tmp;

	path_to_dir = path[0] ? create_path(path, file->name) : file->name;
	files = get_files_in_dir(path_to_dir, flags);
	sort_files(files, flags);
	printf("%s:\n", path_to_dir);
	print_files(files, flags);
	printf("\n");
	cur_file = files->begin;
	while (cur_file)
	{
		tmp = cur_file->content;
		if (flags & F_RECURSIVE && tmp->premissions & (uint32_t)S_IFDIR && ft_strcmp(tmp->name, ".") && ft_strcmp(tmp->name, ".."))
			ft_ls_recursive(path_to_dir, tmp, flags);
		cur_file = cur_file->next;
	}
	free_fileslst(files);
	if (path_to_dir != file->name)
		free(path_to_dir);
}

int 		ft_ls(t_argdata	*args)
{
	t_list	*files;
	t_list_node	*cur_file_name;
	t_filedata	*tmp;

	files = get_files_by_name(args->dirs);
	sort_files(files, args->flags);
	cur_file_name = files->begin;
	while (cur_file_name)
	{
		tmp = cur_file_name->content;
		if (!(tmp->premissions & (uint32_t)S_IFDIR))
			print_file(tmp, args->flags);
		else
			ft_ls_recursive("", tmp, args->flags);
		cur_file_name = cur_file_name->next;
	}
	free_fileslst(files);
	return (errno ? 1 : 0);
}