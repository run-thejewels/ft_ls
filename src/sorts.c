/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorts.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbethany <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/19 18:09:15 by kbethany          #+#    #+#             */
/*   Updated: 2019/10/19 18:13:35 by kbethany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_list.h"
#include "ft_ls.h"
#include "ft_string.h"

static void		swap_nodes(t_list *lst, t_list_node *l, t_list_node *r)
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
	r->prev = l->prev;
	l->prev = r;
}

static void		lst_sort(t_list *files_list,
				int (*f)(t_filedata *, t_filedata *), char rev)
{
	t_list_node	*tmp;
	t_list_node	*pmt;

	tmp = files_list->end;
	while (tmp)
	{
		pmt = files_list->begin;
		while (pmt->next)
		{
			if (f(pmt->content, pmt->next->content) * (rev ? -1 : 1) > 0)
			{
				swap_nodes(files_list, pmt, pmt->next);
				if (tmp == pmt->prev)
					tmp = pmt;
			}
			else
				pmt = pmt->next;
		}
		tmp = tmp->prev;
	}
}

void			sort_files(t_list *files_list, uint32_t flags)
{
	lst_sort(files_list, name_sort, flags & F_REVERSE);
	if (flags & F_SIZE)
		lst_sort(files_list, size_sort, flags & F_REVERSE);
	if (flags & F_MTIME || flags & F_CTIME || flags & F_ATIME)
		lst_sort(files_list, mtime_sort, flags & F_REVERSE);
}
