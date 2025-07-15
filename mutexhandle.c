/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutexhandle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 04:45:15 by jaicastr          #+#    #+#             */
/*   Updated: 2025/07/15 14:15:31 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static inline void	handle_err(int status, t_mutops op)
{
	if (!status)
		return ;
	if ((status == EINVAL && ((op == LOCK || op == UNLOCK)
				|| op == INIT)) || status == EDEADLK || status == EPERM
		|| status == ENOMEM || status == EBUSY)
		exit(EXIT_FAILURE);
}

void	mut_handler(t_mut *mut, t_mutops op)
{
	if (!mut)
		return ;
	if (op == LOCK)
		handle_err(pthread_mutex_lock(mut), op);
	else if (op == UNLOCK)
		handle_err(pthread_mutex_unlock(mut), op);
	else if (op == INIT)
		handle_err(pthread_mutex_init(mut, NULL), op);
	else if (op == DESTROY)
		handle_err(pthread_mutex_destroy(mut), op);
	else
	{
		write(stderr->_fileno, "Wrong flag\n", 11);
		exit(EXIT_FAILURE);
	}
}
