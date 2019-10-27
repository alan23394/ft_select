void					print_list_gridpos(struct s_dnode *string,
							unsigned int str_maxlen)
{
	while (string)
	{
		ft_printf("%*s, l: %d, x: %d, y: %d\n", str_maxlen,
				((struct s_select_string *)string->content)->str,
				((struct s_select_string *)string->content)->str_len,
				((struct s_select_string *)string->content)->pos.x,
				((struct s_select_string *)string->content)->pos.y);
		string = string->next;
	}
}

ft_putstr("\n");
print_queue(strings, str_maxlen);
ft_printf("str_maxlen: %d, lines: %d, cols: %d, wrap: %d\n",
		select_info.str_maxlen, select_info.term_size.y,
		select_info.term_size.x, select_info.str_wraplen);
