#include "../inc/push_swap.h"

//move!
void move(char *smaller,char *bigger, int index, t_stacks *stacks)
{
	t_stack stack;

	if (smaller[1] == 'a')
		stack = stacks->a;
	else
		stack = stacks->b;
	if (index >= stack.size/2)
		while(index--)
			pick(bigger, stacks);
	else
	{
		index = stack.size - index;
		while(index--)
			pick(smaller, stacks);
	}
}

void calculate(t_stacks *stacks)
{
	int i;
	int j;
	int aux;
	int sorted[stacks->a.size];

	i = -1;
	while(++i < stacks->a.size)
		sorted[i] = stacks->a.arr[i];
	i = 0;
	while(i < stacks->a.size-1)
	{
		j = 0;
		while (j < stacks->a.size - i - 1)
		{
			if(sorted[j] > sorted[j + 1])
			{
				aux = sorted[j + 1];
				sorted[j + 1] = sorted[i];
				sorted[i] = sorted[j + 1];
			}
			j++;
		}
		i++;
	}	
	stacks->middle = sorted[stacks->a.size];
	stacks->smallest = sorted[0];
}

int fillable(t_stack stack, char **argv)
{
	int i = 0;

	while (*argv)
	{
		if(!ft_isnbr(*argv))
			return (0);
		stack.arr[i++] = ft_atoi(*argv++);
	}
	i = 1;
	// while (stack.size-- > 1)
	// 	if (*stack.arr++ == stack.arr[i++])
	// 		return (0);
	return (1);
}

void	init_stack(t_stack *stack, int alloc, int size)
{
	stack->arr = malloc(sizeof(int) * alloc);
	stack->size = size;
}

t_stacks *new_stacks(int size)
{
	t_stacks *stacks = malloc(sizeof(t_stacks));
	init_stack(&stacks->a, size, size);
    init_stack(&stacks->b, size, 0);
	calculate(stacks);
	return(stacks);
}

int main(int argc, char *argv[])
{
	--argc;

	t_stacks *stacks = new_stacks(argc);
	// what about argc == 0 ? later.
	if(!fillable(stacks->a, &argv[1])) //refactor this bs, make is_valid and fill by itself ?
		return(write(1, "Error", 5));
	
	/* after checking that everything is good
	if(argc <= 3)
		smolsort
	else if (argc <= 5)
		fivesort
	else
		ultimatesort
	*/
	/*** ^ T E S T ^ ***/
	display_stack(stacks->a);
	// printf("order is = %d\n", find_order(stacks));
	// push_to_b(stacks, 1);
	seperate_order(stacks);
	display_stack(stacks->a);
	printf("is stack_a sorted? %d\n", is_sorted(stacks));
}