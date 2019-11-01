/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   left_down_up_right.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alan <alanbarnett328@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 23:03:07 by alan              #+#    #+#             */
/*   Updated: 2019/11/01 06:54:58 by alan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"
#include "select_string.h"
#include "drawing.h"
#include "ft_dnode.h"
#include "ft_iter.h"

int	ft_select_left(struct s_select *info)
{
	draw_string(info, info->strings->cur->content);
	ft_iter_cprev(info->strings);
	draw_cursor_string(info, info->strings->cur->content);
	return (1);
}

int	ft_select_down(struct s_select *info)
{
	int	start_col;

	draw_string(info, info->strings->cur->content);
	start_col = ((struct s_select_string *)info->strings->cur->content)->pos.x;
	ft_iter_cnext(info->strings);
	while (((struct s_select_string *)info->strings->cur->content)->pos.x \
			!= start_col)
	{
		ft_iter_cnext(info->strings);
	}
	draw_cursor_string(info, info->strings->cur->content);
	return (1);
}

int	ft_select_up(struct s_select *info)
{
	int	start_col;

	draw_string(info, info->strings->cur->content);
	start_col = ((struct s_select_string *)info->strings->cur->content)->pos.x;
	ft_iter_cprev(info->strings);
	while (((struct s_select_string *)info->strings->cur->content)->pos.x \
			!= start_col)
	{
		ft_iter_cprev(info->strings);
	}
	draw_cursor_string(info, info->strings->cur->content);
	return (1);
}

int	ft_select_right(struct s_select *info)
{
	draw_string(info, info->strings->cur->content);
	ft_iter_cnext(info->strings);
	draw_cursor_string(info, info->strings->cur->content);
	return (1);
}
