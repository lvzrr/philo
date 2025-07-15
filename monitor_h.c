/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_h.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 15:31:34 by jaicastr          #+#    #+#             */
/*   Updated: 2025/07/15 15:36:09 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	waitall_run(t_data *data)
{
	size_t	r;

	r = 0;
	while (r != data->pnum)
		r = get_size(&data->data_mut, &data->rnum);
}

void	increase_c(t_mut *mut, size_t *to_inc)
{
	mut_handler(mut, LOCK);
	(*to_inc)++;
	mut_handler(mut, UNLOCK);
}
