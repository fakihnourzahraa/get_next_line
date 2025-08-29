/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfakih <nfakih@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 16:05:59 by nfakih            #+#    #+#             */
/*   Updated: 2025/06/07 16:05:59 by nfakih           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strlen( char *str)
{
	int		a;

	a = 0;
	while (str[a] != '\0')
	{
		a++;
	}
	return (a);
}

char	*ft_strdup(char *s)
{
	int		size;
	char	*a;
	int		i;

	i = 0;
	size = ft_strlen(s);
	a = (char *)malloc(size + 1);
	if (!a)
	{
		return (0);
	}
	while (s[i])
	{
		a[i] = s[i];
		i++;
	}
	a[i] = '\0';
	return (a);
}

char	*ft_strjoin(char *a, char *b)
{
	char	*r;
	int		i;
	int		j;

	i = 0;
	j = 0;
	r = (char *)malloc(ft_strlen(a) + ft_strlen(b) + 1);
	if (!r)
		return (NULL);
	while (a[i])
	{
		r[i] = a[i];
		i++;
	}
	while (b[j])
	{
		r[i + j] = b[j];
		j++;
	}
	r[i + j] = '\0';
	return (r);
}

int	getalloc( int start, char *s, int *b, int len)
{
	int	alloc;

	if (start >= ft_strlen(s))
	{
		alloc = 0;
		*b = 0;
	}
	else if (ft_strlen(s) >= (len + start))
		alloc = len;
	else
		alloc = ft_strlen(s) - start;
	return (alloc);
}

char	*ft_substr(char *r, int start, int len)
{
	char	*a;
	int		n;
	int		alloc;
	int		b;

	b = 1;
	alloc = getalloc(start, r, &b, len);
	n = 0;
	a = (char *)malloc(alloc + 1);
	if (!a)
	{
		return (0);
	}
	while (b && r[start + n] && n < len)
	{
		a[n] = r[start + n];
		n++;
	}
	a[n] = '\0';
	return (a);
}
