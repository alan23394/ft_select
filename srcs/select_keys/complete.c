/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complete.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alan <alanbarnett328@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/01 07:01:30 by alan              #+#    #+#             */
/*   Updated: 2019/12/03 11:10:01 by abarnett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "select_config.h"
#include "select_info.h"
#include "select_string.h"
#include "ft_dnode.h"
#include "ft_iter.h"
#include "ft_string.h"

/*
** Returns the number of strings that are selected, and sets the pointer to len
** to the sum of their lengths.
*/

static int	count_selected(struct s_dnode *list, int *len)
{
	int	selected;

	selected = 0;
	*len = 0;
	while (list)
	{
		if (((struct s_select_string *)list->content)->selected)
		{
			*len += ((struct s_select_string *)list->content)->str_len;
			++selected;
		}
		list = list->next;
	}
	return (selected);
}

/*
** Takes the list of strings (which may or may not be selected), and the total
** size of the string
**
** The int total_size SHOULD CONSIDER the length of the padding
** The pad character will be used to strinit the output string
** The pad length will be used to move the cursor forward in between strings
** The string has nothing appended to it at the end
*/

static char	*ft_select_output(struct s_dnode *list, int total_size,
							char padding_char, int padding_len)
{
	char					*comb;
	char					*cur;
	struct s_select_string	*string;

	if (!(comb = ft_strinit(total_size, padding_char)))
		return (0);
	cur = comb;
	while (list && (cur - comb < total_size))
	{
		string = list->content;
		if (string && string->selected)
		{
			if (cur != comb)
				cur += padding_len;
			ft_strncpy(cur, string->str, string->str_len);
			cur += string->str_len;
		}
		list = list->next;
	}
	return (comb);
}

/*
** This function makes a new string with only the selected strings, and sets
** it to info->output.
**
** It gets the amount of selected strings, as well as the cumulative length of
** them. It uses that, as well as an adjustable padding length, to calculate
** the total length of the output string. It then makes the final string with
** it's padding.
*/

int			ft_select_complete(struct s_select *info)
{
	int	count;
	int	total_len;

	count = count_selected(info->strings->head, &total_len);
	if (count == 0 || total_len == 0)
		return (0);
	if (count > 0)
		total_len += OUTPUT_PAD_LEN * (count - 1);
	info->output = ft_select_output(info->strings->head, total_len, \
									OUTPUT_PAD_CHAR, OUTPUT_PAD_LEN);
	return (0);
}
