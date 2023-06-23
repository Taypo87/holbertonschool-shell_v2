#include <stdio.h>
#include "header.h"

int main(int argc, char **argv, char **envp)
{
 
	char *line = NULL, *new_line, *temp;
	size_t bufsize = 0;
	int flags, exit_status = 0;
    EnvNode *top = NULL;
	CommandNode *head = NULL;
    char **env_array;

	env = envp;
    top = load_env(envp);
	if (argc > 1)
	{
		printf("%s\n", argv[1]);
	}
    
	while (1)
	{
		if (isatty(STDIN_FILENO))
			printf("($) ");
		flags = getline(&line, &bufsize, stdin);
		if (flags == -1)
		{
			if (isatty(STDIN_FILENO) != 0)
				printf("\n");
			break;
		}
		else
		{
            env_array = linked_list_to_array(&top);
			temp = (handle_builtins(line, &head, &top, env_array));
			if (temp != NULL)
			{
				new_line = copy_string(temp);
				free(temp);
			}
			else
			{
				new_line = NULL;
				free(temp);
			}
			if (head != NULL)
			{
				free_command_list(&head);
			}
            free_array(env_array);
			if (new_line != NULL)
				head = parse_input(new_line, &head);
            env_array = linked_list_to_array(&top);

			
			if (head != NULL)
			{
				head->command = pathfinder(head->command, &top);
				if (access(head->command, F_OK) != 0)
				{
					fprintf(stderr, "./hsh: 1: %s: not found\n", head->command);
					exit_status = 127;
				}
				else
				{
					execute_commands(head, env_array);
				}
				free_command_list(&head);
			}
            free_array(env_array);
		}
		free(new_line);
	
	}
	free(new_line);
	free(line);
    free_env_list(&top);
	free_command_list(&head);
	exit(exit_status);
}