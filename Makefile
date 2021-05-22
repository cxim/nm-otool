C_FLAGS =  -I
NAME_NM = ft_nm
NAME_OTOOL = ft_otool

SRCS_ALL = errors.c magic.c mach_o.c lst_fuctions.c cpu_file.c mach_o_64.c mach_o_32_64.c
SRCS_NM = nm.c  file_inside.c  print_nm.c fat_o.c fat_o_64.c print_nm_m_p_two.c

SRCS_OTOOL = otool.c mach_o_otool.c print_otool.c fat_otool.c fat_otool_64.c

G_FLAGS = -Wall -Werror -Wextra
OBJ_ALL = $(SRCS_ALL:.c=.o)
OBJECTS_NM = $(SRCS_NM:.c=.o)
OBJECTS_OTOOL = $(SRCS_OTOOL:.c=.o)
LIBFT = libft/
HEADER = libft/libft.h
LIB = libft/libft.a


all: $(OBJ_ALL) $(NAME_NM) $(NAME_OTOOL)

$(OBJ_ALL): %.o: %.c
	clang -g  $(C_FLAGS) $(HEADER) -o $@ -c $<
	clang -g $(G_FLAGS) $(C_FLAGS) $(HEADER) -o $@ -c $<

$(NAME_OTOOL): $(OBJECTS_OTOOL)
	make -C $(LIBFT)
	gcc -o $(NAME_OTOOL) $(OBJECTS_OTOOL) $(OBJ_ALL) $(LIB)

$(NAME_NM): $(OBJECTS_NM)
	make -C $(LIBFT)
	gcc -o $(NAME_NM) $(OBJECTS_NM) $(OBJ_ALL) $(LIB)

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
	/bin/rm -f $(OBJ_ALL)

fclean: clean
	make fclean -C $(LIBFT)
	/bin/rm -f $(NAME_NM)
	/bin/rm -f $(NAME_OTOOL)

re: fclean all
