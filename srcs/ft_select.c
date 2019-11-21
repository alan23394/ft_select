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

#include "debug.h"
#include "error.h"
#include "terminal.h"
#include "ft_select.h"
#include "ft_printf.h"
#include <unistd.h>
#include <stdlib.h>

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

static enum e_err_code	select_setup(int argc)
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
	if (tgetent(0, term_name) != 1)
	{
		return (E_NOTERMINFO);
	}
	if ((err = terminal_setup()) != 0)
	{
		return (err);
	}
	return (0);
}

enum e_err_code			ft_select(const char **selected, int argc, char **argv)
{
	enum e_err_code	err;

	if ((err = select_setup(argc)) != 0)
	{
		return (err);
	}
	return (select_return(0));
}
