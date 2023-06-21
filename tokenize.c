#include "header.h"

CommandNode* parse_input(char *line, CommandNode **head)
{
	CommandNode *current = NULL;
	char *line_copy, *token;
	line_copy = copy_string(line);
	token = strtok(line_copy, " \n");
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

size_t handle_builtins(char *line, CommandNode **head, EnvNode **top, char **env_array)
{
	char *exit_string = "exit", *cd = "cd", *previousdir = "-";
	char *env = "env", *set_evniron = "setenv", *unset_environ = "unsetenv";
	char *line_copy, *token, *key, *value, *pwd = "PWD", *cwd;
	line_copy = copy_string(line);

	token = strtok(line_copy, " ");

	if (token != NULL)
	{
		if (string_compare(token, exit_string) == 0)
		{
			free(line_copy);
			free(line);
            free_array(env_array);
            free_env_list(top);
			free_command_list(head);
			exit(0);
		}
		else if (string_compare(token, cd) == 0)
		{
			token = strtok(NULL, " \n");
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
				change_to_home_directory(*top);
				free(line_copy);
				return(1);
			}
			cwd = getcwd(NULL, 0);
			set_env(top, pwd, cwd);
			free(line_copy);
			free(cwd);
		}
		else if (string_compare(token, env) == 0)
		{
			print_env();
			free(line_copy);
			return(1);
		}
        else if (string_compare(token, set_evniron) == 0)
        {
            key = strtok(NULL, " ");
            value = strtok(NULL, " \n");
            set_env(top, key, value);
            free(line_copy);
            return(1);
        }
        else if (string_compare(token, unset_environ) == 0)
        {
            token = strtok(NULL, " \n");
            unset_env(top, token);
            free(line_copy);
            return(1);
        }
	}
	free(line_copy);
	return(0);
}

char *pathfinder(char *command, EnvNode **top)


{
	char *current_path, *temp_path, *fullpath;
	char *path_tok, *path = "PATH";
	size_t arglen = string_length(command);

	fullpath = NULL;
	if (access(command, F_OK) == 0)
	{
		return (command);
	}
	path_tok = NULL;
	current_path = get_env(*top, path);
	temp_path = copy_string(current_path);
	path_tok = strtok(temp_path, ":");
	while (path_tok)
	{
		fullpath = malloc(arglen + string_length(path_tok) + 2);
		sprintf(fullpath, "%s/%s", path_tok, command);
		if (access(fullpath, F_OK) == 0)
		{
			free(command);
			free(temp_path);
			return (fullpath);
		}
		path_tok = strtok(NULL, ":");
		free(fullpath);

	}
	free(temp_path);
	return (NULL);
}
