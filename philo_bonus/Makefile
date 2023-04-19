CFLAGS = #-Wall -Werror -Wextra #-fsanitize=thread
NAME = philo_bonus
RM = rm -rf
SRC = ft_atoi.c ft_work.c main_philo.c ft_philo_init.c ft_philo.c check_args.c ft_end_life.c
OBJ = $(SRC:.c=.o)

$(NAME): $(OBJ)
	@$(CC) -Wno-deprecated-declarations $(CFLAGS) $(OBJ) -o $(NAME)

%.o: %.c
	$(CC) -Wno-deprecated-declarations $(CFLAGS) -o $@ -c $<

all: $(NAME)

clean:
	$(RM) $(OBJ) $(BOBJ)

fclean: clean
	$(RM) $(NAME) $(BONUS)

re: fclean all

.PHONY: clean fclean re bonus all