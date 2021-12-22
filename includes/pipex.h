/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-makh <hel-makh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 15:24:52 by hel-makh          #+#    #+#             */
/*   Updated: 2021/12/22 21:58:40 by hel-makh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>

size_t	ft_strlen(const char *s);
char	*ft_strcpy(char *dst, const char *src);
char	*ft_strdup(const char *s1);
char	*ft_strchr(const char *s, int c);
char	*ft_strstr(const char *haystack, const char *needle);
char	*ft_strnjoin(char const *s1, char const *s2, size_t n);
char	**ft_split(char const *s, char c);
char	*ft_free(void *ptr);
void	ft_free_2d(char **array);
void	ft_free_3d(char ***array);
char	*ft_getenv(char *var, char *envp[]);
char	*ft_cmdpath(char *cmd, char *envp[]);
char	**ft_execve_argv(char *cmd, char *envp[]);
int		ft_perror(char *str);

#endif