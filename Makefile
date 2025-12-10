# ==== minishell Makefile ====

NAME = minishell
CC = cc

CFLAGS = -Wall -Wextra -Werror
LDFLAGS = -lreadline -lncurses

RM = rm -f

SRCS = main.c \
	   mehdi/find_in_path.c \
	   mehdi/execution.c \
	   mehdi/redirections_exec.c \
	   mehdi/execute_pipes.c \
	   mehdi/signals.c \
	   mehdi/exec_builtin.c \
	   mehdi/builtin_list/ft_cd.c \
	   mehdi/builtin_list/ft_echo.c \
	   mehdi/builtin_list/ft_env.c \
	   mehdi/builtin_list/ft_exit.c \
	   mehdi/builtin_list/ft_export.c \
	   mehdi/builtin_list/ft_pwd.c \
	   mehdi/builtin_list/ft_unset.c \
	   mehdi/builtin_list/utils.c \
	   kais/built.c \
	   kais/read_command.c \
	   kais/redir2.c \
	   kais/redirection.c \
	   kais/split.c \
	   kais/tokens.c \
	   kais/utils.c \
	   kais/quotes.c

OBJS = $(SRCS:.c=.o)

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

all: $(LIBFT) $(NAME)

$(LIBFT):
	@echo "🔧 Building libft..."
	@$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(OBJS) $(LIBFT)
	@echo "🧩 Linking $(NAME)..."
	@$(CC) $(OBJS) -L$(LIBFT_DIR) -lft $(LDFLAGS) -o $(NAME)
	@echo "✅ Build complete!"

clean:
	@echo "🧹 Cleaning object files..."
	@$(RM) $(OBJS)
	@$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	@echo "🗑  Removing $(NAME)..."
	@$(RM) $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
