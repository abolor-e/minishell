/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abolor-e <abolor-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 13:34:44 by abolor-e          #+#    #+#             */
/*   Updated: 2024/08/06 14:51:20 by abolor-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GNL_H
# define GNL_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 32
# endif

# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# include <limits.h>
# include <fcntl.h>
# include <stddef.h>
# include <sys/types.h>
# include <sys/uio.h>

typedef struct s_list
{
	char			*str_buf;
	struct s_list	*next;
}				t_list;

int		ft_get_next_line(int fd, char **next_line);
int		create_buffer_list(t_list **list, int fd);
void	include_list(t_list **list, char *res);
char	*get_until_newline(t_list *list);
void	prep_for_next_line(t_list **list);
int		newline_check_list(t_list *list);
t_list	*ft_lstlast(t_list *list);
int		len_until_newline(t_list *list);
void	copy(t_list *list, char *new_str);
void	free_list(t_list **list, t_list *new_node, char *str);
void	free_staticbuf_readerror(t_list **list);

#endif
