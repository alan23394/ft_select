/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select_terminal.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarnett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/27 08:17:05 by abarnett          #+#    #+#             */
/*   Updated: 2019/12/08 03:27:49 by abarnett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SELECT_TERMINAL_H
# define SELECT_TERMINAL_H

# include "error.h"
# include <termios.h>

enum e_err_code	terminal_setup(void);
enum e_err_code	terminal_restore(void);

#endif
