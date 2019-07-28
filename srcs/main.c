/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alan <alanbarnett328@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 00:10:33 by alan              #+#    #+#             */
/*   Updated: 2019/07/28 03:11:27 by abarnett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "debug.h"
#include "error.h"
#include "terminal.h"
#include "ft_select.h"
#include "ft_printf.h"
#include <termios.h>
#include <unistd.h>

int		main(int argc, char **argv)
{
	enum e_err_code	err;
	const char		*selected;

	if (!isatty(STDIN_FILENO))
	{
		return (print_error(E_NOTATTY));
	}
	print_debug("Setting up terminal");
	if ((err = terminal_setup()) != 0)
	{
		select_exit(err);
	}
	print_debug("Selecting");
	selected = ft_select(argc - 1, argv + 1);
	ft_printf("%s\n", selected);
	print_debug("Resetting and quitting");
	select_exit(0);
}
