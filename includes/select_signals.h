/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select_signals.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alan <alanbarnett328@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 18:29:16 by alan              #+#    #+#             */
/*   Updated: 2019/11/26 20:17:21 by alan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SELECT_SIGNALS_H
# define SELECT_SIGNALS_H

struct s_select;

void	signal_catch(int sig);
int		signal_release(void);

void	setup_signal_handling(void);
void	restore_signal_handling(void);

int		handle_signal(struct s_select *info);

#endif
