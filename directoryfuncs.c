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

void change_to_previous_directory(EnvNode *top)
{
    const char *previous_directory;
    char* oldpwd = "OLDPWD";

    previous_directory = get_env(top, oldpwd);
    if (previous_directory != NULL)
    {
        if (chdir(previous_directory) == -1)
        {
            perror("chdir");
        }
    }
}

void change_directory(EnvNode *top, char *path)
{
    char *previous_directory, *pwd = "PWD", *oldpwd = "OLDPWD", *newpwd;

    previous_directory = get_env(top, pwd);
    if (chdir(path) == -1)
    {
        perror("chdir");
    }
    else
    {
        newpwd = get_env(top, pwd);
        set_env(&top, oldpwd, previous_directory);
        set_env(&top, pwd, newpwd);
    }

}