/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threadhandle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 05:03:07 by jaicastr          #+#    #+#             */
/*   Updated: 2025/07/15 14:15:26 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static inline void	handle_err(int status, t_threadop op)
{
	if (!status)
		return ;
	if (status == EPERM || (status == EINVAL && (op == CREATE
				|| op == JOIN || op == DETACH)) || status == ESRCH
		|| status == EDEADLK)
		exit(EXIT_FAILURE);
}

void	thread_handler(pthread_t *thread, t_threadop op,
	void *(*fn)(void *), t_philo *philo)
{
	if (op == CREATE)
		handle_err(pthread_create(thread, NULL, fn, philo), op);
	else if (op == DETACH)
		handle_err(pthread_detach(*thread), op);
	else if (op == JOIN)
		handle_err(pthread_join(*thread, NULL), op);
	else
	{
		write(stderr->_fileno, "Wrong flag\n", 11);
		exit(EXIT_FAILURE);
	}
}

void	create_monitor(t_data *data)
{
	handle_err(
		pthread_create(&data->monitor, NULL, monitor, (void *)data),
		CREATE);
}
