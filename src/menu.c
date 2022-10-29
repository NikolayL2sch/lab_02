#include "constants.h"
#include "errors.h"
#include "measure_time.h"
#include "struct_funcs.h"
#include "input_funcs.h"

void print_menu(void)
{
	printf("\nМеню взаимодействия:\n\t"
        "1 - Загрузить данные из файла\n\t"
        "2 - Добавить запись\n\t"
        "3 - Удалить студентов по значению средней оценки\n\t"
        "4 - Вывести список студентов, указанного года поступления, живущих в общежитии\n\t"
        "5 - Отсортировать таблицу студентов (bubble)\n\t"
        "6 - Отсортировать таблицу ключей (bubble)\n\t"
        "7 - Отсортировать таблицу студентов (qsort)\n\t"
        "8 - Отсортировать таблицу ключей (qsort)\n\t"
        "9 - Сравнить сортировки\n\t"
        "10 - Вывести таблицу студентов\n\t"
        "11 - Вывести табоицу студентов по таблице ключей\n\t"
        "12 - Вывести таблицу ключей\n\t"
        "13 - Очистить таблицу\n\t"
        "0 - Завершить выполнение программы\n");
}


int menu()
{
    student_t students[MAX_SIZE];
    table_t table = {.size_max = MAX_SIZE, .size = 0};
    int choice = -1, rc = 0;
    char filename[MAX_FILENAME_LEN];
    key_t keys[MAX_SIZE];

    
    while (choice != 0)
    {
    	print_menu();
    	
    	if (scanf("%d", &choice) != 1)
        	print_error(INCORRECT_CHOICE);
        	
    	if (choice == 1)
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
        	int size = table.size;
        	rc = read_from_file(f_in, students, &size, keys);
        	if (rc)
        	{
        		printf("\nОшибка при чтении из файла!\n");
            	print_error(rc);
            	return rc;
        	}
	
        	table.size = size;
        	table.keys = keys;
        	table.ptr_first = students;
	
        	fclose(f_in);
        	printf("\nДанные из файла загружены в таблицу!\n");
    	}
    	else if (choice == 2)
    	{
        	int size = table.size;
	
        	rc = add_student(students, &size, keys);
	
        	if (rc)
        	{
            	print_error(rc);
            	return rc;
        	}
	
        	table.size = size;
        	table.keys = keys;
        	table.ptr_first = students;
    	}
    	else if (choice == 3)
    	{
        	int size = table.size;
	
        	rc = delete_by_grade(students, &size, keys);
	
        	if (rc)
        	{
            	print_error(rc);
            	return rc;
        	}
	
        	table.size = size;
        	table.keys = keys;
        	table.ptr_first = students;
    	}
    	else if (choice == 4)
    	{
        	rc = search(table);
        	if (rc)
        	{
            	print_error(rc);
            	return rc;
        	}
    	}
    	else if (choice == 5)
    	{
        	system("clear");
        	rc = bubble_table(table);
        	if (rc)
        	{
            	print_error(rc);
            	return rc;
        	}
        	puts("Таблица отсортирована.");
    	}
    	else if (choice == 6)
    	{
        	system("clear");
        	rc = bubble_table_keys(table);
        	if (rc)
        	{
            	print_error(rc);
            	return rc;
        	}
        	puts("Таблица отсортирована.");
    	}
    	else if (choice == 7)
    	{
        	system("clear");
        	rc = qsort_table(table);
        	if (rc)
        	{
            	print_error(rc);
            	return rc;
        	}
        	puts("Таблица отсортирована.");
    	}
    	else if (choice == 8)
    	{
        	system("clear");
        	rc = qsort_keys(table);
        	if (rc)
        	{
            	print_error(rc);
            	return rc;
        	}
        	puts("Таблица отсортирована.");
    	}
    	else if (choice == 9)
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
        	rc = compare_sorts(f_in);
        	if (rc)
        	{
            	print_error(rc);
            	return rc;
        	}
        	fclose(f_in);
    	}
    	else if (choice == 10)
    	{
    		//printf("%d", table.size);
        	rc = print_table(table);
        	if (rc)
        	{
            	print_error(rc);
            	return rc;
        	}
    	}
    	else if (choice == 11)
    	{
        	rc = print_table_by_keys(table);
        	if (rc)
        	{
            	print_error(rc);
            	return rc;
        	}
    	}
    	else if (choice == 12)
    	{
        	rc = print_keys(table);
        	if (rc)
        	{
            	print_error(rc);
            	return rc;
        	}
    	}
    	else if (choice == 13)
    	{
        	system("clear");
        	table.size = 0;
        	puts("Таблица успешно очищена\n");
    	}
    	else if (choice != 0)
    	{
        	print_error(INCORRECT_CHOICE);
        	return INCORRECT_CHOICE;
    	}
    	else
    	{
    		break;
    	}
    }
    return EXIT_SUCCESS;
}
