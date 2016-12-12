/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thendric <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/29 11:33:27 by thendric          #+#    #+#             */
/*   Updated: 2016/12/10 13:57:24 by thendric         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "get_next_line.h"
#include <stdio.h>
#include <string.h>

//TODO TODO still getting garbage values sometimes
//TODO Return line set to the lst-line
//TODO have function return correct 0 1 or -1
//TODO make ft_gead_data 25 lines

/*
** Adds more memory to an already existing string
** 
** @param str 		the string to add memory
** @param amount	the amount of memory to add in bytes
**
** @return 			the str with more memory allocated
*/
char	*ft_strrealloc(char *str, size_t amount)
{
	char	*old;

	old = ft_strnew(ft_strlen(str));
	ft_strcpy(old, str);
	str = ft_strnew(BUFF_SIZE * (amount + 1));
	ft_bzero(str, BUFF_SIZE * (amount + 1));
	ft_strcpy(str, old);
	free(old);
	return (str);
}


//TODO check if end of file
int 	ft_read_data(t_ext *lst, char *data)
{
	long long	c_read;

	// HOW TO CHECK CURRENT ERROR -> -> ft_strchr(lst->leftover, '\n'))
	if (!(c_read = read(lst->fd, data, BUFF_SIZE)))
		return (0);
	if (c_read == -1)
		return (-1);
	if (!lst->line[0])
		if (ft_strchr(data, '\n'))
		{
			lst->line = (ft_strncat(lst->line, data, ft_strchr(data, '\n') - data));
			lst->leftover = ft_strdup(data + (ft_strchr(data, '\n') - data + 1));
		}
		else
		{
			lst->line = ft_strcat(lst->line, data);
		}
	else
	{
		if (ft_strchr(data, '\n'))
		{
			lst->line = ft_strrealloc(lst->line, (lst->cur_place / BUFF_SIZE) + ft_strlen(lst->leftover));
			lst->line = (ft_strncat(lst->line, data, ft_strchr(data, '\n') - data));
			lst->leftover = ft_strdup(data + (ft_strchr(data, '\n') - data + 1));
		}
		else
		{
			ft_strrealloc(lst->line, (lst->cur_place / BUFF_SIZE) + ft_strlen(lst->leftover));
			lst->line = ft_strncat(lst->line, data, c_read);
			ft_bzero(lst->leftover, ft_strlen(lst->leftover));
		}
	}
	lst->cur_place += c_read;
	if (ft_strchr(data, '\n'))
		return (0);
	return (1);
}

/*
** Creates a new t_ext list
**
** @param fd the file descriptor of the t_ext
*/
t_ext *ft_create_lst(int fd)
{
	t_ext	*new;

	new = (t_ext *)malloc(sizeof(t_ext));
	new->fd = fd;
	new->line = ft_strnew(BUFF_SIZE);//(char *)malloc(sizeof(char) * BUFF_SIZE);
	new->leftover = ft_strnew(BUFF_SIZE);
	ft_bzero(new->line, BUFF_SIZE);
	new->cur_place = 0;
	new->next = 0;
	return (new);
}

/*
** Searchs through a t_ext list for the passed in file descriptor
**
** @param head	lst the beginning of the *lst
** @param fd 	the file descriptor ro look for
** @return 		new lst if doesn't exit, location of fd, or add new fd to list
*/
t_ext 	*iterate_lst_fd(t_ext *lst, int fd)
{
	if (!lst)
	{
		lst = ft_create_lst(fd);
		return (lst);
	}
	while (lst)
	{
		if (lst->fd == fd)
		{
			return (lst);
		}
		lst = lst->next;
	}
	lst = ft_create_lst(fd);
	return (lst);
}

/*
** Reads the first line from a file descriptor and returns it
** without the \n
**
** @param  fd   the file descriptor from which to read
** @param  line the pointer to a char in which to store the line read
** @return      1 if success, 0 when completed, -1 if error
*/
int		get_next_line(const int fd, char **line)
{
	static t_ext	*head;
	t_ext			*lst;
	char			*data;
	int				ret;

	ret = 1;
	if (fd < 0 || !line || BUFF_SIZE < 1)
		return (-1);
	if (head == NULL)
		head = ft_create_lst(fd);
	lst = head;
	lst = iterate_lst_fd(lst, fd);
	//Code for newline leftover Prob shouldn't return -1
	if (ft_strchr(lst->leftover, '\n'))
	{
		lst->line = ft_strndup(lst->leftover, ft_strlen(lst->leftover) - ft_strlen(ft_strchr(lst->leftover, '\n')));
		*line = ft_strdup(lst->line);
		lst->leftover = ft_strdup(lst->leftover + (ft_strchr(lst->leftover, '\n') - lst->leftover + 1));
		return (1);
	}
	lst->line = ft_strdup(lst->leftover);
	data = ft_strnew(ft_strlen(lst->line) + BUFF_SIZE);
	ret = ft_read_data(lst, data);
	while (ret && ret != -1)
		ret = ft_read_data(lst, ft_strnew(ft_strlen(lst->line) + BUFF_SIZE));
	*line = ft_strdup(lst->line);
	ft_bzero(lst->line, ft_strlen(lst->line));
	if (ret == -1)
		return (-1);
	if (!(*data))
		return (0);
	return (1);
}
