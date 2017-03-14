/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thendric <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/17 14:31:47 by thendric          #+#    #+#             */
/*   Updated: 2017/02/17 14:33:34 by thendric         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_H
# define CLIENT_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/socket.h>
# include <arpa/inet.h>
# include <unistd.h>

# define BUF_SIZE 2000

typedef struct	s_client
{
	int					sock;
	int					amt_read;
	struct sockaddr_in	server;
	char				message[BUF_SIZE];
	char				server_reply[BUF_SIZE];
	int					shut_down;
}				t_client;

#endif
