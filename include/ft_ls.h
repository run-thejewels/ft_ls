#ifndef FT_LS_H
#define FT_LS_H

#include "arg_parser.h"
#include "sys/stat.h"

typedef struct      s_filedata
{
	mode_t			premissions;
	uid_t			user_id;
	gid_t			group_id;
	off_t			size;
	char			*name;
	char            *u_name;
	char            *g_name;
	char            *l_name;
	char            *p_str;
	char            *t_name;
	nlink_t			h_links;
	struct timespec	mtime;
	struct timespec atime;
	struct timespec	ctime;
}                   t_filedata;


typedef struct 			s_par
{
    int             p_par;
    int             h_par;
	int 			u_par;
	int				g_par;
	int 			s_par;
}						t_par;


int ft_ls(t_argdata *args);

#endif
