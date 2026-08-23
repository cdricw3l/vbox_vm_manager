CC=gcc
CFLAGS= -Werror -Wextra -Wall
NAME=vboxmanager

SRCS= VBoxStarter.c

SRCS_OBJ= ${SRCS:.c=.o}

%.o: %.c 
	$(CC) $(CFLAGS) $< -o $@

$(NAME): $(SRCS_OBJ)
	$(CC) $(CFLAGS) $(SRCS_OBJ) -o $(NAME)

clean:
	rm -f $(SRCS_OBJ)

fclean: clean
	rm -f $(NAME)

all: $(NAME)

COM="generic com"

git: fclean
	git add .
	git commit -m $(COM)
	git push origin $(shell git branch --show-current)

.PHONY: all clean fclean $(NAME)