/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alan <alanbarnett328@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 19:42:04 by alan              #+#    #+#             */
/*   Updated: 2019/11/27 00:12:15 by alan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"
#include "select_info.h"
#include "select_signals.h"
#include "drawing.h"
#include "ft_term.h"
#include "ft_termcaps.h"
#include <unistd.h>
#include <signal.h>
#include <sys/ioctl.h>

int	quit_select(struct s_select *info)
{
	(void)info;
	return (0);
}

int	redraw_screen(struct s_select *info)
{
	ft_tc_put(TC_CLEAR);
	calibrate_screen(info);
	draw_screen(info);
	return (1);
}

int	pause_select(struct s_select *info)
{
	restore_screen();
	ft_term_switch_old();
	signal(SIGTSTP, SIG_DFL);
	ioctl(STDIN_FILENO, TIOCSTI, "\x1a");
	signal(SIGTSTP, signal_catch);
	ft_term_switch_new();
	setup_screen();
	redraw_screen(info);
	return (1);
}

int	handle_signal(struct s_select *info)
{
	int			sig;
	static int	(*signal_functions[64])(struct s_select *info) = {
		[SIGTERM] = quit_select,
		[SIGINT] = quit_select,
		[SIGTSTP] = pause_select,
		[SIGWINCH] = redraw_screen,
	};

	sig = signal_release();
	if (signal_functions[sig])
		return (signal_functions[sig](info));
	return (1);
}
