#include "constants.h"
#include "input_funcs.h"
#include "struct.h"

int read_from_file(FILE *f, student_t *students, int *size, key_t *keys)
{
    system("clear");
    
    int stud_cnt = *size;
    int rc = 0;
    while(!feof(f))
    {
    	rc = fscanf(f, "%100s %d %d %d %d %d", students[stud_cnt].name, &students[stud_cnt].sex, &students[stud_cnt].age, &students[stud_cnt].average_grade, &students[stud_cnt].admission_year, &students[stud_cnt].house_type);
    	keys[stud_cnt].id = stud_cnt;
        keys[stud_cnt].key = students[stud_cnt].average_grade;
    	if (rc != 6)
    		return INCORRECT_DATA;

        if (students[stud_cnt].house_type == 0)
        {
            home_adress_t adress;
            rc = fscanf(f, "%s %d %d", adress.street, &adress.house_num, &adress.flat_num);
            if (rc != 3)
                return INCORRECT_DATA;
            students[stud_cnt].home_adress.home_adress = adress;

        }
        else if (students[stud_cnt].house_type == 1)
        {
            obshaga_t obshaga;
            rc = fscanf(f, "%d %d", &obshaga.obshaga_num, &obshaga.room_num);
            if (rc != 2)
                return INCORRECT_DATA;
            students[stud_cnt].home_adress.obshaga_adress = obshaga;
            
        }
        else
        {
            rc = INCORRECT_DATA;
            break;
        }
        stud_cnt++;
        if (stud_cnt > MAX_SIZE)
        {
            rc = MEMORY_ERROR;
            break;
        }
    }
    fseek(f, 0, SEEK_SET);

    *size = stud_cnt;

    return EXIT_SUCCESS;
}

int add_student(student_t *students, int *size, key_t *keys)
{
    student_t new_student;
    system("clear");
    int rc = 0;

    printf("Введите имя студента: ");
    rc = string_field_input(new_student.name);
    if (rc)
        return INCORRECT_DATA;
    
    printf("Введите пол студента (0 - женский, 1 - мужской): ");
    if (scanf("%d", &new_student.sex) != 1 || (new_student.sex != 0 && new_student.sex != 1))
        return INCORRECT_DATA;
    
    printf("Введите возраст (от 17 до 40 лет): ");
    if (scanf("%d", &new_student.age) != 1 || new_student.age < MIN_AGE || new_student.age > MAX_AGE)
        return INCORRECT_DATA;
    
    printf("Введите среднюю оценку (от 0 до 100 баллов): ");
    if (scanf("%d", &new_student.average_grade) != 1 || new_student.average_grade < MIN_AVERAGE || \
     new_student.average_grade > MAX_AVERAGE)
        return INCORRECT_DATA;
    
    printf("Введите год поступления (от 1800 до 2022 года): ");
    if (scanf("%d", &new_student.admission_year) != 1 || new_student.admission_year < MIN_YEAR || \
     new_student.admission_year > MAX_YEAR)
        return INCORRECT_DATA;
    
    printf("Введите тип дома (0 - обычный дом, 1 - общага): ");
    if (scanf("%d", &new_student.house_type) != 1 || (new_student.house_type != 0 && new_student.house_type != 1))
        return INCORRECT_DATA;

    if (new_student.house_type)
    {
        printf("Введите номер общаги (от 1 до 9): ");
        if (scanf("%d", &new_student.home_adress.obshaga_adress.obshaga_num) != 1 || \
         new_student.home_adress.obshaga_adress.obshaga_num < 1 || new_student.home_adress.obshaga_adress.obshaga_num > 9)
            return INCORRECT_DATA;
        
        printf("Введите номер комнаты (от 1 до 100): ");
        if (scanf("%d", &new_student.home_adress.obshaga_adress.room_num) != 1 || \
         new_student.home_adress.obshaga_adress.room_num < 1 || new_student.home_adress.obshaga_adress.room_num > 100)
            return INCORRECT_DATA;
    }
    else if (new_student.house_type == 0)
    {
        printf("Введите имя улицы: ");
        rc = string_field_input(new_student.home_adress.home_adress.street);
        if (rc)
            return INCORRECT_DATA;
        
        printf("Введите номер дома (от 1 до 100): ");
        if (scanf("%d", &new_student.home_adress.home_adress.house_num) != 1 || \
         new_student.home_adress.home_adress.house_num < 1 || new_student.home_adress.home_adress.house_num > 100)
            return INCORRECT_DATA;
        
        printf("Введите номер квартиры (от 1 до 1000): ");
        if (scanf("%d", &new_student.home_adress.home_adress.flat_num) != 1 || \
         new_student.home_adress.home_adress.flat_num < 1 || new_student.home_adress.home_adress.flat_num > 1000)
            return INCORRECT_DATA;
    }
    else
        return INCORRECT_DATA;
    
    *size += 1;

    if (*size > MAX_SIZE)
        return MEMORY_ERROR;

    keys[*size - 1].key = new_student.average_grade;
    keys[*size - 1].id = *size - 1;

    students[*size - 1] = new_student;

    return EXIT_SUCCESS;
}

void swap_students(student_t *students, int i, int j)
{
    student_t tmp;

    tmp = students[i];
    students[i] = students[j];
    students[j] = tmp;
}


void swap_keys(key_t *keys, int i, int j)
{
    key_t tmp;

    tmp = keys[i];
    keys[i] = keys[j];
    keys[j] = tmp;
}

void del_by_id(student_t *students, key_t *keys, int size, int id)
{
    for (int i = id; i < size; i++)
    {
        swap_students(students, i, i + 1);
    }

    for (int i = id; i < size; i++)
    {
        swap_keys(keys, i, i + 1);
        keys[i].id -= 1;
    }
}

int delete_by_grade(student_t *students, int *size, key_t *keys)
{
    int rc = 0;
    int students_cnt = *size;

    system("clear");

    if (*size == 0)
        return DATA_EMPTY_ERR;

    puts("Введите значение средней оценки: ");
    int avg_grade_to_del;
    rc = scanf("%d", &avg_grade_to_del);
    if (rc != 1 || avg_grade_to_del < 0 || avg_grade_to_del > 100)
        return INCORRECT_DATA;
    
    for (int student = 0; student < students_cnt; student++)
    {
        if (students[student].average_grade == avg_grade_to_del)
        {
            del_by_id(students, keys, *size, student);
            *size -= 1;
        }
    }

    if (*size == students_cnt)
        printf("\nСтуденты с таким средним баллом не найдены.\n");
    else
        printf("\nСтуденты с таким средним баллом успешно удалены.\n");

    return EXIT_SUCCESS;
}

void print_student(student_t student)
{
    printf("%-20s | %7d | %6d | %6d |  %5d | %5d |", student.name, student.sex, student.age, student.average_grade, student.admission_year, student.house_type);

    if (student.house_type == 1)
        printf(" %18d | %7d |       --      |  -- |     --   \n", student.home_adress.obshaga_adress.obshaga_num, student.home_adress.obshaga_adress.room_num);
    else if (student.house_type == 0)
        printf("         --         |    --   | %14s | %3d | %8d", student.home_adress.home_adress.street, student.home_adress.home_adress.house_num, student.home_adress.home_adress.flat_num);
}

int search(table_t table)
{
    int admission_year;
    system("clear");

    if (table.size == 0)
        return DATA_EMPTY_ERR;

    printf("Введите год поступления (от 1800 до 2022 года): ");
    if (scanf("%d", &admission_year) != 1 || admission_year < MIN_YEAR || \
     admission_year > MAX_YEAR)
        return INCORRECT_DATA;

    int flag = 0;

    for (int student = 0; student < table.size; student++)
    {
        if ((table.ptr_first[student].house_type == 1) && (table.ptr_first[student].admission_year == admission_year))
        {
            if (flag == 0)
            {
                puts("\n\n    Имя   | Пол | Возраст |  Средняя оценка  |  Год поступления | Тип жилища |  Номер общежития   | Комната |     Улица     | Дом | Квартира");

                puts("--------------------------------------------------------------------------------------------------------------");
            }

            print_student(table.ptr_first[table.keys[student].id]);

            flag = 1;
        }
    }

    if (!flag)
        printf("\nЗначений, подходящих под данный фильтр не найдено.\n");

    return EXIT_SUCCESS;
}

int print_table(table_t table)
{
    system("clear"); 
    int size = table.size;
    if (table.size == 0)
        return DATA_EMPTY_ERR;

    student_t *students = table.ptr_first;

    puts("    Имя   | Пол | Возраст |  Средняя оценка  |  Год поступления | Тип жилища |  Номер общежития   | Комната |     Улица     | Дом | Квартира");

    puts("--------------------------------------------------------------------------------------------------------------");

    for (int student = 0; student < size; student++)
    {
        print_student(students[student]);
    }
}

int print_keys(table_t table)
{
    system("clear"); 
    int size = table.size;
    if (table.size == 0)
        return INCORRECT_DATA;

    key_t *keys = table.keys;
    puts("    Таблица ключей");
    for (int key = 0; key < size; key++)
    {
        printf("Номер: %3d  | Средняя оценка: %9d  \n", keys[key].id, keys[key].key);
    }
}

int print_table_by_keys(table_t table)
{
    system("clear");
    if (table.size == 0)
        return INCORRECT_DATA;

    puts("    Имя   | Пол | Возраст |  Средняя оценка  |  Год поступления | Тип жилища |  Номер общежития   | Комната |     Улица     | Дом | Квартира");

    puts("--------------------------------------------------------------------------------------------------------------");
    for (int student = 0; student < table.size; student++)
    {
        print_student(table.ptr_first[table.keys[student].id]);
    }
}