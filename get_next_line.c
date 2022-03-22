/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igbocha3 <igbocha3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 14:09:04 by igbocha3          #+#    #+#             */
/*   Updated: 2022/03/20 09:05:29 by igbocha3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_pre_nline(char *str)
{
	int		i;
	char	*pre_temp;

	i = 0;
	if (!str)
		return (NULL);
	while (str[i] != '\n' && str[i])
		i++;
	if (str[0] == '\0')
	{
		return (NULL);
	}
	pre_temp = malloc(sizeof(char) * i + 2);
	if (!pre_temp)
		return (NULL);
	i = 0;
	while (str[i] != '\n' && str[i])
	{
		pre_temp[i] = str[i];
		i++;
	}
	if (str[i] == '\n')
		pre_temp[i++] = '\n';
	pre_temp[i] = '\0';
	return (pre_temp);
}

char	*ft_post_nline(char *str)
{
	int		i;
	int		j;
	char	*post_temp;

	j = 0;
	i = ft_strlen(str);
	if (!str)
		return (NULL);
	while (str[j] != '\n' && str[j])
		j++;
	if (str[j] == '\0')
	{
		free(str);
		return (NULL);
	}
	post_temp = malloc(sizeof(char) * (i - j));
	if (!post_temp)
		return (NULL);
	i = 0;
	j++;
	while (str[j])
		post_temp[i++] = str[j++];
	post_temp[i] = '\0';
	free(str);
	return (post_temp);
}

int	ft_find_nline(char *str)
{
	if (!str)
		return (0);
	while (*str)
	{
		if (*str == '\n')
			return (1);
		str++;
	}
	return (0);
}

char	*ft_read_file(int fd, char *read_buf, char *temp, char *str)
{
	int		i;

	i = 1;
	while (i != 0)
	{
		i = read(fd, read_buf, BUFFER_SIZE);
		if (i == -1)
		{
			free (read_buf);
			return (NULL);
		}
		read_buf[i] = '\0';
		temp = str;
		if (!temp)
		{
			temp = malloc(sizeof(char) * 1);
			temp[0] = '\0';
		}
		str = ft_strjoin(temp, read_buf);
		free(temp);
		if (ft_find_nline(str) == 1)
			break ;
	}
	free(read_buf);
	return (str);
}

char	*get_next_line(int fd)
{
	static char	*str;
	char		*read_buf;
	char		*next_line;
	char		*temp;

	temp = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	read_buf = malloc(BUFFER_SIZE + 1);
	if (!read_buf)
		return (NULL);
	str = ft_read_file(fd, read_buf, temp, str);
	if (!str)
		return (NULL);
	next_line = ft_pre_nline(str);
	str = ft_post_nline(str);
	return (next_line);
}
