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

/*
** 
*/

char	*ft_strrealloc(char *str, size_t size)
{
	char	*old;

	old = (char *)malloc(sizeof(char) * ft_strlen(str));
	ft_strcpy(old, str);
	printf("Add %lu bytes\n", size);
	printf("realloc old: %s\n", str);
	free(str);
	//FIGURE OUT HOW MUCH TO ALLOCATE
	if (!(str = (char *)malloc(sizeof(char) * size)))
		return (NULL);
	size = 0;
	ft_strcpy(str, old);
	printf("realloc: %s\n", str);
	return (str);
}

int 	ft_read_data(t_ext *lst)
{
	char	*data;
	size_t	c_read;

	c_read = 0;
	data = ft_strnew(BUFF_SIZE);
	c_read += read(lst->fd, data, BUFF_SIZE);
	//It now exists because of malloc, need to see if it has been gone through before
	if (!lst->line[0])
	{
		printf("Doesn't exist!\n");
		if (ft_strchr(data, '\n'))
			lst->line = ft_strndup(data, ft_strchr(data, '\n') - data);
		else
			lst->line = ft_strndup(data, c_read);
	}
	else
	{
		printf("Exists!\n");
		if (ft_strchr(data, '\n'))
		{
			ft_strrealloc(lst->line, (size_t)(ft_strchr(data, '\n') - data));
			ft_strncpy(lst->line + lst->cur_place, data, ft_strchr(data, '\n') - data);
		}
		else
		{
			ft_strrealloc(lst->line, ft_strlen(data));
			ft_strcpy(lst->line + lst->cur_place, data);
		}
	}
	lst->cur_place += c_read;
	printf("lst->line: %s\n", lst->line);
	if (ft_strchr(data, '\n'))
		return (0);
	else
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
int 	iterate_lst_fd(t_ext *lst, int fd)
{
	if (!lst)
	{
		//printf("Create new list\n");
		lst = ft_create_lst(fd);
		//printf("Cur lst fd: %d\n", lst->fd);
		//ft_read_data(lst);
		return (0);
	}
	while (lst)
	{
		if (lst->fd == fd)
		{
			return (1);
		}
		lst = lst->next;
	}
	lst->next = ft_create_lst(fd);
	return (0);
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

	if (head == NULL)
		head = ft_create_lst(fd);
	lst = head;

	line = 0;

	//Search through lst for fd or create new
	iterate_lst_fd(lst, fd);

	//Add the current buf size text to lst of fd
	while (ft_read_data(lst))
		;

	//gnl_free(data);
	return (0);
}
