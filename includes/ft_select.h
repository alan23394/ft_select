/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarnett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/27 08:09:56 by abarnett          #+#    #+#             */
/*   Updated: 2019/10/27 00:12:32 by alan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SELECT_H
# define FT_SELECT_H

# include "error.h"
# include "point.h"

# define DEFAULT_PADDING 4

/*
** combine selected strings into output string
**
** select struct
** iterator list of strings
** stack of deleted strings
** string for final output
** overall widest string
** word trimming length
** number of string columns
** s_point for window size
**	lines in terminal
**	columns in terminal
*/

struct s_select
{
	struct s_iter	*strings;
//	struct s_stack	*deleted;
	const char		*output;
	unsigned int	str_maxlen;
	unsigned int	str_wraplen;
	unsigned int	str_padding;
	unsigned int	sel_columns;
	struct s_point	term_size;
};

void			select_info_init(struct s_select *select_info);

enum e_err_code	ft_select(const char **selected, int num_args, char **args);
enum e_err_code	select_return(enum e_err_code error_code);

#endif
