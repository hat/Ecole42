#include "get_next_line.h"
#include <stdio.h>

//TODO IN MAIN FUNCTION CHECK IF NEED TO READ OR GRAB FROM LEFTOVER ETC...

char	*ft_realloc(char *str, size_t amount)
{
	char	*old;

	if (str)
	{
		old = ft_memalloc(ft_strlen(str));
		ft_memcpy(old, str, ft_strlen(str));
		ft_bzero(str, BUFF_SIZE * (amount + 1));
		ft_memcpy(str, old, BUFF_SIZE * (amount + 1));
		free(old);
	}
	else
		str = ft_strnew(BUFF_SIZE * (amount + 1));
	return (str);
}

t_list	*iterate_lst_fd(t_list *lst, int fd)
{
	if (lst->content_size == (size_t)fd)
	{
		return (lst);
	}
	while (lst)
	{
		if (lst->content_size == (size_t)fd)
		{
			return (lst);
		}
		lst = lst->next;
	}
	lst = ft_lstnew(ft_strnew(BUFF_SIZE), (size_t)fd);
	return (lst);
}

ssize_t		ft_read_line(t_list *lst, char **line)
{
	ssize_t	b_read;

	b_read = 1;
	if (!lst->content)
	{
		b_read = 0;
		*line = NULL;
	}
	else
	{
		if (!(ft_strchr(lst->content, '\n')))
		{
			printf("Trying to read\n");
			b_read = read(lst->content_size, lst->content, BUFF_SIZE);
			printf("B_read = %zd\n", b_read);
		}
		if (ft_strchr(lst->content, '\n'))
		{
			*line = ft_realloc(*line, (ft_strlen(lst->content) / BUFF_SIZE));
			*line = (ft_strncat(*line, lst->content, ft_strchr(lst->content, '\n') - (char *)lst->content));
			lst->content = ft_strdup(lst->content + (ft_strchr(lst->content, '\n') - (char *)lst->content + 1));
			b_read = 0;
		}
		else
		{
			*line = ft_realloc(*line, (ft_strlen(lst->content) / BUFF_SIZE));
			*line = (ft_strdup(lst->content));
			lst->content = NULL;
		}
	}
	//printf("***ft_read_line lst->content returned: %s\n", lst->content);
	//printf("***ft_read_line line returned: %s\n", *line);
	printf("***ft_read_line return: %zd\n", b_read);
	return (b_read);
}

int		get_next_line(const int fd, char **line)
{
	static t_list	*head;
	t_list			*lst;
	int				ret;

	ret = 1;
	if (fd < 0 || !line || BUFF_SIZE < 1)
		return (-1);
	if (!head)
		head = ft_lstnew(ft_strnew(BUFF_SIZE), (size_t)fd);
	lst = head;
	lst = iterate_lst_fd(lst, fd);
	while (ret && ret != -1)
	{
		ret = ft_read_line(lst, line);
	}
	if (*line && ret != -1)
	{
		return (1);
	}
	return (ret);
}