/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alan <alanbarnett328@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 00:10:33 by alan              #+#    #+#             */
/*   Updated: 2019/09/05 20:51:44 by abarnett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"
#include "ft_printf.h"

int		main(int argc, char **argv)
{
	const char		*selected;

	if (argc < 2)
		return (0);
	selected = ft_select(argc - 1, argv + 1);
	ft_printf("%s\n", selected);
	return (0);
}
