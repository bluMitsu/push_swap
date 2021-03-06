/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pick.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bharghaz <bharghaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 22:30:16 by bharghaz          #+#    #+#             */
/*   Updated: 2021/10/19 22:30:16 by bharghaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/push_swap.h"

int	run(t_push_swap *stacks, char *cmd, void (*func)(t_stack **))
{
	if (cmd[1] == 'a' && ft_strlen(cmd) <= 3)
		func(&stacks->a);
	else if (cmd[1] == 'b' && ft_strlen(cmd) <= 3)
		func(&stacks->b);
	else if (cmd[1] == 'r' && ft_strlen(cmd) <= 3)
	{
		func(&stacks->a);
		func(&stacks->b);
	}
	else
		return (0);
	return (1);
}

void	pick(char *cmd, t_push_swap *stacks)
{
	if (cmd[0] == 's')
		run(stacks, cmd, &swap);
	else if (cmd[0] == 'r' && !cmd[3])
		run(stacks, cmd, &rotate);
	else if (cmd[0] == 'r' && cmd[3])
		run(stacks, &cmd[1], &reverse);
	else if (cmd[0] == 'p')
	{
		if (cmd[1] == 'b')
		{
			push(&stacks->a, &stacks->b);
			stacks->size_a--;
			stacks->size_b++;
		}
		else if (cmd[1] == 'a')
		{
			push(&stacks->b, &stacks->a);
			stacks->size_a++;
			stacks->size_b--;
		}
	}
	write(1, cmd, ft_strlen(cmd));
}
