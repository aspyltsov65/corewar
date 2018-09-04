/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xor.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akupriia <akupriia@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/13 19:49:23 by vbrazas           #+#    #+#             */
/*   Updated: 2018/09/02 21:26:48 by akupriia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>

void		xor(t_car *self, t_vm *v)
{
	self->reg[self->arg_val[2]] = self->reg[self->arg_val[0]] ^ self->reg[self->arg_val[1]]; //rili?
	self->carry = self->reg[self->arg_val[2]] ? false : true;
	move_pc(self, v, self->pc_padding);
	self->pc_padding = 0;
}