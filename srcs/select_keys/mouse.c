/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alan <alanbarnett328@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/24 06:00:31 by alan              #+#    #+#             */
/*   Updated: 2019/12/07 19:04:30 by alan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "select_config.h"
#include "select_info.h"
#include "select_string.h"
#include "select_keys.h"
#include "drawing.h"
#include "ft_dnode.h"
#include "ft_iter.h"
#include "ft_termcaps.h"
#include <unistd.h>

static struct s_dnode	*get_node_at_coord(struct s_select *info, int x, int y)
{
	int				last_line;
	int				last_col;
	int				goal;
	struct s_dnode	*cursor;

	last_line = ((struct s_select_string *)info->strings->tail->content)->pos.y;
	last_col = info->sel_columns - 1;
	if (y > last_line || x > last_col)
		return (0);
	goal = (y * info->sel_columns) + x;
	cursor = info->strings->head;
	while (goal)
	{
		cursor = cursor->next;
		--goal;
	}
	return (cursor);
}

int						ft_select_mouse_leftclick(struct s_select *info)
{
	int				x;
	int				y;
	int				col;
	unsigned int	overhang;
	struct s_dnode	*selected_node;

	x = 0;
	y = 0;
	read(STDIN_FILENO, &x, 1);
	read(STDIN_FILENO, &y, 1);
	x -= 33;
	y -= 33;
	col = (x / (info->sel_column_width + SELECT_STRING_PADDING));
	overhang = (x % (info->sel_column_width + SELECT_STRING_PADDING));
	selected_node = get_node_at_coord(info, col, y);
	if (selected_node && (overhang <
				((struct s_select_string *)selected_node->content)->str_len))
	{
		((struct s_select_string *)selected_node->content)->selected ^= 1;
		if (info->strings->cur->content == selected_node->content)
			draw_cursor_string(info, selected_node->content);
		else
			draw_string(info, selected_node->content);
	}
	return (1);
}

int						ft_select_mouse_rightclick(struct s_select *info)
{
	int				x;
	int				y;
	int				col;
	unsigned int	overhang;
	struct s_dnode	*selected_node;

	x = 0;
	y = 0;
	read(STDIN_FILENO, &x, 1);
	read(STDIN_FILENO, &y, 1);
	x -= 33;
	y -= 33;
	col = (x / (info->sel_column_width + SELECT_STRING_PADDING));
	overhang = (x % (info->sel_column_width + SELECT_STRING_PADDING));
	selected_node = get_node_at_coord(info, col, y);
	if (selected_node && (overhang <
				((struct s_select_string *)selected_node->content)->str_len))
	{
		select_delete_node(info, selected_node);
	}
	return (1);
}
