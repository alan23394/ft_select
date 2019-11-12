/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select_string.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alan <alanbarnett328@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/20 01:42:13 by alan              #+#    #+#             */
/*   Updated: 2019/11/07 07:56:53 by alan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SELECT_STRING_H
# define SELECT_STRING_H

#include "point.h"

/*
** string struct
** char pointer to string from argv (not reallocated)
** int for it's length
** int for an index in the starting array (since it can come in any sort)
** int for whether or not it's selected
** s_point for it's grid position, not actual (x,y) terminal coords
**	x for col
**	y for row
*/

struct s_select_string
{
	const char		*str;
	unsigned int	str_len;
	unsigned int	str_index;
	unsigned char	selected;
	struct s_point	pos;
};

struct s_select_string	*select_string_init(char *str, int len, int index);

#endif
