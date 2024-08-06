/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abolor-e <abolor-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 15:06:28 by abolor-e          #+#    #+#             */
/*   Updated: 2024/08/06 15:54:30 by abolor-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	visit_and_fix_node_types(t_tree *current_node)
{
	if (!current_node)
		return ;
	if (current_node->reduc == R_FILENAME)
		current_node->right->type = A_FILE;
	if (current_node->reduc == R_HERE_END)
		current_node->right->type = A_LIMITER;
	if (current_node->reduc > R_CMD_WORD)
	{
		if (current_node->left && current_node->left->type == A_CMD)
			current_node->left->type = A_PARAM;
		if (current_node->right && current_node->right->type == A_CMD)
			current_node->right->type = A_PARAM;
	}
	visit_and_fix_node_types(current_node->left);
	visit_and_fix_node_types(current_node->right);
}

t_tree	*fix_parameter_types(t_tree *syntax_tree)
{
	if (syntax_tree && syntax_tree->type == -1)
		syntax_tree->type = -2;
	visit_and_fix_node_types(syntax_tree);
	return (syntax_tree);
}

/*
** REMOVE NODE FROM LIST
** Remove a node from the list that will be attached under a reduction
** node
*/

void	remove_node_from_list(t_tree **head, t_tree *target_node)
{
	t_tree	*prev_node;
	t_tree	*current_node;

	prev_node = NULL;
	current_node = NULL;
	if (*head == target_node)
	{
		*head = target_node->next;
		return ;
	}
	else
	{
		current_node = *head;
		while (current_node)
		{
			if (current_node == target_node)
			{
				prev_node->next = current_node->next;
				return ;
			}
			prev_node = current_node;
			current_node = current_node->next;
		}
	}
}
