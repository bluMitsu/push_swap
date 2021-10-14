#include "push_swap.h"

int	main(int argc, char *argv[])
{
	t_push_swap	*stacks;

	if (argc == 1)
		return (1);
	stacks = init(--argc);
	if (!parse_and_validate(stacks, ++argv, argc))
	{
		ultimate_free(stacks);
		write(1, "Error\n", 6);
		return (1);
	}
	if (check_sorted(stacks->a))
	{
		ultimate_free(stacks);
		return (0);
	}
	else
		solve(stacks);
}
