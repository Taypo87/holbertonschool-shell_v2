#include "header.h"

int main(int argc, char **argv, char **envp)
{
    //check for pipes and redirections
    //First things first. get the user input with _getline
    //handle builtins
    //parse user input, this is tricky because of the pipes and redirects
    // must parse it in a manner that breaks it up into seperate commands
    // if operator is found
    char *line;
    char *buffer;
    CommandNode list;

    env = envp;

    while (1)
    {
        if (isatty(STDIN_FILENO))
			printf("($) ");
        if (getline(&line, 0, stdin) == -1)
        {
            if (isatty(STDIN_FILENO) != 0)
			    printf("\n");
            free(line);
            exit(0);
        }
        handle_builtins(line); //check for builtins exit cd env
        list = parse_input(line);

        execute_commands(list);
        

    }
}