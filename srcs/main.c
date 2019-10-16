/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alan <alanbarnett328@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 00:10:33 by alan              #+#    #+#             */
/*   Updated: 2019/10/16 11:35:08 by alan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"
#include "ft_string.h"
#include "ft_printf.h"

int		main(int argc, char **argv)
{
	enum e_err_code	err;
	const char		*selected;

	selected = 0;
	err = ft_select(&selected, argc - 1, argv + 1);
	if (err != 0)
	{
		return (print_error(err));
	}
	if (selected)
	{
		ft_printf("%s\n", selected);
		ft_strdel((char **)&selected);
	}
	return (0);
}
