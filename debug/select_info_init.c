
#define DEFAULT_PADDING 4
//#define COLUMNS_OVERRIDE 0

void					select_info_init(struct s_select *select_info)
{
	select_info->strings = 0;
	select_info->first_on_screen = 0;
	select_info->last_on_screen = 0;
//	select_info->deleted = 0;
	select_info->output = 0;
	select_info->str_amount = 0;
	select_info->str_maxlen = 0;
	select_info->str_wraplen = 0;
	select_info->str_padding = DEFAULT_PADDING;
//	select_info->forced_columns = COLUMNS_OVERRIDE;
//	select_info->min_columns = 0;
//	select_info->min_width = 0;
//	select_info->sel_lines = 0;
	select_info->sel_columns = 0;
	select_info->total_lines = 0;
	select_info->first_term_line = 0;
	select_info->on_screen_lines = 0;
	select_info->term_size.x = 0;
	select_info->term_size.y = 0;
}
