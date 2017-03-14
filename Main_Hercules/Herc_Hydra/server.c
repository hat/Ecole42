/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thendric <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/17 11:50:45 by thendric          #+#    #+#             */
/*   Updated: 2017/02/17 12:52:36 by thendric         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <server.h>

void	close_parent(t_server *serv_env)
{
	close(serv_env->newsockfd);
	exit(0);
}

void	get_response(t_server *serv_env)
{
	if (!strncmp(serv_env->buffer, "ping", 4))
		write(serv_env->newsockfd, "Pong\nPong\n", 10);
	else if (!strncmp(serv_env->buffer, "ET", 2))
		write(serv_env->newsockfd, "Phone home\n", 11);
	else if (!strncmp(serv_env->buffer, "Peanut Butter", 13))
		write(serv_env->newsockfd, "Jelly Time!\n", 12);
	else if (!strncmp(serv_env->buffer, "SHUT DOWN", 9))
	{
		write(serv_env->newsockfd, "Closing server...\n", 18);
		serv_env->shut_down = 0;
		kill(serv_env->pid, SIGINT);
	}
	else if (!serv_env->daemon)
		write(1, serv_env->buffer, serv_env->read);
	else
		write(serv_env->newsockfd, "This is a one way street.\n", 26);
}

void	listen_server(t_server *serv_env)
{
	serv_env->clilen = sizeof(serv_env->cli_addr);
	serv_env->newsockfd = accept(serv_env->sockfd,
		(struct sockaddr *)&serv_env->cli_addr, &serv_env->clilen);
	if (serv_env->newsockfd > 0)
	{
		write(serv_env->newsockfd, "Pong\nPong\n", 10);
		serv_env->pid = fork();
		if (serv_env->pid == 0)
		{
			close(serv_env->sockfd);
			bzero(serv_env->buffer, BUF_SIZE);
			while ((serv_env->read = read(serv_env->newsockfd,
					serv_env->buffer, BUF_SIZE)) > 0)
				get_response(serv_env);
		}
		else
		{
			if (serv_env->daemon)
				close_parent(serv_env);
			else
				while ((serv_env->read = read(1, serv_env->buffer, BUF_SIZE)) > 0)
					write(serv_env->newsockfd, serv_env->buffer, serv_env->read);
		}
	}
}

void	start_server(char *argv[], t_server *serv_env)
{
	write(1, "Server starting...\n", 19);
	serv_env->shut_down = 1;
	serv_env->sockfd = socket(PF_INET, SOCK_STREAM, 0);
	if (serv_env->sockfd < 0)
		write(1, "ERROR opening socket\n", 21);
	if (serv_env->daemon)
		serv_env->portno = atoi(argv[2]);
	else
		serv_env->portno = atoi(argv[1]);
	serv_env->serv_addr.sin_family = PF_INET;
	serv_env->serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_env->serv_addr.sin_port = htons(serv_env->portno);
	if (bind(serv_env->sockfd, (struct sockaddr *)&serv_env->serv_addr,
			sizeof(serv_env->serv_addr)) < 0)
	{
		write(1, "ERROR on binding\n", 17);
		exit(0);
	}
	listen(serv_env->sockfd, 5);
	while (serv_env->shut_down)
		listen_server(serv_env);
}

int		main(int argc, char *argv[])
{
	t_server	*serv_env;

	serv_env = (t_server *)malloc(sizeof(t_server));
	if (argc < 2)
	{
		write(STDERR_FILENO, "ERROR, no port provided\n", 24);
		exit(1);
	}
	if (!strcmp(argv[1], "-D"))
	{
		serv_env->daemon = 1;
	}
	start_server(argv, serv_env);
	kill(0, SIGINT);
	close(serv_env->newsockfd);
	free(serv_env);
	return (0);
}
