/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 23:13:38 by jaicastr          #+#    #+#             */
/*   Updated: 2025/07/15 15:34:46 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <string.h>
# include <stdbool.h>
# include <sys/time.h>
# include <stddef.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdint.h>
# include <stdio.h>
# include <limits.h>
# include <errno.h>

typedef struct timeval			t_time;
typedef pthread_mutex_t			t_mut;
typedef struct s_data			t_data;

typedef enum e_state
{
	TAKE_FFORK,
	TAKE_SFORK,
	EATING,
	SLEEPY,
	THINKING,
	DEAD,
}	t_state;

typedef struct s_fork
{
	size_t			id;
	t_mut			mutex;
}	t_fork;

typedef struct s_philo
{
	size_t		id;
	pthread_t	thread_id;
	t_state		state;
	size_t		nmeals;
	size_t		last_meal;
	bool		isdead;
	bool		isfull;
	t_fork		*first_fork;
	t_fork		*second_fork;
	t_data		*data;
	t_mut		pmut;
}	t_philo;

typedef enum e_fstate
{
	F_USED,
	F_FREE,
}	t_fstate;

struct s_data
{
	size_t				pnum;
	size_t				rnum;
	size_t				ttdie;
	size_t				tteat;
	size_t				ttsleep;
	size_t				forkc;
	size_t				max_meals;
	t_fork				*forks;
	t_philo				*philos;
	size_t				time;
	bool				endit;
	bool				synced;
	t_mut				data_mut;
	t_mut				dataw_mut;
	pthread_t			monitor;
};

typedef enum e_mutex
{
	LOCK,
	UNLOCK,
	DESTROY,
	INIT,
}	t_mutops;

typedef enum e_thread
{
	CREATE,
	JOIN,
	DETACH,
}	t_threadop;

size_t			ft_atoul(const char *str);
unsigned char	ft_isnumeric(const char *__restrict__ s);
t_data			serialize(int argc, char **argv);
size_t			gett_ms(void);
void			mut_handler(t_mut *mut, t_mutops op);
void			thread_handler(pthread_t *thread, t_threadop op,
					void *(*fn)(void *), t_philo *philo);
void			philo_init(t_data *data);
void			set_bool(t_mut *mut, bool *dest, bool val);
bool			get_bool(t_mut *mut, bool *dest);
void			set_size(t_mut *mut, size_t *dest, size_t val);
size_t			get_size(t_mut *mut, size_t *dest);
void			logger(t_philo *p, t_state status);
void			p_sleep(t_philo *philo);
bool			finish_sim(t_data *data);
void			*dinner_sim(void *p);
void			dinner_init(t_data *data);
void			eat(t_philo *p);
void			init_sim(t_data *data);
void			think(t_philo *p, bool a);
void			increase_c(t_mut *mut, size_t *to_inc);
void			waitall_run(t_data *data);
void			*monitor(void *d);
void			dsync(t_philo *p);
void			create_monitor(t_data *data);
#endif
