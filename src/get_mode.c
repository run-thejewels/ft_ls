/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_mode.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbethany <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/19 18:00:26 by kbethany          #+#    #+#             */
/*   Updated: 2019/10/19 18:43:54 by kbethany         ###   ########.fr       */
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
#include <stdio.h>
#include "ft_printf.h"
#include "ft_ls.h"

static char	firts_char(mode_t mode)
{
	if (S_ISDIR(mode))
		return ('d');
	else if (S_ISBLK(mode))
		return ('b');
	else if (S_ISCHR(mode))
		return ('c');
	else if (S_ISLNK(mode))
		return ('l');
	else if (S_ISSOCK(mode))
		return ('s');
	else if (S_ISFIFO(mode))
		return ('p');
	else
		return ('-');
}

static void	sst_char(mode_t mode, char *res)
{
	if (mode & S_ISVTX)
		res[9] = res[9] == '-' ? 'T' : 't';
	if (mode & S_ISGID)
		res[6] = res[6] == '-' ? 'S' : 's';
	if (mode & S_ISUID)
		res[3] = res[3] == '-' ? 'S' : 's';
}

static void	attr_res10(t_filedata *f, char *res)
{
	acl_t	tmp;
	ssize_t	ret;

	if ((tmp = acl_get_file(f->path, ACL_TYPE_EXTENDED)) != NULL)
		res[10] = '+';
	else if (errno == 2)
		errno = 0;
	else
		perror(strerror(errno));
	acl_free(tmp);
	if ((ret = listxattr(f->path, NULL, 0, XATTR_NOFOLLOW)) < 0)
	{
		errno = 0;
		return ;
	}
	if (ret > 0)
	{
		res[10] = '@';
	}
}

char		*get_mode_string(t_filedata *f)
{
	char	*res;

	res = malloc(12);
	ft_bzero(res, 12);
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
	if (res[10] == '+' || res[10] == '@')
		res[11] = '\0';
	else
		res[10] = '\0';
	return (res);
}
