NAME = philo 

SRCS = utilis.c main.c philo_do.c philo_utils.c

OBJS = $(SRCS:.c=.o)

HEADER = philo.h

CC = gcc

RM = rm -f

CFLAGS = -g -Wall -Wextra -Werror -I philo.h

all: $(NAME)

%.o:	%.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
		$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
		
clean:
		$(RM) $(OBJS)

fclean: clean
		$(RM) $(NAME)

re:		fclean all

.PHONY:	all clean fclean re