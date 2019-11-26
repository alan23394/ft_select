/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select_config.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alan <alanbarnett328@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 17:14:05 by alan              #+#    #+#             */
/*   Updated: 2019/11/25 23:15:47 by alan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SELECT_CONFIG_H
# define SELECT_CONFIG_H

/*
** This is the amount of padding between the columns while selecting.
*/

# define SELECT_STRING_PADDING 4

/*
** This is the string that is used to truncate a string that's too long to fit
** on one line, or when you set a number of columns and force strings to be
** truncated. It's length is passed in as the precision to printf, so shorter
** values truncate the trimming string while longer values do nothing other
** than arbitrarily reduce the length of the string getting trimmed (due to
** subtracting the length of this string from the width of the column to be
** printed).
*/

#define SELECT_TRIM_STR "..."
#define SELECT_TRIM_STRLEN 3

/*
** This is the minimum length of a string, with the trimming string included.
** This determines when select can't draw anything, i.e. if the terminal width
** is less than this.
*/

# define SELECT_STRING_MIN_LEN 12

/*
** This is the character used for padding the output strings. It should only be
** a single character, because it's what the output string is initialized to.
** You could set it to \n to make it return a newline separated list, for
** example. The length is the amount of gap given between strings.
*/

# define OUTPUT_PAD_CHAR ' '
# define OUTPUT_PAD_LEN 1

/*
** This section is for colors used when selecting and moving the cursor, as
** well as normal text
**
** Available headers are in the includes/colors folder
*/

# include "colors/standard.h"

#endif
