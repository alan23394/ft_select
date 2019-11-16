/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alan <alanbarnett328@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 04:47:56 by alan              #+#    #+#             */
/*   Updated: 2019/10/27 05:05:06 by alan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "select_info.h"
#include "select_string.h"
#include "ft_dnode.h"
#include "ft_iter.h"
#include <curses.h>
#include <term.h>
#include <unistd.h>

/*
** Printing function I need to work with subshells
** STDIN_FILENO still references the terminal when in a subshell
*/
/* TODO doesn't need to be in here, split termcaps stuff into it's own thing */

int		print_char_stdin(int c)
{
	return (write(STDIN_FILENO, &c, 1));
}

/*
** draw string and draw cursor string, combined with move to gridpos
**
** move to gridpos translates grid coordinates to terminal x and y, and moves
** draw string writes it onto the screen
** draw cursor string draws the string with underline
** they both need to draw reverse video if the string is selected
*/

void	move_to_gridpos(struct s_select *info, unsigned int x, unsigned int y)
{
	char			*termcaps_str;

	x = (x * info->str_maxlen) + (x * info->str_padding);
	termcaps_str = tgetstr("cm", 0);
	termcaps_str = tparm(termcaps_str, y, x);
	tputs(termcaps_str, 1, print_char_stdin);
}

void	draw_string(struct s_select *info, struct s_select_string *string)
{
	move_to_gridpos(info, string->pos.x, string->pos.y);
	if (string->selected)
	{
		tputs("\e[7m", 1, print_char_stdin);
		tputs(string->str, 1, print_char_stdin);
		tputs("\e[0m", 1, print_char_stdin);
	}
	else
	{
		tputs(string->str, 1, print_char_stdin);
	}
}

void	draw_cursor_string(struct s_select *info, struct s_select_string *string)
{
	move_to_gridpos(info, string->pos.x, string->pos.y);
	if (string->selected)
	{
		tputs("\e[4;7m", 1, print_char_stdin);
		tputs(string->str, 1, print_char_stdin);
		tputs("\e[0m", 1, print_char_stdin);
	}
	else
	{
		tputs("\e[4m", 1, print_char_stdin);
		tputs(string->str, 1, print_char_stdin);
		tputs("\e[0m", 1, print_char_stdin);
	}
}

void	draw_screen(struct s_select *info)
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
