/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_helpe1_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohimi <mohimi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 15:40:09 by mohimi            #+#    #+#             */
/*   Updated: 2024/10/11 18:26:29 by mohimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_bonus.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && (s1[i] != '\0' || s2[i] != '\0'))
	{
		if ((unsigned char) s1[i] != (unsigned char) s2[i])
			return ((unsigned char) s1[i] - (unsigned char) s2[i]);
		i++;
	}
	return (0);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while ((s1[i] != '\0' || s2[i] != '\0'))
	{
		if ((unsigned char) s1[i] != (unsigned char) s2[i])
			return ((unsigned char) s1[i] - (unsigned char) s2[i]);
		i++;
	}
	return (0);
}

static int	sersh(const char *str, char c)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0' && c != str[i])
		i++;
	if (c == str[i])
		return (1);
	else
		return (0);
}

char	*ft_strtrim(const char *s1, const char *set)
{
	size_t	start;
	size_t	end;

	start = 0;
	end = ft_strlen(s1);
	if (s1 == NULL || set == NULL)
		return (NULL);
	while (start < end && sersh(set, s1[start]))
		start++;
	if (start >= end)
		return (ft_strdup(""));
	while (end > 0 && sersh(set, s1[end - 1]))
		end--;
	return (ft_substr(s1, start, end - start));
}

int	ft_atoi(const char *str)
{
	int		i;
	int		s;
	long	r;
	char	*tmp;

	(1) && (i = 0, s = 1, r = 0);
	tmp = ft_strtrim(str, " ");
	if (tmp[i] == '-' || tmp[i] == '+')
		if (tmp[i++] == '-')
			s *= -1;
	while (tmp[i])
	{
		r = r * 10 + (tmp[i] - 48);
		if ((r * s > 2147483647) || (r * s < -2147483648)
			|| (tmp[i] < '0' || tmp[i] > '9'))
			ft_error_message("Error: Invalid color!!");
		i++;
	}
	return (r * s);
}
