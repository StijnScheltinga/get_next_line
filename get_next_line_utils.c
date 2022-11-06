/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stijn <stijn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 13:32:55 by stijn             #+#    #+#             */
/*   Updated: 2022/11/04 16:28:54 by stijn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *str)
{
	int	i;

	i = 0;
    if (!str)
        return(0);
	while (str[i])
		i++;
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*join;
	int		len;
	int		i;
	int		j;

	len = ft_strlen(s1) + ft_strlen(s2) + 1;
	join = malloc(sizeof(char) * len);
	if (!join)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i])
	{
		join[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		join[i + j] = s2[j];
		j++;
	}
	join[i + j] = '\0';
	return (join);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*ret;
	size_t			i;
	unsigned int	j;

	i = 0;
	j = 0;
	if (len > ft_strlen(s))
		len = ft_strlen(s);
	ret = malloc(sizeof(char) * len + 1);
	if (!ret)
		return (ret);
	while (s[i])
	{
		while (j < len && i >= start)
		{
			ret[j] = s[i];
			j++;
			i++;
		}
		if (j == len)
			break ;
		i++;
	}
	ret[j] = '\0';
	return (ret);
}