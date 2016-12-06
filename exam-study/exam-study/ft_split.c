// Write a function that takes a string, splits it into words, and returns them as
// a NULL-terminated array of strings.
// A "word" is defined as a part of a string delimited either by spaces/tabs/new
// lines, or by the start/end of the string.
// Your function must be declared as follows:
// char    **ft_split(char *str);

#include <stdio.h>
#include <stdlib.h>

int 	is_space(char c)
{
	if (c == ' ' || c == '\t' || c == '\n')
		return (1);
	return (0);
}

long	word_count(char *str)
{
	long	i;
	long	count;

	i = 0;
	count = 0;

	while (str[i])
	{
		while (is_space(str[i]) && str[i])
			i++;
		if (str[i])
			count++;
		while (!is_space(str[i]) && str[i])
			i++;
	}
	return (count);
}

long	word_len(char *str)
{
	long i;
	long len;

	i = 0;
	len = 0;
	while (!is_space(str[len]) && str[len])
		len++;
	return (len);
}

char	**ft_split(char *str)
{
	long 	j;
	long	i;
	long	s_ind;
	char	**split;

	j = 0;
	i = 0;
	s_ind = 0;
	split = 0;
	if (!(split = (char **)malloc(sizeof(char *) * word_count(str) + 1)))
		return (0);
	while (str[j])
	{
		i = 0;
		while (is_space(str[j]) && str[j])
			j++;
		if (!(split[s_ind] = (char *)malloc(sizeof(char) * word_len(str))))
			return (0);
		while (!is_space(str[j]) && str[j])
		{
			split[s_ind][i] = str[j];
			j++;
			i++;
		}
		s_ind++;
		j++;
	}
	split[s_ind] = "\0";
	return (split);
}

int 	main(void)
{
	char	str[100] = "    hello there cruel   world   how are    you";
	char	**split;

	split = ft_split(str);
	for (int i = 0; i < word_count(str); i++)
		printf("Split: %s\n", split[i]);
	return (0);
}

//THIS ONE FAILED!!! WTF!!! Possibly didn't check for null getting passed in...