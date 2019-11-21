/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarnett <alanbarnett328@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/27 08:28:17 by abarnett          #+#    #+#             */
/*   Updated: 2019/11/20 22:17:50 by alan             ###   ########.fr       */
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

const char			*ft_select_loop(struct s_select *info)
{
	uint32_t		input;
	int				ret;

	while (42)
	{
		input = 0;
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
	return (info->output);
}

static enum e_err_code	select_return(enum e_err_code error_code)
{
	enum e_err_code	terminal_code;

	if (restore_screen())
	{
		PRINT_DEBUG("Can't properly restore screen");
	}
	terminal_code = terminal_restore();
	if (terminal_code != 0)
	{
		if (error_code == 0)
			error_code = terminal_code;
		else
			print_error(terminal_code);
	}
	return (error_code);
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
	*selected = ft_select_loop(&select_info);
	return (select_return(0));
}
