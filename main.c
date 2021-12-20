/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-makh <hel-makh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/19 12:20:36 by hel-makh          #+#    #+#             */
/*   Updated: 2021/12/20 19:27:19 by hel-makh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/pipex.h"

#include "srcs/ft_free.c"
#include "srcs/ft_split.c"
#include "srcs/ft_strchr.c"
#include "srcs/ft_strdup.c"
#include "srcs/ft_strlen.c"
#include "srcs/ft_strnjoin.c"
#include "srcs/ft_strstr.c"
#include "srcs/ft_getenv.c"
#include "srcs/ft_cmdpath.c"
#include "srcs/ft_perror.c"
#include "srcs/ft_execve_argv.c"

void	ft_execve_first(char ***cmds, char *infile, int p[2])
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
	execve(cmds[0][0], cmds[0], NULL);
	exit(EXIT_FAILURE);
}

void	ft_execve_second(char ***cmds, char *outfile, int p[2])
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
		execve(cmds[1][0], cmds[1], NULL);
		exit(EXIT_FAILURE);
	}
	else
		waitpid(pid, NULL, 0);
	ft_free_3d(cmds);
}

int	main(int argc, char *argv[], char *envp[])
{
	char	**cmds[3];
	int		p[2];
	pid_t	pid;

	if (argc != 5)
		exit(EXIT_FAILURE);
	cmds[0] = ft_execve_argv(argv[2], envp);
	cmds[1] = ft_execve_argv(argv[3], envp);
	cmds[2] = NULL;
	if (pipe(p) == -1)
		return (ft_perror("pipe"));
	pid = fork();
	if (pid == -1)
		return (ft_perror("fork"));
	else if (pid == 0)
		ft_execve_first(cmds, argv[1], p);
	else if (pid > 0)
	{
		waitpid(pid, NULL, 0);
		ft_execve_second(cmds, argv[4], p);
	}
	return (EXIT_SUCCESS);
}
