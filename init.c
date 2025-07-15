/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 05:44:10 by jaicastr          #+#    #+#             */
/*   Updated: 2025/07/15 14:35:29 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	assign_fork(t_philo *p)
{
	if (p->id % 2 == 0)
	{
		p->first_fork = &p->data->forks[p->id];
		p->second_fork = &p->data->forks[(p->id + 1) % p->data->pnum];
	}
	else
	{
		p->first_fork = &p->data->forks[(p->id + 1) % p->data->pnum];
		p->second_fork = &p->data->forks[p->id];
	}
}

void	philo_init(t_data *data)
{
	size_t	i;

	i = 0;
	while (i < data->pnum)
	{
		data->philos[i] = (t_philo){0};
		data->philos[i].id = i;
		data->philos[i].data = data;
		assign_fork(data->philos + i);
		mut_handler(&data->philos[i].pmut, INIT);
		++i;
	}
}

void	init_sim(t_data *data)
{
	size_t	i;

	i = 0;
	data->synced = false;
	mut_handler(&data->data_mut, INIT);
	mut_handler(&data->dataw_mut, INIT);
	while (i < data->pnum)
	{
		mut_handler(&data->forks[i].mutex, INIT);
		data->forks[i].id = i;
		++i;
	}
}
