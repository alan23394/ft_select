/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarnett <alanbarnett328@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/27 08:28:17 by abarnett          #+#    #+#             */
/*   Updated: 2019/12/07 19:18:28 by alan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "select_terminal.h"
#include "select_screen.h"
#include "select_info.h"
#include "select_signals.h"
#include "select_keys.h"
#include "select_debug.h"
#include "error.h"
#include "drawing.h"
#include "ft_iter.h"
#include <unistd.h>
#include <stdint.h>

static void				ft_select_loop(struct s_select *info)
{
	uint32_t		input;
	int				ret;

	while (42)
	{
		input = 0;
		if (ft_iter_isempty(info->strings))
			break ;
		if (!handle_signal(info))
			break ;
		ret = read(STDIN_FILENO, &input, 4);
		if (ret && input)
		{
			if (input == 'q' || input == '\033')
				break;
			if (info->sel_columns == 0)
				continue ;
			if (input >= 128)
				ret = handle_fourbyte_input(input, info);
			else
				ret = handle_onebyte_input((char)input, info);
			if (!ret)
				break ;
		}
	}
}

static enum e_err_code	select_restore(void)
{
	enum e_err_code	err;

	if (restore_screen())
	{
		PRINT_DEBUG("Can't properly restore screen");
	}
	err = terminal_restore();
	return (err);
}

enum e_err_code			ft_select(const char **selected, int argc, char **argv)
{
	enum e_err_code		err;
	struct s_select		info;

	if (argc < 1)
	{
		return (E_NOARGS);
	}
	if ((err = terminal_setup()) != 0)
	{
		return (err);
	}
	setup_signal_handling();
	if (setup_screen())
	{
		PRINT_DEBUG("Can't properly set up screen");
	}
	select_info_init(&info);
	info.strings = make_select_iter(argc, argv, &(info.str_maxlen));
	calibrate_screen(&info);
	draw_screen(&info);
	ft_select_loop(&info);
	*selected = info.output;
	err = select_restore();
	restore_signal_handling();
	return (err);
}
