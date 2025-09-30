# =========================
# Minishell - Makefile
# =========================

# ---- Project ----
NAME    := minishell

# ---- Compiler / Flags ----
CC      := gcc
CFLAGS  := -Wall -Wextra -Werror -Iheader -Ilibft -Iexec
# (optionnel) ajoute ton include pour readline si besoin:
# CFLAGS += -I/usr/include/readline
LDFLAGS := -no-pie
LIBS    := -lreadline

# ---- Libft ----
LIBFT_DIR := libft
LIBFT_A   := $(LIBFT_DIR)/libft.a

# ---- Sources ----
MAIN_SRCS := \
	main/main.c \
	main/init_envp.c

PARSING_SRCS := \
	parsing/general_utils.c \
	parsing/commands/parser.c \
	parsing/commands/utils_commands.c \
	parsing/expansion/variable_detection.c \
	parsing/pre_parsing/pre_check.c \
	parsing/pre_parsing/utils_pre_check.c \
	parsing/tokenization/lists.c \
	parsing/tokenization/tokens.c \
	parsing/tokenization/utils_lists.c \
	parsing/tokenization/utils_tokens.c \
	parsing/free.c \
	manip_env/manip_env.c \
	manip_env/utils_manip_env.c
# NE PAS inclure parsing/main_parsing.c (main de test)

EXEC_SRCS := \
	exec/builtin/builtin_cd.c \
	exec/builtin/builtin_export.c \
	exec/builtin/builtin_unset.c \
	exec/builtin/builtin_simple.c \
	exec/builtin/utils_builtin.c \
	exec/builtin/utils_parse_export.c \
	exec/external_command/exec_external_cmd.c \
	exec/external_command/path/path.c \
	exec/external_command/path/utils_path.c \
	exec/external_command/path/utils_path2.c \
	exec/external_command/path/utils_path3.c

SRCS := $(MAIN_SRCS) $(PARSING_SRCS) $(EXEC_SRCS)
OBJS := $(SRCS:.c=.o)

# ---- Rules ----
.PHONY: all clean fclean re libft

all: $(NAME)

$(NAME): $(LIBFT_A) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT_A) $(LIBS) $(LDFLAGS) -o $@

$(LIBFT_A):
	$(MAKE) -C $(LIBFT_DIR)

clean:
	$(RM) $(OBJS)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	$(RM) $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean || true

re: fclean all
