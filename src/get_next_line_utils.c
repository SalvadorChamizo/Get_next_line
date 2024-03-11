/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schamizo <schamizo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 16:10:46 by schamizo          #+#    #+#             */
/*   Updated: 2023/12/22 10:58:43 by schamizo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
	{
		i++;
	}
	return (i);
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*p;

	p = malloc(count * size);
	if (p == NULL)
		return (NULL);
	ft_memset(p, 0, count * size);
	return (p);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*s3;
	char	*p;
	size_t	len1;
	size_t	len2;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	s3 = malloc(len1 + len2 + 1);
	if (s3 == NULL)
		return (NULL);
	p = s3;
	while (len1--)
		*p++ = *s1++;
	while (len2--)
		*p++ = *s2++;
	*p = '\0';
	return (s3);
}

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*p;

	p = b;
	if (len == 0)
		return (b);
	while (len > 0)
	{
		*p = (unsigned char) c;
		p++;
		len--;
	}
	return (b);
}

void	safe_free(char *str)
{
	free(str);
	str = NULL;
}
