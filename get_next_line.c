/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stijn <stijn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 10:16:31 by stijn             #+#    #+#             */
/*   Updated: 2022/11/06 23:15:17 by stijn            ###   ########.fr       */
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
	while (stash[i])
	{
		if (stash[i] == '\n')
			break ;
		i++;
	}
	i++;
	while (stash[i])
	{
		j++;
		i++;
	}
	new = malloc(sizeof(char) * (j + 1));
	if (!new)
		return(NULL);
	i -= j;
	j = 0;
	while(stash[i])
	{
		new[j] = stash[i];
		i++;
		j++;
	}
	new[j] = '\0';
	return(new);
}

char *ft_stash(char *buff)
{	
	int			i;
	char		*line;
	static char	*stash;

	i = 0;
	if (stash == NULL)
		stash = ft_strjoin("\0", buff);
	else
		stash = ft_strjoin(stash, buff);
	printf("stash: %s\n", stash);
	if (!stash)
		return (stash);
	while (stash[i])
	{
		if (stash[i] == '\n')
		{
			line = ft_substr(stash, 0, i + 1);
			stash = ft_clean(stash);
			return(line);
		}
		i++;
	}
	return(NULL);
}

char    *get_next_line(int fd)
{
	char    		*buff;
	size_t  		nbyte;
	unsigned long	bytes_read;
	char			*line;

	nbyte = 10;
	#ifdef BUFFER_SIZE
		nbyte = BUFFER_SIZE;
	#endif
	bytes_read = nbyte;
	buff = malloc(sizeof(char) * (nbyte + 1));
	if (!buff)
		return(buff);
	while (bytes_read == nbyte)
	{
		bytes_read = read(fd, (void *) buff, nbyte);
		// if (bytes_read != nbyte)
		buff[bytes_read] = '\0';
		printf("buff: %s\n", buff); 
		line = ft_stash(buff);
		if (line != NULL)
		{
			free(buff);
			return (line);
		}
	}
	return(NULL);
}

int main()
{
	int fd;

	fd = open("text.txt", O_RDONLY);
	// get_next_line(fd);
	// get_next_line(fd);
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
}