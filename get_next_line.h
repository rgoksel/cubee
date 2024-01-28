/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgur <mgur@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 13:29:24 by mgur              #+#    #+#             */
/*   Updated: 2022/11/10 13:29:24 by mgur             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

char	*get_next_line(int fd);
char	*ft_strdup3(const char *s1);
char	*ft_strchr3(const char *s, int c);
char	*ft_strjoin3(char const *s1, char const *s2);
char	*ft_substr3(char const *s, unsigned int start, size_t len);
char	*last(char **s, char **line);
char	*check(char **s, char **line, int count);
size_t	ft_strlen3(const char *s);

#endif
