NAME = libftprintf.a
CC = gcc
CFLAGS = -Wall -Wextra -Werror -c

SOURCES  = ft_printf.c \
ft_print_ptr.c  print_num_base.c  print_unsigned_base.c\

OBJECTS = $(SOURCES:.c=.o)


all: $(NAME)


$(NAME): $(OBJECTS)
	ar rcs $(NAME) $(OBJECTS) 

%.o : %.c
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -f $(OBJECTS) $(BONOBJS) 
fclean: clean 
	rm -f $(NAME)
re: fclean $(NAME)

.PHONY:  all clean fclean re bonus