/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoi.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdelaby <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 08:52:44 by cdelaby           #+#    #+#             */
/*   Updated: 2019/10/07 08:53:54 by cdelaby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int				char_is_alpha(char c)
{
	if (c >= 48 && c <= 57)
		return (1);
	else
		return (0);
}

static int				char_to_int(const char *str, int i, int neg)
{
	unsigned int	final;

	final = 0;
	while (str[i] && char_is_alpha(str[i]))
	{
		if (neg == 1 && final > (unsigned int)2147483647)
			return (-1);
		else if (final > (unsigned int)2147483648)
			return (0);
		final = final * 10 + (str[i] - 48);
		i++;
	}
	return (final);
}

int						ft_atoi(const char *str)
{
	int			i;
	int			neg;
	long		s;

	i = 0;
	neg = 1;
	while (str[i] == '\t' || str[i] == '\n' || str[i] == '\r' || str[i] == '\v'
			|| str[i] == '\f' || str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			neg = -1;
		i++;
	}
	s = char_to_int(str, i, neg) * neg;
	return (s);
}
