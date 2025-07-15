/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 13:17:08 by jaicastr          #+#    #+#             */
/*   Updated: 2025/07/15 13:26:09 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_bool(t_mut *mut, bool *dest, bool val)
{
	mut_handler(mut, LOCK);
	*dest = val;
	mut_handler(mut, UNLOCK);
}

bool	get_bool(t_mut *mut, bool *dest)
{
	bool	ret;

	mut_handler(mut, LOCK);
	ret = *dest;
	mut_handler(mut, UNLOCK);
	return (ret);
}

void	set_size(t_mut *mut, size_t *dest, size_t val)
{
	mut_handler(mut, LOCK);
	*dest = val;
	mut_handler(mut, UNLOCK);
}

size_t	get_size(t_mut *mut, size_t *dest)
{
	size_t	ret;

	mut_handler(mut, LOCK);
	ret = *dest;
	mut_handler(mut, UNLOCK);
	return (ret);
}

bool	finish_sim(t_data *data)
{
	return (get_bool(&data->data_mut, &data->endit));
}
