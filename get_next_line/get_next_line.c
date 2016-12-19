/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thendric <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/17 21:56:53 by thendric          #+#    #+#             */
/*   Updated: 2016/12/17 21:56:56 by thendric         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*
** ft_mem reallocates memory for a string
**
** @param lst a list which stores content that may need to be copied
** @param str the string to allocate memory
** @param amount the amount to allocate in string
**
** @return the newly allocated string
*/

char		*ft_mem(t_list *lst, char *str, size_t amount)
{
	char	*new;
	size_t	buff_size;

	buff_size = BUFF_SIZE;
	if (str[0])
	{
		new = ft_strnew(buff_size * (amount + 1) + ft_strlen(lst->content));
		ft_strncpy(new, str, buff_size * (amount + 1));
		ft_bzero(str, ft_strlen(str));
	}
	else
	{
		new = ft_strnew(buff_size * (amount + 1) + ft_strlen(lst->content));
		ft_bzero(new, buff_size * (amount + 1));
	}
	free(str);
	return (new);
}

/*
** iterate_lst_fd searches through list to create or find lst with fd
**
** @param lst a list holding all the file descriptors and content
** @param fd the file descriptor to search for or create
**
** @return the place in the list with the correct file descriptor
*/

t_list		*iterate_lst_fd(t_list *lst, int fd)
{
	if (lst->content_size == (size_t)fd)
		return (lst);
	while (lst)
	{
		if (lst->content_size == (size_t)fd)
			return (lst);
		if (lst->next == NULL)
		{
			lst->next = ft_lstnew(ft_strnew(BUFF_SIZE), (size_t)fd);
			lst = lst->next;
			lst->content = ft_strnew(BUFF_SIZE);
			ft_bzero(lst->content, ft_strlen(lst->content));
			return (lst);
		}
		lst = lst->next;
	}
	return (lst);
}

/*
** f_norm checks if t_list content has newline and if data was read
**
** @param lst a lst which stores content read
** @param line where to store the line being returned
** @param b_read the amount of bytes read
**
** @return 0 if end of line otherwise 1
*/

ssize_t		f_norm(t_list *lst, char **line, ssize_t b_read)
{
	if (ft_strchr(lst->content, '\n'))
	{
		*line = (ft_strncat(*line, lst->content, ft_strchr(lst->content, '\n')
			- (char *)lst->content));
		return (0);
	}
	if (b_read)
	{
		*line = ft_strcat(*line, lst->content);
		if (b_read < BUFF_SIZE)
		{
			lst->content = NULL;
			return (0);
		}
	}
	else
	{
		lst->content = NULL;
		return (0);
	}
	return (1);
}

/*
** ft_read_line allocated memory to line and checks for end of line
**
** @param lst a lst which stores content that may need to be copied
** @param line where to store the line being returned
**
** @return 0 end of line 1 not end of line -1 error reading -2 \n in content
*/

ssize_t		ft_read_line(t_list *lst, char **line)
{
	ssize_t	i;

	i = 1;
	if (!lst->content &&
		!(i = read(lst->content_size, lst->content, BUFF_SIZE)))
	{
		*line = NULL;
		return (0);
	}
	if (*line)
		*line = ft_mem(lst, *line, (ft_strlen(*line) / BUFF_SIZE));
	else
		*line = ft_mem(lst, lst->content, ft_strlen(lst->content) / BUFF_SIZE);
	if (ft_strchr(*line, '\n'))
		*line = ft_strdup(*line + (ft_strchr(*line, '\n') - *line) + 1);
	if (!(ft_strchr(lst->content, '\n')))
	{
		lst->content = ft_strnew(BUFF_SIZE);
		i = read(lst->content_size, lst->content, BUFF_SIZE);
		if (i == -1)
			return (-1);
	}
	if (!f_norm(lst, line, i))
		return (lst->content) ? -2 : 0;
	return (ft_strlen(*line));
}

/*
** get_next_line gets the next line of a file and stores it in line
**
** @param fd the file descriptor to read from
** @param line where to store the line being returned
**
** @return 0 end of line 1 not end of line -1 error reading -2 \n in content
*/

int			get_next_line(const int fd, char **line)
{
	static t_list	*head;
	t_list			*lst;
	int				ret;

	ret = 1;
	if (fd < 0 || !line || BUFF_SIZE < 1)
		return (-1);
	if (!head)
		head = ft_lstnew(ft_strnew(BUFF_SIZE), (size_t)fd);
	if (fd == 0)
		head->content = ft_strnew(BUFF_SIZE);
	lst = head;
	lst = iterate_lst_fd(lst, fd);
	if (*line)
		*line = NULL;
	while (ret && ret != -1 && ret != -2)
		ret = ft_read_line(lst, line);
	if (*line && ft_strchr(*line, '\n'))
	{
		lst->content = ft_strdup(ft_strchr(*line, '\n') + 1);
		*line = (ft_strndup(*line, ft_strchr(*line, '\n') - *line));
	}
	if ((*line) && ((ft_strlen(*line) && ret != -1)))
		return (1);
	return (ret == -2) ? 1 : ret;
}
