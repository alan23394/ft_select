/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarnett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/27 08:16:34 by abarnett          #+#    #+#             */
/*   Updated: 2019/07/28 03:05:47 by abarnett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "terminal.h"
#include <stdlib.h>

void	select_exit(enum e_err_code error_code)
{
	enum e_err_code	terminal_code;

	terminal_code = terminal_restore();
	if (terminal_code != 0)
	{
		print_error(terminal_code);
	}
	exit(print_error(error_code));
}
