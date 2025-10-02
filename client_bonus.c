/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgregori <rgregori@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 10:23:03 by rgregori          #+#    #+#             */
/*   Updated: 2025/10/02 11:22:03 by rgregori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>

volatile sig_atomic_t	g_server_ack = 1;

static void	ft_erro_exit(void)
{
	write(1, "Error\n", 6);
	exit(1);
}

static int	parse_pid(const char *s, pid_t *out)
{
	long	n;
	int		i;

	n = 0;
	i = 0;
	if (!s || !s[0])
		return (0);
	while (s[i])
	{
		if (s[i] < '0' || s[i] > '9')
			return (0);
		n = n * 10 + (s[i] - '0');
		if (n > 2147483647)
			return (0);
		i++;
	}
	if (n <= 0)
		return (0);
	*out = (pid_t)n;
	return (1);
}

void	ft_shoot_chars(int pid, char c)
{
	int	j;
	int	bit;

	j = 7;
	while (j >= 0)
	{
		g_server_ack = 0;
		bit = (c >> j) & 1;
		if (bit == 0)
		{
			if (kill(pid, SIGUSR1) == -1)
				ft_erro_exit();
		}
		else if (bit == 1)
		{
			if (kill(pid, SIGUSR2) == -1)
				ft_erro_exit();
		}
		j--;
		while (g_server_ack == 0)
			pause();
	}
}

void	client_handler(int signum, siginfo_t *info, void *context)
{
	(void)info;
	(void)context;
	if (signum == SIGUSR1)
		g_server_ack = 1;
	if (signum == SIGUSR2)
		g_server_ack = -1;
}

int	main(int argc, char **argv)
{
	pid_t				pid;
	struct sigaction	sa;
	int					i;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = client_handler;
	if (argc != 3 || parse_pid(argv[1], &pid) <= 0)
		ft_erro_exit();
	if (sigaction(SIGUSR1, &sa, 0) == -1 || sigaction(SIGUSR2, &sa, 0) == -1)
	{
		write(1, "Erro ao configurar handler.\n", 28);
		return (1);
	}
	i = 0;
	while (argv[2][i])
	{
		ft_shoot_chars(pid, argv[2][i]);
		i++;
	}
	ft_shoot_chars(pid, '\0');
	write(1, "Mensagem enviada com sucesso.\n", 28);
	return (0);
}
