/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bharghaz <bharghaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 22:29:03 by bharghaz          #+#    #+#             */
/*   Updated: 2021/10/19 22:29:03 by bharghaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*res;
	char	*res_aux;

	if (s1 && s2)
	{
		res = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
		if (!res)
			return (NULL);
		res_aux = res;
		while (*s1)
			*res++ = *s1++;
		while (*s2)
			*res++ = *s2++;
		*res = '\0';
		return (res_aux);
	}
	return (NULL);
}
