#include "header.h"

CommandNode *create_node(char *command)
{
	int i = 0;

	CommandNode *node = (CommandNode *)malloc(sizeof(CommandNode));
	node->command = copy_string(command);
	node->pipeflag = 0;
	node->redirection = NULL;
	node->redirection_file = NULL;
	for (i = 0; i < 13; i++)
		{
			node->args[i] = NULL;
		}
	node->next = NULL;
	return (node);
}

void free_command_list(CommandNode **head)
{
	CommandNode *current = *head;

	while (current != NULL)
	{
		CommandNode *next = current->next;

		free(current->command);
		if (current->args != NULL)
		{
			for (int i = 0; current->args[i] != NULL; i++)
			{
				free(current->args[i]);
			}
		}
		free(current->redirection_file);
		free(current);

		current = next;
	}

	*head = NULL; // Update the head pointer to NULL after freeing all nodes
}

void add_argument(CommandNode *node, char *argument)
{
	int num_args = 0;
	if (node->args != NULL)
	{
		while (node->args[num_args] != NULL)
			num_args++;
	}
  
	if (num_args < 12)
	{
		node->args[num_args] = copy_string(argument);
		node->args[num_args + 1] = NULL;
	}
}


