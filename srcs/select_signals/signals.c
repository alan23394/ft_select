/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alan <alanbarnett328@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 17:14:14 by alan              #+#    #+#             */
/*   Updated: 2019/12/01 13:22:07 by abarnett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <signal.h>
#include <sys/ioctl.h>

/*
** Sets internal signal to passed int. If passed 0, it returns the internal
** variable and clears it back to 0.
*/

static int	hold_sig(int sig)
{
	static int	hold_sig = 0;

	if (sig == 0)
	{
		sig = hold_sig;
		hold_sig = 0;
		return (sig);
	}
	else
	{
		hold_sig = sig;
		return (0);
	}
}

/*
** The function that runs to catch signals and store them in the holder
** It sends in a null byte to stdin to exit the read and cause the loop to
** continue
** If the read in my loop returns 0, then nothing happens anyway, so this
** doesn't mess with select at all
** The chances of it putting a null character in-between some actual multi-byte
** character seems to be extremely low, I doubt it will ever happen
*/

void		signal_catch(int sig)
{
	hold_sig(sig);
	signal(sig, signal_catch);
	ioctl(STDIN_FILENO, TIOCSTI, "\0");
}

/*
** This function returns the current signal state, and clears the signal state
** as well.
*/

int			signal_release(void)
{
	return (hold_sig(0));
}
