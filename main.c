#include <stdio.h>
#include "header.h"

int main(int argc, char **argv, char **envp)
{
 
	char *line = NULL;
	size_t bufsize = 0, is_builtin = 0;
	int flags;
    EnvNode *top = NULL;
	CommandNode *head = NULL;

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
			is_builtin = handle_builtins(line, &head, &top); //check for builtins exit cd env
			head = parse_input(line, &head);

			if (is_builtin == 0)
			{
				head->command = pathfinder(head->command, &top);
				execute_commands(head);
				free_command_list(&head);
			}
		}
	
	}
	free(line);
    free_env_list(&top);
	free_command_list(&head);
	exit(0);
}