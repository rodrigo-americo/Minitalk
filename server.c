/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgregori <rgregori@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 15:29:51 by rgregori          #+#    #+#             */
/*   Updated: 2025/09/30 14:45:46 by rgregori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>
#include <sys/types.h>

static void	ft_putpid(pid_t pid)
{
	char	buf[32];
	int		i;
	long	n;

	write(1, "Server PID: ", 12);
	n = (long)pid;
	if (n == 0)
		write(1, "0", 1);
	i = 0;
	while (n > 0)
	{
		buf[i++] = '0' + (n % 10);
		n /= 10;
	}
	while (i--)
		write(1, &buf[i], 1);
	write(1, "\n", 1);
}

static void	ft_helper_sinal(int signum, siginfo_t *info, pid_t *pid_active)
{
	static unsigned char	current_char = 0;
	static int				current_bit = 0;

	if (signum == SIGUSR2)
		current_char |= (1 << (7 - current_bit));
	current_bit++;
	if (current_bit == 8)
	{
		if (current_char == '\0')
			write(1, "\n", 1);
		else
			write(1, &current_char, 1);
		if (current_char == '\0')
			*pid_active = 0;
		current_bit = 0;
		current_char = 0;
	}
	kill(info->si_pid, SIGUSR1);
}

static void	signal_handler(int signum, siginfo_t *info, void *context)
{
	static pid_t	client_pid = 0;

	(void)context;
	if (client_pid == 0)
		client_pid = info->si_pid;
	if (info->si_pid == client_pid)
		ft_helper_sinal(signum, info, &client_pid);
	else
		kill(info->si_pid, SIGUSR2);
}

int	main(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = signal_handler;
	if (sigaction(SIGUSR1, &sa, 0) == -1 || sigaction(SIGUSR2, &sa, 0) == -1)
	{
		write(2, "Erro ao configurar handler.\n", 28);
		return (1);
	}
	ft_putpid(getpid());
	while (1)
		pause();
	return (0);
}
