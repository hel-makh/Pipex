/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-makh <hel-makh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/19 22:37:34 by hel-makh          #+#    #+#             */
/*   Updated: 2021/12/20 16:19:04 by hel-makh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

char	*ft_getenv(char *var, char *envp[])
{
	int		i;

	i = 0;
	while (envp[i])
	{
		if (ft_strstr(envp[i], var))
			return (&envp[i][ft_strlen(var) + 1]);
		i ++;
	}
	return (NULL);
}
