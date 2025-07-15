/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 12:53:26 by jaicastr          #+#    #+#             */
/*   Updated: 2025/07/15 15:34:21 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	waitall(t_data *data)
{
	while (!get_bool(&data->data_mut, &data->synced))
		;
}

void	*dinner_sim(void *p)
{
	t_philo	*philo;

	if (!p)
		return (NULL);
	philo = (t_philo *)p;
	set_size(&philo->pmut, &philo->last_meal, (size_t)gett_ms());
	increase_c(&philo->data->data_mut, &philo->data->rnum);
	dsync(philo);
	waitall(philo->data);
	while (!finish_sim(philo->data))
	{
		if (philo->isfull)
			break ;
		eat(philo);
		p_sleep(philo);
		think(philo, false);
	}
	return (NULL);
}

void	*dinner_alone(void *p)
{
	t_philo	*philo;

	if (!p)
		return (NULL);
	philo = (t_philo *)p;
	increase_c(&philo->data->data_mut, &philo->data->rnum);
	waitall(philo->data);
	set_size(&philo->pmut, &philo->last_meal, (size_t)gett_ms());
	logger(philo, TAKE_FFORK);
	while (!finish_sim(philo->data))
		usleep(philo->data->ttsleep);
	return (NULL);
}

void	dinner_init(t_data *data)
{
	size_t	i;

	i = 0;
	if (!data->max_meals || !data->pnum)
		return ;
	if (data->pnum == 1)
		thread_handler(&data->philos[0].thread_id, CREATE,
			dinner_alone, data->philos);
	else
	{
		while (i < data->pnum)
		{
			thread_handler(&data->philos[i].thread_id, CREATE,
				dinner_sim, data->philos + i);
			i++;
		}
	}
	create_monitor(data);
	data->time = gett_ms();
	set_bool(&data->data_mut, &data->synced, true);
	i = 0;
	while (i < data->pnum)
		thread_handler(&data->philos[i++].thread_id, JOIN, NULL, NULL);
	set_bool(&data->data_mut, &data->endit, true);
	thread_handler(&data->monitor, JOIN, NULL, NULL);
}
