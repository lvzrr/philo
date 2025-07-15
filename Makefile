NAME    := philo
SRCS    := main.c time.c init.c actions.c dinner.c monitor.c parsing.c        \
           threadhandle.c helpers.c ft_atoul.c monitor_h.c ft_isnumeric.c     \
           mutexhandle.c
OBJS    := $(SRCS:.c=.o)
CC      := cc
CFLAGS  := -Wall -Wextra -Werror
RM      := rm -f

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all
