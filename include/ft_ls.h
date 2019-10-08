#ifndef FT_LS_H
#define FT_LS_H

typedef struct      s_filedata
{
	mode_t			premissions;
	uid_t			user_id;
	gid_t			group_id;
	off_t			size;
	char			*name;
	dev_t			d_type;
}                   t_filedata;

int ft_ls(t_argdata *args);

#endif
