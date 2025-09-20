#include <signal.h> // Necessário para SIGUSR1 e SIGUSR2
#include <unistd.h> // Necessário para usleep

void ft_shoot_chars(int pid, char c)
{
    int j;
    int bit;

    j = 7;
    while (j >= 0)
    {
        bit = (c >> j) & 1;
        if (bit == 0)
            kill(pid, SIGUSR1);
        else if (bit == 1)
            kill(pid, SIGUSR2);
        usleep(100);
        j--;
    }
}

void ft_str_bit(int pid, char *c)
{
    int i;

    if (!c)
        return;
    i = 0;
    while (c[i])
    {
        ft_shoot_chars(pdi, c[i]);
        i++;
    }
    ft_shoot_chars(pdi, '\0');
}

#include "libft.h"
void ft_val_pid(int argc, char **argv)
{
    int pid;

    if (argc != 3)
    {
        return ;
    }
    pid = ft_atoi(argv[1]);
    if (pid <= 0)
        return ;
    ft_str_bit(pid, argv[2]);
}

int main(int argc, char **argv)
{
    ft_val_pid(argc, argv);
    return (0);
}
