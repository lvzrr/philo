/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isnumeric.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 23:12:35 by jaicastr          #+#    #+#             */
/*   Updated: 2025/07/09 23:12:36 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

unsigned char	ft_isnumeric(const char *__restrict__ s)
{
	unsigned char	has_digit;

	if (!s || !*s)
		return (0);
	has_digit = 0;
	while (*s)
	{
		if (*s >= '0' && *s <= '9')
			has_digit = 1;
		else if (*s != '+')
			return (0);
		s++;
	}
	return (has_digit);
}
