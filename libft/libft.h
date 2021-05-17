/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft1.h                                            :+:      :+:    :+:  */
/*                                                    +:+ +:+         +:+     */
/*   By: mnarwhal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 12:44:20 by mnarwhal          #+#    #+#             */
/*   Updated: 2020/02/19 18:20:13 by selly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# define BUFF_SIZE 32
# define BUFFER_SIZE 32
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <fcntl.h>

typedef struct s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}				t_list;

int				ft_strcmp(const char *s1, const char *s2);
void			ft_putchar(char c);
void			ft_putstr(char const *s);
void			ft_putendl(char const *s);
void			ft_putnbr(int n);
void			ft_putchar_fd(char c, int fd);
void			ft_putstr_fd(char const *s, int fd);
void			ft_putendl_fd(char const *s, int fd);
void			ft_putnbr_fd(int n, int fd);
int				ft_putchar_mod(char c, int *m);
int				ft_char_in_string(char c, char *s);
int				ft_cut_space(const char **s);
int				ft_get_integer(const char **p);
int				ft_strlen_mod(char const *str);
int				ft_putstr_mod(char const *str, int fd);
size_t			ft_strlen(const char *s);
#endif
