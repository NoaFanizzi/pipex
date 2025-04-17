/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 11:11:21 by nofanizz          #+#    #+#             */
/*   Updated: 2025/03/11 15:27:26 by nofanizz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	ft_exec_failure(t_infos *infos, int i)
{
	if (i == 1)
		perror("pipe");
	if (i == 2)
		perror("fork");
	free(infos->options);
	exit(EXIT_FAILURE);
}

char	**ct_get_env(char **env)
{
	size_t	size;
	size_t	i;
	char	**options;

	i = 0;
	while (ft_strncmp(env[i], "PATH=", 5) != 0)
		i++;
	size = ct_count_size(env[i]);
	options = ft_split(env[i] + 5, ':');
	return (options);
}

void	pipex(char **argv, char **env, t_infos *infos)
{
	infos->options = ct_get_env(env);
	if (!infos->options)
		return ;
	if (pipe(infos->pipe) == -1)
		ft_exec_failure(infos, 1);
	infos->pid_1 = fork();
	if (infos->pid_1 == -1)
		ft_exec_failure(infos, 2);
	if (infos->pid_1 == 0)
		ft_first_cmd(argv, env, infos);
	infos->pid_2 = fork();
	if (infos->pid_2 == -1)
		ft_exec_failure(infos, 1);
	if (infos->pid_2 == 0)
		ft_second_cmd(argv, env, infos);
	else
	{
		close(infos->pipe[0]);
		close(infos->pipe[1]);
	}
	free_tab(infos->options);
}

int	main(int argc, char **argv, char **env)
{
	size_t	i;
	t_infos	infos;
	int		exit_status;

	i = 0;
	exit_status = 0;
	if (argc != 5)
		exit(0);
	if (!(argv[2]) || !(argv[3]))
		exit(127);
	if (!*env)
		return (127);
	pipex(argv, env, &infos);
	waitpid(infos.pid_1, &exit_status, 0);
	waitpid(infos.pid_2, &exit_status, 0);
	return (WEXITSTATUS(exit_status));
}
