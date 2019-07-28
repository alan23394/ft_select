/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarnett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/27 08:18:10 by abarnett          #+#    #+#             */
/*   Updated: 2019/07/28 03:12:52 by abarnett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "debug.h"
#include "error.h"
#include "terminal.h"
#include <termios.h>
#include <unistd.h>

static struct s_my_term	g_term;

enum e_err_code	terminal_setup(void)
{
	if (tcgetattr(STDIN_FILENO, &g_term.old_term) != 0)
	{
		print_debug("Failed to save old terminal attributes");
		return (E_TCGETAT_FAIL);
	}
	print_debug("Saved old attributes");
	if (tcgetattr(STDIN_FILENO, &g_term.new_term) != 0)
	{
		print_debug("Failed to save new terminal attributes");
		return (E_TCGETAT_FAIL);
	}
	print_debug("Saved new attributes");
	g_term.new_term.c_lflag &= ~(ICANON|ECHO);
	g_term.new_term.c_cc[VMIN] = 1;
	g_term.new_term.c_cc[VTIME] = 0;
	if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &g_term.new_term) != 0)
	{
		print_debug("Failed to enter non-canonical mode");
		return (E_TCSETAT_FAIL);
	}
	print_debug("Enabled non-canonical mode");
	return (0);
}

enum e_err_code	terminal_restore(void)
{
	if (tcsetattr(STDIN_FILENO, TCSANOW, &g_term.old_term) != 0)
	{
		print_debug("Failed to restore old terminal state");
		return (E_TCSETAT_FAIL);
	}
	print_debug("Reset terminal settings");
	return (0);
}
