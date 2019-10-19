/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_sorts.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbethany <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/19 18:09:38 by kbethany          #+#    #+#             */
/*   Updated: 2019/10/19 18:12:08 by kbethany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "ft_string.h"

int			mtime_sort(t_filedata *a, t_filedata *b)
{
	return ((int)(a->cur_time.tv_sec - b->cur_time.tv_sec));
}

int			size_sort(t_filedata *a, t_filedata *b)
{
	return ((int)(b->size - a->size));
}

int			name_sort(t_filedata *a, t_filedata *b)
{
	return (ft_strcmp(a->name, b->name));
}
