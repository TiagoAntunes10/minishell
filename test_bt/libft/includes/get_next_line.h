/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapcampo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 12:34:51 by rapcampo          #+#    #+#             */
/*   Updated: 2023/11/03 12:34:53 by rapcampo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

// external libraries

# include <unistd.h>
# include <stdlib.h>

// defining buffer size
// can change buffer size with flag -D BUFFER_SIZE=n

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

// main function

char	*get_next_line(int fd);

// utils

size_t	ft_get_strlen(char *str);
char	*ft_get_strchr(char *str, int c);
void	*ft_get_calloc(size_t nmemb, size_t size);
void	fill_buffer(char *str);
char	*ft_get_strjoin(char *s1, char *s2);

#endif
