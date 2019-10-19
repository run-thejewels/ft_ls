/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_files.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbethany <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/19 17:23:11 by kbethany          #+#    #+#             */
/*   Updated: 2019/10/19 18:51:40 by kbethany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <dirent.h>
#include <sys/stat.h>
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
#include "ft_ls.h"

static uint32_t	sizelen(long s)
{
	int		i;
	long	k;

	i = 1;
	k = 1;
	while (k < s)
	{
		k *= 10;
		i++;
	}
	return (i);
}

static void		print_l(t_filedata *pr, t_par *p)
{
	time_t	now;
	int		i;

	now = time(NULL);
	pr->t_name = get_name_by_time(pr);
	i = (now - pr->cur_time.tv_sec > 15811200) ? 15 : 7;
	if (S_ISLNK(pr->premissions))
		ft_printf("%-*s%*d %-*s  %-*s  %*lld %.7s%1.5s %s -> %s\n", p->p_par,
			pr->p_str, p->h_par, pr->h_links, p->u_par, pr->u_name,
			p->g_par, pr->g_name, p->s_par, pr->size, pr->t_name,
			pr->t_name + i, pr->name, pr->l_name);
	else
		ft_printf("%-*s%*d %-*s  %-*s  %*lld %.7s%1.5s %s\n", p->p_par,
			pr->p_str, p->h_par, pr->h_links, p->u_par, pr->u_name,
			p->g_par, pr->g_name, p->s_par, pr->size, pr->t_name,
			pr->t_name + i, pr->name);
	free(pr->u_name);
	free(pr->g_name);
	free(pr->p_str);
	free(pr->l_name);
}

static void		get_l_par(t_filedata *fil, t_par *par)
{
	ssize_t	i;

	fil->p_str = get_mode_string(fil);
	if (ft_strlen(fil->p_str) > par->p_par)
		par->p_par = ft_strlen(fil->p_str);
	if (S_ISLNK(fil->premissions))
	{
		fil->l_name = (char*)malloc(NAME_MAX);
		i = readlink(fil->path, fil->l_name, NAME_MAX);
		fil->l_name[i] = '\0';
	}
	fil->u_name = get_name_by_uid(fil->user_id);
	if (ft_strlen(fil->u_name) > par->u_par)
		par->u_par = ft_strlen(fil->u_name);
	fil->g_name = get_name_by_gid(fil->group_id);
	if (ft_strlen(fil->g_name) > par->g_par)
		par->g_par = ft_strlen(fil->g_name);
	if (sizelen(fil->h_links) > par->h_par)
		par->h_par = sizelen(fil->h_links);
	if (sizelen(fil->size) > par->s_par)
		par->s_par = sizelen(fil->size);
	par->bl += fil->blocks;
}

void			print_file(t_filedata *file, uint32_t flags)
{
	t_par	*p;

	p = ft_memalloc(sizeof(t_par));
	(void)flags;
	if (flags & F_L)
	{
		get_l_par(file, p);
		print_l(file, p);
	}
	else
		ft_printf("%s ", file->name);
	free(p);
}

void			print_files(t_list *files_list, uint32_t flags)
{
	t_list_node	*cur;
	t_filedata	*fil;
	t_par		*par;

	cur = files_list->begin;
	par = ft_memalloc(sizeof(t_par));
	if (flags & F_L)
	{
		par->bl = 0;
		while (cur)
		{
			get_l_par(cur->content, par);
			cur = cur->next;
		}
		cur = files_list->begin;
		ft_printf("total %lld\n", par->bl);
	}
	while (cur)
	{
		fil = cur->content;
		(flags & F_L) ? print_l(fil, par) : ft_printf("%s ", fil->name);
		cur = cur->next;
	}
	write(1, "\n", 1);
	free(par);
}
