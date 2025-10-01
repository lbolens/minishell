# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lbolens <lbolens@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/30 15:38:04 by lbolens           #+#    #+#              #
#    Updated: 2025/09/30 16:05:16 by lbolens          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# =========================
# Minishell - Makefile
# =========================

# ---- Project ----
NAME    := minishell

# ---- Compiler / Flags ----
CC      := gcc
CFLAGS  := -Wall -Wextra -Werror -Iheader -Ilibft -Iexec
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
	manip_env/utils_manip_env.c \
	signals/signals.c

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

# ---- Colors ----
GREEN   := \033[0;32m
YELLOW  := \033[1;33m
GRAY    := \033[0;37m
RESET   := \033[0m

# ---- Silence ----
.SILENT:

# ---- Rules ----
.PHONY: all clean fclean re libft animation progress

all: $(NAME)

$(NAME): $(LIBFT_A) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT_A) $(LIBS) $(LDFLAGS) -o $@
	$(MAKE) --no-print-directory progress
	$(MAKE) --no-print-directory animation

$(LIBFT_A):
	@$(MAKE) --no-print-directory -C $(LIBFT_DIR)

clean:
	$(RM) $(OBJS)
	@$(MAKE) --no-print-directory -C $(LIBFT_DIR) clean

fclean: clean
	$(RM) $(NAME)
	@$(MAKE) --no-print-directory -C $(LIBFT_DIR) fclean || true

re: fclean all

# ---- Progress Bar (animated & colorful) ----
progress:
	@printf "\nCompilation en cours : "
	@for i in 1 2 3 4 5 6 7 8 9 10; do \
		done_bar=$$(printf "$(GREEN)%0.s#$(RESET)" $$(seq 1 $$i)); \
		remain_bar=$$(printf "$(GRAY)%0.s-$(RESET)" $$(seq $$i 9)); \
		percent=$$((i*10)); \
		printf "\rCompilation en cours : [$$done_bar$$remain_bar] $$percent%%"; \
		sleep 0.1; \
	done; \
	printf "\n\n"

# ---- Animation ----
animation:
	@echo "$(GREEN)   ███╗   ███╗██╗███╗   ██╗██╗███████╗██╗  ██╗███████╗██╗     ██╗     $(RESET)"
	@echo "$(GREEN)   ████╗ ████║██║████╗  ██║██║██╔════╝██║  ██║██╔════╝██║     ██║     $(RESET)"
	@echo "$(GREEN)   ██╔████╔██║██║██╔██╗ ██║██║███████╗███████║█████╗  ██║     ██║     $(RESET)"
	@echo "$(GREEN)   ██║╚██╔╝██║██║██║╚██╗██║██║╚════██║██╔══██║██╔══╝  ██║     ██║     $(RESET)"
	@echo "$(GREEN)   ██║ ╚═╝ ██║██║██║ ╚████║██║███████║██║  ██║███████╗███████╗███████╗$(RESET)"
	@echo "$(GREEN)   ╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═╝╚══════╝╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝$(RESET)"
	@echo ""
	@echo "$(YELLOW)✨ Compilation terminée avec succès !$(RESET)"
