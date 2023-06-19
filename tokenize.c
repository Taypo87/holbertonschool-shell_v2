#include "header.h"

CommandNode* parse_input(char *line, CommandNode **head)
{
    CommandNode *current = NULL;
    char *line_copy = malloc(string_length(line) + 1);
    copy_string(line, line_copy);
    char *token = strtok(line_copy, " \n");
    if (token != NULL)
    
    {
        *head = create_node(token);
        current = *head;
    }
    else
    {
        *head = create_node(line);
        current = *head;
        add_argument(current, line);
        return (*head);
    }
    while (token != NULL)
    {
        if (check_pipe(token))
            handle_pipe(head, current, line);
        else if (check_redirections(token))
        {
            if (current != NULL)
            {
                handle_redirection(current, token);
                break;
            }
        }
        else
        {
            if (current == NULL)
            {
                *head = create_node(token);
                current = *head;
            }
            else
                add_argument(current, token);
        }
        token = strtok(NULL, " \n");
    }
    return(*head);
}

void handle_builtins(char *line)
{
    char *exit_string = "exit", *cd = "cd", *previousdir = "-";
    char *env = "env";
    char *line_copy = malloc(string_length(line) + 1);
    copy_string(line, line_copy);
    char *token = strtok(line_copy, " ");

    if (token != NULL)
    {
        if (string_compare(token, exit_string) == 0)
            exit(0);
        else if (string_compare(token, cd) == 0)
        {
            token = strtok(NULL, " ");
            if (token != NULL)
            {
                if (string_compare(token, previousdir) == 0)
                    change_to_previous_directory();
                else
                    change_directory(token);
            }
            else
                change_to_home_directory();
            // Update PWD environment variable
            // this will need to be updated when we get to handling setenv and getenv
            char *cwd = getcwd(NULL, 0);
            setenv("PWD", cwd, 1);
            free(cwd);
        }
        else if (string_compare(token, env) == 0)
            print_env();
    }
}


