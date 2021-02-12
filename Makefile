NAME = philo_one
FLAGS = -Wall -Wextra -Werror
SOURCES = philo_one.c parser.c utils.c init_param.c
OBJECTS = $(SOURCES:%.c=%.o)
HEADER = philo_one.h

all: $(NAME)

$(NAME): $(OBJECTS) $(HEADER)
	gcc $(FLAGS) $(SOURCES) -o $(NAME)

%.o: %.c $(HEADER)
	gcc $(FLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS)

fclean:	clean
	rm -f $(NAME)
	
re:	fclean all
