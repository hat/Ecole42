#include "get_next_line.h"
#include <stdio.h>
#include <string.h>

// void	gnl_free(char *ptr)
// {
// 	ptr = 0;
// }

//TODO Use ft_strnew ft_strdup ... look through functions to decide
//TODO pass fd into read. Doesn't need to open each fd more than once but can pass in multiple


/*
** 
*/

void	ft_read_data(t_ext *lst)
{
	char	*data;
	size_t	c_read;

	c_read = 0;
	// data = ft_strnew(BUFF_SIZE);
	// c_read += read(lst->fd, data, BUFF_SIZE);
	// printf("Data: %s\n", data);
	// lst->line = ft_strndup(data, c_read);
	// lst->cur_place += c_read;
	// printf("lst->line: %s\n", lst->line);
	// printf("Lst->Cur: %lu\n", lst->cur_place);
	// data = ft_strnew(BUFF_SIZE);

	// //Read the next part until newline
	// c_read += read(lst->fd, data, BUFF_SIZE);
	// printf("Data 2: %s\n", data);
	// ft_strcpy(lst->line + lst->cur_place, data);
	// lst->cur_place += c_read;
	// printf("lst->line 2: %s\n", lst->line);

	// printf("Lst FD: %d\n", lst->fd);
	data = ft_strnew(BUFF_SIZE);
	c_read += read(lst->fd, data, BUFF_SIZE);
	if (!lst->line)
	{
		printf("Line does not currently exist\n");
		lst->line = ft_strndup(data, c_read);
		printf("lst->line: %s\n", lst->line);
		printf("Lst->Cur: %lu\n", lst->cur_place);
	}
	else
	{
		printf("Line already exists!\n");
		ft_strcpy(lst->line + lst->cur_place, data);
		printf("lst->line: %s\n", lst->line);
		printf("Lst->Cur: %lu\n", lst->cur_place);
	}
	lst->cur_place += c_read;
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
	t_ext	*lst;

	line = 0;

	//Create lst
	lst = (t_ext *)malloc(sizeof(t_ext));
	lst->line = NULL;

	//Search through lst for fd already existing

	//If it doesnt exist add to  lst
	lst->fd = fd;
	lst->cur_place = 0;

	//Add the current buf size text to lst of fd
	ft_read_data(lst);

	//data = ft_strnew(BUFF_SIZE);
	//read(fd, data, BUFF_SIZE);
	//printf("%s\n", data);
	//*line = strdup(data);
	//gnl_free(data);
	return (0);
}
