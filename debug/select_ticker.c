/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select_ticker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alan <alanbarnett328@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/04 03:41:59 by alan              #+#    #+#             */
/*   Updated: 2019/10/18 04:58:33 by alan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_math.h"
#include "ft_printf.h"

#define GAP 5

/*
** This function takes a string and it's shift index (and other things), and
** returns a allocated string with the ticker effect applied
**	because then your function can control sleeping and printing and all the
**	other weird things that I don't ~want to~ need to handle
**	the shift index would be from 0 to the length of the string + the gap
**	indexes higher will automatically be modded
** The function takes:
**	string to print
**	string's length
**	index of ticker to print
**	width of that string
**	space between the strings
*/
/*
** Logic with comments:
**	// make sure the gap is not too small with small strings
**	gap = FT_MAX(GAP, width - string_len);
**	// mod the index to wrap properly with the string
**	*index %= (string_len + gap);
**	// start at total length minus how many characters we've lost (index)
**	// max at width, however
**	length_one = FT_MIN(string_len + gap - *index, width);
**	// scooch the string forward by the index, or to the null terminator
**	string_one = string + FT_MIN(*index, string_len);
**	// length of two is the difference of the first length and the width
**	length_two = width - length_one;
*/

char	*get_ticker_string(char *string, int string_len, int *index, int width)
{
	int		gap;
	int		length_one;
	int		length_two;
	char	*string_one;
	char	*new_string;

	gap = FT_MAX(GAP, width - string_len);
	*index %= (string_len + gap);
	length_one = FT_MIN(string_len + gap - *index, width);
	string_one = string + FT_MIN(*index, string_len);
	length_two = width - length_one;
	new_string = 0;
	ft_sprintf(&new_string, "%-*.*s%-*.*s", length_one, length_one, string_one,
			length_two, length_two, string);
	return (new_string);
}
