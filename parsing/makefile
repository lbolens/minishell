NAME = minishell

SRCS = main_parsing.c general_utils.c \
       commands/parser.c commands/utils_commands.c \
       pre_parsing/pre_check.c pre_parsing/utils_pre_check.c \
       tokenization/tokens.c tokenization/lists.c \
       tokenization/utils_tokens.c tokenization/utils_lists.c

OBJS = $(SRCS:.c=.o)
CFLAGS = -Wall -Wextra -Werror
LIBS = -lreadline

$(NAME): $(OBJS)
	gcc $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean $(NAME)