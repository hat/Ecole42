// Assignment name  : sort_int_tab
// Expected files   : sort_int_tab.c
// Allowed functions: 
// --------------------------------------------------------------------------------
// Write the following function:
// void sort_int_tab(int *tab, unsigned int size);
// It must sort (in-place) the 'tab' int array, that contains exactly 'size'
// members, in ascending order.
// Doubles must be preserved.
// Input is always coherent.

#include <stdio.h>

void	sort_int_tab(int *tab, unsigned int size)
{
	unsigned int 	i;
	unsigned int 	j;
	int 	temp;

	i = 0;
	while (i < size - 1)
	{
		j = i;
		while (j < size)
		{
			if (tab[i] > tab[j])
			{
				temp = tab[i];
				tab[i] = tab[j];
				tab[j] = temp;

			}
			j++;
		}
		i++;
	}
}

int main(void)
{
	int tab[10] = {0, 5, 7, 2, 5, 9, 2, 12, 62, 8};

	sort_int_tab(tab, 10);
	for (int i = 0; i < 10; i++)
		printf("%d, ", tab[i]);
	printf("\n");
}