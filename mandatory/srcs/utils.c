/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 13:54:48 by nofanizz          #+#    #+#             */
/*   Updated: 2025/03/12 15:27:22 by nofanizz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	free_tab(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

void	ft_strcpy(char *dest, char *src)
{
	size_t	i;

	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
}

void	ft_strcat(char *dest, char *src)
{
	size_t	i;
	size_t	j;

	i = ft_strlen(dest);
	j = 0;
	while (src[j])
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	dest[i] = '\0';
}

size_t	ct_count_size(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_is_command(char **env, char *argv, char *path)
{
	size_t	i;
	char	*adding_slash;

	i = 0;
	if (argv == NULL || argv[0] == '\0')
		return (NULL);
	while (env[i])
	{
		adding_slash = ft_strjoin(env[i], "/");
		if (!adding_slash)
			return (NULL);
		path = ft_strjoin(adding_slash, argv);
		free(adding_slash);
		if (!path)
			return (NULL);
		if (access(path, X_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	path = ft_check_if_command(argv, path);
	return (path);
}
