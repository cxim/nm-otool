/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnarwhal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/06 16:20:51 by mnarwhal          #+#    #+#             */
/*   Updated: 2019/09/11 17:53:45 by mnarwhal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char	*buf;
	unsigned char	*srcbuf;
	size_t			i;

	i = 0;
	buf = (unsigned char*)dst;
	srcbuf = (unsigned char*)src;
	while (i < n)
	{
		buf[i] = srcbuf[i];
		if (buf[i] == (unsigned char)c)
			return (dst + i + 1);
		i++;
	}
	return (NULL);
}
