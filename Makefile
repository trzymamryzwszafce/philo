NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror
SRC = main.c init.c monitor.c routine.c routine_utils.c utils.c init_utils.c
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
