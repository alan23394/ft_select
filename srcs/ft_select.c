/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarnett <alanbarnett328@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/27 08:28:17 by abarnett          #+#    #+#             */
/*   Updated: 2019/11/22 14:21:25 by alan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"
#include "select_terminal.h"
#include "select_info.h"
#include "select_keys.h"
#include "select_debug.h"
#include "error.h"
#include "drawing.h"
#include "ft_iter.h"
#include <unistd.h>
#include <stdint.h>

static void		ft_select_loop(struct s_select *info)
{
	uint32_t		input;
	int				ret;

	if (!info)
		return ;
	while (42)
	{
		input = 0;
		if (ft_iter_isempty(info->strings))
			break;
		ret = read(STDIN_FILENO, &input, 4);
		if (ret)
		{
			if (input >= 128)
				ret = handle_arrow_key(input, info);
			else
				ret = handle_char_input((char)input, info);
			if (!ret)
				break;
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
	struct s_select		select_info;

	if (argc < 1)
	{
		return (E_NOARGS);
	}
	if ((err = terminal_setup()) != 0)
	{
		return (err);
	}
	if (setup_screen())
	{
		PRINT_DEBUG("Can't properly set up screen");
	}
	select_info_init(&select_info);
	select_info.strings = make_select_iter(argc, argv, &(select_info.str_maxlen));
	calibrate_screen(&select_info);
	draw_screen(&select_info);
	ft_select_loop(&select_info);
	*selected = select_info.output;
	err = select_restore();
	return (err);
}
