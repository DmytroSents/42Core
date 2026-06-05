NAME		= push_swap
CC			= cc
CFLAGS		= -Wall -Wextra -Werror
RM			= rm -f

SRC			= main.c \
			  src/parsing_args.c \
			  src/small_n_sort.c \
			  src/radix.c \
			  src/swap_push.c \
			  src/rotate_reverse.c \
			  src/is_itsorted.c

LIBFT_SRC	= libft/ft_lstadd_back.c \
			  libft/ft_lstadd_front.c \
			  libft/ft_lstlast.c \
			  libft/ft_lstnew.c \
			  libft/ft_lstsize.c \
			  libft/ft_printf.c \
			  libft/ft_split.c \
			  libft/ft_strchr.c \
			  libft/ft_strjoin.c \
			  libft/ft_strlen.c \
			  libft/ft_substr.c \
			  libft/lst_clear_all.c \
			  libft/num_base_ptr.c

OBJ			= $(SRC:.c=.o)
LIBFT_OBJ	= $(LIBFT_SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT_OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT_OBJ) -o $(NAME)

%.o: %.c push_header.h libft/libft.h
	$(CC) $(CFLAGS) -I. -Ilibft -c $< -o $@

clean:
	$(RM) $(OBJ) $(LIBFT_OBJ)

# Test rules
t100: all
	@ARG=$$(shuf -i 1-2147483647 -n 100 | tr '\n' ' '); \
	./push_swap $$ARG | wc -l; \
	./push_swap $$ARG | ./checker_linux $$ARG

t500: all
	@ARG=$$(shuf -i 1-2147483647 -n 500 | tr '\n' ' '); \
	./push_swap $$ARG | wc -l; \
	./push_swap $$ARG | ./checker_linux $$ARG

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
