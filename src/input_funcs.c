#include "constants.h"

int file_input(char *filename)
{
    if (!fgets(filename, MAX_FILENAME_LEN, stdin))
    {
    	//printf("|%s|",filename);
        return INCORRECT_FILENAME;
	}
    int len = strlen(filename);
    if (filename[len - 1] == '\n')
   	{
        filename[--len] = '\0';
    }
	//printf("|%s|",filename);
    if (len > MAX_FILENAME_LEN - 1)
        return INCORRECT_FILENAME;

    return EXIT_SUCCESS;
}
