//
// Created by Jasper Leann on 12/10/2019.
//

#include "arg_parser.h"


#include <stdint.h>
#include <dirent.h>
#include <sys/stat.h>


#include <stdio.h>
#include <ft_ls.h>
#include <libft.h>
#include <errno.h>
#include <pwd.h>
#include <grp.h>

static char *get_mode_string(mode_t mode)
{
	char *res;

	res = malloc(11);
	if (S_ISDIR(mode))
		res[0] = 'd';
	else if (S_ISBLK(mode))
		res[0] = 'b';
	else if (S_ISCHR(mode))
		res[0] = 'c';
	else if (S_ISLNK(mode))
		res[0] = 'l';
	else if (S_ISSOCK(mode))
		res[0] = 's';
	else
		res[0] = mode & S_IFIFO ? 'p' : '-';
	res[1] = mode & S_IRUSR ? 'r' : '-';
	res[2] = mode & S_IWUSR ? 'w' : '-';
	res[3] = mode & S_IXUSR ? 'x' : '-';
	res[4] = mode & S_IRGRP ? 'r' : '-';
	res[5] = mode & S_IWGRP ? 'w' : '-';
	res[6] = mode & S_IXGRP ? 'x' : '-';
	res[7] = mode & S_IROTH ? 'r' : '-';
	res[8] = mode & S_IWOTH ? 'w' : '-';
	res[9] = mode & S_IXOTH ? 'x' : '-';
	res[10] = '\0';
	return res;
}

static char *get_name_by_uid(uid_t uid)
{
	struct passwd *pass = getpwuid(uid);
	if (pass)
		return strdup(pass->pw_name);
	else
		return strdup("");
}

static char *get_name_by_gid(gid_t gid)
{
	struct group *pass = getgrgid(gid);
	if (pass)
		return strdup(pass->gr_name);
	else
		return strdup("");
}

void print_line(t_list_node *s, t_par *p)
{
	t_filedata *pr;

	while (s)
	{
		pr = s->content;
		printf("%s 0 %*s %*s %*lld %s\n",
			   get_mode_string(pr->premissions), p->u_par,
			   pr->u_name, p->g_par, pr->g_name, p->s_par,
			   pr->size,
			   pr->name);
		s = s->next;
	}
}

void		print_file(t_filedata *file, uint32_t flags)
{
	printf("%s ", file->name);
}

int         sizelen(off_t s)
{
	int i;
	int k;

	i = 1;
	k = 1;
	while (k < s)
	{
		k *= 10;
		i++;
	}
	return (i);
}

void		print_files(t_list *files_list, uint32_t flags)
{
	off_t 			s;
	t_list_node	*cur;
	t_filedata	*fil;
	t_par       *par;

	cur = files_list->begin;
	par = (t_par *)malloc(sizeof(par));
	par->u_par = 0;
	par->g_par = 0;
	par->s_par = 0;
	if (flags & F_L)
	{
		while (cur)
		{
			fil = cur->content;
			fil->u_name = get_name_by_uid(fil->user_id);
			fil->g_name = get_name_by_gid(fil->group_id);
			if (ft_strlen(fil->u_name) > par->u_par)
				par->u_par = ft_strlen(fil->u_name);
			if (ft_strlen(fil->g_name) > par->g_par)
				par->g_par = ft_strlen(fil->g_name);
			if (sizelen(fil->size) > par->s_par)
				par->s_par = sizelen(fil->size);
			s += fil->size;
			cur = cur->next;
		}
		s = s / 512 + (s % 512 != 0);
		printf("total %lld\n", s);
		cur = files_list->begin;
		print_line(cur, par);
	}
	else
		while (cur)
		{
			fil = cur->content;
			printf("%s ", fil->name);
			cur = cur->next;
		}
}
