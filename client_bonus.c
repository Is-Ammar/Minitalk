/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iammar <iammar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 20:16:51 by iammar            #+#    #+#             */
/*   Updated: 2024/12/24 09:01:12 by iammar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

t_data	g_data;

void	signal_send(pid_t pid, unsigned char c)
{
	int	i;
	int	pid_check;

	i = 7;
	while (i >= 0)
	{
		g_data.bit = (c >> i) & 1;
		if (g_data.bit)
			pid_check = kill(pid, SIGUSR2);
		else
			pid_check = kill(pid, SIGUSR1);
		if (pid_check == -1)
		{
			write(1, "invalid pid\n", 13);
			exit(1);
		}
		usleep(500);
		i--;
	}
}

void	handle_signal_back(int signum)
{
	(void)signum;
	write(1, "server: Message fully received\n", 32);
}

int	main(int ac, char **av)
{
	pid_t		pid;
	char		*msg;

	if (ac != 3)
	{
		write(1, "args should be : ./client <server_PID> <message>\n", 50);
		return (1);
	}
	signal(SIGUSR2, handle_signal_back);
	msg = av[2];
	pid = ft_atoi(av[1]);
	if (pid <= 0)
	{
		write(1, "invalid pid\n", 13);
		return (1);
	}
	while (*msg)
	{
		signal_send(pid, (unsigned char)*msg);
		msg++;
	}
	signal_send(pid, '\0');
	return (0);
}
