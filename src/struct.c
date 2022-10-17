#include "constants.h"
#include "struct.h"

int load_table(FILE *f, struct StudentTable *tbl)
{
    int size;

    clear_table(tbl);

    if (fscanf(f, "%d\n\n", &size) != 1)
        return INCORRECT_DATA;

    for (int i = 0; i < size; i++)
    {
        fscanf(f, "\n");
        add_to_table(tbl, input_student_file(f));
    }

    return EXIT_SUCCESS;
}

void clear_table(struct StudentTable *tbl)
{
    tbl->size = 0;
    tbl->size_max = 0;

    if (tbl->ptr_first)
    {
        free(tbl->ptr_first);
        tbl->ptr_first = NULL;
    }
}

int save_table_into_file(FILE *f, struct StudentTable *tbl)
{
    struct Student *ptr_cur = tbl->ptr_first; //ptr_first - указатель на первого студента
    fprintf(f, "%d\n\n", tbl->size);

    for (int i = 0; i < tbl->size; i++)
    {
        print_students_into_file(f, *ptr_cur);
        ptr_cur++;
    }

    return EXIT_SUCCESS;
}

void print_students_into_file(FILE *f, struct Student stud)
{
    fprintf(f, "%s\n", stud.name);
    fprintf(f, "%d\n", stud.sex);
    fprintf(f, "%d\n", stud.age);
    fprintf(f, "%d\n", stud.average_grade);
    fprintf(f, "%d\n", stud.admission_year);
    fprintf(f, "%d\n", stud.house_type);

    if (stud.house_type)
    {
        fprintf(f, "%d\n", stud.adress.obshaga.obshaga_num);
        fprintf(f, "%d\n", stud.adress.obshaga.room_num);
    }
    else
    {
        fprintf(f, "%s\n", stud.adress.home_adress.street);
        fprintf(f, "%d\n", stud.adress.home_adress.house_num);
        fprintf(f, "%d\n", stud.adress.home_adress.flat_num);
    }
    fprintf(f, "\n");
}

int add_to_table(struct StudentTable *tbl, const struct Student *stud)
{

    if (tbl->size >= tbl->size_max)
    {
        struct Student *ptr_free = tbl->ptr_first;
        struct Student *ptr_tmp = tbl->ptr_first;

        tbl->size_max += MALLOC_STEP;

        struct Student *ptr_new = (struct Student*) malloc(tbl->size_max * sizeof(struct Student));

        if (ptr_new == NULL)
            return MEMORY_ERROR;

        tbl->ptr_first = ptr_new;

        for (int i = 0; i < tbl->size; i++)
        {
            *ptr_new = *ptr_tmp;
            ptr_tmp++;
            ptr_new++;
        }
        free(ptr_free);
    }

    tbl->size++;
    tbl->ptr_first[tbl->size - 1] = *stud;

    return EXIT_SUCCESS;
}

int remove_from_table(struct StudentTable *tbl, int i)
{
    if (i > 0 && i <= tbl->size)
    {
        tbl->ptr_first[i-1] = tbl->ptr_first[tbl->size-1];
        tbl->size--;
        return EXIT_SUCCESS;
    }
    return EXIT_FAILURE;
}

int cmp_stud(const void *a, const void *b)
{
    return ((struct Student*) a)->average_grade - ((struct Student*) b)->average_grade;
}

void sort_stud_table(struct StudentTable *tbl)
{
    qsort(tbl->ptr_first, tbl->size, sizeof(struct Student), cmp_stud);
}

void output_stTable_console(struct StudentTable *tbl)
{
    struct Student *ptr_cur = tbl->ptr_first;
    printf("\nTable:\n");

    if (!tbl->size)
        puts("Table is empty!");
    else
    {
        printf("--------------------------------------------\n");
        for (int i = 0; i < tbl->size; i++)
        {

            printf("[ Student %d ]\n", (i + 1));
            output_student_console(*ptr_cur);
            printf("--------------------------------------------\n");
            ptr_cur++;
        }
    }
}

int create_key_table(struct StudentTable* arr_stud, struct KeyTable* arr_keys)
{
    struct Student *ptr_s;
    struct Key *ptr_key;

    clear_key_table(arr_keys);

    arr_keys->n = arr_stud->size;

    arr_keys->ptr_first = (struct Key*) malloc(sizeof(struct Key) * arr_keys->n);

    if (arr_keys->ptr_first == NULL)
        return -1; // Error in malloc
    ptr_s = arr_stud->ptr_first;
    ptr_key = arr_keys->ptr_first;
    for (int i = 0; i < arr_keys->n; i++)
    {
        ptr_key->id = i;
        ptr_key->key = ptr_s->admission_year;
        ptr_key++;
        ptr_s++;
    }

    return 0;
}

int cmp_key(const void *key1, const void  *key2)
{
    return ((struct Key*) key1)->key - ((struct Key*) key2)->key;
}

void sort_key_table(struct KeyTable *arr_keys)
{
    qsort(arr_keys->ptr_first, arr_keys->n, sizeof(struct Key), cmp_key);
}

void print_key_table(const struct KeyTable* arr_keys)
{
    printf("\nKey table:\n");

    if (arr_keys->n <= 0)
        printf("Key table is empty.\n");
    else
    {
        struct Key* ptr_key = arr_keys->ptr_first;

        printf("--------------------------------------------\n");
        for (int i = 0; i < arr_keys->n; i++)
        {
            printf("ID:   %d\n", ptr_key->id + 1);
            printf("Key:  %d\n", ptr_key->key);
            printf("--------------------------------------------\n");

            ptr_key++;
        }
    }

}

int print_stud_table_by_key(const struct StudentTable* arr_stud, const struct KeyTable* arr_keys)
{
    struct Key* ptr_key = arr_keys->ptr_first;

    if (arr_keys-> n != arr_stud->size)
    {
        printf("Different sizes of arrays.\nTry to create key table first (7)\n");
        return -1; // Different sizes
    }

    printf("\nTable in key order:\n");

    if (arr_stud->size == 0)
                printf("Table is empty.\n");
    else
    {
        printf("--------------------------------------------\n");

        for (int i = 0; i < arr_keys->n; i++)
        {
            if (ptr_key->id<0 || ptr_key->id>(arr_stud->size - 1))
                return -2; // Invalid ID found

            printf("[ Student %d ]\n", (i + 1));
            output_student_console(arr_stud->ptr_first[ptr_key->id]);
            printf("--------------------------------------------\n");

            ptr_key++;
            }
    }

    return 0;
}

void search(struct StudentTable *tbl)
{
    int flag = 0;
    int year_to_find;

    struct Student *ptr = tbl->ptr_first;
    printf("Input year of admission to find students, that live in hostel: ");
    scanf("%d", &year_to_find);

    for (int i = 0; i < tbl->size; i++)
    {
        if (ptr->admission_year == year_to_find && ptr->house_type == 1)
        {
            flag++;

            printf("[ Student %d ]\n", (i + 1));
            output_student_console(*ptr);
            printf("--------------------------------------------\n");
        }
        ptr++;
    }

    if (!flag)
        printf("  Nothing found.\n");

}