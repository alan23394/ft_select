/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alan <alanbarnett328@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 05:00:53 by alan              #+#    #+#             */
/*   Updated: 2019/12/08 03:34:44 by abarnett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DRAWING_H
# define DRAWING_H

struct s_select;
struct s_select_string;

void	move_to_gridpos(struct s_select *info, unsigned int x, unsigned int y);
void	draw_string(struct s_select *info, struct s_select_string *string);
void	draw_cursor_string(struct s_select *info,
							struct s_select_string *string);
void	draw_screen(struct s_select *info);

#endif
