/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmdpath.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-makh <hel-makh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/19 22:39:02 by hel-makh          #+#    #+#             */
/*   Updated: 2021/12/23 19:46:19 by hel-makh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

char	*ft_cmdpath(char *cmd, char *envp[])
{
	char	*env_path;
	char	**paths;
	int		i;

	if (!cmd || !ft_strlen(cmd))
		return (ft_strdup(""));
	env_path = ft_getenv("PATH", envp);
	if (!env_path)
		return (ft_strdup(""));
	paths = ft_split(env_path, ':');
	i = 0;
	while (paths[i])
	{
		paths[i] = ft_strnjoin(paths[i], "/", 1);
		paths[i] = ft_strnjoin(paths[i], cmd, ft_strlen(cmd));
		if (access(paths[i], X_OK) == 0)
		{
			ft_free_2d(paths);
			return (ft_strdup(paths[i]));
		}
		i ++;
	}
	ft_free_2d(paths);
	return (ft_strdup(""));
}
