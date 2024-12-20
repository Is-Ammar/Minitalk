/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iammar <iammar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 20:43:10 by iammar            #+#    #+#             */
/*   Updated: 2024/12/19 09:14:23 by iammar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

t_data g_data;

void signal_handler(int signum)
{
    g_data.current_char = (g_data.current_char << 1) | (signum == SIGUSR2);
    if (++g_data.bit_count == 8)
    {
        write(1, &g_data.current_char, 1);
        g_data.bit_count = 0;
        g_data.current_char = 0;
    }
}

int main(void)
{
    struct sigaction sa = {0};

    sa.sa_handler = signal_handler;
    sigaction(SIGUSR1, &sa, NULL);
    sigaction(SIGUSR2, &sa, NULL);

    write(1, "Server PID: ", 12);
    ft_putnbr_fd(getpid(), 1);
    write(1, "\n", 1);

    while (1)
        pause();

    return 0;
}
