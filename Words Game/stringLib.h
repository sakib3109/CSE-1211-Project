
#include <stdio.h>

int stringLength(char word[])
{
    // finding length of a string
    int i = 0;
    while (word[i] != '\0')
    {
        i++;
    }
    return i;
}

int stringCmp(char word[], char input[])
{
    // copmaring whether two strings are same or not
    int i = 0;

    while (1)
    {
        if (word[i] != input[i])
            return 0;
        if (word[i] == '\0')
            break;
        i++;
    }

    return 1;
}
