/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tialbert <tialbert@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 15:16:43 by tialbert          #+#    #+#             */
/*   Updated: 2025/01/11 16:47:19 by tialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	ft_putstr_fd(char *s, int fd)
{
	while (*s != '\0')
	{
		if (fd == -1)
			return (-1);
		if (write(fd, s, 1) == -1)
			return -1;
		s = s + 1;
	}
	return (0);
}

/*int	main(void)
{
	char	*str;

	str = "abcd";
	ft_putstr_fd(str, 1);
}*/
