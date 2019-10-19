/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_pars.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbethany <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/19 17:54:27 by kbethany          #+#    #+#             */
/*   Updated: 2019/10/19 17:59:36 by kbethany         ###   ########.fr       */
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

char	*get_name_by_uid(uid_t uid)
{
	struct passwd *pass;

	pass = getpwuid(uid);
	if (pass)
		return (strdup(pass->pw_name));
	else
		return (strdup(""));
}

char	*get_name_by_gid(gid_t gid)
{
	struct group *pass;

	pass = getgrgid(gid);
	if (pass)
		return (strdup(pass->gr_name));
	else
		return (strdup(""));
}

char	*get_name_by_time(t_filedata *s)
{
	char	*a;

	a = ctime(&(s->cur_time.tv_sec)) + 4;
	return (a);
}
