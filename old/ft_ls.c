//#include <zconf.h>
//#include <dirent.h>
//
//#include <sys/stat.h>
//#include <unistd.h>
//
//#include <stdio.h>
//#include <errno.h>
//#include <string.h>
//
//#include <stdlib.h>
//
//#include <pwd.h>
//#include <grp.h>
//
//#include "arg_parser.h"
//#include "ft_ls.h"
//#include "ft_printf.h"
//
//t_argdata *G_ARGS;
//
//char *get_mode_string(mode_t mode)
//{
//	char *res;
//
//	res = malloc(11);
//	res[0] = S_ISDIR(mode) ? 'd' : '-';
//	res[1] = mode & S_IRUSR ? 'r' : '-';
//	res[2] = mode & S_IWUSR ? 'w' : '-';
//	res[3] = mode & S_IXUSR ? 'x' : '-';
//	res[4] = mode & S_IRGRP ? 'r' : '-';
//	res[5] = mode & S_IWGRP ? 'w' : '-';
//	res[6] = mode & S_IXGRP ? 'x' : '-';
//	res[7] = mode & S_IROTH ? 'r' : '-';
//	res[8] = mode & S_IWOTH ? 'w' : '-';
//	res[9] = mode & S_IXOTH ? 'x' : '-';
//	res[10] = '\0';
//	return res;
//}
//
//char *get_name_by_uid(int uid)
//{
//	struct passwd *pass = getpwuid(uid);
//	if (pass)
//		return strdup(pass->pw_name);
//	else
//		return strdup("");
//}
//
//char *get_name_by_gid(int gid)
//{
//	struct group *pass = getgrgid(gid);
//	if (pass)
//		return strdup(pass->gr_name);
//	else
//		return strdup("");
//}
//
//
//void print_line(t_filedata *data)
//{
//	if (G_ARGS->flags & F_L)
//		ft_printf("%s %10s %10s %10ld %s\n",
//				get_mode_string(data->premissions),
//				get_name_by_uid(data->user_id),
//				get_name_by_gid(data->group_id),
//				data->size,
//				data->name);
//	else
//		ft_printf("%s ", data->name);
//}
//
//char *create_path(char *l, char *r)
//{
//	size_t l1, l2;
//	l1 = strlen(l);
//	l2 = strlen(r);
//	char *res = malloc(l1 + l2 + 2);
//	memcpy(res, l, l1);
//	res[l1] = '/';
//	memcpy(res + l1 + 1, r, l2);
//	res[l1 + l2 + 1] = 0;
//	return (res);
//}
//
//
//int recursive_ls(t_list_node *node, char *rel_path)
//{
//	if (!S_ISDIR(((t_filedata *)(node->content))->premissions))
//	{
//		print_line((t_filedata *)(node->content));
//		return 0;
//	}
//
//	char *dir_path = create_path(rel_path, ((t_filedata *)(node->content))
//	->name);
//
//	DIR *dir = opendir(dir_path);
//
//	struct dirent *res;
//	struct stat buff;
//	char *tmp;
//	errno = 0;
//
//	t_list	*files_in_dir;
//
//	files_in_dir = ft_lstinit();
//
//	while ((res = readdir(dir)))
//	{
//		tmp = create_path(dir_path, res->d_name);
//		lstat(tmp, &buff);
//		ft_lstadd(files_in_dir, )
//	}
//
//	return 0;
//
//
//
//}
//
//int ls_iterative(t_list_node *node)
//{
//	if (S_ISDIR(((t_filedata *)(node->content))->premissions))
//		return (recursive_ls(node, ((t_filedata *)(node->content))->name));
//	else
//	{
//		print_line((t_filedata *)(node->content));
//		return 0;
//	}
//}
//
//void	fill_data(t_filedata *d, struct stat *data)
//{
//	d->size = data->st_size;
//	d->group_id = data->st_gid;
//	d->user_id = data->st_uid;
//	d->premissions = data->st_mode;
//}
//
//int	get_files_data(t_list *files_list, t_list *target_list)
//{
//	cur = target_list->begin;
//	while (cur)
//	{
//		if (lstat(cur->content, &buff) == -1)
//			return (-1);
//		tmp.name = cur->content;
//		fill_data(&tmp, &buff);
//		ft_lstaddend(files_list, ft_lstnew_node(&tmp, sizeof(t_filedata)));
//		cur = cur->next;
//	}
//	return (0);
//}
//
//int ft_ls(t_argdata *args)
//{
//
//    t_list      files_list;
//    t_list      dir_list;
//    t_list_node *cur;
//    int 		res;
//
//    G_ARGS = args;
//    files_list.begin = NULL;
//    files_list.end = NULL;
//    files_list.len = 0;
//	get_files_data(&files_list, args->dirs);
//    //sort_files_first(files_list);
//    cur = files_list.begin;
//    res = ft_lstiter(&files_list, ls_iterative);
//	return (res);
//}
