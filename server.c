/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-moue <hel-moue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 02:01:44 by hel-moue          #+#    #+#             */
/*   Updated: 2023/04/11 22:36:19 by hel-moue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putnbr(int n)
{
	long	nb;

	nb = n;
	if (nb < 0)
	{
		ft_putchar('-');
		nb = -nb;
	}
	if (nb > 9)
		ft_putnbr((nb / 10));
	ft_putchar((nb % 10) + '0');
}

void	secend(int signal, siginfo_t *sa, void *context)
{
	static int	bit;
	static char	i;
	static int	pid;

	context = NULL;
	if (pid != sa->si_pid)
	{
		bit = 0;
		i = 0;
	}
	if (signal == SIGUSR1)
		i = i | (1 << bit);
	bit++;
	if (bit == 8)
	{
		write(1, &i, 1);
		bit = 0;
		i = 0;
	}
	pid = sa->si_pid;
}

int	main(int argc, char **argv)
{
	struct sigaction	sa;

	(void)argv;
	if (argc != 1)
	{
		write(1, "Error\n", 6);
		return (0);
	}
	ft_putnbr(getpid());
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = &secend;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	write(1, "\n", 1);
	while (1)
		pause ();
	return (0);
}
