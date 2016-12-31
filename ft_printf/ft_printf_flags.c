#include "ft_printf.h"

void		ft_add_width(t_input *input, size_t var_size)
{
	while (input->width-- > (int)var_size)
		input->str = ft_strjoin(input->str, " ");
}

int			ft_atoi_flags(const char *str)
{
	int		ans;
	int		i;
	int		neg;

	ans = 0;
	i = 0;
	neg = 1;
	//Add all flags here
	while ((str[i] > 8 && str[i] < 14) || str[i] == 32 || str[i] == '#')
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

int 	ft_check_conversion(char c)
{
	if (c == 'd' || c == 'i' || c == 's' || c == 'c'
			|| c == '%' || c == 'f' || c == 'o' || c == 'x'
			|| c == 'u' || c == 'O' || c == 'X' || c == 'p'
			|| c == 'U')
	{
		return (1);
	}
	return (0);
}

//TODO CHECK IF ALL FLAGS PASSED IN WERE VALID
//TODO GET WIDTH
//TODO atoi to skip all conversions rather than white space
int		ft_getflags(t_input *input)
{
	int 	i;
	char	*c;

	i = 1;
	c = ft_strdup(input->form + 1);
	while (input->form[i] && !ft_check_conversion(ft_tolower(input->form[i])))
		i++;
	c[i - 1] = '\0';
	input->flags = ft_strjoin(input->flags, c);
	input->width = ft_atoi_flags(input->flags);
	//printf("Length: %zu\n", ft_strlen(input->flags));
	//printf("Width: %d\n", width);
	return (ft_strlen(input->flags));
}