#include "header.h"

int check_pipe(char *token)
{
	char * pipe = "|";
    return (string_compare(token, pipe) == 0);
}

void handle_pipe(CommandNode **head, CommandNode *current, char* line)
{
	char *cmd;
    CommandNode *next_command;
    current->pipeflag = 1;
	
	cmd = strtok(line, " \n");
    next_command = create_node(cmd);
    next_command->args[0] = copy_string(cmd);

    if (*head == NULL)
	{
        *head = next_command;
        current = next_command;
    }
	else
	{
        (*current).next = next_command;
        current = next_command;
    }

}

int check_redirections(char *token)
{
	char *single_left = "<";
	char *double_left = "<<";
	char *single_right = ">";
	char *double_right = ">>";

	if (string_compare(token, single_left) == 0)
		return(1);
	if (string_compare(token, double_left) == 0)
		return(1);
	if (string_compare(token, single_right) == 0)
		return(1);
	if (string_compare(token, double_right) == 0)
		return(1);
	return(0);
}

void handle_redirection(CommandNode *node, char *redirection)
{
	char *single_left = "<";
	char *double_left = "<<";
	char *single_right = ">";
	char *double_right = ">>";

    if (string_compare(redirection, single_right) == 0)
    {
        char *file = strtok(NULL, " \n");
        node->redirection = ">";
        node->redirection_file = copy_string(file);
    }
    else if (string_compare(redirection, single_left) == 0)
    {
        char *file = strtok(NULL, " \n");
        node->redirection = "<";
        node->redirection_file = copy_string(file);
    }
    else if (string_compare(redirection, double_right) == 0)
    {
        char *file = strtok(NULL, " \n");
        node->redirection = ">>";
        node->redirection_file = copy_string(file);
    }
	else if (string_compare(redirection, double_left) == 0)
    {
        char *file = strtok(NULL, " \n");
        node->redirection = "<<";
        node->redirection_file = copy_string(file);
    }
}


int print_env(char **env_array)
{
	int i = 0;


	while (env_array[i] != NULL)
	{

		printf("%s\n", env_array[i++]);
	}
	return(0);
}

