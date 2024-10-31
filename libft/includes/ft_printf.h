/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapcampo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 13:36:51 by rapcampo          #+#    #+#             */
/*   Updated: 2023/10/24 13:36:55 by rapcampo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

//libraries to be used

# include <unistd.h>
# include <stdarg.h>
//# include <stdlib.h>
//# include <stddef.h>
//# include <stdio.h>

//define bases

# define SDECIMAL "-0123456789"
# define UDECIMAL "0123456789"
# define HEX_LO "0123456789abcdef"
# define HEX_UP "0123456789ABCDEF"

// functions used

int		ft_char(int c);
int		ft_string(char *str);
int		ft_print_nbr(int fd, size_t n, const char *base);
int		ft_printf(const char *format, ...);
int		ft_pointer(size_t ptr, const char *base);

#endif
