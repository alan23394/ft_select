/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarnett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/27 08:17:05 by abarnett          #+#    #+#             */
/*   Updated: 2019/07/27 08:39:07 by abarnett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TERMINAL_H
# define TERMINAL_H

#include <termios.h>

struct	s_my_term
{
	struct termios	old_term;
	struct termios	new_term;
};

int		terminal_setup(void);
void	terminal_restore(void);

#endif
