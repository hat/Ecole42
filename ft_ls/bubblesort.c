#include <ft_ls.h>

void	swap(t_file *a, t_file *b)
{
	t_file	*temp;

	temp = a;
	a = b;
	b = temp;
}

void	bubblesort(t_file *head)
{
	int		swapped;
	t_file	*one;
	t_file	*two;

	one = head;
	if (one == NULL)
		return ;
	swapped = 1;
	while (swapped)
	{
		swapped = 0;
		one = head;
		while (one->next != two)
		{
			if (ft_strcmp(one->name, one->next->name) > 0)
			{
				ft_printf("Swap 'em!\n");
				swap(one, one->next);
				swapped = 1;
			}
			one = one->next;
		}
		two = one;
	}
}
