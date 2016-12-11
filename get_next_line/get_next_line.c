#include "get_next_line.h"
#include <stdio.h>
#include <string.h>

// void	gnl_free(char *ptr)
// {
// 	ptr = 0;
// }

//TODO Use ft_strnew ft_strdup ... look through functions to decide
//TODO pass fd into read. Doesn't need to open each fd more than once but can pass in multiple
//TODO no matter what return single line. Reason for list of fd is to start again where you left off. Always returns single pointer to single line though...
//TODO Alloc the lst->line initally, then realloc every time you need to add to it


//TODO TODO TODO make it where data is declared in g_n_l function and holds where it has
//					already read to. Also, make sure to safe the stuff after the \n


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
	size_t	c_read;

	if (!(c_read = read(lst->fd, data, BUFF_SIZE)))
		return (0);
	if (!lst->line[0])
		if (ft_strchr(data, '\n'))
			lst->line = ft_strndup(data, ft_strchr(data, '\n') - data);
		else
			lst->line = ft_strndup(data, c_read);
	else
		if (ft_strchr(data, '\n'))
		{
			lst->line = ft_strrealloc(lst->line, lst->cur_place / BUFF_SIZE);
			ft_strncpy(lst->line + lst->cur_place, data, ft_strchr(data, '\n') - data);
		}
		else
		{
			ft_strrealloc(lst->line, lst->cur_place / BUFF_SIZE);
			ft_strcpy(lst->line + lst->cur_place, data);
		}
	lst->cur_place += c_read;
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
	new->line = (char *)malloc(sizeof(char) * BUFF_SIZE);
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
	int 			read;
	char			*data;

	read = 1;
	data = ft_strnew(BUFF_SIZE);
	if (fd < 0 || !line || BUFF_SIZE < 1)
		return (-1);
	printf("gnl fd: %i\n", fd);
	if (head == NULL)
		head = ft_create_lst(fd);
	lst = head;
	line = 0;
	lst = iterate_lst_fd(lst, fd);
	while ((read = ft_read_data(lst, data)))
		if (!read)
			return (1);
	printf("Setting line to: %s\n", lst->line);
	line = &lst->line;
	printf("Line is: %s\n", *line);
	if (*line != NULL)
		return (1);
	return (0);
}
