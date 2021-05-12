C_FLAGS =  -I
NAME = nm
SRCS = main.c errors.c file_inside.c magic.c mach_o.c lst_fuctions.c print_nm.c fat_o.c
G_FLAGS = -Wall -Werror -Wextra
OBJECTS = $(SRCS:.c=.o)
LIBFT = ft_printf/
HEADER = ft_printf/includes/printf.h
LIB = ft_printf/libftprintf.a


all: $(NAME)

$(NAME): $(OBJECTS)
	make -C $(LIBFT)
	gcc -o $(NAME) $(OBJECTS) $(LIB)

$(OBJECTS):	%.o: %.c
	clang -g  $(C_FLAGS) $(HEADER) -o $@ -c $<
	clang -g $(G_FLAGS) $(C_FLAGS) $(HEADER) -o $@ -c $<

clean:
	make clean -C $(LIBFT)
	/bin/rm -f $(OBJECTS)

fclean: clean
	make fclean -C $(LIBFT)
	/bin/rm -f $(NAME)

re: fclean all
