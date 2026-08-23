CC=cc
#CFLAGS= -Werror -Wextra -Wall
CFLAGS=
NAME=vboxmanager

SRCS= 	srcs/vboxstarter.c \
		srcs/error.c

SRCS_OBJ= ${SRCS:.c=.o}

%.o: %.c 
	$(CC) -c $(CFLAGS) $^ -o $@

$(NAME): $(SRCS_OBJ) lib
	$(CC) $(CFLAGS) $(SRCS_OBJ) -Llibft -lft -o $(NAME)

run: $(NAME)
	./$(NAME)

clean:
	rm -f $(SRCS_OBJ)

fclean: clean
	make -C libft fclean
	rm -f $(NAME)

all: $(NAME)

lib:
	Make -C  libft 

COM="generic com"

git: fclean
	git add .
	git commit -m $(COM)
	git push origin $(shell git branch --show-current)

.PHONY: all clean fclean $(NAME)