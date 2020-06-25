/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 16:18:03 by niboute           #+#    #+#             */
/*   Updated: 2020/06/23 21:39:15 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <string.h>

# define BUFF_SIZE 256
# define INPUT_SIZE 255
# define WR_RED   "\x1B[31m"
# define WR_GRN   "\x1B[32m"
# define WR_YEL   "\x1B[33m"
# define WR_BLU   "\x1B[34m"
# define WR_MAG   "\x1B[35m"
# define WR_CYN   "\x1B[36m"
# define WR_WHT   "\x1B[37m"
# define WR_RESET "\x1B[0m"

typedef struct		s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}					t_list;

typedef struct		s_file
{
	int				fd;
	char			buff[BUFF_SIZE + 1];
	struct s_file	*next;
}					t_file;

typedef struct		s_line
{
	char			buff[BUFF_SIZE + 1];
	struct s_line	*next;
}					t_line;

int					get_next_line(const int fd, char **line,
					unsigned int destroy);
int					destroy_gnl_files(t_file **files);
t_file				*create_destroy_file(int act, const int fd, t_file **files);
long				ft_abs(long value);
int					ft_atoi(const char *src);
void				ft_bzero(void *s, size_t n);
void				*ft_calloc(size_t t_s, size_t num);
size_t				ft_count_words(char const *s, char c);
int					ft_error(char *str);
int					ft_errordel(char *str, char **ptr);
double				ft_dmap(double val, double range, double min2, double max2);
char				*ft_hextoa(unsigned int hex, int maj);
int					ft_isalnum(int c);
int					ft_isalpha(int c);
int					ft_isascii(int c);
int					ft_isdigit(int c);
int					ft_isprint(int c);
char				*ft_itoa(int n);
void				ft_lstadd(t_list **alst, t_list *lstnew);
void				ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void				ft_lstdelone(t_list **alst, void (*del)(void *, size_t));
void				ft_lstiter(t_list *lst, void (*f)(t_list *elem));
t_list				*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
t_list				*ft_lstnew(void const *content, size_t content_size);
int					ft_max_2(int a, int b);
int					ft_max_3(int a, int b, int c);
int					ft_max_4(int a, int b, int c, int d);
void				*ft_memalloc(size_t size);
void				*ft_memccpy(void *dst, const void *src, int c, size_t n);
void				*ft_memchr(const void *s, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
void				*ft_memcpy(void *dst, const void *src, size_t n);
void				ft_memdel(void **ap);
void				*ft_memdup(void *ptr, size_t size);
void				*ft_memmove(void *dst, const void *src, size_t len);
void				*ft_memset(void *b, int c, size_t len);
int					ft_min_2(int a, int b);
int					ft_min_3(int a, int b, int c);
int					ft_min_4(int a, int b, int c, int d);
int					ft_modulo(int nb, int div);
long				ft_power(long nb, int pow);
void				ft_putchar(char c);
void				ft_putchar_fd(char c, int fd);
void				ft_putendl(char const *s);
void				ft_putendl_fd(char const *s, int fd);
void				ft_putnbr(int n);
void				ft_putnbr_fd(int n, int fd);
void				ft_putstr(char const *s);
void				ft_putstr_fd(char const *s, int fd);
int					ft_read_check_input(char *text, char *error,
					void *data, int (*fct)(char*, void*));
char				*ft_strcat(char *s1, const char *s2);
char				*ft_strchr(const char *str, int c);
int					ft_strichr(const char *s, int c);
size_t				ft_strclen(const char *str, char c);
void				ft_strclr(char *str);
int					ft_strcmp(const char *s1, const char *s2);
char				*ft_strcpy(char *dst, const char *src);
char				*ft_strcpy_hextoa(char *dest, unsigned int hex, int maj);
void				ft_strdel(char **as);
char				*ft_strdup(const char *str);
int					ft_strequ(char const *s1, char const *s2);
void				ft_strexit(char *str);
void				ft_striter(char *s, void (*f)(char *));
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
char				*ft_strjoin(char const *s1, char const *s2);
size_t				ft_strlcat(char *dst, const char *src, size_t size);
size_t				ft_strlen(const char *str);
char				*ft_strmap(char const *s, char (*f)(char));
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char				*ft_strncat(char *s1, const char *s2, size_t n);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
char				*ft_strncpy(char *dst, const char *src, size_t len);
char				*ft_strndup(const char *str, size_t size);
int					ft_strnequ(char const *s1, char const *s2, size_t n);
char				*ft_strnew(size_t size);
char				*ft_strnrstr(const char *str, const char *substr,
					size_t len);
char				*ft_strnstr(const char *str, const char *substr,
					size_t len);
char				*ft_strrchr(const char *s, int c);
char				**ft_strsplit(char const *s, char c);
char				*ft_strstr(const char *str, const char *substr);
char				*ft_strsub(char const *s, unsigned int start, size_t len);
char				*ft_strtrim(char const *s);
long				ft_sqrt(long x);
void				ft_swap_int_2(int *a, int *b);
void				ft_tabdel(void ***tab, size_t size);
int					ft_tolower(int c);
int					ft_toupper(int c);

#endif
