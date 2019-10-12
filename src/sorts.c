//
// Created by Jasper Leann on 09/10/2019.
//
#include "ft_list.h"
#include "ft_ls.h"
#include "arg_parser.h"
#include "ft_string.h"

void        swap_nodes(t_list *lst, t_list_node *l, t_list_node *r)
{

	if (l->prev)
		l->prev->next = r;
	else
		lst->begin = r;
	if (r->next)
		r->next->prev = l;
	else
		lst->end = l;
	l->next = r->next;
	r->next = l;
	r->prev = l ->prev;
	l->prev = r;
}

int         time_sort(t_filedata *a, t_filedata *b)
{
	(void)a;
	(void)b;
	return (0);
}

int         size_sort(t_filedata *a, t_filedata *b)
{
	return ((int)(b->size - a->size));
}

int         name_sort(t_filedata *a, t_filedata *b)
{
	return(ft_strcmp(a->name, b->name));
}

void		lst_sort(t_list *files_list,int (*f)(t_filedata *, t_filedata *), char rev)
{
	t_list_node *tmp;
	t_list_node *pmt;

	tmp = files_list->end;
	while (tmp) {
		pmt = files_list->begin;
		while (pmt->next) {
			if (f(pmt->content, pmt->next->content) * (rev ? -1 : 1) > 0)
				swap_nodes(files_list, pmt, pmt->next);
			else
				pmt = pmt->next;
		}
		tmp = tmp->prev;
	}
}
void        sort_files(t_list *files_list, uint32_t flags)
{
	lst_sort(files_list, name_sort, flags & F_REVERSE);
//    if (flags & F_TIME)
//        lst_sort(files_list, time_sort, flags & F_REVERSE);
	if (flags & F_TIME)
		lst_sort(files_list, size_sort, flags & F_REVERSE);
}

