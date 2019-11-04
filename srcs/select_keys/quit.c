/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alan <alanbarnett328@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/01 07:02:00 by alan              #+#    #+#             */
/*   Updated: 2019/11/03 18:00:12 by alan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Forward declare the struct, because we don't actually need to do anything
** here other than return zero. This just quits the selecting loop without
** setting a string inside info (which is initialized to zero, so we don't even
** need to do that). The function controlling the loop will deal with freeing
** the memory for things.
*/

struct s_select;

int	ft_select_quit(struct s_select *info)
{
	(void)info;
	return (0);
}
