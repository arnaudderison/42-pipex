# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aderison <aderison@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/09 16:01:42 by aderison          #+#    #+#              #
#    Updated: 2024/05/11 01:28:47 by aderison         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
LIBFT = libft.a
LIBFT_I = ./lib/libft/include
PIPEX_I = ./include
CC = gcc
OBJ_DIR = obj
CFLAGS = -Wall -Wextra -Werror
INCLUDES = -I$(LIBFT_I) -I$(PIPEX_I)

# Colors
RED=\033[0;31m
GREEN=\033[0;32m
YELLOW=\033[1;33m
CYAN=\033[0;36m
NC=\033[0m

#Libft string
LIBFT_STRING = $(addprefix string/, ft_atoi.c ft_putchar_fd.c ft_putnbr_fd.c \
ft_split.c ft_strdup.c ft_strlcat.c ft_strmapi.c ft_strrchr.c ft_tolower.c \
ft_isalpha.c ft_putendl_fd.c ft_putptr.c ft_strchr.c ft_striteri.c ft_strlcpy.c \
ft_strncmp.c ft_strtrim.c ft_toupper.c ft_isprint.c ft_pointer.c ft_puthex_fd.c \
ft_putstr_fd.c ft_strlen.c ft_u_putnbr_fd.c ft_strnstr.c ft_strjoin.c)

#Libft number
LIBFT_NUM = $(addprefix number/, ft_isalnum.c ft_isascii.c ft_isdigit.c ft_itoa.c)

#Libft memory
LIBFT_MEM = $(addprefix memory/, ft_bzero.c ft_calloc.c ft_memchr.c ft_memcmp.c \
ft_memcpy.c ft_memmove.c ft_memset.c ft_free.c ft_free_matrice.c)

#Libft list
LIBFT_LST = $(addprefix list/, ft_lstadd_back_bonus.c ft_lstclear_bonus.c \
ft_lstiter_bonus.c ft_lstmap_bonus.c ft_lstsize_bonus.c ft_lstadd_front_bonus.c \
ft_lstdelone_bonus.c ft_lstlast_bonus.c ft_lstnew_bonus.c)

#Libft process
LIBFT_PROC = $(addprefix process/, ft_close_pipes.c ft_create_pipes.c)

#Libft ft_printf
LIBFT_PRINTF = ft_printf/ft_printf.c

# Libft sources
LIBFT_SRCS = $(addprefix lib/libft/src/, $(LIBFT_STRING) $(LIBFT_NUM) $(LIBFT_MEM) \
$(LIBFT_LST) $(LIBFT_PRINTF) $(LIBFT_PROC))
LIBFT_OBJS = $(LIBFT_SRCS:%c=obj/%o)

#pipex srcs
PIPEX_PATH = $(addprefix path/, path_exist.c)
PIPEX_STRUCT = $(addprefix struct/, init_struct.c)
PIPEX_FAIL = $(addprefix fail/, exit.c)
PIPEX_UTILS = $(addprefix utils/, $(PIPEX_PATH) $(PIPEX_STRUCT) $(PIPEX_FAIL))
PIPEX_SRCS = $(addprefix src/, main.c $(PIPEX_UTILS))
PIPEX_OBJS = $(PIPEX_SRCS:%c=obj/%o)

# Compilation rules
all: $(LIBFT) $(NAME)

$(LIBFT): $(LIBFT_OBJS)
	@ar rcs $(LIBFT) $^
	@echo "\n${YELLOW}Library $(LIBFT) created.${NC}"

$(NAME): $(PIPEX_OBJS) $(LIBFT)
	@$(CC) $(CFLAGS) $^ -o $@
	@echo "\n${YELLOW}Executable $(NAME) created.${NC}"

obj/%.o: %.c
	@mkdir -p $(dir $@)
	@printf "${CYAN}\rCompiling $<...       ${NC}"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@rm -rf obj
	@echo "${GREEN}Object files cleaned.${NC}"

fclean: clean
	@rm -f libft.a
	@rm -f pipex
	@echo "${RED}All files removed.${NC}"

re: fclean all

.PHONY: all clean fclean re
