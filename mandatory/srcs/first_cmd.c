/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 11:02:15 by nofanizz          #+#    #+#             */
/*   Updated: 2025/03/11 15:27:48 by nofanizz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	ft_close_all(t_infos *infos)
{
	close(infos->fd);
	close(infos->pipe[0]);
	close(infos->pipe[1]);
}

char	*ft_check_if_command(char *argv, char *path)
{
	if (access(argv, X_OK) == 0)
	{
		path = ft_strdup(argv);
		return (path);
	}
	return (NULL);
}

static void	ft_prepare_execution(t_infos *infos, char **argv)
{
	infos->fd = open(argv[1], O_RDONLY);
	if (infos->fd == -1)
	{
		perror("Infile");
		close(infos->pipe[0]);
		close(infos->pipe[1]);
		free_tab(infos->options);
		exit(1);
	}
	infos->cmd = ft_split(argv[2], ' ');
	if (!(infos->cmd))
	{
		ft_close_all(infos);
		free_tab(infos->options);
		exit(EXIT_FAILURE);
	}
	infos->path = ft_is_command(infos->options, infos->cmd[0], infos->path);
	if (infos->path == NULL)
	{
		ft_putstr_fd("Command not found\n", 1);
		free_tab(infos->cmd);
		free_tab(infos->options);
		ft_close_all(infos);
		exit(127);
	}
}

void	ft_first_cmd(char **argv, char **env, t_infos *infos)
{
	ft_prepare_execution(infos, argv);
	if (dup2(infos->fd, STDIN_FILENO) == -1)
		ft_dup2_pb (infos);
	if (dup2(infos->pipe[1], STDOUT_FILENO) == -1)
		ft_dup2_pb (infos);
	ft_close_all(infos);
	free_tab(infos->options);
	if (execve(infos->path, infos->cmd, env) == -1)
	{
		perror("execve");
		free(infos->path);
		free_tab(infos->cmd);
		exit(EXIT_FAILURE);
	}
}
