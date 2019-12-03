/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alan <alanbarnett328@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 04:47:56 by alan              #+#    #+#             */
/*   Updated: 2019/12/03 11:28:51 by abarnett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "select_config.h"
#include "select_info.h"
#include "select_string.h"
#include "ft_printf.h"
#include "ft_dnode.h"
#include "ft_iter.h"
#include "ft_termcaps.h"
#include <unistd.h>

/*
** draw string and draw cursor string, combined with move to gridpos
**
** move to gridpos translates grid coordinates to terminal x and y, and moves
** draw string writes it onto the screen
** draw cursor string draws the string with underline
** they both need to draw reverse video if the string is selected
*/

static void	move_to_gridpos(struct s_select *info,
							unsigned int x, unsigned int y)
{
	x = (x * info->sel_column_width) + (x * SELECT_STRING_PADDING);
	ft_tc_cursor_move(y, x);
}

/*
** TODO make these better! print \e[0m at the end and check if you need to
** print the starting character instead of a bunch of different printfs
** or make a before and after variable you can set at once
** print the whole thing once with the stuff considered
*/

void		draw_string(struct s_select *info, struct s_select_string *string)
{
	const char	*color;

	move_to_gridpos(info, string->pos.x, string->pos.y);
	color = COLOR_NORMAL;
	if (string->selected)
	{
		color = COLOR_SELECTED;
	}
	if (string->str_len > info->sel_column_width)
	{
		ft_printfd(STDIN_FILENO, "%s%.*s%.*s%s", color,
				info->sel_column_width - SELECT_TRIM_STRLEN, string->str,
				SELECT_TRIM_STRLEN, SELECT_TRIM_STR, "\e[0m");
	}
	else
	{
		ft_printfd(STDIN_FILENO, "%s%.*s%s", color,
				info->sel_column_width, string->str, "\e[0m");
	}
}

void		draw_cursor_string(struct s_select *info,
								struct s_select_string *string)
{
	const char	*color;

	move_to_gridpos(info, string->pos.x, string->pos.y);
	color = COLOR_CURSOR;
	if (string->selected)
	{
		color = COLOR_SELECTED_CURSOR;
	}
	if (string->str_len > info->sel_column_width)
	{
		ft_printfd(STDIN_FILENO, "%s%.*s%.*s%s", color,
				info->sel_column_width - SELECT_TRIM_STRLEN, string->str,
				SELECT_TRIM_STRLEN, SELECT_TRIM_STR, "\e[0m");
	}
	else
	{
		ft_printfd(STDIN_FILENO, "%s%.*s%s", color,
				info->sel_column_width, string->str, "\e[0m");
	}
}

void		draw_screen(struct s_select *info)
{
	struct s_dnode	*dnode;

	if (!info || ft_iter_isempty(info->strings))
	{
		return ;
	}
	dnode = info->strings->head;
	while (dnode)
	{
		draw_string(info, dnode->content);
		dnode = dnode->next;
	}
	draw_cursor_string(info, info->strings->cur->content);
}
