C_FLAGS =  -I
NAME_NM = nm
NAME_OTOOL = otool

SRCS_NM = nm.c errors.c file_inside.c magic.c mach_o.c lst_fuctions.c print_nm.c fat_o.c cpu_file.c

SRCS_OTOOL = otool.c mach_o_otool.c

G_FLAGS = -Wall -Werror -Wextra
OBJECTS_NM = $(SRCS_NM:.c=.o)
OBJECTS_OTOOL = $(SRCS_OTOOL:.c=.o)
LIBFT = ft_printf/
HEADER = ft_printf/includes/printf.h
LIB = ft_printf/libftprintf.a


all: $(NAME_NM) $(NAME_OTOOL)

$(NAME_OTOOL): $(OBJECTS_OTOOL)
	make -C $(LIBFT)
	gcc -o $(NAME_OTOOL) $(OBJECTS_OTOOL) $(LIB)

$(NAME_NM): $(OBJECTS_NM)
	make -C $(LIBFT)
	gcc -o $(NAME_NM) $(OBJECTS_NM) $(LIB)

$(OBJECTS_NM):	%.o: %.c
	clang -g  $(C_FLAGS) $(HEADER) -o $@ -c $<
	clang -g $(G_FLAGS) $(C_FLAGS) $(HEADER) -o $@ -c $<

$(OBJECTS_OTOOL):	%.o: %.c
	clang -g  $(C_FLAGS) $(HEADER) -o $@ -c $<
	clang -g $(G_FLAGS) $(C_FLAGS) $(HEADER) -o $@ -c $<

clean:
	make clean -C $(LIBFT)
	/bin/rm -f $(OBJECTS_NM)
	/bin/rm -f $(OBJECTS_OTOOL)

fclean: clean
	make fclean -C $(LIBFT)
	/bin/rm -f $(NAME_NM)
	/bin/rm -f $(NAME_OTOOL)

re: fclean all
