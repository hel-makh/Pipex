/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-makh <hel-makh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/19 12:20:36 by hel-makh          #+#    #+#             */
/*   Updated: 2021/12/25 15:07:58 by hel-makh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/pipex_bonus.h"

static void	ft_exec_first_cmd(
	char **cmd, char *infile, int p[2], char *envp[]
	)
{
	int	fd;

	close(p[STDIN_FILENO]);
	if (dup2(p[STDOUT_FILENO], STDOUT_FILENO) == -1)
		exit(ft_perror("write-end pipe dup2"));
	close(p[STDOUT_FILENO]);
	fd = open(infile, O_RDONLY);
	if (dup2(fd, STDIN_FILENO) == -1)
		exit(ft_perror("input-file dup2"));
	close(fd);
	execve(cmd[0], cmd, envp);
	exit(EXIT_FAILURE);
}

static void	ft_exec_second_cmd(
	char **cmd, char *outfile, int p[2], char *envp[]
	)
{
	int		fd;
	pid_t	pid;

	close(p[STDOUT_FILENO]);
	if (dup2(p[STDIN_FILENO], STDIN_FILENO) == -1)
		exit(ft_perror("read-end pipe dup2"));
	close(p[STDIN_FILENO]);
	pid = fork();
	if (pid == -1)
		exit(ft_perror("fork"));
	else if (pid == 0)
	{
		fd = open(outfile, O_RDWR | O_TRUNC | O_CREAT, 0644);
		if (dup2(fd, STDOUT_FILENO) == -1)
			exit(ft_perror("output-file dup2"));
		close(fd);
		execve(cmd[0], cmd, envp);
		exit(EXIT_FAILURE);
	}
	else if (pid > 0)
		waitpid(pid, NULL, 0);
}

static void	ft_multiple_pipes(
	char ***cmds, char *infile, char *outfile, char *envp[]
	)
{
	int		i;
	int		p[2];
	pid_t	pid;

	i = 0;
	while (cmds[i])
	{
		if (pipe(p) == -1)
			exit(ft_perror("pipe"));
		pid = fork();
		if (pid == -1)
			exit(ft_perror("fork"));
		else if (pid == 0 && i == 0)
			ft_exec_first_cmd(cmds[i], infile, p, envp);
		else if (pid == 0 && i > 0)
			ft_exec_first_cmd(cmds[i], outfile, p, envp);
		else if (pid > 0)
		{
			waitpid(pid, NULL, 0);
			ft_exec_second_cmd(cmds[++i], outfile, p, envp);
		}
		i ++;
	}
}

int	main(int argc, char *argv[], char *envp[])
{
	char	**cmds[1024];
	int		i;

	if (argc < 5)
		exit(EXIT_FAILURE);
	i = 0;
	while (i < argc - 3)
	{
		cmds[i] = ft_execve_argv(argv[i + 2], envp);
		i ++;
	}
	if ((!ft_strcmp(argv[1], "here_doc") && i % 2 == 0)
		|| (ft_strcmp(argv[1], "here_doc") && i % 2 != 0))
		cmds[i++] = ft_execve_argv("cat", envp);
	cmds[i] = NULL;
	if (!ft_strcmp(argv[1], "here_doc"))
		ft_here_doc(&cmds[1], argv[argc - 1], argv[2], envp);
	else
		ft_multiple_pipes(cmds, argv[1], argv[argc - 1], envp);
	ft_free_3d(cmds);
	return (EXIT_SUCCESS);
}
