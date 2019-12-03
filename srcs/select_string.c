/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select_string.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alan <alanbarnett328@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/20 01:42:40 by alan              #+#    #+#             */
/*   Updated: 2019/12/03 12:59:31 by abarnett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "select_string.h"
#include "point.h"
#include "ft_mem.h"
#include <stdlib.h>

struct s_select_string	*select_string_init(char *str, int len, int index)
{
	struct s_select_string	*s;

	s = (struct s_select_string *)ft_memalloc(sizeof(struct s_select_string));
	if (!s)
		return (0);
	s->str = str;
	s->str_len = len;
	s->str_index = index;
	s->selected = 0;
	s->pos.x = 0;
	s->pos.y = 0;
	return (s);
}

void					select_string_delete(struct s_select_string **str)
{
	if (!str || !*str)
		return ;
	ft_memdel((void **)str);
}
