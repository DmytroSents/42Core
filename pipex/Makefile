NAME = pipex
CC = cc
CFLAGS = -g -I./include -I./libft	#  -Wall -Wextra -Werror
OBJ_DIR = obj
SRCS = main.c utils.c forking.c
   #	src/main.c src/pipex.c src/check_path.c src/utils.c


OBJS = $(SRCS:src/%.c=$(OBJ_DIR)/%.o)


LIBFT_DIR := libft
LIBFT := $(LIBFT_DIR)/libft.a
LIBFT_PATH := -L./libft -lft
RM := rm -rf


all: $(NAME)

$(LIBFT):@make -C $(LIBFT_DIR) all

$(NAME): $(OBJS) 
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT_PATH) -o $(NAME)


$(OBJ_DIR)/%.o: src/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@


$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)
	mkdir -p $(sort $(dir $(OBJS)))

clean:
	$(RM) $(OBJ_DIR)
	#@make -C $(LIBFT_DIR) clean


fclean: clean
	$(RM) $(NAME)
	#@make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re

# valgrind --leak-check=full --track-fds=yes ./pipex st_in.txt "grep F" "wc -l" s_out.txt