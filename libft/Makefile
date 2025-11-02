# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mehdi <mehdi@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/02 16:40:19 by ellabiad          #+#    #+#              #
#    Updated: 2025/11/02 02:33:25 by mehdi            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
#                                   SETTINGS                                   #
# **************************************************************************** #

NAME = libft.a

CC = cc
CFLAGS = -Wall -Wextra -Werror
AR = ar rcs
RM = rm -f

SRCS = ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c \
       ft_strlen.c ft_memset.c ft_memcpy.c ft_memmove.c ft_strlcpy.c \
       ft_strlcat.c ft_toupper.c ft_tolower.c ft_strchr.c ft_strncmp.c \
       ft_memchr.c ft_memcmp.c ft_strnstr.c ft_calloc.c ft_atoi.c \
       ft_strdup.c ft_substr.c ft_strjoin.c ft_bzero.c ft_strtrim.c \
       ft_strrchr.c ft_split.c ft_itoa.c ft_strmapi.c ft_striteri.c \
       ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
       ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c \
       ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c \
       ft_free_tab.c

GNL_SRCS = get_next_line/get_next_line.c get_next_line/get_next_line_utils.c

PRINTF_SRCS = ft_printf/ft_printf.c ft_printf/src/utils_hex.c \
              ft_printf/src/utils_string.c

ALL_SRCS = $(SRCS) $(GNL_SRCS) $(PRINTF_SRCS)
OBJS = $(ALL_SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	@echo "📦 Archiving $(NAME)..."
	@$(AR) $(NAME) $(OBJS)
	@echo "✅ Build complete!"

%.o: %.c
	@echo "🛠  Compiling $<"
	@$(CC) $(CFLAGS) -I . -I ft_printf -I ft_printf/src -I get_next_line -c $< -o $@

clean:
	@echo "🧹 Cleaning object files..."
	@$(RM) $(OBJS)

fclean: clean
	@echo "🗑  Removing $(NAME)..."
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re