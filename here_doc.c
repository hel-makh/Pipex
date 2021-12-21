/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-makh <hel-makh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 21:10:00 by hel-makh          #+#    #+#             */
/*   Updated: 2021/12/22 00:48:59 by hel-makh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/pipex.h"

static void	ft_hd_exec_first_cmd(char **cmd, int infd, int p[2])
{
	close(p[0]);
	if (dup2(p[1], STDOUT_FILENO) == -1)
		exit(ft_perror("write-end pipe dup2"));
	close(p[1]);
	if (dup2(infd, STDIN_FILENO) == -1)
		exit(ft_perror("input-file dup2"));
	// close(infd);
	execve(cmd[0], cmd, NULL);
	exit(EXIT_FAILURE);
}

static void	ft_hd_exec_second_cmd(char **cmd, int outfd, int p[2])
{
	pid_t	pid;

	close(p[1]);
	if (dup2(p[0], STDIN_FILENO) == -1)
		exit(ft_perror("read-end pipe dup2"));
	close(p[0]);
	pid = fork();
	if (pid == -1)
		exit(ft_perror("fork"));
	else if (pid == 0)
	{
		if (dup2(outfd, STDOUT_FILENO) == -1)
			exit(ft_perror("output-file dup2"));
		// close(outfd);
		execve(cmd[0], cmd, NULL);
		exit(EXIT_FAILURE);
	}
	else if (pid > 0)
		waitpid(pid, NULL, 0);
}

static void	ft_hd_multiple_pipes(char ***cmds, int outfd, int p[2])
{
	int		i;
	int		p2[2];
	pid_t	pid;

	i = 0;
	while (cmds[i])
	{
		if (pipe(p2) == -1)
			exit(ft_perror("pipe"));
		pid = fork();
		if (pid == -1)
			exit(ft_perror("fork"));
		else if (pid == 0)
			ft_hd_exec_first_cmd(cmds[i], p[0], p2);
		else if (pid > 0)
		{
			waitpid(pid, NULL, 0);
			if (!cmds[i + 2])
				ft_hd_exec_second_cmd(cmds[++i], outfd, p2);
			else
				ft_hd_exec_second_cmd(cmds[++i], p[1], p2);
		}
		i ++;
	}
}

void	ft_here_doc(char *limiter, char *outfile, char ***cmds)
{
	int		fd;
	int		p[2];
	char	*input;
	
	if (pipe(p) == -1)
		exit(ft_perror("pipe"));
	input = get_next_line(STDIN_FILENO, "heredoc> ");
	write(p[1], input, ft_strlen(input));
	while (ft_strlen(input) != ft_strlen(limiter) + 1
		|| ft_strncmp(input, limiter, ft_strlen(limiter)))
	{
		free(input);
		input = get_next_line(STDIN_FILENO, "heredoc> ");
		write(p[1], input, ft_strlen(input));
	}
	free(input);
	fd = open(outfile, O_RDWR | O_CREAT | O_APPEND, 0666);
	ft_hd_multiple_pipes(cmds, fd, p);
	// printf("\n> %s", get_next_line(p[0], ""));
	close(fd);
	close(p[0]);
	close(p[1]);
}
