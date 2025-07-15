/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 23:09:29 by jaicastr          #+#    #+#             */
/*   Updated: 2025/07/15 13:33:24 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static inline bool	check_integrity(int argc, char **argv)
{
	if (!ft_isnumeric(argv[1]) || !ft_isnumeric(argv[2])
		|| !ft_isnumeric(argv[3])
		|| !ft_isnumeric(argv[4])
		|| (argc >= 6 && !ft_isnumeric(argv[5])))
		return (false);
	return (true);
}

static inline t_data	check_timings(t_data out)
{
	if (out.tteat < 6e4 || out.ttsleep < 6e4
		|| out.ttdie < 6e4)
	{
		write(stderr->_fileno, "Time must be > 60ms\n", 20);
		return (free(out.forks), free(out.philos), (t_data){0});
	}
	return (out);
}

t_data	serialize(int argc, char **argv)
{
	t_data		out;

	out = (t_data){0};
	if (!check_integrity(argc, argv))
		return ((t_data){0});
	out.pnum = ft_atoul(argv[1]);
	out.forkc = out.pnum;
	out.forks = malloc(out.pnum * sizeof(t_fork));
	if (!out.forks)
		return ((t_data){0});
	out.philos = malloc(out.pnum * sizeof(t_philo));
	if (!out.philos)
		return (free(out.forks), (t_data){0});
	out.ttdie = ft_atoul(argv[2]) * 1e3;
	out.tteat = ft_atoul(argv[3]) * 1e3;
	out.ttsleep = ft_atoul(argv[4]) * 1e3;
	if (argc < 6)
		out.max_meals = SIZE_MAX;
	else
		out.max_meals = ft_atoul(argv[5]);
	return (check_timings(out));
}
