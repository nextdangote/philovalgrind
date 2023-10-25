NAME			= philo

SRCS			= sources/ft_action.c sources/ft_atoi.c sources/ft_checker.c sources/ft_create.c sources/ft_threading.c sources/ft_utils_2.c sources/ft_utils.c sources/main.c sources/ft_create_2.c

OBJS			= $(SRCS:.c=.o)

CC				= cc
RM				= rm -f
CFLAGS			= -Wno-unused-variable -o -Wall -Wextra -Werror -I.

all:			$(NAME)

$(NAME):		$(OBJS)
				$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

clean:
				$(RM) $(OBJS)

fclean:			clean
				$(RM) $(NAME)

re:				fclean $(NAME)

.PHONY:			all clean fclean re bonus
