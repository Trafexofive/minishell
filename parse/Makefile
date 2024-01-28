
CC := cc

NAME	:= minishell

CFLAGS	:= -Wextra -Wall -Werror 

SRCS	:= tokenizer.c garbage.c

LIBFT := ../libft/libft.a

OBJS	:= ${SRCS:.c=.o}

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME) #-lreadline

lib : 
	@make -C ../libft

%.o: %.c $(HEADERS) | lib
	@$(CC) $(CFLAGS) -c $< -o $@

run :
	./minishell
push:
	git add .
	git commit -m "Lazy_push"
	git push

clean:
	make clean -C ../libft
	rm -rf $(OBJS)

fclean: clean
	make fclean -C ../libft
	rm -rf $(NAME)

re: fclean all

.PHONY: all, lib, push,  clean, fclean, re
