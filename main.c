/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abolor-e <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 15:09:46 by abolor-e          #+#    #+#             */
/*   Updated: 2024/07/17 15:10:35 by abolor-e         ###   ########.fr       */
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
	t_table		**parsing_table;
	t_toolkit	*toolkit;
	t_envb		*env;

	inp = readline("");
	input = ft_lexer(inp);
	parsing_table = ft_init_parsing_table();
	tree = syntax_analysis(input, parsing_table);
	env = env_init(envp);
	if (!tree)
		printf("Tree is NULL\n");
	else
		ast_executor(tree, env);
	return (1);
}
