/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alan <alanbarnett328@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 17:26:31 by alan              #+#    #+#             */
/*   Updated: 2019/11/19 03:28:39 by alan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "select_info.h"
#include "select_string.h"
#include "ft_string.h"
#include "ft_iter.h"

/*
** Takes the amount of strings in the array, an array of strings to be in the
** iterator, and a pointer to a variable who will hold the length of the
** longest string. This is so I don't have to calculate it immediately after
** this.
*/

struct s_iter	*make_select_iter(int str_amnt, char **str_array,
					unsigned int *str_maxlen)
{
	struct s_iter			*strings;
	struct s_select_string	*new_sel_str;
	unsigned int			str_len;
	int						i;

	strings = ft_iter_init();
	new_sel_str = 0;
	i = 0;
	while (i < str_amnt)
	{
		str_len = ft_strlen(str_array[i]);
		if (*str_maxlen < str_len)
			*str_maxlen = str_len;
		new_sel_str = select_string_init(str_array[i], str_len, i);
		ft_iter_add_tail(strings, new_sel_str, sizeof(struct s_select_string));
		++i;
	}
	return (strings);
}

/*
** Assumes that your strings have been created, and the max length is known.
** Make sure to update the max length before running this function, if it may
** have changed (i.e. when deleting a string). This function sets the
** terminal's size (maybe after it's been changed), then it re-calculates the
** amount of columns there will be. It then goes and sets new grid positions
** for the strings. I would like to give the strings an index instead of a grid
** position, which would make this step unnecessary (all I'd have to do is
** correct the indexes when deleting/inserting an item from the strings).
*/

void			calibrate_screen(struct s_select *info)
{
	update_term_size(info);
	update_select_columns(info);
	update_grid_pos(info);
}
