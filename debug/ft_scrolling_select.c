/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarnett <alanbarnett328@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/27 08:28:17 by abarnett          #+#    #+#             */
/*   Updated: 2019/10/26 21:04:05 by alan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "debug.h"
#include "error.h"
#include "terminal.h"
#include "select_string.h"
#include "ft_math.h"
#include "ft_string.h"
#include "ft_put.h"
#include "ft_mem.h"
#include "ft_printf.h"
#include "ft_dnode.h"
#include "ft_iter.h"
#include <unistd.h>
#include <stdlib.h>
#include <curses.h>
#include <term.h>

/*
** Key select functions {{{
*/

static enum e_err_code	ft_select_setup(int argc)
{
	enum e_err_code	err;
	const char		*term_name;

	if (argc < 1)
	{
		return (E_NOARGS);
	}
	if (!isatty(STDIN_FILENO))
	{
		return (E_NOTATTY);
	}
	PRINT_DEBUG("Setting up terminal");
	term_name = getenv("TERM");
	if (tgetent(STDIN_FILENO, term_name) != 1)
	{
		return (E_NOTERMINFO);
	}
	if ((err = terminal_setup()) != 0)
	{
		return (err);
	}
	return (0);
}

static enum e_err_code	select_return(enum e_err_code error_code)
{
	enum e_err_code	terminal_code;

	terminal_code = terminal_restore();
	if (terminal_code != 0)
	{
		print_error(terminal_code);
	}
	return (error_code);
}

struct s_iter			*make_strings_list(int str_amnt, char **str_array,
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
		PRINT_DEBUG("Grabbing argument");
		str_len = ft_strlen(str_array[i]);
		if (*str_maxlen < str_len)
			*str_maxlen = str_len;
		new_sel_str = select_string_init(str_array[i], str_len, i);
		ft_iter_add_tail(strings, new_sel_str,
				sizeof(struct s_select_string));
		++i;
	}
	PRINT_DEBUG("Returning strings iter");
	return (strings);
}

/*
** }}}
*/

/*
** Returns the length of the longest string in the iter. If a string is longer
** than max, it returns max instead. If max is 0, it is ignored.
*/

int						get_str_maxlen(struct s_iter *select_strings,
							unsigned int max)
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

#define TC_LINES "li"
#define TC_COLS "co"

void					set_terminal_size(struct s_select *info)
{
	info->term_size.x = tgetnum(TC_COLS);
	info->term_size.y = tgetnum(TC_LINES);
}

void					initial_terminal_wrapping(struct s_select *info)
{
	info->str_wraplen = info->term_size.x;
}

void					update_terminal_wrapping(struct s_select *info)
{
	int	cols;
	int	width;

	cols = 0;
	width = 0;
	while (width < info->term_size.x)
	{
		++cols;
		width = (info->str_maxlen * cols) + (info->str_padding * (cols - 1));
	}
	if (width == info->term_size.x)
		info->sel_columns = cols;
	else
		info->sel_columns = cols - 1;
	info->total_lines = ft_ceil( \
		((struct s_select_string *)info->strings->tail->content)->str_index \
		/ info->sel_columns);
}

/*
** Assumes the grid positions are updated (i.e. after screen resizing)
** Moves the starting position up if it's too low
** Sets the ending position to match the starting position
** Takes lines to move in either direction
**	still checks for updates if scroll lines is 0
*/
void					update_scroll_boundaries(struct s_select *info,
							int n_lines)
{
	
}

void					set_grid_pos(struct s_select *info)
{
	unsigned int	line;
	unsigned int	col;
	struct s_dnode	*node;

	if (!info || ft_iter_isempty(info->strings))
		return ;
	info->lines = (struct s_dnode **)ft_memalloc(sizeof(struct s_dnode *) * total_lines);
	line = 0;
	col = 0;
	node = info->strings->head;
	while (node)
	{
		if (col >= info->sel_columns)
		{
			col = 0;
			++line;
			info->lines[line] = node;
		}
		((struct s_select_string *)node->content)->pos.x = col;
		((struct s_select_string *)node->content)->pos.y = line;
		++col;
		node = node->next;
	}
}

void					setup_screen(struct s_select *info)
{
	char	*termcaps_str;

	termcaps_str = tgetstr("ti", 0);
	tputs(termcaps_str, 1, ft_putchar);
	info->first_term_line = 0;
}

void					restore_screen(struct s_select *info)
{
	char	*termcaps_str;

	termcaps_str = tgetstr("te", 0);
	tputs(termcaps_str, 1, ft_putchar);
	info->first_term_line = 0;
}

/*
** draw lines function
** give it how many lines you want drawn starting at the starting line
** it draws over empty space
*/

/*
** void					scroll_if_necessary(struct s_select *info,
** 							unsigned int y)
** {
** 	if (y <= info->scroll_start_line)
** 	{
** 		if (y == 0)
** 			info->scroll_start_line = 0;
** 		else
** 			info->scroll_start_line = y - 1;
** 	}
** 	if (y - info->scroll_start_line 
** }
*/

/*
** draw string and draw cursor string, combined with move to gridpos
**
** move to gridpos translates grid coordinates to terminal x and y
** draw string writes it onto the screen
** draw cursor string draws the string with underline
** they both need to draw reverse video if the string is selected
** they also both use move to gridpos to reposition the cursor to the string
*/

void					move_to_gridpos(struct s_select *info,
							unsigned int x, unsigned int y)
{
	char			*termcaps_str;

	x = (x * info->str_maxlen) + (x * info->str_padding);
	y = info->first_term_line + (y - info->scroll_start_line);
	termcaps_str = tgetstr("cm", 0);
	termcaps_str = tparm(termcaps_str, y, x);
	tputs(termcaps_str, 1, ft_putchar);
}

void					draw_string(struct s_select *info,
							struct s_select_string *string)
{
	move_to_gridpos(info, string->pos.x, string->pos.y);
	if (string->selected)
	{
		tputs("\e[7m", 1, ft_putchar);
		tputs(string->str, 1, ft_putchar);
		tputs("\e[0m", 1, ft_putchar);
	}
	else
	{
		tputs(string->str, 1, ft_putchar);
	}
}

void					draw_cursor_string(struct s_select *info,
							struct s_select_string *string)
{
	move_to_gridpos(info, string->pos.x, string->pos.y);
	if (string->selected)
	{
		tputs("\e[4;7m", 1, ft_putchar);
		tputs(string->str, 1, ft_putchar);
		tputs("\e[0m", 1, ft_putchar);
	}
	else
	{
		tputs("\e[4m", 1, ft_putchar);
		tputs(string->str, 1, ft_putchar);
		tputs("\e[0m", 1, ft_putchar);
	}
}

void					draw_lines(struct s_select *info,
							struct s_dnode *start, unsigned int n_lines)
{
	if (!n_lines)
		return ;
	while (start && n_lines)
	{
		draw_string(info, start->content);
		if (((struct s_select_string *)start->next->content)->pos.y >
				((struct s_select_string *)start->content)->pos.y)
			--n_lines;
		start = start->next;
	}
	
}

void					scroll_up(struct s_select *info, unsigned int n_lines)
{
	struct s_select_string	*string;
	unsigned int			start_diff;
	unsigned int			end_diff;

	string = ((struct s_select_string *)info->first_on_screen->content);
	n_lines = FT_MIN((int)n_lines, string->pos.y);
	if (!n_lines)
		return ;
	start_diff = n_lines * info->sel_columns;
	string = ((struct s_select_string *)info->last_on_screen->content);
	end_diff = ((n_lines - 1) * info->sel_columns) + string->pos.x + 1;
	while (start_diff && info->first_on_screen)
	{
		info->first_on_screen = info->first_on_screen->prev;
		--start_diff;
	}
	while (end_diff && info->last_on_screen)
	{
		info->last_on_screen = info->last_on_screen->prev;
		--end_diff;
	}
}

void					scroll_down(struct s_select *info, unsigned int n_lines)
{
	struct s_select_string	*string;
	struct s_select_string	*last_string;
	unsigned int			start_diff;
	unsigned int			end_diff;

	string = ((struct s_select_string *)info->last_on_screen->content);
	last_string = ((struct s_select_string *)info->strings->tail->content);
	n_lines = FT_MIN(n_lines, (unsigned int)last_string->pos.y - string->pos.y);
	if (!n_lines)
		return ;
	start_diff = n_lines * info->sel_columns;
	end_diff = ((n_lines - 1) * info->sel_columns) + last_string->pos.x + 1;
	while (start_diff && info->first_on_screen)
	{
		info->first_on_screen = info->first_on_screen->next;
		--start_diff;
	}
	while (end_diff && info->last_on_screen)
	{
		info->last_on_screen = info->last_on_screen->next;
		--end_diff;
	}
}

void					draw_screen(struct s_select *info)
{
	if (!info->first_on_screen)
	{
		return ;
	}
	draw_lines(info, info->first_on_screen, info->term_size.y);
	draw_cursor_string(info, info->strings->cur->content);
}

int						ft_select_left(struct s_select *info)
{
	if (!info->strings->cur)
		return (0);
	draw_string(info, info->strings->cur->content);
	ft_iter_cprev(info->strings);
	draw_cursor_string(info, info->strings->cur->content);
	return (1);
}

int						ft_select_down(struct s_select *info)
{
	int	start_col;

	if (!info->strings->cur)
		return (0);
	draw_string(info, info->strings->cur->content);
	start_col = ((struct s_select_string *)info->strings->cur->content)->pos.x;
	ft_iter_cnext(info->strings);
	while (((struct s_select_string *)info->strings->cur->content)->pos.x \
			!= start_col)
	{
		ft_iter_cnext(info->strings);
	}
	draw_cursor_string(info, info->strings->cur->content);
	return (1);
}

int						ft_select_up(struct s_select *info)
{
	int	start_col;

	if (!info->strings->cur)
		return (0);
	draw_string(info, info->strings->cur->content);
	start_col = ((struct s_select_string *)info->strings->cur->content)->pos.x;
	ft_iter_cprev(info->strings);
	while (((struct s_select_string *)info->strings->cur->content)->pos.x \
			!= start_col)
	{
		ft_iter_cprev(info->strings);
	}
	draw_cursor_string(info, info->strings->cur->content);
	return (1);
}

int						ft_select_right(struct s_select *info)
{
	if (!info->strings->cur)
		return (0);
	draw_string(info, info->strings->cur->content);
	ft_iter_cnext(info->strings);
	draw_cursor_string(info, info->strings->cur->content);
	return (1);
}

int						ft_select_head(struct s_select *info)
{
	if (!info->strings->cur)
		return (0);
	draw_string(info, info->strings->cur->content);
	info->strings->cur = info->strings->head;
	draw_cursor_string(info, info->strings->cur->content);
	return (1);
}

int						ft_select_tail(struct s_select *info)
{
	if (!info->strings->cur)
		return (0);
	draw_string(info, info->strings->cur->content);
	info->strings->cur = info->strings->tail;
	draw_cursor_string(info, info->strings->cur->content);
	return (1);
}

int						ft_select_select(struct s_select *info)
{
	if (!info->strings->cur)
		return (0);
	((struct s_select_string *)info->strings->cur->content)->selected ^= 1;
	draw_string(info, info->strings->cur->content);
	ft_iter_cnext(info->strings);
	draw_cursor_string(info, info->strings->cur->content);
	return (1);
}

int						ft_select_all(struct s_select *info)
{
	struct s_dnode	*start;

	if (!info->strings->cur)
		return (0);
	start = info->strings->cur;
	((struct s_select_string *)info->strings->cur->content)->selected = 1;
	ft_iter_cnext(info->strings);
	while (info->strings->cur != start)
	{
		((struct s_select_string *)info->strings->cur->content)->selected = 1;
		ft_iter_cnext(info->strings);
	}
	draw_screen(info);
	return (1);
}

int						ft_deselect_all(struct s_select *info)
{
	struct s_dnode	*start;

	if (!info->strings->cur)
		return (0);
	start = info->strings->cur;
	((struct s_select_string *)info->strings->cur->content)->selected = 0;
	ft_iter_cnext(info->strings);
	while (info->strings->cur != start)
	{
		((struct s_select_string *)info->strings->cur->content)->selected = 0;
		ft_iter_cnext(info->strings);
	}
	draw_screen(info);
	return (1);
}

int						ft_select_invert(struct s_select *info)
{
	struct s_dnode	*start;

	if (!info->strings->cur)
		return (0);
	start = info->strings->cur;
	((struct s_select_string *)info->strings->cur->content)->selected ^= 1;
	ft_iter_cnext(info->strings);
	while (info->strings->cur != start)
	{
		((struct s_select_string *)info->strings->cur->content)->selected ^= 1;
		ft_iter_cnext(info->strings);
	}
	draw_screen(info);
	return (1);
}

int						count_selected(struct s_dnode *list, int *len)
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

char					*ft_select_output(struct s_dnode *list, int total_size)
{
	char			*comb;
	char			*cur;

	if (!list)
		return (0);
	comb = ft_strnew(total_size);
	cur = comb;
	while (list)
	{
		if (((struct s_select_string *)list->content)->selected)
		{
			if (cur != comb)
			{
				*cur = ' ';
				++cur;
			}
			ft_strncpy(cur,
					((struct s_select_string *)list->content)->str,
					((struct s_select_string *)list->content)->str_len);
			cur += ((struct s_select_string *)list->content)->str_len;
		}
		list = list->next;
	}
	return (comb);
}

int						ft_select_complete(struct s_select *info)
{
	int		count;
	int		total_len;

	count = count_selected(info->strings->head, &total_len);
	if (count == 0 || total_len == 0)
		return (0);
	if (count > 0)
		total_len += count - 1;
	info->output = ft_select_output(info->strings->head, total_len);
	return (0);
}

int						ft_select_quit(struct s_select *info)
{
	(void)info;
	return (0);
}

/*
** This function returns 1 if the loop is to continue, or 0 if it is to quit.
*/

int						handle_input(char input, struct s_select *info)
{
	static int	(*input_functions[128])(struct s_select *info) = {
		['h'] = ft_select_left,
		['j'] = ft_select_down,
		['k'] = ft_select_up,
		['l'] = ft_select_right,
		['g'] = ft_select_head,
		['G'] = ft_select_tail,
		['a'] = ft_select_all,
		['d'] = ft_deselect_all,
		['i'] = ft_select_invert,
		[' '] = ft_select_select,
		['\n'] = ft_select_complete,
		['q'] = ft_select_quit,
		['\033'] = ft_select_quit,
	};

	if (input_functions[(int)input])
	{
		return (input_functions[(int)input](info));
	}
	return (1);
}

const char			*ft_select_comb(struct s_dnode *start, int total_size)
{
	char			*comb;
	char			*cur;
	struct s_dnode	*dnode;

	if (!start)
		return (0);
	comb = ft_memalloc(total_size);
	cur = comb;
	dnode = start;
	while (dnode)
	{
		ft_strncpy(cur, ((struct s_select_string *)dnode->content)->str,
				((struct s_select_string *)dnode->content)->str_len);
		cur += ((struct s_select_string *)dnode->content)->str_len;
		dnode = dnode->next;
	}
	return (comb);
}

const char			*ft_select_loop(struct s_select *info)
{
	char			c;
	int				ret;

	while (42)
	{
		ret = read(STDIN_FILENO, &c, 1);
		if (ret)
		{
			ret = handle_input(c, info);
			if (!ret)
				break;
		}
	}
	return (info->output);
}

enum e_err_code			ft_select(const char **selected, int argc, char **argv)
{
	enum e_err_code		err;
	struct s_select		select_info;
	unsigned int		str_maxlen;


	if ((err = ft_select_setup(argc)) != 0)
	{
		return (err);
	}
	select_info_init(&select_info);
	set_terminal_size(&select_info);
	initial_terminal_wrapping(&select_info);
	PRINT_DEBUG("Making strings list");
	str_maxlen = 0;
	select_info.strings = make_strings_list(argc, argv, &str_maxlen);
	select_info.str_amount = argc;
	select_info.str_maxlen = FT_MIN(str_maxlen, select_info.str_wraplen);
	update_terminal_wrapping(&select_info);
	set_grid_pos(&select_info);
	setup_screen(&select_info);
	draw_screen(&select_info);
	// *selected = ft_select_loop(&select_info, strings);
	*selected = ft_select_loop(&select_info);
	restore_screen(&select_info);
	PRINT_DEBUG("Resetting and quitting");
	return (select_return(0));
}

	/*
	ft_putstr("\n");
	print_queue(strings, str_maxlen);
	ft_printf("str_maxlen: %d, lines: %d, cols: %d, wrap: %d\n",
			select_info.str_maxlen, select_info.term_size.y,
			select_info.term_size.x, select_info.str_wraplen);
	*/
