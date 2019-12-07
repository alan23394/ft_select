/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alan <alanbarnett328@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 16:38:05 by alan              #+#    #+#             */
/*   Updated: 2019/12/06 18:52:47 by alan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "select_info.h"
#include "select_string.h"
#include "drawing.h"
#include "ft_mem.h"
#include "ft_dnode.h"
#include "ft_iter.h"
#include "ft_termcaps.h"

int	select_delete_node(struct s_select *info, struct s_dnode *node)
{
	struct s_select_string	*str;
	unsigned int			new_max;

	str = ft_iter_rm_node(info->strings, node);
	if (str->str_len >= info->str_maxlen)
	{
		new_max = get_str_maxlen(info->strings, str->str_len);
		if (new_max < str->str_len)
		{
			info->str_maxlen = new_max;
			update_select_columns(info);
		}
	}
	ft_memdel((void **)&str);
	update_grid_pos(info);
	ft_tc_put(TC_CLEAR);
	draw_screen(info);
	return (1);
}

int	ft_select_delete(struct s_select *info)
{
	return (select_delete_node(info, info->strings->cur));
}
