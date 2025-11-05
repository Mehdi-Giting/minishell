# ==== minishell Makefile ====

NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f

SRCS = main.c find_in_path.c

OBJS = $(SRCS:.c=.o)

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

all: $(LIBFT) $(NAME)

$(LIBFT):
	@echo "🔧 Building libft..."
	@$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(OBJS) $(LIBFT)
	@echo "🧩 Linking $(NAME)..."
	@$(CC) $(CFLAGS) $(OBJS) -L$(LIBFT_DIR) -lft -o $(NAME)
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
