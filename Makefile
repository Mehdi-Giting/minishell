# ==== minishell Makefile ====

NAME = minishell
CC = cc

CFLAGS = -Wall -Wextra -Werror
LDFLAGS = -lreadline -lncurses

RM = rm -f

# Dossier pour les fichiers objets
OBJ_DIR = obj

# Répertoires
EXEC_DIR = src/execution
BUILTIN_DIR = src/builtins

# Fichiers principaux
SRCS = main.c

# Fichiers d'exécution
SRCS += $(EXEC_DIR)/executor.c \
        $(EXEC_DIR)/executor_simple.c \
        $(EXEC_DIR)/executor_pipeline.c \
		$(EXEC_DIR)/executor_pipeline_utils.c \
        $(EXEC_DIR)/path_resolver.c \
		$(EXEC_DIR)/path_error_exit.c \
        $(EXEC_DIR)/redirections.c \
        $(EXEC_DIR)/signals.c \
		$(EXEC_DIR)/heredoc.c

# Fichiers des builtins
SRCS += $(BUILTIN_DIR)/builtin_executor.c \
        $(BUILTIN_DIR)/builtin_cd.c \
        $(BUILTIN_DIR)/builtin_echo.c \
        $(BUILTIN_DIR)/builtin_env.c \
        $(BUILTIN_DIR)/builtin_exit.c \
        $(BUILTIN_DIR)/builtin_export.c \
		$(BUILTIN_DIR)/builtin_export2.c \
        $(BUILTIN_DIR)/builtin_pwd.c \
        $(BUILTIN_DIR)/builtin_unset.c \
        $(BUILTIN_DIR)/env_utils.c

# Fichiers du parser (inchangés)
PARSER_DIR = parser

PARSER_SRCS = $(PARSER_DIR)/lexer/lexer.c \
              $(PARSER_DIR)/lexer/lexer_operators.c \
              $(PARSER_DIR)/lexer/lexer_words.c \
              $(PARSER_DIR)/lexer/lexer_utils.c \
              $(PARSER_DIR)/tokens/token.c \
              $(PARSER_DIR)/tokens/token_utils.c \
              $(PARSER_DIR)/parser/parser.c \
              $(PARSER_DIR)/parser/parser_redirections.c \
              $(PARSER_DIR)/parser/parser_utils.c \
              $(PARSER_DIR)/parser/syntax_checker.c \
              $(PARSER_DIR)/expander/expander.c \
              $(PARSER_DIR)/expander/expander_string.c \
              $(PARSER_DIR)/expander/expander_utils.c \
              $(PARSER_DIR)/utils/builtin_detector.c \
              $(PARSER_DIR)/utils/memory_cleaner.c

SRCS += $(PARSER_SRCS)

# Les .o gardent la même structure de dossiers dans obj/
OBJS = $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

all: $(LIBFT) $(NAME)

$(LIBFT):
# 	@echo "🔧 Building libft..."
	@$(MAKE) -C $(LIBFT_DIR)

# Créer les sous-dossiers nécessaires dans obj/
$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
# 	@echo "🔨 Compiling $<..."
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS) $(LIBFT)
	@echo "🧩 Linking $(NAME)..."
	@$(CC) $(OBJS) -L$(LIBFT_DIR) -lft $(LDFLAGS) -o $(NAME)
	@echo "✅ Build complete!"

clean:
	@echo "🧹 Cleaning object files..."
	@$(RM) -r $(OBJ_DIR)
	@$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	@echo "🗑  Removing $(NAME)..."
	@$(RM) $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re