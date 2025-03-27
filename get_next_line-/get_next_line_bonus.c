/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aycami <aycami@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 17:13:40 by aycami            #+#    #+#             */
/*   Updated: 2024/12/03 20:25:54 by aycami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*read_with_buffer(char *str, int fd)
{
	int		i;
	char	*buf;

	if (!str)
		str = ft_strdup("");
	while (!ft_strchr(str, '\n'))
	{
		buf = malloc(((unsigned int)BUFFER_SIZE + 1) * sizeof(char));
		if (!buf)
			return (free(str), free(buf), NULL);
		i = read(fd, buf, (unsigned int)BUFFER_SIZE);
		if (i == -1)
			return (free(str), free(buf), NULL);
		if (i == 0)
		{
			if (ft_strlen(str) == 0)
			{
				return (free(str), free(buf), NULL);
			}
			return (free(buf), str);
		}
		buf[i] = '\0';
		str = ft_strjoin(str, buf);
	}
	return (str);
}

char	*first_line(char *str)
{
	int		i;
	char	*ret;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		i++;
	ret = ft_substr(str, 0, i);
	return (ret);
}

char	*rest_lines(char *str)
{
	int		i;
	char	*rest;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	rest = ft_substr(str, i + 1, ft_strlen(str + i));
	free(str);
	return (rest);
}

char	*get_next_line(int fd)
{
	static char	*str[1024];
	char		*line;

	if (fd < 0 || (unsigned int)BUFFER_SIZE <= 0)
		return (NULL);
	str[fd] = read_with_buffer(str[fd], fd);
	if (!str[fd])
		return (NULL);
	line = first_line(str[fd]);
	str[fd] = rest_lines(str[fd]);
	return (line);
}
