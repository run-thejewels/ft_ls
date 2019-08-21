#include <zconf.h>
#include "arg_parser.h"

int ft_ls(t_argdata *args)
{
    t_list      files_list;
    t_list      dir_list;
    t_list_node *cur;

    get_file_data(&files_list, args->dirs);
    sort_files_first(files_list);
    cur = files_list.begin;
    while (cur)
    {
        if (is_dir(cur->content))
    }
}

int recursive_ls(t_list *dir_list)
{
    t_list 
    sort_files();
}