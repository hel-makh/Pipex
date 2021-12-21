/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-makh <hel-makh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/19 12:20:36 by hel-makh          #+#    #+#             */
/*   Updated: 2021/12/21 22:07:35 by hel-makh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/pipex.h"

#include "srcs/ft_free.c"
#include "srcs/ft_split.c"
#include "srcs/ft_strchr.c"
#include "srcs/ft_strcpy.c"
#include "srcs/ft_strdup.c"
#include "srcs/ft_strlen.c"
#include "srcs/ft_strnjoin.c"
#include "srcs/ft_strstr.c"
#include "srcs/ft_getenv.c"
#include "srcs/ft_cmdpath.c"
#include "srcs/ft_perror.c"
#include "srcs/ft_execve_argv.c"

static void	ft_exec_first_cmd(char **cmd, char *infile, int p[2])
{
	int	fd;

	close(p[0]);
	if (dup2(p[1], STDOUT_FILENO) == -1)
		exit(ft_perror("write-end pipe dup2"));
	close(p[1]);
	fd = open(infile, O_RDONLY);
	if (dup2(fd, STDIN_FILENO) == -1)
		exit(ft_perror("input-file dup2"));
	close(fd);
	execve(cmd[0], cmd, NULL);
	exit(EXIT_FAILURE);
}

static void	ft_exec_second_cmd(char **cmd, char *outfile, int p[2])
{
	int		fd;
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
		if (access(outfile, F_OK) == 0)
			unlink(outfile);
		fd = open(outfile, O_RDWR | O_CREAT, 0666);
		if (dup2(fd, STDOUT_FILENO) == -1)
			exit(ft_perror("output-file dup2"));
		close(fd);
		execve(cmd[0], cmd, NULL);
		exit(EXIT_FAILURE);
	}
	else if (pid > 0)
		waitpid(pid, NULL, 0);
}

int	main(int argc, char *argv[], char *envp[])
{
	char	**cmds[3];
	int		cmds_count;
	int		p[2];
	pid_t	pid;

	if (argc != 5)
		exit(EXIT_FAILURE);
	cmds_count = -1;
	while (++cmds_count < argc - 3)
		cmds[cmds_count] = ft_execve_argv(argv[cmds_count + 2], envp);
	cmds[cmds_count] = NULL;
	if (pipe(p) == -1)
		return (ft_perror("pipe"));
	pid = fork();
	if (pid == -1)
		return (ft_perror("fork"));
	else if (pid == 0)
		ft_exec_first_cmd(cmds[0], argv[1], p);
	else if (pid > 0)
	{
		waitpid(pid, NULL, 0);
		ft_exec_second_cmd(cmds[1], argv[argc - 1], p);
	}
	ft_free_3d(cmds);
	return (EXIT_SUCCESS);
}
