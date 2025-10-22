/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fomanca <fomanca@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 18:53:05 by fomanca           #+#    #+#             */
/*   Updated: 2025/10/22 21:21:39 by fomanca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>

int	main(void)
{
	int fd = open("tests/dracula.txt", O_RDONLY);
	//int fd = open("tests/empty_test.txt", O_RDONLY);
	//int fd = open("tests/hhgttg.txt", O_RDONLY);
	//int fd = open("tests/large_file.txt", O_RDONLY);
	//int fd = open("tests/nl_and_eof_one.txt", O_RDONLY);
	//int fd = open("tests/one_big_fat_line.txt", O_RDONLY);
	//int fd = open("tests/some_lines.txt", O_RDONLY);

	char	*line;
	while ((line = get_next_line(fd)))
	{
		if (!line)
			break;
		printf("%s", line);
		free(line);
	}
	return (0);
}
