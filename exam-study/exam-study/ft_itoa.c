static size_t	ft_numdigits(int n)
{
	size_t	num;

	num = 0;
	while (n != 0)
	{
		n /= 10;
		num++;
	}
	return (num);
}

char			*ft_itoa(int n)
{
	int		neg;
	size_t	size;
	size_t	temp;
	char	*numstr;

	neg = 0;
	temp = (size_t)n;
	if (n <= 0)
		neg = 1;
	if (neg)
		temp *= -1;
	size = ft_numdigits(n) + neg;
	if (!(numstr = ft_strnew(size)))
		return (0);
	numstr[size--] = '\0';
	if (temp == 0)
		numstr[0] = '0';
	while (temp != 0)
	{
		numstr[size--] = (temp % 10) + '0';
		temp /= 10;
	}
	if (neg && numstr[0] != '0')
		numstr[0] = '-';
	return (numstr);
}
