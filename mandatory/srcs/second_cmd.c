/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   second_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 12:18:25 by nofanizz          #+#    #+#             */
/*   Updated: 2025/03/11 15:27:16 by nofanizz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static void	ft_prepare_execution(t_infos *infos, char **argv)
{
	infos->fd = open(argv[4], O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (infos->fd == -1)
	{
		perror("Outfile");
		close(infos->pipe[0]);
		close(infos->pipe[1]);
		free_tab(infos->options);
		exit(1);
	}
	infos->cmd = ft_split(argv[3], ' ');
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

void	ft_dup2_pb(t_infos *infos)
{
	free_tab(infos->cmd);
	free_tab(infos->options);
	free(infos->path);
	ft_close_all(infos);
	perror("Dup2 error");
	exit(1);
}

void	ft_second_cmd(char **argv, char **env, t_infos *infos)
{
	ft_prepare_execution(infos, argv);
	if (dup2(infos->pipe[0], STDIN_FILENO) == -1)
		ft_dup2_pb(infos);
	if (dup2(infos->fd, STDOUT_FILENO) == -1)
		ft_dup2_pb(infos);
	ft_close_all(infos);
	free_tab(infos->options);
	if (execve(infos->path, infos->cmd, env) == -1)
	{
		perror("execve");
		free(infos->path);
		free_tab(infos->cmd);
		free(infos->options);
		exit(EXIT_FAILURE);
	}
}
