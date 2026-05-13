 # Makefile for A-Maze-ing project
NAME = amazing

CC = cc
CFLAGS = -std=c99 
#-Wall -Wextra -Werror  -g3

SRCDIR = src
MAZEDIR = mazegen
SRCS = $(wildcard $(SRCDIR)/*.c) $(wildcard $(MAZEDIR)/*.c)  main.c terminc.c
OBJS = $(SRCS:.c=.o)

#default config
CONFIG = config.txt

all: $(NAME)
	@$(MAKE) clean
	

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

src/%.o: src/%.c
	@$(CC) $(CFLAGS) -c $< -o $@

test: $(NAME)
	@./$(NAME) $(CONFIG)

clean:
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(OBJS) $(NAME)

re: fclean all

debug: CFLAGS += -fsanitize=address -g
debug: re

valgrind: $(NAME)
	@valgrind --leak-check=full --track-origins=yes ./$(NAME) $(CONFIG)

.PHONY: all clean fclean re test debug valgrind