/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarnett <alanbarnett328@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/27 08:28:17 by abarnett          #+#    #+#             */
/*   Updated: 2019/10/06 08:47:15 by abarnett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "debug.h"
#include "error.h"
#include "terminal.h"
#include "ft_select.h"
#include "ft_printf.h"
#include <unistd.h>
#include <stdlib.h>
#include <term.h>
#include <curses.h>

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

int				print_char(int c)
{
	return (write(1, &c, 1));
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
	const char		*termcap_str;

	if ((err = select_setup(argc)) != 0)
	{
		return (err);
	}

	PRINT_DEBUG("Selecting");

	tputs("testing pre alternate screen\n", 1, print_char);
	sleep(1);
	termcap_str = tgetstr("ti", 0);
	tputs(termcap_str, 1, print_char);
	tputs("testing in alternate screen\n", 1, print_char);
	sleep(1);
	termcap_str = tgetstr("te", 0);
	tputs(termcap_str, 1, print_char);
	tputs("testing post alternate screen\n", 1, print_char);

	sleep(5);
	sleep(1);
	(void)selected;
	(void)argv;
	PRINT_DEBUG("Resetting and quitting");
	return (select_return(0));
}
