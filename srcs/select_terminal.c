/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select_terminal.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarnett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/27 08:18:10 by abarnett          #+#    #+#             */
/*   Updated: 2019/11/16 08:37:39 by alan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "select_terminal.h"
#include "select_debug.h"
#include "error.h"
#include "ft_term.h"
#include "ft_termcaps.h"
#include "ft_mem.h"
#include <termios.h>

/*
** This function enables noncanonical mode, disables character echoing, and
** sets the minimum read characters to 1 with blocking read.
*/

static int		select_term_setup(struct termios *term)
{
	term->c_lflag &= ~(ICANON|ECHO);
	term->c_cc[VMIN] = 1;
	term->c_cc[VTIME] = 0;
	return (0);
}

enum e_err_code	terminal_setup(void)
{
	if (ft_tc_setup() != 0)
	{
		return (E_NOTERMINFO);
	}
	if (init_terms(select_term_setup) != 0)
	{
		return (E_TINIT_FAIL);
	}
	if (ft_term_switch_new() != 0)
	{
		return (E_TNONCANON_FAIL);
	}
	return (0);
}

enum e_err_code	terminal_restore(void)
{
	if (ft_term_switch_old() != 0)
	{
		return (E_TRESTORE_FAIL);
	}
	PRINT_DEBUG("Restored previous terminal state successfully");
	delete_terms();
	return (0);
}
