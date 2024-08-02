#include "minishell.h"

// void	sigquit_handler(int sig)
// {
// 	if (isatty(STDIN_FILENO))
// 	{
// 		(void)sig;
// 		signal(SIGQUIT, SIG_IGN);
// 		ft_putstr_fd("\b\b", 2);

// 	}
// 	return ;
// }

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	if (s == NULL)
		return ;
	while (s[i] != '\0')
	{
		write(fd, &s[i], 1);
		i++;
	}
}

void	sigint_handler(int sig)
{
	(void)sig;
	if (isatty(STDIN_FILENO))
	{
		write(STDOUT_FILENO, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	signal_handlers(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	reset_signal_handlers(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}