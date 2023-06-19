#include "header.h"

CommandNode *create_node(char *command)
{
    CommandNode *node = (CommandNode *)malloc(sizeof(CommandNode));
    node->command = strdup(command);
    node->args = NULL;
    node->pipeflag = 0;
    node->redirection_file = NULL;
    node->next = NULL;
    return node;
}

void free_command_list(CommandNode *head)
{
    CommandNode *current = head;
    CommandNode *next;

    while (current != NULL)
    {
        next = current->next;

        free(current->command);
        if (current->args != NULL)
        {
            for (int i = 0; current->args[i] != NULL; i++)
                free(current->args[i]);
            free(current->args);
        }
        free(current->redirection_file);

        free(current);

        current = next;
    }
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
        node->args[num_args] = strdup(argument);
        node->args[num_args + 1] = NULL;
    }
}


