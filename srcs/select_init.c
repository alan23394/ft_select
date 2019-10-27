/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alan <alanbarnett328@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/26 23:53:19 by alan              #+#    #+#             */
/*   Updated: 2019/10/26 23:54:51 by alan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void					select_info_init(struct s_select *select_info)
{
	select_info->strings = 0;
//	select_info->deleted = 0;
	select_info->output = 0;
	select_info->str_maxlen = 0;
	select_info->str_wraplen = 0;
	select_info->sel_columns = 0;
	select_info->str_padding = DEFAULT_PADDING;
	select_info->term_size.x = 0;
	select_info->term_size.y = 0;
}
