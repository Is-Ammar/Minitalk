/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iammar <iammar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 21:47:50 by iammar            #+#    #+#             */
/*   Updated: 2024/12/15 20:29:17 by iammar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

t_data	g_data;

void	signal_send(int pid, unsigned char c)
{
	int	i;
	int	pid_check;

	i = 7;
	while (i >= 0)
	{
		g_data.byte = (c >> i) & 1;
		if (g_data.byte)
			pid_check = kill(pid, SIGUSR2);
		else
			pid_check = kill(pid, SIGUSR1);
		if (pid_check == -1 && c != '\n')
		{
			write(1, "pid not found\n", 14);
			return ;
		}
		usleep(500);
		i--;
	}
}

int	main(int ac, char **av)
{
	int		pid;
	char	*msg;

	if (ac != 3)
	{
		write(1, "invalid args", 12);
		return (0);
	}
	msg = av[2];
	pid = ft_atoi(av[1]);
	if (pid == -1)
		return (0);
	while (*msg)
	{
		signal_send(pid, (unsigned char)*msg);
		msg++;
	}
	signal_send(pid, '\n');
	return (0);
}
