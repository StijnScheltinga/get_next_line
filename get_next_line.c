/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschelti <sschelti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 10:16:31 by stijn             #+#    #+#             */
/*   Updated: 2022/11/17 18:46:39 by sschelti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_clean(char *stash)
{
	char	*new;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (stash[i] != '\n' && stash[i])
		i++;
	if (stash[i] == '\n')
		i++;
	if (stash[i] == 0)
		return (free(stash), NULL);
	while (stash[i + j])
		j++;
	new = malloc(sizeof(char) * (j + 1));
	if (!new)
		return (NULL);
	j = 0;
	while (stash[i + j])
	{
		new[j] = stash[i + j];
		j++;
	}
	new[j] = '\0';
	return (free(stash), new);
}

char	*ft_line(char *stash)
{
	int		i;
	char	*line;

	i = 0;
	while (stash[i] != '\n' && stash[i] != '\0')
		i++;
	line = ft_substr(stash, 0, i + 1);
	return (line);
}

char	*ft_find_line(int fd, char	*stash)
{
	char	*buff;
	int		bytes_read;

	buff = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buff)
		return (NULL);
	bytes_read = 1;
	while (!ft_strchr(stash, '\n') && bytes_read != 0)
	{
		bytes_read = read(fd, buff, BUFFER_SIZE);
		if (bytes_read == -1 || (bytes_read == 0 && stash == NULL))
			return (free(buff), free(stash), NULL);
		buff[bytes_read] = 0;
		stash = ft_strjoin(stash, buff);
	}
	free(buff);
	return (stash);
}

char	*get_next_line(int fd)
{	
	static char	*stash;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE >= 2147483647)
		return (NULL);
	stash = ft_find_line(fd, stash);
	if (!stash)
		return (stash);
	line = ft_line(stash);
	stash = ft_clean(stash);
	return (line);
}

// int main()
// {
// 	int	fd;

// 	fd = open("text.txt", O_RDONLY);
// 	printf("\nprint1: |%s|\n\n", get_next_line(fd));
// 	printf("\nprint2: |%s|\n\n", get_next_line(fd));
// 	printf("\nprint3: |%s|\n\n", get_next_line(fd));
// 	printf("\nprint4: |%s|\n\n", get_next_line(fd));
// 	printf("\nprint5: |%s|\n\n", get_next_line(fd));
// 	printf("\nprint6: |%s|\n\n", get_next_line(fd));
// }
