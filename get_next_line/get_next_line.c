#include "get_next_line.h"
#include <stdio.h>

//TODO IN MAIN FUNCTION CHECK IF NEED TO READ OR GRAB FROM LEFTOVER ETC...
//TODO CHECK REALLOC AND MAKE SURE TO SAVE BUFFER AFTER NEWLINE

/*
**
**
**
*/
char	*ft_realloc(char *str, size_t amount)
{
	char	*new;

	if (str[0])
	{
		new = ft_strnew(BUFF_SIZE * (amount + 1));
		ft_strncpy(new, str, BUFF_SIZE * (amount + 1));
		ft_bzero(str, ft_strlen(str));
	}
	else
	{
		new = ft_strnew(BUFF_SIZE * (amount + 1));
		ft_bzero(new, BUFF_SIZE * (amount + 1));
	}
	return (new);
}

/*
**
**
**
*/
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

/*
**
**
**
*/
ssize_t		ft_read_line(t_list *lst, char **line)
{
	ssize_t	b_read;

	//printf("\nSTART ft_read_line\n");
	b_read = 1;
	if (!lst->content)
	{
		//printf("Null returning 0\n");
		*line = NULL;
		return (0);
	}
	else
	{
		*line = ft_realloc(lst->content, (ft_strlen(lst->content) / BUFF_SIZE));
		//printf("Line before read: %s\n", *line);
		if (ft_strchr(*line, '\n'))
				return (0);
		if (!(ft_strchr(lst->content, '\n')))
			b_read = read(lst->content_size, lst->content, BUFF_SIZE);
				if (b_read == -1)
					return (-1);
					else
						//printf("Read: %s\n", lst->content);
		if (ft_strchr(lst->content, '\n'))
		{
			//printf("1\n");
			*line = (ft_strncat(*line, lst->content, ft_strchr(lst->content, '\n') - (char *)lst->content));
			lst->content = ft_strdup(lst->content + (ft_strchr(lst->content, '\n') - (char *)lst->content) + 1);
			//printf("1 Line: %s Content: %s\n", *line, lst->content);
			return (0);
		}
		else
		{
			//printf("Else...\n");
			if (b_read)
			{
				//printf("2\n");
				*line = ft_strcat(*line, lst->content);//(ft_strdup(lst->content));
				//printf("Line is: %s\n", *line);
				if (b_read < BUFF_SIZE)
				{
					lst->content = NULL;
					return (0);
				}
			}
			else
			{
				//printf("3\n");
				lst->content = NULL;
				return (0);
			}
		}
	}
	return (ft_strlen(*line));
}

/*
**
**
**
*/
int		get_next_line(const int fd, char **line)
{
	static t_list	*head;
	t_list			*lst;
	int				ret;

	//printf("We're here, bitch!\n");
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
	if (*line && ft_strchr(*line, '\n'))
	{
		lst->content = ft_strdup(ft_strchr(*line, '\n') + 1);
		*line = (ft_strndup(*line, ft_strchr(*line, '\n') - *line));
	}
	//printf("Line is: %s\n", *line);
	//printf("Leftover is: %s\n", lst->content);
	if (*line && ft_strlen(*line) && ret != -1)
	{
		return (1);
	}
	return (ret);
}
