/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abolor-e <abolor-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 15:09:46 by abolor-e          #+#    #+#             */
/*   Updated: 2024/07/23 13:58:18 by abolor-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// t_toolkit	*init_toolkit(t_tree *tree, t_table **table)
// {
// 	t_toolkit	*toolkit;

// 	toolkit = malloc(sizeof(t_toolkit *));
// 	if (!toolkit)
// 		return (NULL);
// 	// toolkit->parsing_table = table;
// 	toolkit->tree = tree;
// 	// toolkit->hd_fds = NULL;
// 	return (toolkit);
// }

int	main(int ac, char **av, char **envp)
{
	t_token		*input;
	char		*inp;
	t_tree		*tree;
	t_table		**parsingtable;
	t_toolkit	*toolkit;
	t_envb		*env;

	while (1)
	{
		inp = readline("");
		add_history(inp);
		input = ft_lexer(inp);
		parsingtable = ft_init_parsing_table();
		tree = syntax_analysis(input, parsingtable);
		env = env_init(envp);
		if (!tree)
			printf("Tree is NULL\n");
		else
			ast_executor(tree, env);
		//return (1);
	}
	// inp = readline("");
	// input = ft_lexer(inp);
	// parsingtable = ft_init_parsing_table();
	// tree = syntax_analysis(input, parsingtable);
	// env = env_init(envp);
	// if (!tree)
	// 	printf("Tree is NULL\n");
	// else
	// 	ast_executor(tree, env);
	// return (1);
}
