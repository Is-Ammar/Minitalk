/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iammar <iammar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 20:16:36 by iammar            #+#    #+#             */
/*   Updated: 2024/12/22 20:26:55 by iammar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

t_data	g_data;

void	signal_handler(int signum, siginfo_t *siginfo, void *context)
{
	(void)context;
	g_data.character = (g_data.character << 1) | (signum == SIGUSR2);
	if (++g_data.bit_count == 8)
	{
		write(1, &g_data.character, 1);
		if (g_data.character == '\0')
		{
			write(1, "\n", 1);
			kill(siginfo->si_pid, SIGUSR2);
		}
		g_data.bit_count = 0;
		g_data.character = 0;
	}
}

int	main(void)
{
	struct sigaction	sa;

	sa = (struct sigaction){0};
	sa.sa_sigaction = signal_handler;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	write(1, "Server PID: ", 12);
	ft_putnbr_fd(getpid(), 1);
	write(1, "\n", 1);
	while (1)
		pause();
	return (0);
}
