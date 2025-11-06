/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fomanca <fomanca@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 14:08:06 by fomanca           #+#    #+#             */
/*   Updated: 2025/11/02 12:46:39 by fomanca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_read_fd(int fd, char *rem)
{
	char	*buf;
	char	*tmp;
	int		bytes;

	buf = malloc(BUFFER_SIZE + 1);
	if (!buf)
		return (NULL);
	bytes = 1;
	while (!ft_strchr(rem, '\n') && bytes > 0)
	{
		bytes = read(fd, buf, BUFFER_SIZE);
		if (bytes == -1)
		{
			free(buf);
			free(rem);
			return (NULL);
		}
		if (bytes == 0)
			break ;
		buf[bytes] = '\0';
		tmp = ft_strjoin(rem, buf);
		rem = tmp;
	}
	free(buf);
	return (rem);
}

char	*ft_extract_line(char *rem)
{
	int		i;
	char	*line;

	i = 0;
	if (!rem || !rem[i])
		return (NULL);
	while (rem[i] && rem[i] != '\n')
		i++;
	line = malloc(sizeof(char) * (i + 2));
	if (!line)
		return (NULL);
	i = 0;
	while (rem[i] && rem[i] != '\n')
	{
		line[i] = rem[i];
		i++;
	}
	if (rem[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

char	*ft_reminder(char *rem)
{
	int		i;
	int		j;
	char	*new;

	i = 0;
	while (rem[i] && rem[i] != '\n')
		i++;
	if (!rem[i])
		return (free(rem), NULL);
	new = malloc(sizeof(char) * (ft_strlen(rem) - i));
	if (!new)
		return (NULL);
	i++;
	j = 0;
	while (rem[i])
		new[j++] = rem[i++];
	new[j] = '\0';
	free(rem);
	return (new);
}

char	*get_next_line(int fd)
{
	static char	*rem;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	rem = ft_read_fd(fd, rem);
	if (!rem)
		return (NULL);
	line = ft_extract_line(rem);
	rem = ft_reminder(rem);
	return (line);
}
