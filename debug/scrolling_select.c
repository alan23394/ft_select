/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarnett <alanbarnett328@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/27 08:28:17 by abarnett          #+#    #+#             */
/*   Updated: 2019/11/15 04:47:19 by abarnett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "debug.h"
#include "error.h"
#include "terminal.h"
#include "ft_select.h"
#include "ft_printf.h"
#include <unistd.h>
#include <stdlib.h>
#include <curses.h>
#include <term.h>

#include <signal.h>
#include <sys/ioctl.h>

/*
** select_return does terminal restoring, and returns whatever number it's
** passed. It's meant to carry error codes back a level to something that
** catches it and prints it.
*/

enum e_err_code	select_return(enum e_err_code error_code)
{
	enum e_err_code	terminal_code;

	terminal_code = terminal_restore();
	if (terminal_code != 0)
	{
		print_error(terminal_code);
	}
	return (error_code);
}

void			sig_return(int sig)
{
	(void)sig;
	select_return(0);
}

void			sig_stop(int sig)
{
	ft_printf("in stop handler, sig: %d\n", sig);
	//terminal_swap();
	ioctl(STDIN_FILENO, TIOCSIG, SIGSTOP);
}

void			sig_cont(int sig)
{
	ft_printf("in cont handler, sig: %d\n", sig);
	terminal_swap();
}

int				print_char(int c)
{
	return (write(1, &c, 1));
}

static enum e_err_code	select_setup(int argc)
{
	enum e_err_code	err;
	const char		*term_name;

	if (argc < 1)
	{
		return (E_NOARGS);
	}
	if (!isatty(STDIN_FILENO))
	{
		return (E_NOTATTY);
	}
	PRINT_DEBUG("Setting up terminal");
	term_name = getenv("TERM");
	if (tgetent(0, term_name) != 1)
	{
		return (E_NOTERMINFO);
	}
	if ((err = terminal_setup()) != 0)
	{
		return (err);
	}
	return (0);
}

#define ENTER_ALT_SCREEN "ti"
#define EXIT_ALT_SCREEN "te"
#define SCROLL_UP "sf"
#define SCROLL_DOWN "sr"

#define CURSOR_HOME "ho"
#define CURSOR_END "ll"

#define TERM_LINES "li"
#define TERM_COLS "co"

/*
void					check_flags(void)
{

}
*/

enum e_err_code			ft_select(const char **selected, int argc, char **argv)
{
	enum e_err_code	err;
	char			*termcap_str;
	int				num_lines;
	int				num_cols;
	int				scroll_region;

	if ((err = select_setup(argc)) != 0)
	{
		return (err);
	}

	PRINT_DEBUG("Selecting");

	/*
	** Make queue of strings
	** 	store their length
	**	store the longest length
	** do math with longest length and strings to get rows and columns
	**
	** signals
	** 	sigwinch
	** 		update row and column, go through queue and reposition things
	**
	*/

	signal(SIGINT, sig_return);
	signal(SIGTSTP, sig_stop);
	signal(SIGCONT, sig_cont);

	/*
	tputs("testing pre scroll up\n", 1, print_char);
	sleep(1);
	termcap_str = tgetstr("sf", 0);
	tputs(termcap_str, 1, print_char);
	sleep(1);
	tputs("testing scrolled up\n", 1, print_char);
	sleep(1);
	termcap_str = tgetstr("sr", 0);
	tputs(termcap_str, 1, print_char);
	sleep(1);
	tputs("testing scrolled down\n", 1, print_char);
	*/

	num_lines = tgetnum(TERM_LINES);
	num_cols = tgetnum(TERM_COLS);
	scroll_region = 30;

	// Scroll scroll_region - 1 lines up
	termcap_str = tgetstr("SF", 0);
	termcap_str = tparm(termcap_str, scroll_region - 1);
	tputs(termcap_str, scroll_region, print_char);
	//sleep(1);

	/*
	** // Enter alternate screen
	** termcap_str = tgetstr("ti", 0);
	** tputs(termcap_str, 1, print_char);
	** //sleep(1);
	*/

	// Make a scrolling region in the bottom of size scroll_region
	termcap_str = tgetstr("cs", 0);
	termcap_str = tparm(termcap_str, num_lines - scroll_region, num_lines);
	tputs(termcap_str, 1, print_char);
	//sleep(1);

	int loop_counter = 4;
A:

	// Move cursor to the top of that region
	termcap_str = tgetstr("cm", 0);
	termcap_str = tparm(termcap_str, num_lines - scroll_region, 0);
	tputs(termcap_str, 1, print_char);
	//sleep(1);

	// Print a lot of shit
	for (int i = 0; i < 45; ++i)
	{
		ft_printf("%d: ", i);
		tputs("a string! in a region!\n", 1, print_char);
		usleep(75000);
	}

	/*
	** // Undo scroll region
	** termcap_str = tgetstr("cs", 0);
	** termcap_str = tparm(termcap_str, 0, num_lines);
	** tputs(termcap_str, 1, print_char);
	** //sleep(1);
	*/

	// Move cursor to top of region to clear it
	termcap_str = tgetstr("cm", 0);
	termcap_str = tparm(termcap_str, num_lines - scroll_region, 0);
	tputs(termcap_str, 1, print_char);
	//sleep(1);

	// Clear screen below scroll region
	termcap_str = tgetstr("cd", 0);
	tputs(termcap_str, 1, print_char);
	//sleep(1);

	--loop_counter;
	if (loop_counter >= 0)
		goto A;

	/*
	** // Exit alternate screen
	** termcap_str = tgetstr("te", 0);
	** tputs(termcap_str, 1, print_char);
	** //sleep(1);
	*/

	// Undo scroll region
	termcap_str = tgetstr("cs", 0);
	termcap_str = tparm(termcap_str, 0, num_lines);
	tputs(termcap_str, 1, print_char);
	//sleep(1);

	(void)selected;
	(void)argv;
	PRINT_DEBUG("Resetting and quitting");
	return (select_return(0));
}
