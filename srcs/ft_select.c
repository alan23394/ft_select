/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarnett <alanbarnett328@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/27 08:28:17 by abarnett          #+#    #+#             */
/*   Updated: 2019/09/03 20:11:30 by abarnett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "debug.h"
#include "error.h"
#include "terminal.h"
#include "ft_select.h"
#include "ft_printf.h"
#include <termios.h>
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

enum e_err_code	ft_select(const char **selected, int num_args, char **args)
{
	enum e_err_code	err;

	if (num_args < 1)
	{
		return (E_NOARGS);
	}
	if (!isatty(STDIN_FILENO))
	{
		return (E_NOTATTY);
	}
	PRINT_DEBUG("Setting up terminal");
	if ((err = terminal_setup()) != 0)
	{
		return (select_return(err));
	}
	PRINT_DEBUG("Selecting");
	(void)selected;
	(void)num_args;
	(void)args;
	PRINT_DEBUG("Resetting and quitting");
	return (select_return(0));
}
