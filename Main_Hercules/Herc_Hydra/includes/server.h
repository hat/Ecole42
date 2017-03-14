/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thendric <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/17 14:31:47 by thendric          #+#    #+#             */
/*   Updated: 2017/02/17 14:33:34 by thendric         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_H
# define SERVER_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <sys/stat.h>
# include <string.h>

# define BUF_SIZE 2000

typedef struct	s_server
{
	int					sockfd;
	int					newsockfd;
	int					portno;
	socklen_t			clilen;
	long				read;
	char				buffer[BUF_SIZE];
	struct sockaddr_in	serv_addr;
	struct sockaddr_in	cli_addr;
	int					n;
	pid_t				pid;
	int					daemon;
	int					shut_down;
}				t_server;

#endif
