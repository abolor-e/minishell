/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abolor-e <abolor-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 15:04:35 by abolor-e          #+#    #+#             */
/*   Updated: 2024/08/06 16:51:47 by abolor-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_tree	*stack_to_node(t_stack *popped)
{
	t_tree	*node;

	node = (t_tree *)malloc(sizeof(*node));
	if (node)
	{
		node->type = popped->type;
		node->reduc = -1;
		if (popped->type >= 100)
		{
			node->type = -1;
			node->reduc = popped->type;
		}
		node->data = popped->data;
		node->qt_rm = popped->quote;
		popped->data = NULL;
		node->left = NULL;
		node->right = NULL;
		node->next = NULL;
		return (node);
	}
	return (NULL);
}

t_tree	*find_reduction(t_tree **tree, int reduction)
{
	t_tree	*begin;
	t_tree	*result;

	result = NULL;
	begin = *tree;
	*tree = (*tree)->next;
	while (*tree)
	{
		if ((*tree)->reduc == reduction)
		{
			result = *tree;
			remove_node_from_list(&begin, *tree);
			break ;
		}
		*tree = (*tree)->next;
	}
	*tree = begin;
	return (result);
}

t_tree	*add_reduction_front(t_tree **tree, int reduction)
{
	t_tree	*node;

	node = (t_tree *)malloc(sizeof(*node));
	if (node)
	{
		node->type = -1;
		node->reduc = reduction;
		node->data = NULL;
		node->left = NULL;
		node->right = NULL;
		node->next = *tree;
		*tree = node;
		return (node);
	}
	return (NULL);
}

int	build_syntax_tree(t_tree **tree, t_tree *rdc, t_stack **tokens)
{
	t_stack	*initial_stack;
	int		index;
	t_tree	*new_node;

	new_node = NULL;
	initial_stack = *tokens;
	index = -1;
	while (*tokens)
	{
		if ((*tokens)->type >= 100)
			new_node = find_reduction(tree, (*tokens)->type);
		else
			new_node = stack_to_node(*tokens);
		if (!new_node)
			return (-1);
		if (++index == 0)
			rdc->right = new_node;
		else
			rdc->left = new_node;
		if (index == 1 && (*tokens)->next)
			rdc = rdc->left;
		*tokens = (*tokens)->next;
	}
	*tokens = initial_stack;
	return (0);
}

int	add_syntax_tree(t_tree **syntax_tree, t_stack **token_list, int rule)
{
	t_tree	*reduce_node;

	reduce_node = NULL;
	reduce_node = add_reduction_front(syntax_tree, rule);
	if (reduce_node)
	{
		if (!build_syntax_tree(syntax_tree, reduce_node, token_list))
			return (0);
	}
	return (-1);
}
