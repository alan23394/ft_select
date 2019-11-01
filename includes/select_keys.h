/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alan <alanbarnett328@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/01 06:50:24 by alan              #+#    #+#             */
/*   Updated: 2019/11/01 06:52:02 by alan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SELECT_KEYS_H
# define SELECT_KEYS_H

struct s_select;

int	ft_select_left(struct s_select *info);
int	ft_select_down(struct s_select *info);
int	ft_select_up(struct s_select *info);
int	ft_select_right(struct s_select *info);

#endif
