NAME = test_builtins
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g3
LIBFT_DIR = ../libft
BUILTIN_DIR = builtin

SRCS = main_builtins.c \
       $(BUILTIN_DIR)/builtin_simple.c \
       $(BUILTIN_DIR)/utils_builtin.c
INCLUDES = -I$(LIBFT_DIR)

all: $(NAME)

$(NAME): $(SRCS)
	$(CC) $(CFLAGS) $(INCLUDES) $(SRCS) $(LIBFT_DIR)/libft.a -o $(NAME)

clean:
	rm -f $(NAME)

fclean: clean

re: fclean all

.PHONY: all clean fclean re