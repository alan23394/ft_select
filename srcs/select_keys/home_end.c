/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   home_end.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alan <alanbarnett328@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/01 07:03:16 by alan              #+#    #+#             */
/*   Updated: 2019/11/08 19:03:39 by alan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "select_info.h"
#include "drawing.h"
#include "ft_dnode.h"
#include "ft_iter.h"

int	ft_select_home(struct s_select *info)
{
	draw_string(info, info->strings->cur->content);
	info->strings->cur = info->strings->head;
	draw_cursor_string(info, info->strings->cur->content);
	return (1);
}

int	ft_select_end(struct s_select *info)
{
	draw_string(info, info->strings->cur->content);
	info->strings->cur = info->strings->tail;
	draw_cursor_string(info, info->strings->cur->content);
	return (1);
}
