/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 23:09:54 by jaicastr          #+#    #+#             */
/*   Updated: 2025/07/15 13:47:58 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	gett_ms(void)
{
	t_time	t;

	(void)gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

void	dsync(t_philo *p)
{
	if (p->data->pnum % 2 == 0)
	{
		if (p->id % 2 == 0)
			usleep(30);
	}
	else
	{
		if (p->id % 2)
			think(p, true);
	}
}
