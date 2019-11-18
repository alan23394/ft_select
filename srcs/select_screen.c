/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select_screen.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alan <alanbarnett328@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 14:55:36 by alan              #+#    #+#             */
/*   Updated: 2019/11/18 12:24:50 by alan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_termcaps.h"

/*
** Returns 0 on success, 1 on failure.
** As of yet, there isn't really a failure case. If we don't have an alternate
** screen (like on the tty), we can just clear the screen and it will be fine.
** If the cursor can't be invisible, then oh well, it doesn't really mean the
** program needs to quit. Pretty much every terminal will support the clear
** termcap, and it's not unreasonable to assume that if we don't have the clear
** termcap, then tgetent would have failed at the beginning (in the case of a
** missing term variable).
*/

int	setup_screen(void)
{
	if (ft_tc_put(TC_ENABLE_ALT_SCREEN) != 0)
	{
		ft_tc_put(TC_CLEAR);
	}
	ft_tc_put(TC_CURSOR_INVISIBLE);
	return (0);
}

/*
** TODO: Jump to last line instead of clearing if we can't leave the alternate
** screen.
*/

int	restore_screen(void)
{
	if (ft_tc_put(TC_DISABLE_ALT_SCREEN) != 0)
	{
		ft_tc_put(TC_CLEAR);
	}
	ft_tc_put(TC_CURSOR_VISIBLE);
	return (0);
}
