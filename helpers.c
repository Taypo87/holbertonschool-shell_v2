int check_pipe(const char *token)
{
	char * pipe = "|";
    return (string_compare(token, pipe) == 0);
}

void handle_pipe(CommandNode **head, CommandNode **current)
{
    (*current)->pipe = 1;

    CommandNode *next_command = create_node(NULL);

    if (*head == NULL)
	{
        *head = next_command;
        *current = next_command;
    }
	else
	{
        (*current)->next = next_command;
        *current = next_command;
    }
}


int print_env()
{
	int i = 0;

	while (env[i])
	{
		printf("%s\n", env[i++]);
	}
	return(0);
}

