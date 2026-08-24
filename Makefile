CC=cc
CFLAGS= -Werror -Wextra -Wall -g
NAME=vboxmanager

SRCS= 	srcs/vboxstarter.c \
		srcs/vbox_vm_list.c \
		srcs/vbox_action_menu.c \
		srcs/vbox_action.c \
		srcs/help.c \
		srcs/error.c

SRCS_OBJ= ${SRCS:.c=.o}

%.o: %.c 
	$(CC) -c $(CFLAGS) $^ -o $@

$(NAME): $(SRCS_OBJ) lib
	$(CC) $(CFLAGS) $(SRCS_OBJ) -Llibft -lft -o $(NAME)


run: $(NAME)
	./$(NAME)

mrun: $(NAME)
	leaks -atExit -- ./$(NAME)

clean:
	rm -f $(SRCS_OBJ)

fclean: clean
	rm -f $(NAME)

ffclean: fclean
	make -C libft fclean


all: $(NAME)

lib:
	Make -C  libft 

COM="generic com"

git: ffclean
	git add .
	git commit -m $(COM)
	git push origin $(shell git branch --show-current)

re: fclean $(NAME)

.PHONY: $(NAME) all git lib re clean fclean ffclean