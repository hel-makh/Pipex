/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-makh <hel-makh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 13:55:32 by hel-makh          #+#    #+#             */
/*   Updated: 2021/12/20 16:19:11 by hel-makh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static char	*ft_strncpy(char *dst, const char *src, size_t len)
{
	size_t	i;
	size_t	src_len;

	i = 0;
	src_len = ft_strlen(src);
	while (i < len)
	{
		if (i <= src_len)
			dst[i] = src[i];
		else
			dst[i] = '\0';
		i ++;
	}
	dst[i] = '\0';
	return (dst);
}

static void	ft_split_free_arr(char **arr, int len)
{
	while (len >= 0)
		free(arr[len--]);
	free(arr);
}

static int	ft_split_count(char *s, char c, int pos)
{
	int	str_count;

	if (!*s)
		return (0);
	if (c == 0 && pos == 0)
		return (1);
	str_count = 0;
	while (ft_strchr(s, c))
	{
		if (ft_strlen(s) - ft_strlen(ft_strchr(s, c)) == 0)
		{
			s ++;
			continue ;
		}
		str_count ++;
		if (pos == str_count)
			return (ft_strlen(s) - ft_strlen(ft_strchr(s, c)));
		s = ft_strchr(s, c) + 1;
	}
	if (s && pos)
		return (ft_strlen(s));
	if (*s)
		str_count ++;
	return (str_count);
}

static char	**ft_split_fill_arr(char **arr, int arr_len, char const *s, char c)
{
	char	*temp_s;
	int		str_len;
	int		i;

	temp_s = (char *)s;
	i = 0;
	while (i < arr_len)
	{
		while (*temp_s == c)
			temp_s ++;
		str_len = ft_split_count((char *)s, c, i + 1);
		arr[i] = (char *) malloc ((str_len + 1) * sizeof(char));
		if (arr[i] == NULL)
		{
			ft_split_free_arr(arr, i - 1);
			return (0);
		}
		ft_strncpy(arr[i], temp_s, str_len);
		temp_s += str_len + 1;
		i ++;
	}
	arr[i] = NULL;
	return (arr);
}

char	**ft_split(char const *s, char c)
{
	char	**arr;
	int		arr_len;

	if (s == NULL)
		return (0);
	arr_len = ft_split_count((char *)s, c, 0);
	arr = (char **) malloc ((arr_len + 1) * sizeof(char *));
	if (arr == NULL)
		return (0);
	arr = ft_split_fill_arr(arr, arr_len, s, c);
	return (arr);
}
