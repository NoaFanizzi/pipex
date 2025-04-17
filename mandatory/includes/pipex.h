/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 14:01:00 by nofanizz          #+#    #+#             */
/*   Updated: 2025/03/11 15:10:31 by nofanizz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_infos
{
	int		pipe[2];
	int		fd;
	pid_t	pid_1;
	pid_t	pid_2;
	char	*path;
	char	**options;
	char	**cmd;
}			t_infos;

void		ft_first_cmd(char **argv, char **env, t_infos *infos);
void		ft_second_cmd(char **argv, char **env, t_infos *infos);
void		free_tab(char **str);
void		ft_strcpy(char *dest, char *src);
void		ft_strcat(char *dest, char *src);
size_t		ct_count_size(char *str);
char		**ct_get_env(char **env);
char		*ft_is_command(char **env, char *argv, char *path);
void		ft_close_all(t_infos *infos);
void		ft_dup2_pb(t_infos *infos);
char		*ft_check_if_command(char *argv, char *path);

#endif