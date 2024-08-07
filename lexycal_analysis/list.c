/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abolor-e <abolor-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 15:47:28 by abolor-e          #+#    #+#             */
/*   Updated: 2024/08/06 16:07:27 by abolor-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	catego_toketype(char *content, int c)
{
	if (!content)
		return (T_END);
	if (!ft_strcmp(content, "|") && !c)
		return (T_PIPE);
	else if (!ft_strcmp(content, "<<") && !c)
		return (T_DLESS);
	else if (!ft_strcmp(content, ">>") && !c)
		return (T_DGREAT);
	else if (!ft_strcmp(content, ">") && !c)
		return (T_RED_TO);
	else if (!ft_strcmp(content, "<") && !c)
		return (T_RED_FROM);
	else
		return (T_WORD);
}

void	ft_tokenadd_back(t_token **lst, t_token *new)
{
	t_token	*current;

	current = NULL;
	if (!(*lst))
	{
		(*lst) = new;
		return ;
	}
	current = (*lst);
	while (current->next != 0)
	{
		current = current->next;
	}
	current->next = new;
}

void	*ft_newtoken(void *content, int c)
{
	t_token		*re;

	re = (t_token *)malloc(sizeof(t_token));
	if (!re)
		return (0);
	re->value = content;
	re->type = catego_toketype(content, c);
	re->quote = c;
	re->next = 0;
	return (re);
}
