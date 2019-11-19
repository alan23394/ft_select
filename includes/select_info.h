/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select_info.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alan <alanbarnett328@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 21:06:42 by alan              #+#    #+#             */
/*   Updated: 2019/11/19 03:02:34 by alan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SELECT_INFO_H
# define SELECT_INFO_H

# include "point.h"

/*
** combine selected strings into output string
**
** select struct
** iterator list of strings
** stack of deleted strings
** string for final output
** overall widest string
** number of string columns
** width of column
** s_point for window size
**	lines in terminal
**	columns in terminal
*/

struct s_select
{
	struct s_iter	*strings;
//	struct s_stack	*deleted;
	const char		*output;
	unsigned int	str_maxlen;
	unsigned int	sel_columns;
	unsigned int	sel_column_width;
	struct s_point	term_size;
};

void			select_info_init(struct s_select *select_info);
void			update_term_size(struct s_select *info);
void			update_select_columns(struct s_select *info);
void			update_grid_pos(struct s_select *info);
struct s_iter	*make_select_iter(int str_amnt, char **str_array,
					unsigned int *str_maxlen);

#endif
