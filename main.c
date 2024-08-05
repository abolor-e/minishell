/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marechalolivier <marechalolivier@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 15:09:46 by abolor-e          #+#    #+#             */
/*   Updated: 2024/07/31 02:32:08 by marechaloli      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*new_bison(void)
{
	char	*pwd;
	char	*buf;
	long	size;

	size = pathconf(".", _PC_PATH_MAX);
	buf = malloc((size_t)size);
	if (!buf)
		return (".");
	pwd = getcwd(buf, size);
	if (pwd == NULL)
		return (".");
	return (pwd);
}

void	free_env(t_envb *env)
{
	free(env->pwd);
	free(env);
}

void	control_d(void)
{
	rl_on_new_line();
	rl_redisplay();
	printf("exit\n");
	exit (0);
}

void	minishell_loop(t_envb *env, char *pt_path, t_token *input)
{
	char	*inp;
	int		fd[2];
	t_table	**parsingtable;
	t_tree	*tree;

	while (1)
	{
		signal_handlers();
		inp = readline("\033[1;35mSUPRAHELL-1.0$ \e[0m");
		if (!inp)
		{
			free_env(env);
			control_d();
		}
		fd[0] = dup(0);
		fd[1] = dup(1);
		add_history((char *)inp);
		input = ft_lexer(inp);
		parsingtable = ft_init_parsing_table(pt_path);
		tree = syntax_analysis(input, parsingtable);
		if (tree)
			ast_executor(tree, env);
		fd[0] = dup2(fd[0], 0);
		fd[1] = dup2(fd[1], 1);
	}
}

int	main(int ac, char **av, char **envp)
{
	t_token		*input;
	t_envb		*env;
	char		**test;
	char		*pt_path;

	if (ac == 1)
	{
		if (!(envp[0]))
			exit (1);
		else
			env = env_init(envp);
		pt_path = ft_strjoin(new_bison(), BISON_AUTOMATON);
		minishell_loop(env, pt_path, input);
		free_env(env);
		reset_signal_handlers();
	}
	else
		write(2, "Very funny, try again!\n", 23);
}
