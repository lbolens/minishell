# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lbolens <lbolens@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/30 15:38:04 by lbolens           #+#    #+#              #
#    Updated: 2025/10/09 17:45:28 by lbolens          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# =========================
# Minishell - Makefile
# =========================

# ---- Project ----
NAME := minishell

# ---- Compiler / Flags ----
CC := gcc
CFLAGS := -Wall -Wextra -Werror -Iheader -Ilibft -Iexec
LDFLAGS := -no-pie
LIBS := -lreadline

# ---- Libft ----
LIBFT_DIR := libft
LIBFT_A := $(LIBFT_DIR)/libft.a

# ---- Sources ----
MAIN_SRCS := \
	main/main.c \
	main/init_envp.c

PARSING_SRCS := \
	parsing/general_utils.c \
	parsing/general_utils_bis.c \
	parsing/commands/parser.c \
	parsing/commands/utils_commands.c \
	parsing/commands/parser_args.c \
	parsing/commands/parser_redir.c \
	parsing/expansion/variable_detection.c \
	parsing/expansion/expansion.c \
	parsing/expansion/expansion_build.c \
	parsing/expansion/expansion_utils.c \
	parsing/pre_parsing/pre_check.c \
	parsing/pre_parsing/utils_pre_check.c \
	parsing/tokenization/lists.c \
	parsing/tokenization/tokens.c \
	parsing/tokenization/utils_lists.c \
	parsing/tokenization/utils_tokens.c \
	parsing/tokenization/utils_token_extract.c \
	parsing/free.c \
	parsing/free_utils.c \
	manip_env/manip_env.c \
	manip_env/manip_env_array.c \
	manip_env/utils_manip_env.c \
	manip_env/utils_manip_env_bis.c \
	signals/signals.c \
	signals/signals_bis.c \
	parsing/quote_removal.c \
	parsing/quote_removal_utils.c

EXEC_SRCS := \
	exec/builtin/builtin_cd.c \
	exec/builtin/builtin_export.c \
	exec/builtin/builtin_unset.c \
	exec/builtin/builtin_simple.c \
	exec/builtin/utils_builtin.c \
	exec/builtin/utils_parse_export.c \
	exec/builtin/utils_builtin_bis.c \
	exec/external_command/exec_external_cmd.c \
	exec/external_command/path/path.c \
	exec/external_command/path/utils_path.c \
	exec/external_command/path/utils_path2.c \
	exec/external_command/path/utils_path3.c \
	exec/pipes/pipes.c \
	exec/pipes/single_exec.c \
	exec/pipes/utils_pipes.c \
	exec/pipes/utils_redir.c \
	exec/pipes/utils_redir_output.c \
	exec/pipes/pipes_spawn.c \
	exec/pipes/utils_spawn.c \
	exec/heredoc/heredoc.c \
	exec/heredoc/heredoc_signals.c

SRCS := $(MAIN_SRCS) $(PARSING_SRCS) $(EXEC_SRCS)
OBJS := $(SRCS:.c=.o)

# ---- Colors ----
GREEN := \\033[0;32m
YELLOW := \\033[1;33m
GRAY := \\033[0;37m
RESET := \\033[0m

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
	@printf "$(GREEN) ███╗   ███╗██╗███╗   ██╗██╗███████╗██╗  ██╗███████╗██╗     ██╗     $(RESET)\n"
	@printf "$(GREEN) ████╗ ████║██║████╗  ██║██║██╔════╝██║  ██║██╔════╝██║     ██║     $(RESET)\n"
	@printf "$(GREEN) ██╔████╔██║██║██╔██╗ ██║██║███████╗███████║█████╗  ██║     ██║     $(RESET)\n"
	@printf "$(GREEN) ██║╚██╔╝██║██║██║╚██╗██║██║╚════██║██╔══██║██╔══╝  ██║     ██║     $(RESET)\n"
	@printf "$(GREEN) ██║ ╚═╝ ██║██║██║ ╚████║██║███████║██║  ██║███████╗███████╗███████╗$(RESET)\n"
	@printf "$(GREEN) ╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═╝╚══════╝╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝$(RESET)\n\n"
	@printf "$(YELLOW)✨ Compilation terminée avec succès !$(RESET)\n"
