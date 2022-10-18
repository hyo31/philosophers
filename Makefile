NAME = philo

CC = gcc

CFLAGS = -Wall -Wextra -Werror

#CFLAGS += -g3 -fsanitize=thread

SRC = philo.c utils.c actions.c

OBJ = $(addprefix obj/,$(SRC:c=o))

OBJDIR = obj/

all: obj/ $(NAME)

obj/:
	@mkdir obj/

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ)

obj/%.o: src/%.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJ)

fclean:
	@rm -f $(OBJ)
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
