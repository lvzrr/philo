/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 15:26:56 by jaicastr          #+#    #+#             */
/*   Updated: 2025/07/15 15:29:32 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	philo_died(t_philo *p)
{
	size_t	elapsed;
	bool	full;

	elapsed = gett_ms() - get_size(&p->pmut, &p->last_meal);
	full = get_bool(&p->pmut, &p->isfull);
	if (elapsed > p->data->ttdie / 1e3 && !full)
		return (true);
	return (false);
}

void	*monitor(void *d)
{
	t_data	*data;
	size_t	i;

	if (!d)
		return (NULL);
	data = (t_data *)d;
	waitall_run(data);
	i = 0;
	while (!finish_sim(data))
	{
		while (i < data->pnum && !finish_sim(data))
		{
			if (philo_died(data->philos + i))
			{
				logger(data->philos + i, DEAD);
				set_bool(&data->data_mut, &data->endit, true);
				return (NULL);
			}
			i++;
		}
		i = 0;
	}
	return (NULL);
}
