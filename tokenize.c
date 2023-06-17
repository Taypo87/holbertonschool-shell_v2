#include "header.h"


void parse_input(char *line, CommandNode **head)
{
    CommandNode *current = NULL;
    char *token = strtok(line, " \n");
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
        return (void);
    }

    while (token != NULL)
    {
        if (check_pipe(token))
            handle_pipe(head, &current);
        else if (check_redirections(token))
        {
            if (current != NULL)
                handle_redirection(current, token);
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
}

void handle_builtins(char *line)
{
    char *line_copy, char *exit = "exit", char *cd = "cd", char *previousdir = "-";
    char *env = "env";
    copy_string(line, line_copy);
    char *token = strtok(line_copy, " ");

    if (token != NULL)
    {
        if (string_compare(token, exit) == 0)
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

