/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-makh <hel-makh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 15:24:52 by hel-makh          #+#    #+#             */
/*   Updated: 2021/12/25 15:09:11 by hel-makh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "pipex.h"

# define BUFFER_SIZE 1

typedef struct s_list
{
	int				fd;
	char			content[BUFFER_SIZE + 1];
	struct s_list	*next;
}	t_list;

void	ft_here_doc(char ***cmds, char *outfile, char *limiter, char *envp[]);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strchr(const char *s, int c);
char	*get_next_line(int fd);

#endif