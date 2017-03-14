/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thendric <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/17 14:23:58 by thendric          #+#    #+#             */
/*   Updated: 2017/02/17 14:24:00 by thendric         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <client.h>

void	listen_client(t_client *client_env)
{
	bzero(&client_env->server_reply, BUF_SIZE);
	bzero(&client_env->message, BUF_SIZE);
	if ((client_env->amt_read = read(client_env->sock,
			client_env->server_reply, BUF_SIZE)) > 0)
	{
		if (!strncmp(client_env->server_reply, "Closing server...", 17))
		{
			client_env->shut_down = 0;
			exit(0);
		}
		write(1, client_env->server_reply, BUF_SIZE);
	}
	if ((client_env->amt_read = read(1, client_env->message, BUF_SIZE)) > 0)
	{
		write(client_env->sock, client_env->message, BUF_SIZE);
	}
}

int		main(int argc, char *argv[])
{
	t_client	*client_env;

	client_env = (t_client *)malloc(sizeof(t_client));
	if (argc > 1)
	{
		client_env->sock = socket(AF_INET, SOCK_STREAM, 0);
		if (client_env->sock == -1)
			return (1);
		client_env->server.sin_addr.s_addr = inet_addr("127.0.0.1");
		client_env->server.sin_family = AF_INET;
		client_env->server.sin_port = htons(atoi(argv[1]));
		if (connect(client_env->sock, (struct sockaddr *)&client_env->server,
				sizeof(client_env->server)) < 0)
			return (1);
		client_env->shut_down = 1;
		while (client_env->shut_down)
			listen_client(client_env);
		close(client_env->sock);
	}
	return (0);
}
