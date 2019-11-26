/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select_terminal.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarnett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/27 08:18:10 by abarnett          #+#    #+#             */
/*   Updated: 2019/11/24 00:23:16 by alan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "select_terminal.h"
#include "error.h"
#include "ft_term.h"
#include "ft_term/term_setups.h"
#include "ft_termcaps.h"
#include "ft_mem.h"

/*
** This function's job is to tell me that my terminal is ready to use termcaps,
** and to enable noncanonical mode. If it returns with a failure, I can be sure
** that it has freed all the memory it may have created.
*/

enum e_err_code	terminal_setup(void)
{
	if (ft_tc_setup() != 0)
	{
		return (E_NOTERMINFO);
	}
	if (init_terms(interactive_term_setup) != 0)
	{
		return (E_TINIT_FAIL);
	}
	if (ft_term_switch_new() != 0)
	{
		delete_terms();
		return (E_TNONCANON_FAIL);
	}
	return (0);
}

/*
** This function disables noncanonical mode by switching to the previous
** terminal, and then deletes the stored terminal struct.
*/

enum e_err_code	terminal_restore(void)
{
	enum e_err_code	err;

	err = 0;
	if (ft_term_switch_old() != 0)
		err = E_TRESTORE_FAIL;
	delete_terms();
	return (err);
}
