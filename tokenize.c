#include "header.h"

CommandNode* parse_input(char *line, CommandNode **head)
{
    CommandNode *current = NULL;
    char *line_copy;
    line_copy = copy_string(line);
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
    free(line_copy);
    return(*head);
}

size_t handle_builtins(char *line, CommandNode **head)
{
    char *exit_string = "exit", *cd = "cd", *previousdir = "-";
    char *env = "env";
    char *line_copy, *token;
    line_copy = copy_string(line);

    token = strtok(line_copy, " ");

    if (token != NULL)
    {
        if (string_compare(token, exit_string) == 0)
        {
            free(line_copy);
            free(line);
            free_command_list(head);
            exit(0);
        }
        else if (string_compare(token, cd) == 0)
        {
            token = strtok(NULL, " ");
            if (token != NULL)
            {
                if (string_compare(token, previousdir) == 0)
                {
                    change_to_previous_directory();
                    free(line_copy);
                    return(1);
                }
                else
                {
                    change_directory(token);
                    free(line_copy);
                    return(1);
                }
            }   
            else
            {
                change_to_home_directory();
                free(line_copy);
                return(1);
            }
            // Update PWD environment variable
            // this will need to be updated when we get to handling setenv and getenv
            char *cwd = getcwd(NULL, 0);
            setenv("PWD", cwd, 1);
            free(line_copy);
            free(cwd);
        }
        else if (string_compare(token, env) == 0)
        {
            print_env();
            free(line_copy);
            return(1);
        }
    }
    free(line_copy);
    return(0);
}

char *pathfinder(char *command)


{
	char *current_path, *temp_path, *fullpath;
	char *path_tok;
	size_t arglen = strlen(command);

	fullpath = NULL;
	if (strchr(command, '/') != NULL && access(command, F_OK) == 0)  // changes
	{
		return (command);
	}
	path_tok = NULL;
	current_path = getenv("PATH");
	temp_path = copy_string(current_path);   // changes
	path_tok = strtok(temp_path, ":");
	while (path_tok)
	{
		fullpath = malloc(arglen + strlen(path_tok) + 2);
		sprintf(fullpath, "%s/%s", path_tok, command);
		if (access(fullpath, F_OK) == 0)
		{
			free(temp_path);
			return (fullpath);
		}
		path_tok = strtok(NULL, ":");
		free(fullpath);

	}
	free(temp_path);
	return (NULL);
}
