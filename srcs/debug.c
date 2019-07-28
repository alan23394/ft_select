/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarnett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/27 09:42:49 by abarnett          #+#    #+#             */
/*   Updated: 2019/07/28 03:09:39 by abarnett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifdef DEBUG

# include "ft_printf.h"
# include <unistd.h>

extern inline void	print_debug(const char *string)
{
	ft_printfd(STDERR_FILENO, "%s: %s\n", "ft_select", string);
}

#else

extern inline void	print_debug(const char *string)
{
	(void)string;
}

#endif
