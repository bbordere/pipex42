/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 12:04:01 by bbordere          #+#    #+#             */
/*   Updated: 2021/11/26 14:24:59 by bbordere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_strdup(const char *source)
{
	char	*dest;
	size_t	i;

	dest = malloc((ft_strlen(source) + 1) * sizeof(char));
	if (!dest)
		return (NULL);
	i = 0;
	while (source[i])
	{
		dest[i] = source[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*source;
	unsigned char	*dest;
	size_t			i;

	source = (unsigned char *) src;
	dest = (unsigned char *) dst;
	i = 0;
	if (!dst && !src)
		return (NULL);
	if (n == 0)
		return (dst);
	while (n--)
	{
		dest[i] = source[i];
		i++;
	}
	return (dst);
}

char	*ft_strjoin(char *s1, char *s2)
{
	size_t	lens1;
	size_t	lens2;
	char	*s3;

	lens1 = ft_strlen(s1);
	lens2 = ft_strlen(s2);
	s3 = malloc((lens1 + lens2 + 1) * sizeof(char));
	if (!s3)
		return (NULL);
	ft_memcpy(s3, s1, lens1);
	ft_memcpy(s3 + lens1, s2, lens2);
	s3[lens1 + lens2] = '\0';
	if (s1)
		free(s1);
	return (s3);
}
