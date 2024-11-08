# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: AleXwern <AleXwern@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/11 23:38:19 by AleXwern          #+#    #+#              #
#    Updated: 2024/11/05 19:19:15 by AleXwern         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= libft.a
FLAG	= -m64 -no-pie -Wall -Wextra -Werror
SRC		= 
TEST	= $(addprefix ./build/,$(TESTS))
OBJ		= $(addprefix ./obj/,$(SRC:.c=.o))
LIBFT	= Libft_ASM.a
INCLS	= -I ./includes
GREEN	= \033[0;32m
PURPLE	= \033[0;35m
STOP	= \033[0m
TEMP0	= 0

.PHONY: all clean fclean re libft

all: $(NAME)

./obj/%.o:./tests/%.c
	@echo "Compiling $(GREEN)$@$(STOP)"
	@mkdir -p obj
	@g++ $(FLAG) -c $< -o $@ $(INCLS)

libft:
	@make -C libft_asm objonly
	@make -C libftc
	@make -C libgfx

libftall:
	@make -C libft_asm objonly
	@make -C libftc
	@make -C ft_malloc
	@make -C libax
	@make -C libgfx

everything: libftall
	@echo "Building $(PURPLE)Libft$(STOP) libraries"
	@mkdir -p build
	@cp libftc/libft.a build
	@cp Libft_ASM/includes/* includes
	@cp libftc/includes/* includes
	@cp libax/libax.a build
	@cp libax/includes/* includes
	@cp libgfx/libgfx.a build
	@cp libgfx/includes/* includes
	@cp ft_malloc/libft_malloc.so build
	@cp ft_malloc/includes/* includes

$(NAME): libft
	@echo "Building $(PURPLE)Libft$(STOP) libraries"
	@mkdir -p build
	@cp libftc/libft.a build
	@cp libftc/includes/* includes
	@cp libgfx/libgfx.a build
	@cp libgfx/includes/* includes

clean:
	@/bin/rm -rf ./obj
	@make -C libft_asm clean
	@make -C ft_malloc clean
	@make -C libgfx clean
	@make -C libax clean
	@make -C libftc clean

fclean: clean
	@/bin/rm -rf ./build
	@make -C libft_asm fclean
	@make -C ft_malloc fclean
	@make -C libgfx fclean
	@make -C libax fclean
	@make -C libftc fclean

re: fclean all
