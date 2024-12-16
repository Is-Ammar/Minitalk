/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iammar <iammar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 21:47:27 by iammar            #+#    #+#             */
/*   Updated: 2024/12/15 20:07:35 by iammar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include <signal.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_data
{
	int		byte;
	int		bit_count;
	char	current_char;

}			t_data;

void		ft_putnbr_fd(int n, int fd);
int			ft_atoi(const char *str);
#endif