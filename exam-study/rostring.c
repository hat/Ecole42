// Assignment name  : rostring
// Expected files   : rostring.c
// Allowed functions: write, malloc, free
// --------------------------------------------------------------------------------
// Write a program that takes a string and displays this string after rotating it
// one word to the left.
// Thus, the first word becomes the last, and others stay in the same order.
// A "word" is defined as a part of a string delimited either by spaces/tabs, or
// by the start/end of the string.
// Words will be separated by only one space in the output.
// If there's less than one argument, the program displays \n.
// Example:
// $>./rostring "abc   " | cat -e
// abc$
// $>
// $>./rostring "Que la      lumiere soit et la lumiere fut"
// la lumiere soit et la lumiere fut Que
// $>
// $>./rostring "     AkjhZ zLKIJz , 23y"
// zLKIJz , 23y AkjhZ
// $>
// $>./rostring | cat -e
// $
// $>

//TODO Almost works, make sure to get rid of extra white space between words

#include <unistd.h>

int 	is_white_space(char c)
{
	if (c == ' ' || c == '\t')
	{
		return (1);
	}
	return (0);
}

int		main(int argc, char *argv[])
{
	int		i;
	int		words;
	char	*str;

	i = 0;
	words = 0;
	if (argc == 2)
	{
		str = argv[1];
		while (is_white_space(str[i]))
			i++;
		while (!is_white_space(str[i]))
			i++;
		while (is_white_space(str[i]))
			i++;
		while (str[i])
		{
			write(1, &str[i], 1);
			i++;
			words = 1;
		}
		i = 0;
		while (is_white_space(str[i]))
			i++;
		while (!is_white_space(str[i]))
		{
			if (words)
			{
				write(1, " ", 1);
				words = 0;
			}
			write(1, &str[i], 1);
			i++;
		}
	}
	write(1, "\n", 1);
	return (0);
}
