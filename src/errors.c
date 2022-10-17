#include "errors.h"
#include "constants.h"

void print_add_err(int rc)
{
    switch (rc)
    {
        case EXIT_FAILURE:
            printf("\nОШИБКА! Введенно неправильное значение.");
            break;
        case DATA_EMPTY_ERR:
            printf("\nОШИБКА! Пропущено значение или записано - ;;");
            break;
        case FILE_NOT_FOUND:
            printf("\nОШИБКА! ФАЙЛ не найден");
            break;
        case MAIN_STRING_OVERFLOW:
            printf("\nОШИБКА! ФАЙЛ - одна из строк переполнена");
            break;
        case INCORRECT_CHOICE:
            printf("\nОШИБКА! Некорректный выбор в меню.");
        case INCORRECT_FILENAME:
            printf("\nОШИБКА! Некорректно задано имя файла.");
    }
}