#include "../../inc/push_swap.h"
#include <stdio.h>

void	solve(t_push_swap *stacks)
{
	(void)stacks;
	auto_move("ra\n", "rra\n",get_index(stacks->a, stacks->smallest), stacks);
}

/*
 * separates the ordered sequence locking it down
 * pushes what's bigger than the mediane to b
 * then pushes the rest to b
 */
int	best_seq(t_stack *stack)
{
	int seq;
	int longest_seq;
	int	seq_number;
	int best;

	seq = 0;
	longest_seq = seq;
	seq_number = stack->num;
	while (stack)
	{
		if (stack->next && stack->num < stack->next->num)
		{	
			if(!seq++)
				seq_number = stack->num;
		}
		else
		{	
			if (longest_seq < seq)
			{	
				best = seq_number;
				longest_seq = seq;
			}
			seq = 0;
		}
		stack = stack->next;
	}
	return (best);
}

int markup(t_stack *stack)
{	
	int	amount;
	int best;

	amount = 1;
	best = best_seq(stack);
	while(stack)
	{
		if(stack->num == best)
		{
			while(stack->next && stack->num < stack->next->num)
			{
				stack->keep = 1;
				stack = stack->next;
				amount++;
			}
			stack->keep = 1;
			stack = stack->next;
			
		}
		else
		{
			stack->keep = 0;
			stack = stack->next;
		}
	}
	return (amount);
}

void push_to_b(t_push_swap *stacks)
{
	int size;
	char *bigger;
	char *smaller;

	if(markup(stacks->a) > stacks->size_a/2)
	{
		bigger = "rra";
		smaller = "ra"; 
	}
	else 
	{
		bigger = "ra";
		smaller = "rra";
	}
	size = stacks->size_a;
	while(size--)
	{
		if(stacks->a->num >= stacks->middle && !stacks->a->keep)
			pick("pb", stacks);
		else
		{	
			if(!is_sorted(stacks->a))
				pick(bigger, stacks);
		}
	}
	size = stacks->size_a;
	while(size--)
	{	
		if(!stacks->a->keep)
			pick("pb", stacks);
		else
		{	
			if(!is_sorted(stacks->a))
				pick(smaller, stacks);
		}
	}
}

/*
 * finds the optimal number to push to a first
 * does the magic to push it back to a
 */
int index_a(t_push_swap *stacks, int index_b)
{
	int index;
	int num;
	int biggest_i;

	index = 0;
	biggest_i = 0;
	num = get_value(stacks->b, index_b)->num;
	while (index < stacks->size_a && num > get_value(stacks->a, index)->num)
	{	
		if(num > get_value(stacks->a, index)->num && get_value(stacks->a, index)->num > get_value(stacks->a, biggest_i)->num)
			biggest_i = index;
		index++;
	}
	return (++biggest_i);
}

int moves(int size, int index)
{
		if(index <= size/2)
			return(index);
		else
			return ((size - index));
}

int best_index(t_push_swap *stacks)
{
	int index_b;
	int num_moves;
	int best_moves;
	int best_index;

	index_b = 0;
	best_index = index_b;
	best_moves = moves(stacks->size_b, index_b) + moves(stacks->size_a, index_a(stacks, index_b));
	while (index_b < stacks->size_b)
	{
		num_moves = moves(stacks->size_b, index_b) + moves(stacks->size_a, index_a(stacks, index_b));
		if(best_moves >= num_moves)
		{	
			best_moves = num_moves;
			best_index = index_b;
		}
		index_b++;
	}
	return (best_index);
}

void push_to_a(t_push_swap *stacks)
{
	int		index[2];

	while (stacks->size_b)
	{
		print_stack(stacks->a, 'a');
		print_stack(stacks->b, 'b');
		index[0] = index_a(stacks, best_index(stacks));
		index[1] = best_index(stacks);
		
		if (index[0] <= stacks->size_b/2 && index[1] <= stacks->size_b/2)
			while(index[0] && index[1])
			{	
				pick("rr", stacks);
				index[0]--;
				index[1]--;
			}
		else if (index[0] > stacks->size_a/2 && index[1] > stacks->size_b/2)
		{
			index[0] = stacks->size_a - index[0];
			index[1] = stacks->size_b - index[1];
			while(index[0] && index[1])
			{	
				pick("rrr", stacks);
				index[0]--;
				index[1]--;
			}
		}
		printf("a: [%d] - b: [%d] \n", index[0], index[1]);
		if(index[0])
			auto_move("ra", "rra", index[0], stacks);
		if(index[1])
			auto_move("rb", "rrb", index[1], stacks);
		pick("pa", stacks);
	}
}