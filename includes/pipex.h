/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-makh <hel-makh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 15:24:52 by hel-makh          #+#    #+#             */
/*   Updated: 2021/12/21 21:29:19 by hel-makh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>

# define BUFFER_SIZE 1

typedef struct s_list
{
	int				fd;
	char			content[BUFFER_SIZE + 1];
	struct s_list	*next;
}	t_list;

size_t	ft_strlen(const char *s);
char	**ft_split(char const *s, char c);
char	*ft_strcpy(char *dst, const char *src);
char	*ft_strdup(const char *s1);
char	*ft_strchr(const char *s, int c);
int     ft_strcmp(const char *s1, const char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strnjoin(char const *s1, char const *s2, size_t n);
char	*ft_free(void *ptr);
void	ft_2d_free(char **array);
char	*ft_strstr(const char *haystack, const char *needle);
char	*ft_getenv(char *var, char *envp[]);
char	*ft_cmdpath(char *cmd, char *envp[]);
char	**ft_execve_argv(char *cmd, char *envp[]);
int		ft_perror(char *str);
char	*get_next_line(int fd, char *prefix);
void	ft_here_doc(char *limiter, char *outfile, char ***cmds);

#endif