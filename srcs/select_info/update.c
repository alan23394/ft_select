/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alan <alanbarnett328@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 17:24:45 by alan              #+#    #+#             */
/*   Updated: 2019/12/08 03:22:52 by abarnett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "select_info.h"
#include "select_string.h"
#include "select_config.h"
#include "point.h"
#include "ft_dnode.h"
#include "ft_iter.h"
#include <unistd.h>
#include <sys/ioctl.h>

void	update_term_size(struct s_select *info)
{
	struct winsize	size;

	ioctl(STDIN_FILENO, TIOCGWINSZ, &size);
	info->term_size.x = size.ws_col;
	info->term_size.y = size.ws_row;
}

/*
** This function uses some comparisons and a division to figure out how many
** columns will fit with a minimum string width and the longest string.
** Eventually I would like for it to support a minimum amount of columns to
** shoot for, but there are other things to work on right now
*/

void	update_select_columns(struct s_select *info)
{
	if (ft_iter_isempty(info->strings) ||
			info->term_size.x < SELECT_STRING_MIN_LEN)
	{
		info->sel_columns = 0;
		return ;
	}
	if ((unsigned int)info->term_size.x < info->str_maxlen)
	{
		info->sel_columns = 1;
		info->sel_column_width = info->term_size.x;
		return ;
	}
	info->sel_column_width = info->str_maxlen;
	info->sel_columns = 1 + (info->term_size.x - info->str_maxlen)
						/ (info->sel_column_width + SELECT_STRING_PADDING);
}

/*
** This function goes through the strings and sets their grid positions using
** the amount of columns.
*/

void	update_grid_pos(struct s_select *info)
{
	unsigned int	line;
	unsigned int	col;
	struct s_dnode	*node;

	if (info->sel_columns == 0)
		return ;
	line = 0;
	col = 0;
	node = info->strings->head;
	while (node)
	{
		if (col >= info->sel_columns)
		{
			col = 0;
			++line;
		}
		((struct s_select_string *)node->content)->pos.x = col;
		((struct s_select_string *)node->content)->pos.y = line;
		++col;
		node = node->next;
	}
	if (((struct s_select_string *)info->strings->tail->content)->pos.y >=
			info->term_size.y)
		info->sel_columns = 0;
}

/*
** Returns the length of the longest string in the iter. If a string is longer
** than max, it returns max instead. If max is 0, it is ignored.
*/

int		get_str_maxlen(struct s_iter *select_strings, unsigned int max)
{
	struct s_dnode	*cursor;
	unsigned int	str_maxlen;
	unsigned int	len;

	cursor = select_strings->head;
	str_maxlen = 0;
	while (cursor)
	{
		len = ((struct s_select_string *)cursor->content)->str_len;
		if (max != 0 && len >= max)
			return (max);
		else if (len > str_maxlen)
		{
			str_maxlen = len;
		}
		cursor = cursor->next;
	}
	return (str_maxlen);
}
