/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v_main.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrazas <vbrazas@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/26 14:56:16 by vbrazas           #+#    #+#             */
/*   Updated: 2018/09/12 02:28:32 by vbrazas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>

static bool				quicker_slower(t_vm *v)
{
	if (v->e->c == RUN_QUICKER)
		v->e->cycles_per_second =
		((v->e->cycles_per_second + SQBIG_VAL) < SQMAX_VAL) ?
		(v->e->cycles_per_second + SQBIG_VAL) : SQMAX_VAL;
	else if (v->e->c == RUN_SLOWER)
		v->e->cycles_per_second = (v->e->cycles_per_second > SQBIG_VAL) ?
		(v->e->cycles_per_second - SQBIG_VAL) : 1;
	else if (v->e->c == RUN_QUICKER2)
		v->e->cycles_per_second =
		((v->e->cycles_per_second + SQSMALL_VAL) < SQMAX_VAL) ?
		(v->e->cycles_per_second + SQSMALL_VAL) : SQMAX_VAL;
	else if (v->e->c == RUN_SLOWER2)
		v->e->cycles_per_second = (v->e->cycles_per_second > SQSMALL_VAL) ?
		(v->e->cycles_per_second - SQSMALL_VAL) : 1;
	else
		return (false);
	return (true);
}

#define CLOCK_FORMULA	(v->e->t + CLOCKS_PER_SEC / v->e->cycles_per_second)

void					visualize_the_game(t_vm *v)
{
	init_windows(v);
	while ((v->e->c = getch()) != EXIT_KEY && I.cycle_to_die > 0)
	{
		if (v->e->c == RUN)
		{
			v->e->is_run = !v->e->is_run;
			print_info(v, false);
		}
		else if (v->e->c == PASS_OVER)
			print_one_cycle(v, true);
		else if (v->e->is_run && clock() >= CLOCK_FORMULA)
		{
			print_one_cycle(v, true);
			v->e->t = clock();
		}
		else if (quicker_slower(v))
			print_info(v, false);
	}
	deinit_windows(v);
}
