/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v_print.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrazas <vbrazas@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/19 01:41:00 by vbrazas           #+#    #+#             */
/*   Updated: 2018/09/03 17:16:35 by vbrazas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>

static inline void		update_carriage_colors(t_curses *e, t_vm *v)
{
	int					*cur_place;
	t_car				*car;

	car = v->head;
	while (car)
	{
		cur_place = e->acolor + (int)(car->pc - v->arena);
		if (car->color_pc != cur_place)
		{
			*car->color_pc = car->color;
			car->color = *cur_place;
			car->color_pc = cur_place;
			*cur_place = COLOR_PAIR(CCOLORS + PL_IND(car));
		}
		car = car->next;
	}
}

static inline void		print_main(t_curses *e, t_vm *v)
{
	int					row;
	int					i;

	i = -1;
	row = START_ROW_MAIN - 1;
	update_carriage_colors(e, v);
	while (++i < MEM_SIZE)
	{
		wattron(e->mainw, e->acolor[i]);
		if (!(i % MW_ROW_LENGHT))
			mvwprintw(e->mainw, ++row, 4, "%0.2x", v->arena[i]);
		else
			wprintw(e->mainw, "%0.2x", v->arena[i]);
		wattroff(e->mainw, e->acolor[i]);
		wprintw(e->mainw, " ");
	}
	wrefresh(e->mainw);
}

static inline void		print_full_info(t_curses *e, t_vm *v, int row, int i)
{
	while (++i < v->player_amount)
	{
		mvwprintw(e->infow, (row += 2), 4, "Player -%d :", i + 1);
		wattroff(e->infow, COLOR_PAIR(INFO) | A_BOLD);
		wattron(e->infow, COLOR_PAIR(PCOLORS + i) | A_BOLD);
		mvwprintw(e->infow, row, CLEAR_LINE_PADD, "%s %s",
		P(i).prog_name, "");//P(i).comment);
		wattroff(e->infow, COLOR_PAIR(PCOLORS + i) | A_BOLD);
		wattron(e->infow, COLOR_PAIR(INFO) | A_BOLD);
		mvwprintw(e->infow, ++row, 6, "Last live\t\t\t:\t%-*d",
		CLEAR_LINE_PADD, P(i).points);
		mvwprintw(e->infow, ++row, 6, "Lives in current period\t:\t%-*d",
		CLEAR_LINE_PADD, P(i).lives_in_cp);
	}
	mvwprintw(e->infow, (row += 3), 4, "CYCLE_TO_DIE:\t%-*d",
	CLEAR_LINE_PADD, I.cycle_to_die);
	mvwprintw(e->infow, (row += 2), 4, "CYCLE_DELTA\t:\t%-*d",
	CLEAR_LINE_PADD, CYCLE_DELTA);
	mvwprintw(e->infow, (row += 2), 4, "NBR_LIVE\t:\t%-*d",
	CLEAR_LINE_PADD, NBR_LIVE);
	mvwprintw(e->infow, (row += 2), 4, "MAX_CHECKS\t:\t%-*d",
	CLEAR_LINE_PADD, MAX_CHECKS);
}

void					print_info(t_curses *e, t_vm *v,
	bool is_print_full_info)
{
	int			row;
	int			i;

	row = START_ROW_INFO;
	i = -1;
	mvwprintw(e->infow, COMMON_HEIGHT - 4, ALIGN_CENTER(START_IW_WIDTH, 13),
	"%-*s", CLEAR_LINE_PADD, (e->is_run) ? "** RUNNING **" : "** PAUSED **");
	mvwprintw(e->infow, row, 4, "Cycles/second limit :\t%-*d",
	CLEAR_LINE_PADD, e->cycles_per_second);
	mvwprintw(e->infow, (row += 2), 4, "Cycle\t:\t%-*d",
	CLEAR_LINE_PADD, I.cur_cycle);
	mvwprintw(e->infow, (row += 2), 4, "Processes\t:\t%-*d",
	CLEAR_LINE_PADD, I.cursors);
	row++;
	if (is_print_full_info)
		print_full_info(e, v, row, i);
	wrefresh(e->infow);
}

void					print_one_cycle(t_curses *e, t_vm *v,
	bool is_pass_cycle)
{
	print_main(e, v);
	print_info(e, v, true);
	if (is_pass_cycle)
		pass_one_cycle(v);
}