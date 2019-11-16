/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select_debug.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarnett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/27 09:11:45 by abarnett          #+#    #+#             */
/*   Updated: 2019/11/16 08:45:34 by alan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SELECT_DEBUG_H
# define SELECT_DEBUG_H

# ifdef DEBUG_PRINT_ON

#  include "ft_printf.h"
#  include <unistd.h>

#  define ERR_FMT(str) "ft_select[debug](%s:%s): %s\n", __FILE__, __func__, str
#  define PRINT_DEBUG(str) ft_printfd(STDERR_FILENO, ERR_FMT(str))

# else

/*
** This is set to void 0, because the compiler will complain of an expected
** expression before a semicolon if there isn't anything. I also have to leave
** the semicolon on the line, because norm will complain that the file may not
** compile for some reasons if there are any lines without semicolons.
*/

#  define PRINT_DEBUG(str) (void)0

# endif

#endif
