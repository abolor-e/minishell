/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abolor-e <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 15:15:41 by abolor-e          #+#    #+#             */
/*   Updated: 2024/07/17 15:15:48 by abolor-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*ft_strnstr(const char *s1, const char *s2, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (!s2[0])
		return ((char *)s1);
	while (s1[i] && len > 0)
	{
		if (s1[i] != '\0')
		{
			j = 0;
			while (s1[i + j] == s2[j] && s1[i + j] && i + j < len && s2[j])
				j++;
			if (s2[j] == '\0')
				return ((char *)(s1 + i));
		}
		i++;
	}
	return (NULL);
}
