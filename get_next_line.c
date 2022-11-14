/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschelti <sschelti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 10:16:31 by stijn             #+#    #+#             */
/*   Updated: 2022/11/14 17:47:11 by sschelti         ###   ########.fr       */
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
	while (stash[i] != '\n')
		i++;
	i++;
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
	free (stash);
	return (new);
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

char	*get_next_line(int fd)
{	
	static char	*stash;
	char		*buff;
	int			bytes_read;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buff = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buff)
		return (NULL);
	buff[BUFFER_SIZE] = 0;
	bytes_read = 1;
	while (!ft_strchr(stash, '\n') && bytes_read != 0)
	{
		bytes_read = read(fd, buff, BUFFER_SIZE);
		buff[bytes_read] = 0;
		stash = ft_strjoin(stash, buff);
	}
	if (stash[0] == 0)
		return (NULL);
	line = ft_line(stash);
	stash = ft_clean(stash);
	free (buff);
	return (line);
}

int main()
{
	int	fd;

	fd = open("text.txt", O_RDONLY);
	printf("print1: |%s|\n", get_next_line(fd));
	printf("print2: |%s|\n", get_next_line(fd));
	printf("print3: |%s|\n", get_next_line(fd));
	printf("print4: |%s|\n", get_next_line(fd));
	printf("print5: |%s|\n", get_next_line(fd));
	printf("print6: |%s|\n", get_next_line(fd));
	// get_next_line(fd);
	// get_next_line(fd);
	// get_next_line(fd);
}
