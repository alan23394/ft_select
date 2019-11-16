/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarnett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/27 08:09:56 by abarnett          #+#    #+#             */
/*   Updated: 2019/11/08 18:47:52 by alan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SELECT_H
# define FT_SELECT_H

# include "error.h"

int				setup_screen(void);
int				restore_screen(void);

enum e_err_code	ft_select(const char **selected, int num_args, char **args);
enum e_err_code	select_return(enum e_err_code error_code);

#endif
