#include "shellV2.h"
/**
 * string_compare - compares two strings
 * Return: 0 for match, -1 if not
*/

int string_compare(char *str1, char *str2)
{
    int i = 0;

    while (str1[i] != '\0' && str2[i] != '\0')
    {
        if (str1[i] != str2[i])
            return (-1);
        i++;
    }
    return(0);

}

int string_length(char *str)
{
    int i = 0;

    while (str[i] != '\0')
    {
        i++;
    }
    return (i);
}

void copy_string(char *string, char *dest)
{
	int i = 0;

	for (i = 0; string[i] != '\0'; i++)
	{
		dest[i] = string[i];
	}
	dest[i] = '\0';
}


 


//if we hit a special charaacter, populate a new node, add new node to end.
// when execute commands start from

