#include "constants.h"

int file_input(char *filename)
{
    if (!fgets(filename, MAX_FILENAME_LEN, stdin))
        return INCORRECT_FILENAME;

    int len = strlen(filename);
    if (filename[len - 1] == '\n')
        filename[--len] = '\0';

    if (len > MAX_FILENAME_LEN - 1)
        return INCORRECT_FILENAME;

    return EXIT_SUCCESS;
}

int string_field_input(char *str)
{
    if (!fgets(str, MAX_FIELD_LEN, stdin))
        return INCORRECT_DATA;

    int len = strlen(str);
    if (str[len - 1] == '\n')
        str[--len] = '\0';

    if (len > MAX_FIELD_LEN - 1)
        return STRING_OVERFLOW;

    return EXIT_SUCCESS;
}
