/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alan <alanbarnett328@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 16:38:05 by alan              #+#    #+#             */
/*   Updated: 2019/11/22 17:00:09 by alan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "select_info.h"
#include "select_string.h"
#include "drawing.h"
#include "ft_mem.h"
#include "ft_dnode.h"
#include "ft_iter.h"
#include "ft_termcaps.h"

int	ft_select_delete(struct s_select *info)
{
	struct s_select_string	*str;

	str = (struct s_select_string *)ft_iter_rm_cur(info->strings);
	ft_memdel((void **)&str);
	ft_tc_put(TC_CLEAR);
	update_grid_pos(info);
	draw_screen(info);
	return (1);
}
