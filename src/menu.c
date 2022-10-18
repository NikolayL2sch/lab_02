#include "constants.h"
#include "errors.h"
#include "measure_time.h"
#include "struct_funcs.h"
#include "input_funcs.h"

int menu()
{
    struct StudentTable studentTable = {NULL, 0, 0};
    struct KeyTable keyTable ={NULL, 0};
    int choice = 0, tmp, rc = 0;
    char filename[MAX_FILENAME_LEN];

    struct Student tmp_stud;

    printf("\nМеню взаимодействия:\n\t"
        "1 - Загрузить данные из файла\n\t"
        "2 - Сохранить данные в файл\n\t"
        "3 - Добавить запись\n\t"
        "4 - Удалить запись\n\t"
        "5 - Сортировать записи\n\t"
        "6 - Вывести таблицу\n\t"
        "7 - Создать таблицу ключей\n\t"
        "8 - Сортировать таблицу ключей\n\t"
        "9 - Вывести таблицу ключей\n\t"
        "10 - Print table in key order\n\t"
        "11 - Выполнить поиск\n\t"
        "12 - Измерить время сортировки данных\n\t"
        "0 - Exit\n");

    if (scanf("%d", &choice) != 1)
        print_error(INCORRECT_CHOICE);
    
    if (choice == 0)
    {
        //clear_table(&stTbl);
        return EXIT_FAILURE;
    }
    else if (choice == 1)
    {
        printf("Введите имя файла: ");
        scanf("\n");
        file_input(filename);
        FILE *f_in = fopen(filename, "r");
        if (f_in == NULL || feof(f_in))
        {
            print_error(INCORRECT_FILENAME);
            return INCORRECT_FILENAME;
        }
        rc = load_table(f_in, &studentTable);
        if (rc)
        {
            print_error(rc);
            return rc;
        }
        fclose(f_in);
        printf("Данные из файла загружены в таблицу!");
    }
    else if (choice == 2)
    {
        printf("Введите имя файла: ");
        file_input(filename);
        FILE *f_out = fopen(filename, "w");
        if (f_out == NULL || feof(f_out))
        {
            print_error(INCORRECT_FILENAME);
            return INCORRECT_FILENAME;
        }

        save_table_into_file(f_out, &studentTable);
        fclose(f_out);
    }
    else if (choice == 3)
    {
        input_student(&tmp_stud);
        add_to_table(&studentTable, &tmp_stud);
    }
    else if (choice == 4)
    {
        printf("Введите индекс студента для удаления: ");
        fflush(stdin);
        if (scanf("%d", &tmp) != 1 || tmp < 1 || tmp > studentTable.size)
            return INCORRECT_DATA;
        
        remove_from_table(&studentTable, tmp);
    }
    else if (choice == 5)
    {
        sort_stud_table(&studentTable);
    }
    else if (choice == 6)
    {
        output_stTable_console(&studentTable);
    }
    else if (choice == 7)
    {
        create_key_table(&studentTable, &keyTable);
        printf("Key table was created.");
    }
    else if (choice == 8)
    {
        sort_key_table(&keyTable);
    }
    else if (choice == 9)
    {
        print_key_table(&keyTable);
    }
    else if (choice == 10)
    {
        print_stud_table_by_key(&studentTable, &keyTable);
    }
    else if (choice == 11)
    {
        search(&studentTable);
    }
    else if (choice == 12)
    {
        measure_sorting_time();
    }
    return EXIT_SUCCESS;
}
