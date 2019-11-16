/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarnett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/27 08:17:05 by abarnett          #+#    #+#             */
/*   Updated: 2019/11/16 07:07:12 by alan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TERMINAL_H
# define TERMINAL_H

# include "error.h"
# include <termios.h>

enum e_err_code	terminal_setup(void);
enum e_err_code	terminal_restore(void);

#endif
