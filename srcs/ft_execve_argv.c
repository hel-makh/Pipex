/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execve_argv.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-makh <hel-makh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 14:55:20 by hel-makh          #+#    #+#             */
/*   Updated: 2021/12/25 15:09:03 by hel-makh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

char	**ft_execve_argv(char *cmd, char *envp[])
{
	char	**argv;
	char	*cmd_name;

	argv = ft_split(cmd, ' ');
	if (access(argv[0], X_OK) != 0)
	{
		cmd_name = argv[0];
		argv[0] = ft_cmdpath(argv[0], envp);
		free(cmd_name);
	}
	return (argv);
}
