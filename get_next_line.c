/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfakih <nfakih@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 16:05:06 by nfakih            #+#    #+#             */
/*   Updated: 2025/06/07 16:05:06 by nfakih           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strchr(char *a, int c)
{
	while (*a != '\0')
	{
		if (*a == (char)c)
		{
			return (a);
		}
		a++;
	}
	if (*a == (char)c)
		return (a);
	return (0);
}

char	*reading(int fd, char *buff, char *excess)
{
	ssize_t	r;
	char	*temp;

	r = 1;
	while (r > 0)
	{
		r = read(fd, buff, BUFFER_SIZE);
		if (r == -1)
		{
			free(excess);
			return (NULL);
		}
		else if (r == 0)
			break ;
		buff[r] = '\0';
		if (!excess)
			excess = ft_strdup("");
		temp = excess;
		excess = ft_strjoin(temp, buff);
		free(temp);
		temp = NULL;
		if (ft_strchr(buff, '\n'))
			break ;
	}
	return (excess);
}

char	*extract_line(char *line)
{
	char	*excess;
	int		i;

	i = 0;
	while (line[i] != '\n' && line[i] != '\0')
		i++;
	if (line[i] == '\0')
		return (NULL);
	excess = ft_substr(line, i + 1, ft_strlen(line) - (i + 1));
	if (*excess == '\0')
	{
		free(excess);
		excess = NULL;
	}
	line[i + 1] = '\0';
	return (excess);
}

char	*get_next_line(int fd)
{
	static char	*excess;
	char		*buff;
	char		*line;

	buff = malloc(BUFFER_SIZE + 1);
	if (!buff)
		return (NULL);
	if (fd == -1 || BUFFER_SIZE <= 0)
	{
		free(excess);
		free(buff);
		return (NULL);
	}
	line = reading(fd, buff, excess);
	free (buff);
	if (!line)
		return (NULL);
	excess = extract_line(line);
	return (line);
}

// int main()
// {
// 	char *line;
// 	int fd = open("hi.txt", O_RDONLY);
// 	while (line = get_next_line(fd))
// 	{
// 	printf("%s",line);
// 	free(line);
// 	}
// 	printf("\nfinished");
// 	close(fd);
// }