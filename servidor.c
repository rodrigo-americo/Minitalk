#include <unistd.h>
#include <signal.h>
#include <stdio.h>

void signal_handler(int signum, siginfo_t *info, void *context)
{
    static int client_pid = 0;

     if (client_pid == 0)
    {
        client_pid = info->si_pid;
    }
    // Se o sinal for SIGUSR2, o bit é 1.
    if (signum == SIGUSR2)
        current_char |= 1;

    // Incrementa a contagem de bits recebidos
    current_bit++;

    // Quando 8 bits foram recebidos, o caractere está completo
    if (current_bit == 8)
    {
        if (current_char == '\0') // Se for o caractere nulo, a string terminou
        {
            printf("\n");
        }
        else
        {
            printf("%c", current_char);
        }
        // Reseta as variáveis para o próximo caractere
        current_bit = 0;
        current_char = 0;
    }
}

int main(void)
{
    struct sigaction sa;

    // Limpa a estrutura para evitar valores aleatórios
    sa.sa_flags = SA_SIGINFO;
    sa.sa_handler = signal_handler;
    sigemptyset(&sa.sa_mask);

    // Registra o handler para SIGUSR1 e SIGUSR2
    if (sigaction(SIGUSR1, &sa, NULL) == -1 || sigaction(SIGUSR2, &sa, NULL) == -1)
    {
        printf("Error configuring signal handler.\n");
        return (1);
    }
    printf("Server PID: %d\n", getpid());
    while (1)
    {
        pause();
    }

    return (0);
}

int main(void)
{
    struct sigaction sa;

    sa.sa_flags = SA_SIGINFO; // Use SA_SIGINFO para obter informações detalhadas
    sa.sa_sigaction = signal_handler; // A função agora é sa_sigaction
    sigemptyset(&sa.sa_mask);

    if (sigaction(SIGUSR1, &sa, NULL) == -1 || sigaction(SIGUSR2, &sa, NULL) == -1)
    {
        printf("Error configuring signal handler.\n");
        return (1);
    }
    
    printf("Server PID: %d\n", getpid());
    
    while (1)
    {
        pause();
    }
    return (0);
}