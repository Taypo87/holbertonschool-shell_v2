#include "header.h"

void setup_output_redirection(CommandNode *command)
{
    int output_fd;
    output_fd = open(command->redirection_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (output_fd == -1)
    {
        perror("open");
        exit(EXIT_FAILURE);
    }
    dup2(output_fd, STDOUT_FILENO);
    close(output_fd);
}

void setup_input_redirection(CommandNode *command)
{
    int input_fd;
    input_fd = open(command->redirection_file, O_RDONLY);
    if (input_fd == -1)
    {
        perror("open");
        exit(EXIT_FAILURE);
    }
    dup2(input_fd, STDIN_FILENO);
    close(input_fd);
}

void setup_append_redirection(CommandNode *command)
{
    int output_fd;
    output_fd = open(command->redirection_file, O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (output_fd == -1)
    {
        perror("open");
        exit(EXIT_FAILURE);
    }
    dup2(output_fd, STDOUT_FILENO);
    close(output_fd);
}

void setup_heredoc_redirection(CommandNode *command)
{
    int input_fd;
    FILE *file = fopen(command->redirection_file, "r");
    if (file == NULL)
    {
        perror("fopen");
        exit(EXIT_FAILURE);
    }
    input_fd = fileno(file);
    if (dup2(input_fd, STDIN_FILENO) == -1)
    {
        perror("dup2");
        exit(EXIT_FAILURE);
    }
    fclose(file);
}
