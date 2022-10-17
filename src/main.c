#include "constants.h"
#include "menu.h"

int main(void)
{
    while (menu() == 0);

    return EXIT_SUCCESS;
}