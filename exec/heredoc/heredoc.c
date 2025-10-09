/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbolens <lbolens@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 11:21:35 by lbolens           #+#    #+#             */
/*   Updated: 2025/10/03 12:51:21 by lbolens          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/parsing.h"

void handle_heredoc_sigint(int signal)
{
    (void)signal;

    write(STDOUT_FILENO, "\n", 1);
    exit(130);
}

void setup_heredoc_signals(void)
{
    signal(SIGINT, handle_heredoc_sigint);
    signal(SIGQUIT, SIG_IGN);
}

void read_one_heredoc(int pipe_fd[2], char *delim, bool has_quotes, t_env *env)
{
    char    *line;
    char    *expanded;
    
    while (1)
    {
        line = readline("> ");
        if (line == NULL)
        {
            printf("warning: here-document delimited by end-of-file (wanted '%s')\n", delim);
            break;
        }
        if (ft_strcmp_pars(line, delim) == 0)
        {
            free(line);
            break;
        }
        if (!has_quotes)
            expanded = build_full_command(line, env);
        else
            expanded = line;
        write(pipe_fd[1], expanded, ft_strlen_pars(expanded));
        write(pipe_fd[1], "\n", 1);
        if (expanded != line)
            free(expanded);
        free(line);
    }
}

int process_heredoc(t_cmd *cmd, t_env *env)
{
    int     pipe_fd[2];
    int     final_fd;
    int     i;
    pid_t   pid;
    int     status;

    if (cmd->heredoc_count == 0)
        return (STDIN_FILENO);
    i = 0;
    while (i < cmd->heredoc_count)
    {
        if (pipe(pipe_fd) == -1)
            return (-1);
        pid = fork();
        if (pid == -1)
        {
            close(pipe_fd[0]);
            close(pipe_fd[1]);
            return (-1);
        }
        if (pid == 0)
        {
            setup_heredoc_signals();
            read_one_heredoc(pipe_fd, cmd->heredoc_delims[i],
                            cmd->heredoc_delim_quotes[i], env);
            close(pipe_fd[0]);
            close(pipe_fd[1]);
            exit(0);
        }
        close(pipe_fd[1]);
        waitpid(pid, &status, 0);
        if (WIFEXITED(status) && WEXITSTATUS(status) == 130)
        {
            close(pipe_fd[0]);
            env->exit_status = 130;
            return (-2);
        }
        if (i == cmd->heredoc_count - 1)
            final_fd = pipe_fd[0];
        else
            close(pipe_fd[0]);
        i++;
    }
    return (final_fd);
}
