# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mlamkadm <mlamkadm@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/19 09:19:12 by mlamkadm          #+#    #+#              #
#    Updated: 2024/02/04 05:31:58 by mlamkadm         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc

NAME = libft.a

SRC = ft_isalpha.c ft_isdigit.c ft_isprint.c ft_strlen.c ft_putchar_fd.c\
		ft_putstr_fd.c ft_putnbr_fd.c ft_calloc.c ft_bzero.c ft_memset.c ft_strdup.c\

OBJ = $(SRC:.c=.o)

HEADER = libft.h

AR = ar -rcs

RM = rm -rf

all : $(NAME)

$(NAME) : $(OBJ)
	$(AR) $(NAME) $(OBJ)

%.o : %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

clean :
	$(RM) $(OBJ)

fclean : clean
	$(RM) $(NAME)
	
re : fclean all

.PHONY : clean fclean re all
