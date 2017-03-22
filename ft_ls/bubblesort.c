#include <ft_ls.h>

void	swap(t_file *a, t_file *b)
{
	char	*temp;

	temp = ft_strdup(a->name);
	a->name = ft_strdup(b->name);
	b->name = ft_strdup(temp);
	ft_strdel(&temp);
}

void	bubblesort(t_file *head)
{
	int		swapped;
	t_file	*one;
	t_file	*two;

	one = head;
	two = NULL;
	if (one == NULL)
		return ;
	swapped = 1;
	while (swapped)
	{
		swapped = 0;
		one = head;
		while (one->next->name)
		{
			if (ft_strcmp(one->name, one->next->name) > 0)
			{
				swap(one, one->next);
				swapped = 1;
			}
			one = one->next;
		}
		two = one;
	}
}
