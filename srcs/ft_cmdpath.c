/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmdpath.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-makh <hel-makh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/19 22:39:02 by hel-makh          #+#    #+#             */
/*   Updated: 2021/12/22 00:46:11 by hel-makh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

char	*ft_cmdpath(char *cmd, char *envp[])
{
	char	*cmd_path;
	char	*env_path;
	char	**paths;
	int		i;

	if (!cmd || !ft_strlen(cmd))
		return (NULL);
	env_path = ft_getenv("PATH", envp);
	if (!env_path)
		return (NULL);
	paths = ft_split(env_path, ':');
	i = 0;
	while (paths[i])
	{
		paths[i] = ft_strnjoin(paths[i], "/", ft_strlen("/"));
		paths[i] = ft_strnjoin(paths[i], cmd, ft_strlen(cmd));
		if (access(paths[i], F_OK) == 0)
		{
			cmd_path = ft_strdup(paths[i]);
			ft_free_2d(paths);
			return (cmd_path);
		}
		i ++;
	}
	return (NULL);
}
