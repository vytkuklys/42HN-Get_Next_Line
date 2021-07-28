/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuklys <vkuklys@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/28 21:22:20 by vkuklys           #+#    #+#             */
/*   Updated: 2021/07/28 22:18:26 by vkuklys          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include "get_next_line.h"

char	*ft_strchr(const char *str, int c)
{
	while (*str)
	{
		if (*str == c)
			return ((char *)str);
		str++;
	}
	if (c == '\0' && *str == '\0')
		return ((char *)str);
	return (0);
}

void	handle_remainder_newline(char **rem, char **line)
{
	int		flag;
	char	*newline;

	flag = 0;
	newline = ft_strchr(*rem, '\n');
	if (newline)
	{
		if (ft_strncmp(*rem, newline, ft_strlen(*rem)) == 0)
		{
			*line = ft_strdup("\n");
			flag = 1;
		}
		*newline = '\0';
		newline++;
		if (flag == 0)
		{
			*line = ft_strdup(*rem);
			*line = ft_strjoin(line, "\n");
		}
		if (ft_strlen(newline) == 0)
			*rem = NULL;
		else
			*rem = ft_strdup(newline);
	}
}

char	*check_remainder(char **rem, char **line)
{
	char	*newline;
	char	*new_rem;

	newline = NULL;
	if (*rem)
	{
		new_rem = *rem;
		newline = ft_strchr(*rem, '\n');
		if (newline)
		{
			newline++;
			handle_remainder_newline(rem, line);
		}
		else
		{
			*line = ft_strdup(*rem);
			*rem = NULL;
		}
		free(new_rem);
	}
	else
		*line = ft_calloc(1, 1);
	if (newline)
		return (newline);
	return (NULL);
}

int	handle_buffer_newline(char *buffer, char **rem)
{
	int		flag;
	char	*nl;

	flag = 0;
	nl = ft_strchr(buffer, '\n');
	if (nl)
	{
		*nl = '\0';
		flag = 1;
		nl++;
		if (ft_strlen(nl) > 1 || (ft_strlen(nl) == 1 && *nl != '\n'))
			*rem = ft_strdup(nl);
	}
	return (flag);
}

char	*get_next_line(int fd)
{
	char		buffer[BUFFER_SIZE + 1];
	static char	*rem;
	char		*p_n;
	int			i[2];
	char		*line;

	i[0] = 0;
	i[1] = read(fd, buffer, BUFFER_SIZE);
	if (i[1] == -1 || (i[1] == 0 && !rem) || fd < 0 || BUFFER_SIZE < 0)
		return (NULL);
	p_n = check_remainder(&rem, &line);
	buffer[i[1]] = '\0';
	if (p_n && i[1] > 0 && ft_strchr(line, '\n'))
		rem = ft_strjoin(&rem, buffer);
	while (i[1] > 0 && !p_n && !i[0])
	{
		buffer[i[1]] = '\0';
		i[0] = handle_buffer_newline(buffer, &rem);
		line = ft_strjoin(&line, buffer);
		if (!i[0])
			i[1] = read(fd, buffer, BUFFER_SIZE);
	}
	if (i[0] == 1)
		line = ft_strjoin(&line, "\n");
	return (line);
}


int main(void)
{
	int fd = open("./foo.txt", O_RDONLY);
	printf("%d", fd);
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	return 0;
}