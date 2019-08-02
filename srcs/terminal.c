/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarnett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/27 08:18:10 by abarnett          #+#    #+#             */
/*   Updated: 2019/09/05 19:28:47 by abarnett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "debug.h"
#include "error.h"
#include "ft_mem.h"
#include "terminal.h"
#include <termios.h>
#include <unistd.h>

/*
** TODO: make an accessor and a mutator, and make this not global
** not actually sure how that's gonna work yet, might just need to be one
** function somehow
*/
static struct s_my_term	g_term;

enum e_err_code	terminal_setup(void)
{
	if (tcgetattr(STDIN_FILENO, &g_term.old_term) != 0)
	{
		print_debug("tcgetattr failed");
		return (E_TSAVE_FAIL);
	}
	print_debug("Saved old terminal attributes");
	ft_memcpy(&g_term.new_term, &g_term.old_term, sizeof(struct termios));
	print_debug("Copied old terminal attributes to a new struct");
	g_term.new_term.c_lflag &= ~(ICANON|ECHO);
	g_term.new_term.c_cc[VMIN] = 1;
	g_term.new_term.c_cc[VTIME] = 0;
	if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &g_term.new_term) != 0)
	{
		print_debug("tcsetattr failed");
		return (E_TNONCANON_FAIL);
	}
	print_debug("Enabled non-canonical mode");
	return (0);
}

enum e_err_code	terminal_restore(void)
{
	if (tcsetattr(STDIN_FILENO, TCSANOW, &g_term.old_term) != 0)
	{
		print_debug("tcsetattr failed");
		return (E_TRESTORE_FAIL);
	}
	print_debug("Restored previous terminal state successfully");
	return (0);
}
