/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select_screen.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alan <alanbarnett328@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 14:55:36 by alan              #+#    #+#             */
/*   Updated: 2019/10/28 17:48:11 by alan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_termcaps.h"

/*
** Returns 0 on success, 1 on failure.
*/

int	setup_screen(void)
{
	if (ft_tc_print(ENABLE_ALT_SCREEN) != 0)
		return (1);
	if (ft_tc_print(CURSOR_INVISIBLE) != 0)
		return (1);
	return (0);
}

int	restore_screen(void)
{
	if (ft_tc_print(DISABLE_ALT_SCREEN) != 0)
		return (1);
	if (ft_tc_print(CURSOR_VISIBLE) != 0)
		return (1);
	return (0);
}
