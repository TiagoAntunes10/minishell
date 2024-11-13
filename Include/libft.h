/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapcampo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 18:26:23 by rapcampo          #+#    #+#             */
/*   Updated: 2024/10/01 13:53:33 by rapcampo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include "../libft/includes/ft_printf.h"
# include "../libft/includes/get_next_line.h"

//typedef struct for bonus//

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

//libc functions//
int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);
int		ft_toupper(int c);
int		ft_tolower(int c);
size_t	ft_strlen(const char *str);
void	*ft_memset(void *b, int c, size_t n);
void	ft_bzero(void *s, size_t n);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	*ft_memmove(void *s1, const void *s2, size_t n);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
char	*ft_strchr(const char *s, int i);
size_t	ft_strlcat(char *dest, const char *src, size_t size);
char	*ft_strrchr(const char *s, int c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
char	*ft_strdup(const char *s);
int		ft_atoi(const char *nptr);
void	*ft_calloc(size_t count, size_t size);
int		ft_strcmp(const char *s1, const char *s2);
void	*ft_mempcpy(void *dest, const void *src, size_t n);

//non libc functions//

char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strtrim(char const *s1, char const *set);
char	**ft_split(char const *s, char c);
char	*ft_itoa(int n);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
size_t	ft_strspn(char const *str, char const *accept);
size_t	ft_strcspn(const char *str, const char *reject);
char	*ft_stpcpy(char *restrict dst, const char *restrict src);
char	*ft_strpbrk(char const *str, char const *accept);
void	*ft_freematrix(char **matrix);
char	*ft_strndup(const char *str, size_t n);

//bonus functions//

t_list	*ft_lstnew(void *content);
int		ft_lstsize(t_list *lst);
void	ft_lstadd_front(t_list **lst, t_list *new);
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
t_list	*ft_lstlast(t_list *lst);

// special split

char	**ft_split_mult(char const *str, char const *delim);
int		ft_wordcount_mult(char const *str, char const *delim);

#endif
