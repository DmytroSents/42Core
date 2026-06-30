
NAME = codexion
CC = cc
CFLAGS =  -pthread #-Wall -Wextra -Werror

SRC_DIR = src
OBJ_DIR = obj
INC_DIR = include

SRCS = $(SRC_DIR)/codexion.c \
       $(SRC_DIR)/utils.c

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