/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_fork.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akupriia <akupriia@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/13 19:50:06 by vbrazas           #+#    #+#             */
/*   Updated: 2019/02/04 23:22:43 by akupriia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>

void					op_fork(t_car *self, t_vm *v)
{
	int	f_arg;

	f_arg = obtain_argval(v, self, 0, true);
	copy_car(self, v, &v->arena[(PC_IND + f_arg % IDX_MOD) % MEM_SIZE]);
	move_pc(self, v, self->pc_padding, false);
	self->pc_padding = 0;
}
