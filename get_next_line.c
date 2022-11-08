/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschelti <sschelti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 10:16:31 by stijn             #+#    #+#             */
/*   Updated: 2022/11/08 16:24:53 by sschelti         ###   ########.fr       */
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

char	*ft_stash(char *buff, unsigned long end_file)
{	
	int			i;
	char		*line;
	static char	*stash;

	i = 0;
	line = NULL;
	if (stash == NULL)
		stash = ft_strdup(buff);
	else
		stash = ft_strjoin(stash, buff);
	if (!stash)
		return (NULL);
	if (end_file == 0)
	{
		line = ft_substr(stash, 0, i + 1);
		free (stash);
		return (line);
	}
	while (stash[i])
	{
		if (stash[i] == '\n')
		{
			line = ft_substr(stash, 0, i + 1);
			stash = ft_clean(stash);
			return (line);
		}
		i++;
	}
	return (line);
}

char	*get_next_line(int fd)
{
	char			buff[BUFFER_SIZE + 1];
	unsigned long	bytes_read;
	char			*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	bytes_read = 1;
	while (bytes_read != 0)
	{
		bytes_read = read(fd, (void *) buff, BUFFER_SIZE);
		printf("\nbytes read: %lu", bytes_read);
		buff[bytes_read] = '\0';
		line = ft_stash(buff, bytes_read);
		if (line != NULL)
			return (line);
	}
	return (NULL);
}

int main()
{
	int fd;

	fd = open("text.txt", O_RDONLY);
	// get_next_line(fd);
	// get_next_line(fd);
	printf("\nprint 1:%s", get_next_line(fd));
	printf("\nprint 2:%s", get_next_line(fd));
}
