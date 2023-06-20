#include "header.h"

uid_t get_uid(void)
{
    const char *self_path = "/proc/self";
    struct stat st;

    if (stat(self_path, &st) == -1)
	{
        perror("stat");
        return -1;
    }

    return (st.st_uid);
}

void change_to_home_directory()
{
    uid_t uid;
    struct passwd *pw;

    uid = get_uid();
    pw = getpwuid(uid);
    if (pw == NULL)
    {
        // Failed to get user information
        perror("getpwuid");
        return;
    }
    if (chdir(pw->pw_dir) != 0)
    {
        // Failed to change directory
        perror("chdir");
    }
}

void change_to_previous_directory()
{
    const char *previous_directory;

    previous_directory = getenv("OLDPWD");  // Get the value of the OLDPWD environment variable
    if (previous_directory != NULL)
    {
        if (chdir(previous_directory) == -1)
        {  // Change to the previous directory using chdir
            perror("chdir");
        }
    }
    else
    {
        printf("No previous directory available\n");
    }
}

void change_directory(char *path)
{
    chdir(path);
}