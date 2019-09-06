/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alan <alanbarnett328@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 00:10:33 by alan              #+#    #+#             */
/*   Updated: 2019/09/03 20:13:10 by abarnett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"
#include "ft_string.h"
#include "ft_printf.h"

int		main(int argc, char **argv)
{
	enum e_err_code	err;
	const char		*selected;

	err = ft_select(&selected, argc - 1, argv + 1);
	if (err != 0)
	{
		return (print_error(err));
	}
	if (selected)
	{
		ft_printf("%s\n", selected);
	}
	ft_strdel((char **)&selected);
	return (0);
}
