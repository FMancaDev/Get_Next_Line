/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fomanca <fomanca@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 12:54:15 by fomanca           #+#    #+#             */
/*   Updated: 2025/11/02 13:02:53 by fomanca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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
		if (bytes < 0)
			return (free(buf), free(rem), NULL);
		buf[bytes] = '\0';
		tmp = ft_strjoin(rem, buf);
		if (!tmp)
			return (free(buf), free(rem), NULL);
		rem = tmp;
	}
	free(buf);
	return (rem);
}

char	*ft_extract_line(char *rem)
{
	int		i;
	char	*line;

	if (!rem || !*rem)
		return (NULL);
	i = 0;
	while (rem[i] && rem[i] != '\n')
		i++;
	line = malloc(i + 2);
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

char	*ft_update_reminder(char *rem)
{
	int		i;
	int		j;
	char	*new;

	i = 0;
	while (rem[i] && rem[i] != '\n')
		i++;
	if (!rem[i])
		return (free(rem), NULL);
	new = malloc(ft_strlen(rem) - i);
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
	static char	*rem[OPEN_MAX];
	char		*line;

	if (fd < 0 || fd >= OPEN_MAX || BUFFER_SIZE <= 0)
		return (NULL);
	rem[fd] = ft_read_fd(fd, rem[fd]);
	if (!rem[fd])
		return (NULL);
	line = ft_extract_line(rem[fd]);
	rem[fd] = ft_update_reminder(rem[fd]);
	return (line);
}
