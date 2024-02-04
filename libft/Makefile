# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mlamkadm <mlamkadm@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/19 09:19:12 by mlamkadm          #+#    #+#              #
#    Updated: 2024/02/04 03:42:55 by mlamkadm         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc

NAME = libft.a

SRC = ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c\
		ft_strlen.c 
		c ft_putchar_fd.c\
		ft_putstr_fd.c ft_putnbr_fd.c c ft_calloc.c\

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
