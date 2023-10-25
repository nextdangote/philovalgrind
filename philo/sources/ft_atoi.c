/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguede <aguede@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 19:26:07 by aguede            #+#    #+#             */
/*   Updated: 2023/10/25 17:00:14 by aguede           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	allerenvoiechacal(char *s, int i)
{
	int	renvoie;

	renvoie = 0;
	while (s[i] >= 48 && s[i] <= 57)
	{
		renvoie = renvoie * 10 + s[i] - 48;
		i++;
	}
	if (i == 0)
		ft_error_message(E_NOVALIDNBR);
	return (renvoie);
}

int	ft_atoi(const char *str)
{
	int		sign;
	int		i;
	int		fdp;
	char	*s;

	s = (char *)str;
	sign = 1;
	i = 0;
	while ((s[i] >= 9 && s[i] <= 13) || s[i] == 32)
	{
		i++;
	}
	if (s[i] == 45 || s[i] == 43)
	{
		if (s[i] == 45)
		{
			sign *= -1;
		}
		i++;
	}
	fdp = allerenvoiechacal(s, i);
	return (fdp * sign);
}
