#ifndef FT_LS_H
#define FT_LS_H

#include <ntsid.h>
#include "arg_parser.h"
#include "sys/stat.h"

typedef struct      s_filedata
{
	mode_t			premissions;
	uid_t			user_id;
	gid_t			group_id;
	off_t			size;
	quad_t          blocks;
	char			*name;
	char            *u_name;
	char            *g_name;
	char            *l_name;
	char            *p_str;
	char            *t_name;
	char            *path;
	nlink_t			h_links;
	struct timespec	mtime;
	struct timespec atime;
	struct timespec	ctime;
}                   t_filedata;


typedef struct	s_par
{
    uint32_t	h_par;
	uint32_t	u_par;
	uint32_t	g_par;
	uint32_t	s_par;
}				t_par;


int ft_ls(t_argdata *args);
char *create_path(char *l, char *r);

#endif
