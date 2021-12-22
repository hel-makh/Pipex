/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-makh <hel-makh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 21:10:00 by hel-makh          #+#    #+#             */
/*   Updated: 2021/12/22 22:09:28 by hel-makh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/pipex_bonus.h"

static void	ft_hd_exec_first_cmd(char **cmd, char *infile, int p[2])
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
	execve(cmd[0], cmd, NULL);
	exit(EXIT_FAILURE);
}

static void	ft_hd_exec_second_cmd(char **cmd, char *outfile, int p[2])
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
		if (!ft_strcmp(outfile, ".here_doc"))
			fd = open(outfile, O_RDWR | O_TRUNC);
		else
			fd = open(outfile, O_RDWR | O_APPEND | O_CREAT, 0644);
		if (dup2(fd, STDOUT_FILENO) == -1)
			exit(ft_perror("output-file dup2"));
		close(fd);
		execve(cmd[0], cmd, NULL);
		exit(EXIT_FAILURE);
	}
	else if (pid > 0)
		waitpid(pid, NULL, 0);
}

static void	ft_hd_multiple_pipes(char ***cmds, char *infile, char *outfile)
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
		else if (pid == 0)
			ft_hd_exec_first_cmd(cmds[i], infile, p);
		else if (pid > 0)
		{
			waitpid(pid, NULL, 0);
			if (cmds[i + 2])
				ft_hd_exec_second_cmd(cmds[++i], infile, p);
			else
				ft_hd_exec_second_cmd(cmds[++i], outfile, p);
		}
		i ++;
	}
}

void	ft_here_doc(char ***cmds, char *outfile, char *limiter)
{
	int		i;
	int		fd;
	char	*line;
	char	*input;

	line = ft_strdup("");
	input = ft_strdup("");
	while (ft_strlen(line) != ft_strlen(limiter) + 1
		|| ft_strncmp(line, limiter, ft_strlen(limiter)))
	{
		i = 1;
		while (cmds[i++])
			write(STDIN_FILENO, "pipe ", 5);
		write(STDIN_FILENO, "heredoc> ", 9);
		input = ft_strnjoin(input, line, ft_strlen(line));
		free(line);
		line = get_next_line(STDIN_FILENO);
	}
	free(line);
	fd = open(".here_doc", O_RDWR | O_CREAT | O_TRUNC, 0666);
	write(fd, input, ft_strlen(input));
	close(fd);
	free(input);
	ft_hd_multiple_pipes(cmds, ".here_doc", outfile);
	unlink(".here_doc");
}
