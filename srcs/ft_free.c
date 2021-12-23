/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-makh <hel-makh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/19 19:43:25 by hel-makh          #+#    #+#             */
/*   Updated: 2021/12/23 17:58:21 by hel-makh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

char	*ft_free(void *ptr)
{
	free(ptr);
	return (NULL);
}

void	ft_free_2d(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		free(array[i++]);
	free(array);
}

void	ft_free_3d(char ***array)
{
	int	i;

	i = 0;
	while (array[i])
		ft_free_2d(array[i++]);
}
