//#include <sys/types.h>
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
//char *strjoin(char *r, char *l)
//{
//	size_t l1, l2;
//	l1 = strlen(r);
//	l2 = strlen(l);
//	char *res = malloc(l1 + l2 + 1);
//	memcpy(res, r, l1);
//	memcpy(res + l1, l, l2);
//	res[l1 + l2] = 0;
//	return res;
//}
//
//char *get_mode_string(int mode)
//{
//    char *res;
//
//    res = malloc(11);
//    res[0] = S_ISDIR(mode) ? 'd' : '-';
//    res[1] = mode & S_IRUSR ? 'r' : '-';
//    res[2] = mode & S_IWUSR ? 'w' : '-';
//    res[3] = mode & S_IXUSR ? 'x' : '-';
//    res[4] = mode & S_IRGRP ? 'r' : '-';
//    res[5] = mode & S_IWGRP ? 'w' : '-';
//    res[6] = mode & S_IXGRP ? 'x' : '-';
//    res[7] = mode & S_IROTH ? 'r' : '-';
//    res[8] = mode & S_IWOTH ? 'w' : '-';
//    res[9] = mode & S_IXOTH ? 'x' : '-';
//    res[10] = '\0';
//    return res;
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
//void print_line(struct dirent *res, struct stat *buff)
//{
//    printf("%s %10s %10s %10lld %s\n",
//           get_mode_string(buff->st_mode),
//           get_name_by_uid(buff->st_uid),
//           get_name_by_gid(buff->st_gid),
//           buff->st_size,
//           res->d_name);
//}
//
//int     print_single(DIR *d, char *path, char r)
//{
//    struct dirent *res;
//    struct stat buff;
//    char *tmp;
//    errno = 0;
//    if (d && (res = readdir(d)))
//    {
//        if (res->d_type == DT_REG || res->d_type == DT_DIR)
//        {
//            tmp = create_path(path, res->d_name);
//            lstat(tmp, &buff);
//            print_line(res, &buff);
//            print_single(d, path, r);
//            if (r && res->d_type == DT_DIR && strcmp("..", res->d_name) != 0 &&
//                strcmp(".", res->d_name) != 0)
//            {
//                d = opendir(tmp);
//                printf("%s:\n", tmp);
//                print_single(d, tmp, r);
//            }
//        }
//    }
//    return 0;
//}
//
//
//
//int 	not_ft_ls(char *path, char R)
//{
//	DIR *kek = opendir(path);
//
//	char *cur_path = path;
//
//	print_single(kek, cur_path, R);
//}
