/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdelaby <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 12:29:46 by cdelaby           #+#    #+#             */
/*   Updated: 2019/10/16 14:42:19 by cdelaby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <fcntl.h>
# include <string.h>
# include <stdlib.h>
# include <limits.h>
# define BUFFER_SIZE 16

int					ft_atoi(const char *str);
void				ft_bzero(void *s, size_t n);
void				*ft_calloc(size_t count, size_t size);
int					ft_isalnum(int c);
int					ft_isalpha(int c);
int					ft_isascii(int c);
int					ft_isdigit(int c);
int					ft_isprint(int c);
char				*ft_itoa(long nbr);
void				*ft_memchr(const void *str, int c, size_t n);
int					ft_memcmp(const void *str1, const void *str2, size_t n);
void				*ft_memcpy(void *str1, const void *str2, size_t n);
void				*ft_memmove(void *str1, const void *str2, size_t n);
void				*ft_memset(void *str, int c, size_t n);
void				ft_putchar_fd(char c, int fd);
void				ft_putendl_fd(char *s, int fd);
void				ft_putnbr_fd(int nb, int fd);
void				ft_putstr_fd(char *s, int fd);
char				**ft_split(char const *str, char c);
char				*ft_strchr(const char *s, int c);
char				*ft_strcpy(char *dest, const char *src);
char				*ft_strdup(const char *src);
char				*ft_strjoin(char const *s1, char const *s2);
unsigned int		ft_strlcat(char *dest, const char *src, size_t size);
unsigned int		ft_strlcpy(char *dest, const char *src, size_t size);
int					ft_strlen(const char *str);
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int					ft_strncmp(const char *s1, const char *s2, size_t n);
char				*ft_strncpy(char *dest, char const *src, size_t n);
char				*ft_strndup(char const *src, size_t n);
char				*ft_strnstr(const char *str, const char *to_find, size_t n);
char				*ft_strrchr(const char *s, int c);
const char			*ft_strstr(const char *str, const char *to_find);
char				*ft_strtrim(char const *s1, char const *set);
char				*ft_substr(char const *s, unsigned int start, size_t len);
int					ft_tolower(int c);
int					ft_toupper(int c);
void				*ft_memccpy(void *str1, const void *str2, int c, size_t n);
char				*ft_strncat(char *dest, const char *src, size_t nb);
char				*ft_strcat(char *dest, const char *src);
int					ft_strcmp(const char *s1, const char *s2);
int					get_size(long long nbr, int base);

typedef	struct		s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

t_list				*ft_lstnew(void *content);
void				ft_lstdelone(t_list *lst, void (*del)(void*));
void				ft_lstadd_front(t_list **alst, t_list *new);
void				ft_lstiter(t_list *lst, void (*f)(void*));
int					ft_lstsize(t_list *lst);
t_list				*ft_lstlast(t_list *lst);
void				ft_lstadd_back(t_list **alst, t_list *new);
void				ft_lstclear(t_list **lst, void (*del)(void*));
t_list				*ft_lstmap(t_list *lst, void *(*f)(void*));
int					get_next_line(int fd, char **line);
char				*ft_stradd(char *rest, char *s2);

#endif
