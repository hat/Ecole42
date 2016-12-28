#include "../ft_printf/ft_printf.h"
#include <stdio.h>

int		main(void)
{
	printf("Basic test:\n");
	printf("\tHello world!\n");
	ft_printf("\tHello World!\n");
	printf("\t\176\n");
	ft_printf("\t\176\n");
	printf("\t\\\n");
	ft_printf("\t\\\n");
	printf("\t%%\n");
	ft_printf("\t%%\n");

	printf("Conversion tests:\n");

	//STRING
	printf("    String\n");
	printf("\t%s\n", "Hello world!");
	ft_printf("\t%s\n", "Hello world!");
	printf("\tWord 1 - %s Word 2 - %s\n", "Hello",  " world!");
	ft_printf("\tWord 1 - %s Word 2 - %s\n", "Hello",  " world!");

	//CHAR
	printf("    Char\n");
	printf("\t%c\n", 'A');
	ft_printf("\t%c\n", 'A');
	printf("\tChar 1 - %c Char 2 - %c\n", 'A',  'B');
	ft_printf("\tChar 1 - %c Char 2 - %c\n", 'A',  'B');

	//DOUBLE
	printf("    Double\n");
	printf("\t%d\n", 10);
	ft_printf("\t%d\n", 10);
	printf("\tNumber - %d\n", 10);
	ft_printf("\tNumber - %d\n", 10);
	printf("\tNum 1 - %d Num 2 - %d\n", 20, -30);
	ft_printf("\tNum 1 - %d Num 2 - %d\n", 20, -30);

	//INT
	printf("    Int\n");
	printf("\t%i\n", 10);
	ft_printf("\t%i\n", 10);
	printf("\tNumber - %i\n", 10);
	ft_printf("\tNumber - %i\n", 10);
	printf("\tNum 1 - %i Num 2 - %i\n", 20, -30);
	ft_printf("\tNum 1 - %i Num 2 - %i\n", 20, -30);

	//FLOAT
	printf("    Float\n");
	printf("\t%f\n", 3.14);
	ft_printf("\t%f\n", 3.14);
	printf("\tChar 1 - %f Char 2 - %f\n", 3.14,  4.14);
	ft_printf("\tChar 1 - %f Char 2 - %f\n", 3.14,  4.14);

	printf("Test cases: \n");
	char a = 'a';
	printf("%hhd\n", a);
	printf("%hhd\n", a);

	printf("Closing program...\n");
	return (0);
}