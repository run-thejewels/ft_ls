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

#include <time.h>
#include <limits.h>
#include <sys/xattr.h>
#include <sys/acl.h>
#include <ft_string.h>
#include "ft_printf.h"

static char firts_char(mode_t mode)
{
    if (S_ISDIR(mode))
        return ('d');
    else if (S_ISBLK(mode))
        return ('b');
    else if (S_ISCHR(mode))
        return('c');
    else if (S_ISLNK(mode))
        return ('l');
    else if (S_ISSOCK(mode))
        return ('s');
    else if(S_ISFIFO(mode))
        return ('p');
    else
        return ('-');
}

 static void sst_char(mode_t mode, char *res)
 {
     if (mode & S_ISVTX)
         res[9] = res[9] == '-' ? 'T' : 't';
     if (mode & S_ISGID)
         res[6] = res[6] == '-' ? 'S' : 's';
     if (mode & S_ISUID)
         res[3] = res[3] == '-' ? 'S' : 's';
 }

 static void attr_res10(t_filedata *f, char *res)
 {
    char *path;

    path = create_path(f->path, f->name);
     if (listxattr(path, NULL , 0, XATTR_NOFOLLOW))
         res[10] = '@';
     else if (acl_get_file(path, ACL_TYPE_EXTENDED) != NULL)
         res[10] = '+';
     else
         res[10] = ' ';
 }

static char *get_mode_string(t_filedata *f)
{
    char *res;

    res = malloc(11);
    res[0] = firts_char(f->premissions);
    res[1] = f->premissions & S_IRUSR ? 'r' : '-';
    res[2] = f->premissions & S_IWUSR ? 'w' : '-';
    res[3] = f->premissions & S_IXUSR ? 'x' : '-';
    res[4] = f->premissions & S_IRGRP ? 'r' : '-';
    res[5] = f->premissions & S_IWGRP ? 'w' : '-';
    res[6] = f->premissions & S_IXGRP ? 'x' : '-';
    res[7] = f->premissions & S_IROTH ? 'r' : '-';
    res[8] = f->premissions & S_IWOTH ? 'w' : '-';
    res[9] = f->premissions & S_IXOTH ? 'x' : '-';
    sst_char(f->premissions, res);

    attr_res10(f, res);
    res[11] = '\0';
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

static char *get_name_by_time(t_filedata *s)
{
    char    *a;

    a = ctime(&(s->mtime.tv_sec)) + 4;
    return (a);

}

void print_line(t_list_node *s, t_par *p)
{
	t_filedata *pr;
	time_t     now;
	int        i;

	now = time (NULL);
	while (s)
    {
		pr = s->content;
        pr->t_name = get_name_by_time(pr);
        if (now - pr->mtime.tv_sec > 15811200)
            i = 15;
        else
            i = 7;
        if (S_ISLNK(pr->premissions))
        {
            ft_printf("%s %*d %-*s  %-*s  %*lld %.7s%1.5s %s -> %s\n", pr->p_str,
                   p->h_par, pr->h_links ,p->u_par, pr->u_name, p->g_par,
                   pr->g_name, p->s_par, pr->size, pr->t_name, pr->t_name + i, pr->name, pr->l_name);
        }
        else
		    ft_printf("%s %*d %-*s  %-*s  %*lld %.7s%1.5s %s\n", pr->p_str,
			   p->h_par, pr->h_links ,p->u_par, pr->u_name, p->g_par,
			   pr->g_name, p->s_par, pr->size, pr->t_name, pr->t_name + i, pr->name);
		s = s->next;
	}
}

void		print_file(t_filedata *file, uint32_t flags)
{
	printf("%s ", file->name);
}

int         sizelen(long s)
{
	int i;
	long k;

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
	t_list_node	*cur;
	t_filedata	*fil;
	t_par       *par;
	quad_t      bl;


	cur = files_list->begin;
	par = ft_memalloc(sizeof(t_par));
	if (flags & F_L)
    {
		bl = 0;
		while (cur)
		{
			fil = cur->content;
			fil->p_str = get_mode_string(fil);
			if (S_ISLNK(fil->premissions))
            {
			    fil->l_name = (char*)malloc(NAME_MAX);
                readlink(fil->path, fil->l_name, NAME_MAX);
            }
			fil->u_name = get_name_by_uid(fil->user_id);
			fil->g_name = get_name_by_gid(fil->group_id);
			if (sizelen(fil->h_links) > par->h_par)
				par->h_par = sizelen(fil->h_links);
			if (ft_strlen(fil->u_name) > par->u_par)
				par->u_par = ft_strlen(fil->u_name);
			if (ft_strlen(fil->g_name) > par->g_par)
				par->g_par = ft_strlen(fil->g_name);
			if (sizelen(fil->size) > par->s_par)
				par->s_par = sizelen(fil->size);
			bl += fil->blocks;
			cur = cur->next;
		}
		printf("total %lld\n", bl);
		print_line(files_list->begin, par);
		free(par);
	}
	else
		while (cur)
		{
			fil = cur->content;
			printf("%s ", fil->name);
			cur = cur->next;
		}
}
