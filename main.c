/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 23:09:42 by jaicastr          #+#    #+#             */
/*   Updated: 2025/07/15 14:35:23 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	clean(t_data *data)
{
	size_t	i;

	i = 0;
	while (i < data->pnum)
	{
		mut_handler(&data->philos[i].pmut, DESTROY);
		mut_handler(&data->forks[i].mutex, DESTROY);
		i++;
	}
	mut_handler(&data->data_mut, DESTROY);
	mut_handler(&data->dataw_mut, DESTROY);
	free(data->forks);
	free(data->philos);
}

int	main(int argc, char **argv)
{
	t_data		state;

	if (argc < 5)
	{
		write(stderr->_fileno, "Usage: <number_of_philosophers> "
			"<size_to_die> <size_to_eat> <size_to_sleep> "
			"[max meals]\n", 32 + 44 + 12);
		return (EXIT_FAILURE);
	}
	state = serialize(argc, argv);
	if (!state.pnum && !state.ttdie && !state.ttsleep && !state.forks
		&& !state.tteat)
		return (write(stderr->_fileno, "Invalid args\n", 13), EXIT_FAILURE);
	init_sim(&state);
	philo_init(&state);
	dinner_init(&state);
	clean(&state);
	return (EXIT_SUCCESS);
}
