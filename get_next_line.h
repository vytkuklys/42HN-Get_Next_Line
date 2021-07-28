/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuklys <vkuklys@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/22 18:18:05 by vkuklys           #+#    #+#             */
/*   Updated: 2021/07/28 22:19:34 by vkuklys          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <unistd.h>
# include <stdlib.h>

char	*get_next_line(int fd);
int		ft_strlen(const char *str);
int		ft_strncmp(const char *str1, const char *str2, unsigned int n);
char	*ft_strdup(const char *str1);
void	*ft_calloc(unsigned int num, unsigned int size);
char	*ft_strjoin(char **s1, char const *s2);

#endif