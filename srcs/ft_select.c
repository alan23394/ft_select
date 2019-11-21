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
#include "select_debug.h"
#include "error.h"
#include <unistd.h>

enum e_err_code	select_return(enum e_err_code error_code)
{
	enum e_err_code	terminal_code;

	terminal_code = terminal_restore();
	if (terminal_code != 0)
	{
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
	return (select_return(0));
}
