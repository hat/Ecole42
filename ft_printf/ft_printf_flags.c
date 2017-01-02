//ANY WAY TO ADD GET WIDTH IN CHECK FLAGS!?!?!?

#include "ft_printf.h"

char 	*ft_checkcon_cap(t_input *input, char *str)
{
	if (ft_getconversion(input->form) == 'X')
		ft_touppercase(str);
	return (str);
}

char	*ft_flagpound(t_input *input, char *str, int upper)
{
	char	*prefix;

	if (ft_getconversion(input->form) == 'x')
		prefix = ft_strdup("0x");
	else if (ft_getconversion(input->form) == 'X')
		prefix = ft_strdup("0X");
	else if (ft_getconversion(input->form) == 'o')
		prefix = ft_strdup("0");
	else if (ft_getconversion(input->form) == 'O')
		prefix = ft_strdup("0");
	else
		printf("Error ft_flagpound\n");  //DELETE THIS OR CHANGE!!!
	if (upper)
		str = ft_strjoin(prefix, str);
	else
		str = ft_strjoin(prefix, str);
	if (str && upper)
		ft_touppercase(str);
	return (str);
}

char	*ft_flagplus(char *str)
{
	str = ft_strjoin("+", str);
	return (str);
}

void	ft_add_width(t_input *input, size_t var_size, char *str)
{
	int 	i;
	int 	leftjustify;
	char	*fill;

	i = 0;
	leftjustify = 0;
	fill = ft_strnew(1);
	fill[0] = ' ';
	while (ft_isflag(input->flags[i]))
	{
		if (input->flags[i] == '-')
		{
			fill[0] = ' ';
			leftjustify++;
		}
		if (input->flags[i] == '0' && !leftjustify)
			fill[0] = '0';
		i++;
	}
	if (leftjustify)
		input->str = ft_strjoin(input->str, str);
	while (input->width-- > (int)var_size)
		input->str = ft_strjoin(input->str, fill);
	if (!leftjustify)
		input->str = ft_strjoin(input->str, str);
	ft_bzero(input->flags, ft_strlen(input->flags));
}

int		ft_atoi_flags(const char *str)
{
	int		ans;
	int		i;
	int		neg;

	ans = 0;
	i = 0;
	neg = 1;
	while ((str[i] > 8 && str[i] < 14) || str[i] == 32 || ft_isflag(str[i]))
		i++;
	if (str[i] == 45 || str[i] == 43)
	{
		if (str[i] == 45)
			neg = -1;
		i++;
	}
	while (str[i] > 47 && str[i] < 58)
	{
		ans = (ans * 10) + (str[i] - '0');
		i++;
	}
	return (ans * neg);
}

void	ft_checkflags(t_input *input, char *str)
{
	int 	i;

	i = 0;
	while (input->flags[i])
	{
		if (input->flags[i] == '+')
			str = ft_flagplus(str);
		if (input->flags[i] == '#')
			str = ft_flagpound(input, str, ft_isupper(input->c));
		i++;
	}
	str = ft_checkcon_cap(input, str);
	ft_add_width(input, ft_strlen(str), str);
}

//TODO CHECK IF ALL FLAGS PASSED IN WERE VALID
int		ft_getflags(t_input *input)
{
	int 	i;
	char	*c;

	i = 1;
	c = ft_strdup(input->form + 1);
	while (input->form[i] && !ft_isconversion(ft_tolower(input->form[i])))
		i++;
	c[i - 1] = '\0';
	input->flags = ft_strjoin(input->flags, c);
	input->width = ft_atoi_flags(input->flags);
	return (ft_strlen(input->flags));
}
