/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarnett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/27 08:18:10 by abarnett          #+#    #+#             */
/*   Updated: 2019/07/27 09:26:19 by abarnett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "debug.h"
#include "terminal.h"
#include <termios.h>
#include <unistd.h>

static struct s_my_term	g_term;

int		terminal_setup(void)
{
	int	err;

	err = tcgetattr(0, &g_term.old_term);
	print_debug("Saved old attributes");
	if (err != 0)
		return (1);
	tcgetattr(STDIN_FILENO, &g_term.new_term);
	print_debug("Saved new attributes");
	g_term.new_term.c_lflag &= ~(ICANON|ECHO);
	g_term.new_term.c_cc[VMIN] = 1;
	g_term.new_term.c_cc[VTIME] = 0;
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &g_term.new_term);
	print_debug("Enabled non-canonical mode");
	return (0);
}

void	terminal_restore(void)
{
	tcsetattr(STDIN_FILENO, TCSANOW, &g_term.old_term);
	print_debug("Reset terminal settings");
}
