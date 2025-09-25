NAME = test_path

CC = gcc
CFLAGS = -Wall -Wextra -Werror -g3

# Directories
LIBFT_DIR = ../libft
PATH_DIR = external_command/path

# Source files (SEULEMENT path, pas built-ins)
PATH_SRCS = $(PATH_DIR)/path.c \
            $(PATH_DIR)/utils_path.c \
            $(PATH_DIR)/utils_path2.c \
            $(PATH_DIR)/utils_path3.c

SRCS = main.c $(PATH_SRCS)

OBJS = $(SRCS:.c=.o)
LIBFT = $(LIBFT_DIR)/libft.a
INCLUDES = -I$(LIBFT_DIR)

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT):
	@make -C $(LIBFT_DIR)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re