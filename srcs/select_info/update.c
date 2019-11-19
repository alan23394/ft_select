/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alan <alanbarnett328@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 17:24:45 by alan              #+#    #+#             */
/*   Updated: 2019/11/18 17:26:13 by alan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "select_info.h"
#include "select_config.h"
#include "point.h"
#include "ft_termcaps.h"

void	update_term_size(struct s_select *info)
{
	info->term_size.x = ft_tc_cols();
	info->term_size.y = ft_tc_lines();
}

/*
** This function uses some comparisons and a division to figure out how many
** columns will fit with a minimum string width and the longest string.
** Eventually I would like for it to support a minimum amount of columns to
** shoot for, but there are other things to work on right now
*/

void	update_select_columns(struct s_select *info)
{
	if (info->term_size.x < SELECT_STRING_MIN_LEN)
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
