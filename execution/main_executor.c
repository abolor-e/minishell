/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_executor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abolor-e <abolor-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 15:20:39 by abolor-e          #+#    #+#             */
/*   Updated: 2024/08/06 16:13:02 by abolor-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	tree_finder(t_tree *tree, int param, int nb)
{
	if (!tree)
		return (nb);
	if (tree->type == param)
		nb++;
	nb = tree_finder(tree->left, param, nb);
	nb = tree_finder(tree->right, param, nb);
	return (nb);
}

int	ast_executor(t_tree *tree, t_envb *env)
{
	int	return_value;
	int	pipe_counter;

	pipe_counter = 0;
	return_value = 0;
	pipe_counter = tree_finder(tree, A_PIPE, 0);
	if (pipe_counter > 0)
		return (exec_simple_cmd(tree, env));
	if (!do_redirection(tree, 0, env))
		return (exec_simple_cmd(tree, env));
	return (0);
}
