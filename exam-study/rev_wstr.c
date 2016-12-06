// Assignment name  : rev_wstr
// Expected files   : rev_wstr.c
// Allowed functions: write, malloc, free
// --------------------------------------------------------------------------------

// Write a program that takes a string as a parameter, and prints its words in 
// reverse order.
// A "word" is a part of the string bounded by spaces and/or tabs, or the 
// begin/end of the string.
// If the number of parameters is different from 1, the program will display 
// '\n'.
// In the parameters that are going to be tested, there won't be any "additional" 
// spaces (meaning that there won't be additionnal spaces at the beginning or at 
// the end of the string, and words will always be separated by exactly one space).
// Examples:
// $> ./rev_wstr "le temps du mepris precede celui de l'indifference" | cat -e
// l'indifference de celui precede mepris du temps le$
// $> ./rev_wstr "abcdefghijklm"
// abcdefghijklm
// $> ./rev_wstr "il contempla le mont" | cat -e
// mont le contempla il$
// $> ./rev_wstr | cat -e
// $
// $>

// int		main(int argc, char *argv[])
// {
// 	int		i;
// 	int		words;
// 	char	*str;

// 	i = 0;
// 	words = 0;
// 	if (argc == 2)
// 	{
// 		str = argv[1];
// 		while (is_white_space(str[i]))
// 			i++;
// 		while (!is_white_space(str[i]))
// 			i++;
// 		while (is_white_space(str[i]))
// 			i++;
// 		while (str[i])
// 		{
// 			write(1, &str[i], 1);
// 			i++;
// 			words = 1;
// 		}
// 		i = 0;
// 		while (is_white_space(str[i]))
// 			i++;
// 		while (!is_white_space(str[i]))
// 		{
// 			if (words)
// 			{
// 				write(1, " ", 1);
// 				words = 0;
// 			}
// 			write(1, &str[i], 1);
// 			i++;
// 		}
// 	}
// 	write(1, "\n", 1);
// 	return (0);
// }

#include <unistd.h>

int 	is_white_space(char c)
{
	if (c == ' ' || c == '\t')
	{
		return (1);
	}
	return (0);
}

void	rev_wstr(char *str, int first)
{
	int	start;
	int	i;

	i = 0;
	if (str[i])
	{
		while (str[i] && is_white_space(s[i]))
			i++;
		if (str[i])
		{
			start = i;
			while (str[i] && !(is_white_space(str[i])))
				i++;
			rev_wstr(&str[i], 0);
			write(1, &str[start], i - start);
			if (!first)
				write(1, " ", 1);
		}
	}
}

int	main(int argc, char **argv)
{
	if (argc == 2)
		rev_wstr(argv[1], 1);
	write(1, "\n", 1);
	return (0);
}

//PASSES PERFECTLY!!!!!
