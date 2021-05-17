cmake_minimum_required(VERSION 3.15)
project(nm_otool C)

set(CMAKE_C_STANDARD 11)

include_directories(.)
include_directories(libft)

add_executable(nm_otool
		libft/ft_putchar.c
		libft/ft_putchar_fd.c
		libft/ft_putchar_mod.c
		libft/ft_putendl.c
		libft/ft_putendl_fd.c
		libft/ft_putstr.c
		libft/ft_putstr_fd.c
		libft/ft_putstr_mod.c
		libft/ft_strcmp.c
		libft/libft.h
		cpu_file.c
		errors.c
		fat_o.c
		fat_o_64.c
		file_inside.c
		lst_fuctions.c
		mach_o.c
		mach_o_32_64.c
		mach_o_64.c
		magic.c
		nm.c
		nmotool.h
		print_nm.c
		libft/ft_strlen.c)
