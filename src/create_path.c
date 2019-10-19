/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleann <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 12:24:00 by jleann            #+#    #+#             */
/*   Updated: 2019/10/09 12:24:03 by jleann           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_string.h>

char	*create_path(char *l, char *r)
{
	char	*res;
	size_t	l1;
	size_t	l2;

	l1 = ft_strlen(l);
	l2 = ft_strlen(r);
	res = malloc(l1 + l2 + 2);
	ft_memcpy(res, l, l1);
	res[l1] = '/';
	ft_memcpy(res + l1 + 1, r, l2);
	res[l1 + l2 + 1] = 0;
	return (res);
}
