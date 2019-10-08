

char *get_mode_string(int mode)
{
   char *res;


       if (S_ISDIR(s->premissions))
           printf("d");
       else if (S_ISBLK(s->premissions))
           printf("b");
       else if (S_ISCHR(s->premissions))
           printf("c");
       else if (S_ISLNK(s->premissions))
           printf("l");
       else if (S_ISSOCK(s->premissions))
           printf("s");
       else if (S_ISFIFO(s->premissions))
           printf("p");
       else
           printf("-");

   res = malloc(11);
   res[0] = S_ISDIR(mode) ? 'd' : '-';
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
void print_line(t_filedata *s)
{
  char a;

  printf("%s %10s %10s %10lld %s\n",
          get_mode_string(buff->st_mode),
          get_name_by_uid(buff->st_uid),
          get_name_by_gid(buff->st_gid),
          buff->st_size,
          res->d_name);
}

void    print(t_list *dir,unsigned flags)
{
  t_list_node *tmp;
  t_filedata  *d;
  off_t       c;


  tmp = dir->begin;
  c = 0
  while(tmp)
  {
    d = tmp->content;
    c += d->size;
    tmp = tmp->next;
  }
  c = c / 512 + (c % 512 != 0);
  t_filedata *somt
    if (flags & 8U)

        print_line(somt);
    else
        print_file(somt);
}
