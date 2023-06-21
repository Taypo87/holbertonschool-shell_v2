#include "header.h"

void setup_redirection(CommandNode *command)
{
    if (command->redirection != NULL)
    {
        if (strcmp(command->redirection, ">") == 0)
        {
            setup_output_redirection(command);
        }
        else if (strcmp(command->redirection, "<") == 0)
        {
            setup_input_redirection(command);
        }
        else if (strcmp(command->redirection, ">>") == 0)
        {
            setup_append_redirection(command);
        }
        else if (strcmp(command->redirection, "<<") == 0)
        {
            setup_heredoc_redirection(command);
        }
    }
}

void setup_pipe(CommandNode *current, int *pipefd, int input_fd)
{
    if (current->pipeflag == 1)
    {
        if (pipe(pipefd) == -1)
        {
            perror("pipe");
            exit(EXIT_FAILURE);
        }
        if (dup2(input_fd, STDIN_FILENO) == -1)
        {
            perror("dup2");
            exit(EXIT_FAILURE);
        }
        if (dup2(pipefd[1], STDOUT_FILENO) == -1)
        {
            perror("dup2");
            exit(EXIT_FAILURE);
        }
        close(pipefd[1]);
    }
}

void execute_command(CommandNode *command, int input_fd, char** env_array)
{
    pid_t pid = fork();
    if (pid == -1)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    else if (pid == 0)
    {
        setup_redirection(command);
        execve(command->command, command->args, env_array);
        perror("execve");
        exit(EXIT_FAILURE);
    }
    else
    {
        int status;
        waitpid(pid, &status, 0);
        if (input_fd != STDIN_FILENO)
            close(input_fd);
    }
}

void cleanup_pipe(CommandNode *current, int *pipefd, int input_fd)
{
    if (current->pipeflag == 1)
    {
        close(pipefd[0]);
        if (input_fd != STDIN_FILENO)
            close(input_fd);
    }
}

void execute_commands(CommandNode *head, char **env_array)
{
    int pipefd[2];
    int input_fd = STDIN_FILENO;

    CommandNode *current;
    current = head;

    while (current != NULL)
    {
        setup_pipe(current, pipefd, input_fd);
        execute_command(current, input_fd, env_array);
        cleanup_pipe(current, pipefd, input_fd);

        if (current->pipeflag)
        {
            input_fd = pipefd[0];
            current = current->next;
        }
        else
        {
            break;
        }
    }
}
