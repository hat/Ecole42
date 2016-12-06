// Assignment name  : brainfuck
// Expected files   : *.c, *.h
// Allowed functions: write, malloc, free
// --------------------------------------------------------------------------------

// Write a Brainfuck interpreter program.
// The source code will be given as first parameter.
// The code will always be valid, with no more than 4096 operations.
// Brainfuck is a minimalist language. It consists of an array of bytes 
// (in our case, let's say 2048 bytes) initialized to zero, 
// and a pointer to its first byte.

// Every operator consists of a single character :
// - '>' increment the pointer ;
// - '<' decrement the pointer ;
// - '+' increment the pointed byte ;
// - '-' decrement the pointed byte ;
// - '.' print the pointed byte on standard output ;
// - '[' go to the matching ']' if the pointed byte is 0 (while start) ;
// - ']' go to the matching '[' if the pointed byte is not 0 (while end).

// Any other character is a comment.

// Examples:

// $>./brainfuck "++++++++++[>+++++++>++++++++++>+++>+<<<<-]>++.>+.+++++++..+++.>++.<<+++++++++++++++.>.+++.------.--------.>+.>." | cat -e
// Hello World!$
// $>./brainfuck "+++++[>++++[>++++H>+++++i<<-]>>>++\n<<<<-]>>--------.>+++++.>." | cat -e
// Hi$
// $>./brainfuck | cat -e
// $


#include <unistd.h>

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

int 	main(int argc, char *argv[])
{
	char 	str[2048] = {0};
	int 	i;
	int 	j;
	int 	nestcount;

	i = 0;
	j = 0;
	nestcount = 0;

	if (argc > 1)
	{
		while (argv[1][i] != '\0')
		{
			if (argv[1][i] == '>')
				j++;
			if (argv[1][i] == '<')
				j--;
			if (argv[1][i] == '+')
				str[j] = str[j] + 1;
			if (argv[1][i] == '-')
				str[j] = str[j] - 1;
			if (argv[1][i] == '.')
				ft_putchar(str[j]);
			if (argv[1][i] == '[' && str[j] == 0)
			{
				nestcount = 1;
				i++;
				while (nestcount != 0)
				{
					i++;
					if (argv[1][i] == ']')
						nestcount--;
					if (argv[1][i] == '[')
						nestcount++;
				}
			}
			if (argv[1][i] == ']' && str[j] != 0)
			{
				nestcount = 1;
				i--;
				while (nestcount != 0)
				{
					i--;
					if (argv[1][i] == '[')
						nestcount--;
					if (argv[1][i] == ']')
						nestcount++;
				}
			}
			i++;
		}
	}
}
