# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: arnaud <arnaud@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/02 19:58:45 by arnaud            #+#    #+#              #
#    Updated: 2024/01/02 20:30:54 by arnaud           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
LIBFT = libft.a
CC = gcc
CFLAGS = -Wall -Wextra -Werror
LIBFT_DIR = ./src/libft/libft
FT_PRINTF_DIR = ./src/libft/ft_printf
INCLUDES = -I$(LIBFT_DIR) -I $(FT_PRINTF_DIR)/includes

# Colors
RED=\033[0;31m
GREEN=\033[0;32m
YELLOW=\033[1;33m
CYAN=\033[0;36m
NC=\033[0m

# Libft sources
LIBFT_SRCS = $(wildcard $(LIBFT_DIR)/*.c)
LIBFT_OBJS = $(LIBFT_SRCS:.c=.o)

# ft_printf sources
FT_PRINTF_SRCS = $(wildcard $(FT_PRINTF_DIR)/*.c) \
				$(wildcard $(FT_PRINTF_DIR)/srcs/*.c)
FT_PRINTF_OBJS = $(FT_PRINTF_SRCS:.c=.o)

#pipex sources
PIPEX_SRCS = $(wildcard ./src/*.c) \
			$(wildcard ./src/pipex/*.c)
PIPEX_OBJS = $(PIPEX_SRCS:.c=.o)

# Compilation rules
all: $(LIBFT) $(NAME) 

$(LIBFT): $(LIBFT_OBJS) $(FT_PRINTF_OBJS)
	@ar rcs $(LIBFT) $^
	@echo "${YELLOW}Library $(LIBFT) created.${NC}"

$(NAME): $(PIPEX_OBJS) $(LIBFT)
	@$(CC) $(CFLAGS) $^ -o $@
	@echo "${YELLOW}Executable $(NAME) created.${NC}"

%.o: %.c
	@echo "${CYAN}Compiling $<...${NC}"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@rm -f $(LIBFT_OBJS) $(FT_PRINTF_OBJS) $(PIPEX_OBJS)
	@echo "${GREEN}Object files cleaned.${NC}"

fclean: clean
	@rm -f $(LIBFT) $(NAME)
	@echo "${RED}All files removed.${NC}"

re: fclean all

.PHONY: all clean fclean re