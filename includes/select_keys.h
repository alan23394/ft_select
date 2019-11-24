/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select_keys.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alan <alanbarnett328@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/01 06:50:24 by alan              #+#    #+#             */
/*   Updated: 2019/11/24 09:07:02 by alan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SELECT_KEYS_H
# define SELECT_KEYS_H

#include "stdint.h"

# define KEY_CTRL_A 1
# define KEY_CTRL_B 2
# define KEY_CTRL_F 6
# define KEY_CTRL_N 14
# define KEY_CTRL_P 16

# define KEY_UP_ARROW 0x415b1b
# define KEY_DOWN_ARROW 0x425b1b
# define KEY_RIGHT_ARROW 0x435b1b
# define KEY_LEFT_ARROW 0x445b1b

# define MOUSE_LEFTCLICK_DOWN 0x204D5b1b

struct s_select;

int	ft_select_complete(struct s_select *info);
int	ft_select_quit(struct s_select *info);

int	ft_select_mouse_click(struct s_select *info);

int	ft_select_select(struct s_select *info);
int	ft_select_all(struct s_select *info);
int	ft_deselect_all(struct s_select *info);
int	ft_select_invert(struct s_select *info);

int	ft_select_left(struct s_select *info);
int	ft_select_down(struct s_select *info);
int	ft_select_up(struct s_select *info);
int	ft_select_right(struct s_select *info);
int	ft_select_home(struct s_select *info);
int	ft_select_end(struct s_select *info);

int	ft_select_delete(struct s_select *info);

int	handle_char_input(char input, struct s_select *info);
int	handle_arrow_key(uint32_t input, struct s_select *info);

#endif
