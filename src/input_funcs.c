#include "constants.h"
#include "struct.h"

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

int input_student(struct Student *stud)
{
    int rc = 0;

    printf("Введите имя студента: ");
    rc = string_field_input(stud->name);

    printf("Введите пол студента (0 - женский, 1 - мужской): ");
    if (scanf("%d", stud->sex) != 1 || (stud->sex != 0 && stud->sex != 1))
        return INCORRECT_DATA;
    
    printf("Введите возраст (от 17 до 40 лет): ");
    if (scanf("%d", stud->age) != 1 || stud->age < MIN_AGE || stud->age > MAX_AGE)
        return INCORRECT_DATA;
    
    printf("Введите среднюю оценку (от 0 до 100 баллов): ");
    if (scanf("%d", stud->average_grade) != 1 || stud->average_grade < MIN_AVERAGE || \
     stud->average_grade > MAX_AVERAGE)
        return INCORRECT_DATA;
    
    printf("Введите год поступления (от 1800 до 2022 года): ");
    if (scanf("%d", stud->admission_year) != 1 || stud->admission_year < MIN_YEAR || \
     stud->admission_year > MAX_YEAR)
        return INCORRECT_DATA;
    
    printf("Введите тип дома (0 - обычный дом, 1 - общага): ");
    if (scanf("%d", stud->house_type) != 1 || (stud->house_type != 0 && stud->house_type != 1))
        return INCORRECT_DATA;

    if (stud->house_type)
    {
        printf("Введите номер общаги (от 1 до 9): ");
        if (scanf("%d", stud->adress.obshaga.obshaga_num) != 1 || \
         stud->adress.obshaga.obshaga_num < 1 || stud->adress.obshaga.obshaga_num > 9)
            return INCORRECT_DATA;
        
        printf("Введите номер комнаты (от 1 до 100): ");
        if (scanf("%d", stud->adress.obshaga.room_num) != 1 || \
         stud->adress.obshaga.room_num < 1 || stud->adress.obshaga.room_num > 100)
            return INCORRECT_DATA;
    }
    else
    {
        printf("Введите имя улицы: ");
        rc = string_field_input(stud->adress.home_adress.street);

        printf("Введите номер дома (от 1 до 100): ");
        if (scanf("%d", stud->adress.home_adress.house_num) != 1 || \
         stud->adress.home_adress.house_num < 1 || stud->adress.home_adress.house_num > 100)
            return INCORRECT_DATA;
        
        printf("Введите номер квартиры (от 1 до 1000): ");
        if (scanf("%d", stud->adress.home_adress.flat_num) != 1 || \
         stud->adress.home_adress.flat_num < 1 || stud->adress.home_adress.flat_num > 1000)
            return INCORRECT_DATA;
    }

    return rc;
}
