/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 13:48:08 by jaicastr          #+#    #+#             */
/*   Updated: 2025/07/15 14:32:17 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	logger(t_philo *p, t_state status)
{
	size_t	elapsed;

	if (p->isfull)
		return ;
	mut_handler(&p->data->dataw_mut, LOCK);
	elapsed = (size_t)gett_ms() - p->data->time;
	if ((status == TAKE_FFORK || status == TAKE_SFORK)
		&& !finish_sim(p->data))
		printf("%-10lu %lu has taken a fork\n", elapsed, p->id);
	else if (status == EATING && !finish_sim(p->data))
		printf("%-10lu %lu is eating\n", elapsed, p->id);
	else if (status == SLEEPY && !finish_sim(p->data))
		printf("%-10lu %lu is sleeping\n", elapsed, p->id);
	else if (status == THINKING && !finish_sim(p->data))
		printf("%-10lu %lu is thinking\n", elapsed, p->id);
	else if (status == DEAD && !finish_sim(p->data))
		printf("%-10lu %lu died\n", elapsed, p->id);
	mut_handler(&p->data->dataw_mut, UNLOCK);
}

void	p_sleep(t_philo *philo)
{
	size_t	time;

	if (finish_sim(philo->data))
		return ;
	time = get_size(&philo->data->data_mut, &philo->data->ttsleep);
	logger(philo, SLEEPY);
	usleep(time);
}

void	eat(t_philo *p)
{
	size_t	tteat;
	size_t	max;

	if (get_bool(&p->pmut, &p->isfull))
		return ;
	tteat = get_size(&p->data->data_mut, &p->data->tteat);
	max = get_size(&p->data->data_mut, &p->data->max_meals);
	mut_handler(&p->first_fork->mutex, LOCK);
	logger(p, TAKE_FFORK);
	mut_handler(&p->second_fork->mutex, LOCK);
	logger(p, TAKE_SFORK);
	set_size(&p->pmut, &p->last_meal, (size_t)gett_ms());
	++p->nmeals;
	if (p->nmeals >= max)
		set_bool(&p->pmut, &p->isfull, true);
	logger(p, EATING);
	usleep(tteat);
	mut_handler(&p->first_fork->mutex, UNLOCK);
	mut_handler(&p->second_fork->mutex, UNLOCK);
}

void	think(t_philo *p, bool f)
{
	ssize_t	tthink;

	if (!f)
		logger(p, THINKING);
	if (p->data->pnum % 2 == 0)
		return ;
	tthink = p->data->tteat * 2 - p->data->ttsleep;
	if (tthink < 0)
		tthink = 0;
	usleep(tthink * .42);
}
