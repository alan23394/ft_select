/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alan <alanbarnett328@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/01 07:02:36 by alan              #+#    #+#             */
/*   Updated: 2019/11/03 17:58:35 by alan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "drawing.h"
#include "ft_dnode.h"
#include "ft_iter.h"
#include "select_string.h"
#include "ft_select.h"

int	ft_select_select(struct s_select *info)
{
	((struct s_select_string *)info->strings->cur->content)->selected ^= 1;
	draw_string(info, info->strings->cur->content);
	ft_iter_cnext(info->strings);
	draw_cursor_string(info, info->strings->cur->content);
	return (1);
}

int	ft_select_all(struct s_select *info)
{
	struct s_dnode	*node;

	node = info->strings->head;
	while (node)
	{
		((struct s_select_string *)node->content)->selected = 1;
		node = node->next;
	}
	draw_screen(info);
	return (1);
}

int	ft_deselect_all(struct s_select *info)
{
	struct s_dnode	*node;

	node = info->strings->head;
	while (node)
	{
		((struct s_select_string *)node->content)->selected = 0;
		node = node->next;
	}
	draw_screen(info);
	return (1);
}

int	ft_select_invert(struct s_select *info)
{
	struct s_dnode	*node;

	node = info->strings->head;
	while (node)
	{
		((struct s_select_string *)node->content)->selected ^= 1;
		node = node->next;
	}
	draw_screen(info);
	return (1);
}
