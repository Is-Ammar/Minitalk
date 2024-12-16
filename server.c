/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iammar <iammar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 20:43:10 by iammar            #+#    #+#             */
/*   Updated: 2024/12/16 10:43:27 by iammar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

t_data	g_data;

void	signal_handler(int signum)
{
	if (signum == SIGUSR1)
	{
		g_data.current_char <<= 1;
	}
	else if (signum == SIGUSR2)
	{
		g_data.current_char <<= 1;
		g_data.current_char |= 1;
	}
	g_data.bit_count++;
	if (g_data.bit_count == 8)
	{
		write(1, &g_data.current_char, 1);
		g_data.bit_count = 0;
		g_data.current_char = 0;
	}
}

int	main(void)
{
	struct sigaction	sa;
	int					pid;

	pid = getpid();
	sa.sa_handler = signal_handler;
	sa.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	write(1, "Server PID :\n", 13);
	ft_putnbr_fd(pid, 1);
	write(1, "\n", 1);
	while (1)
		pause();
	return (0);
}
