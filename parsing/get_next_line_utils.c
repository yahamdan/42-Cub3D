/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: werrahma <werrahma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 23:06:01 by werrahma          #+#    #+#             */
/*   Updated: 2022/12/02 19:15:16 by werrahma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strjoin(char *s1, char *s2)
{
	int		a;
	int		b;
	char	*m;

	a = -1;
	b = -1;
	if (!s1 && s2)
		return (ft_strdup(s2));
	if (s1 && !s2)
		return (ft_strdup(s1));
	m = malloc((ft_strlen(s1) + ft_strlen(s2)) + 1);
	if (!m)
		return (0);
	while (s1[++a])
		m[a] = s1[a];
	while (s2[++b])
		m[a + b] = s2[b];
	m[a + b] = '\0';
	free(s1);
	return (m);
}

size_t	ft_strlen(char *ar)
{
	size_t	a;

	a = 0;
	while (ar[a])
		a++;
	return (a);
}

char	*ft_strdup(char *s1)
{
	int		a;
	int		b;
	char	*p;

	b = ft_strlen(s1);
	p = malloc(sizeof(char) * b + 1);
	if (!p)
		return (0);
	a = 0;
	while (s1[a])
	{
		p[a] = s1[a];
		a++;
	}
	p[a] = '\0';
	return (p);
}
