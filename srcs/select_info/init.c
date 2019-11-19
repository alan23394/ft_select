/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alan <alanbarnett328@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/03 19:30:41 by alan              #+#    #+#             */
/*   Updated: 2019/11/18 17:25:36 by alan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "select_info.h"

void	select_info_init(struct s_select *select_info)
{
	select_info->strings = 0;
//	select_info->deleted = 0;
	select_info->output = 0;
	select_info->str_maxlen = 0;
	select_info->sel_columns = 0;
	select_info->sel_column_width = 0;
	select_info->term_size.x = 0;
	select_info->term_size.y = 0;
}
