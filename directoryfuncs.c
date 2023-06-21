#include "header.h"

void change_to_home_directory(EnvNode *top)
{
    char *home = "HOME";
    const char *home_directory = get_env(top, home);

    if (home_directory != NULL)
    {
        if (chdir(home_directory) == -1)
        {
            perror("chdir");
            return;
        }
    }
}

void change_to_previous_directory()
{
    const char *previous_directory;

    previous_directory = getenv("OLDPWD");
    if (previous_directory != NULL)
    {
        if (chdir(previous_directory) == -1)
        {
            perror("chdir");
        }
    }
}

void change_directory(char *path)
{
    chdir(path);
}