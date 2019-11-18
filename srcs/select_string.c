/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select_string_init.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alan <alanbarnett328@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/20 01:42:40 by alan              #+#    #+#             */
/*   Updated: 2019/11/18 08:45:49 by alan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "select_string.h"
#include "point.h"
#include "ft_mem.h"
#include <stdlib.h>

struct s_select_string	*select_string_init(char *str, int len, int index)
{
	struct s_select_string	*sel_str;

	sel_str = (struct s_select_string *)malloc(sizeof(struct s_select_string));
	if (!sel_str)
		return (0);
	sel_str->str = str;
	sel_str->str_len = len;
	sel_str->str_index = index;
	sel_str->selected = 0;
	sel_str->pos.x = 0;
	sel_str->pos.y = 0;
	return (sel_str);
};

void					select_string_delete(struct s_select_string **sel_str)
{
	if (!sel_str || !*sel_str)
		return ;
	ft_memdel((void **)sel_str);
};
