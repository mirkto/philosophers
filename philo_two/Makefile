NAME = philo_two
FLAGS = -Wall -Wextra -Werror
SOURCES = philo_two.c \
			ft_parser.c \
			ft_utils.c \
			ft_inits.c \
			ft_philo.c
OBJECTS = $(SOURCES:%.c=%.o)
HEADER = philo_two.h

all: $(NAME)

%.o: %.c $(HEADER)
	gcc $(FLAGS) -c $< -o $@

$(NAME): $(OBJECTS) $(HEADER)
	gcc $(FLAGS) $(SOURCES) -o $(NAME)

clean:
	rm -f $(OBJECTS)

fclean:	clean
	rm -f $(NAME)
	
re:	fclean all
