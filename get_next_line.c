/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fomanca <fomanca@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 13:13:55 by fomanca           #+#    #+#             */
/*   Updated: 2025/10/22 18:08:51 by fomanca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*fill_buffer_line(int fd, char *left_char, char *buffer);
static char	*extract_line(char *line);
static char	*ft_strchr(char *str, int c);

char	*get_next_line(int fd)
{
	static char	*left_char;
	char		*line;
	char		*buffer;

	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		free(left_char);
		free(buffer);
		left_char = NULL;
		buffer = NULL;
		return (NULL);
	}
	if (!buffer)
		return (NULL);
	line = fill_buffer_line(fd, left_char, buffer);
	free(buffer);
	buffer = NULL;
	if (!line)
		return (NULL);
	left_char = extract_line(line);
	return (line);
}

static char	*extract_line(char *line_buffer)
{
	char	*left_char;
	ssize_t	i;

	i = 0;
	while (line_buffer[i] != '\n' && line_buffer[i] != '\0')
		i++;
	if (line_buffer[i] == 0 || line_buffer[1] == 0)
		return (NULL);
	left_char = ft_substr(line_buffer, i + 1, ft_strlen(line_buffer) - i);
	if (*left_char == 0)
	{
		free(left_char);
		left_char = NULL;
	}
	line_buffer[i + 1] = 0;
	return (left_char);
}

static char	*fill_buffer_line(int fd, char *left_char, char *buffer)
{
	ssize_t	b_read;
	char	*tmp;

	b_read = 1;
	while (b_read > 0)
	{
		b_read = read(fd, buffer, BUFFER_SIZE);
		if (b_read == -1)
		{
			free(left_char);
			return (NULL);
		}
		else if (b_read == 0)
			break ;
		buffer[b_read] = 0;
		if (!left_char)
			left_char = ft_strdup("");
		tmp = left_char;
		left_char = ft_strjoin(tmp, buffer);
		free(tmp);
		tmp = NULL;
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	return (left_char);
}

static char	*ft_strchr(char *str, int c)
{
	unsigned int	i;
	char			cc;

	cc = (char)c;
	i = 0;
	while (str[i])
	{
		if (str[i] == cc)
			return ((char *) &str[i]);
		i++;
	}
	if (str[i] == cc)
		return ((char *) &str[i]);
	return (NULL);
}
