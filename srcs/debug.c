/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarnett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/27 09:42:49 by abarnett          #+#    #+#             */
/*   Updated: 2019/08/29 22:21:15 by abarnett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifdef DEBUG

# include "ft_printf.h"
# include <unistd.h>

extern inline void	print_debug(const char *func, const char *string)
{
	ft_printfd(STDERR_FILENO, "ft_select(debug:%s): %s\n", func, string);
}

#else

extern inline void	print_debug(const char *func, const char *string)
{
	(void)func;
	(void)string;
}

#endif
