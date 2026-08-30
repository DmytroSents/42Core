
NAME = codexion
CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread

SRC_DIR = src
OBJ_DIR = obj
INC_DIR = include

SRCS =  $(SRC_DIR)/utils.c	$(SRC_DIR)/utils_2.c \
	$(SRC_DIR)/codexion.c   $(SRC_DIR)/routine.c  \
	$(SRC_DIR)/std_queue.c	$(SRC_DIR)/monitor.c

OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c Makefile | $(OBJ_DIR)
	$(CC) $(CFLAGS) -I $(INC_DIR) -c $< -o $@

$(NAME): $(OBJS) Makefile
	@$(CC) $(CFLAGS) $(OBJS) -I $(INC_DIR) -o $(NAME)

clean:
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

# ./codexion {num_coders} {time2_burnout} {time2_compile} {time2_debug}
#	{time2_refactor} {num_compiles_req} {dongle_cooldown} {scheduler}
# valgrind --tool=helgrind ./codexion 6  1200  600  200  200  3  25  fifo
#			valgrind --tool=drd
