#include <stdio.h>
#include "header.h"

int main(int argc, char **argv, char **envp)
{
 
	char *line = NULL;
	size_t bufsize = 0, is_builtin = 0;
	int flags;
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
			is_builtin = handle_builtins(line, &head, &top, env_array); //check for builtins exit cd env
            free_array(env_array);
			head = parse_input(line, &head);
            env_array = linked_list_to_array(&top);

			if (is_builtin == 0)
			{
                
				head->command = pathfinder(head->command, &top);
				execute_commands(head, env_array);
				free_command_list(&head);
			}
            free_array(env_array);
		}
	
	}
    free_array(env_array);
	free(line);
    free_env_list(&top);
	free_command_list(&head);
	exit(0);
}