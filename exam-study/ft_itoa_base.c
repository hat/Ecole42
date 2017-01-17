// Assignment name  : ft_itoa_base
// Expected files   : ft_itoa_base.c
// Allowed functions: malloc
// --------------------------------------------------------------------------------

// Write a function that converts an integer value to a null-terminated string
// using the specified base and stores the result in a char array that you must
// allocate.

// The base is expressed as an integer, from 2 to 16. The characters comprising
// the base are the digits from 0 to 9, followed by uppercase letter from A to F.

// For example, base 4 would be "0123" and base 16 "0123456789ABCDEF".

// If base is 10 and value is negative, the resulting string is preceded with a
// minus sign (-). With any other base, value is always considered unsigned.

// Your function must be declared as follows:

// char	*ft_itoa_base(int value, int base);

#include <stdio.h>
#include <stdlib.h>

char 	*ft_itoa_base(int value, int base)
{
	long 	n;
	long	temp;
	long	len;
	char 	*numstr;
	char 	*basenum;//[17] = "0123456789abcdef";

	len = 0;
	basenum = "0123456789ABCDEF";
	temp = value;
	n = value;
	if (value < 0)
	{
		if (base == 10 && base == 8)
			len++;
		n = n * -1;
	}
	if (!value)
		return ("0");
	while (value)
	{
		value /= base;
		len++;
	}
	numstr = (char *)malloc(sizeof(char) * len + 1);
	if (!numstr)
		return (0);
	numstr[len] = '\0';
	while (n)
	{
		numstr[--len] = basenum[n % base];
		n /= base;
	}
	if (temp < 0)
		if (base == 10)
			numstr[0] = '-';
		if (base == 8)
			numstr[0] = '3';
	return (numstr);
}

int		main(int ac, char **av)
{
	int		value;
	int		base;
	char	*toa;

	if (ac == 3)
	{
		value = atoi(av[1]);
		base = atoi(av[2]);
		toa = ft_itoa_base(value, base);
		printf("%s\n", toa);
	}
	return (0);
}
