/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils7.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abolor-e <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 15:06:37 by abolor-e          #+#    #+#             */
/*   Updated: 2024/07/19 15:06:38 by abolor-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../gnl.h"
#include "../minishell.h"

char	*ft_strchr(const char *s, int c)
{
	if (!s)
		return (NULL);
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		++s;
	}
	if (c == 0)
		return ((char *)s);
	return (NULL);
}

void	*ft_realloc(void *ptr, size_t size)
{
	char	*new;

	if (!ptr || size == 0)
	{
		if (size == 0)
			size = 1;
		new = (char *)malloc(sizeof(*new) * size);
		if (!new)
		{
			free(ptr);
			return (NULL);
		}
		return (new);
	}
	new = (char *)malloc(sizeof(*new) * size);
	if (!new)
	{
		free(ptr);
		return (NULL);
	}
	new = ft_strcpy(new, ptr);
	free(ptr);
	return (new);
}

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	s_len;
	size_t	d_len;
	size_t	i;
	size_t	result;

	i = 0;
	s_len = ft_strlen(src);
	d_len = ft_strlen(dst);
	if (dstsize >= d_len)
		result = s_len + d_len;
	else
		result = s_len + dstsize;
	if (dstsize > d_len)
	{
		while (src[i] && d_len < dstsize - 1)
		{
			dst[d_len] = src[i];
			++d_len;
			++i;
		}
	}
	dst[d_len] = '\0';
	return (result);
}

char	*ft_strcpy(char *dst, const char *src)
{
	size_t	i;

	i = -1;
	if (!src)
	{
		dst[0] = 0;
		return (dst);
	}
	while (src[++i])
		dst[i] = src[i];
	dst[i] = '\0';
	return (dst);
}
