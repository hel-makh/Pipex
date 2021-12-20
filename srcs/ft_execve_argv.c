/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execve_argv.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-makh <hel-makh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 14:55:20 by hel-makh          #+#    #+#             */
/*   Updated: 2021/12/20 16:18:59 by hel-makh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

char	**ft_execve_argv(char *cmd, char *envp[])
{
	char	**argv;
	char	*cmd_name;

	argv = ft_split(cmd, ' ');
	cmd_name = argv[0];
	argv[0] = ft_cmdpath(argv[0], envp);
	free(cmd_name);
	return (argv);
}
