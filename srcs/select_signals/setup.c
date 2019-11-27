/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alan <alanbarnett328@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 19:31:22 by alan              #+#    #+#             */
/*   Updated: 2019/11/26 20:57:50 by alan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "select_signals.h"
#include "signal.h"

/*
** This function sets the signal handler for the signals I'm catching
*/

void	setup_signal_handling(void)
{
	signal(SIGTERM, signal_catch);
	signal(SIGINT, signal_catch);
	signal(SIGTSTP, signal_catch);
	signal(SIGWINCH, signal_catch);
}

/*
** This function disables the signal handling. You should run it once things
** are cleaned up, and you won't be trying to handle signals anymore.
*/

void	restore_signal_handling(void)
{
	signal(SIGTERM, SIG_DFL);
	signal(SIGINT, SIG_DFL);
	signal(SIGTSTP, SIG_DFL);
	signal(SIGWINCH, SIG_DFL);
}
