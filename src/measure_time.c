#include "struct_funcs.h"
#include "input_funcs.h"

#define ITERATIONS 100
#define FILE_NAME_LEN 30

void bubble_sort_students(student_t *students, int size)
{
    for (int i = 0; i < size - 1; i++)
    {
        for (int j = 0; j < size- i - 1; j++)
        {
            if (students[j].admission_year > students[j + 1].admission_year)
                swap_students(students, j, j + 1);
        }
    }
}

int bubble_table(table_t table)
{
    student_t *students = table.ptr_first;

    if (table.size == 0)
        return DATA_EMPTY_ERR;

    bubble_sort_students(students, table.size);
    return EXIT_SUCCESS;
}

void bubble_sort_keys(key_t *keys, int size)
{
    for (int i = 0; i < size - 1; i++)
    {
        for (int j = 0; j < size - i - 1; j++)
        {
            if (keys[j].key > keys[j + 1].key)
            {
                swap_keys(keys, j, j + 1);
            }
        }
    }
}

int bubble_table_keys(table_t table)
{
    key_t *keys = table.keys;

    if (table.size == 0)
        return DATA_EMPTY_ERR;

    bubble_sort_keys(keys, table.size);
    return EXIT_SUCCESS;
}

int comparator_table(const void *val1, const void *val2)
{
    return ((student_t*)(val1))->admission_year - ((student_t*)(val2))->admission_year;
}

int qsort_table(table_t table)
{
    if (table.size == 0)
        return DATA_EMPTY_ERR;
    
    qsort(table.ptr_first, table.size, sizeof(student_t), comparator_table);
    return EXIT_SUCCESS;
}

int comparator_keys(const void *val1, const void *val2)
{
    return ((key_t*)(val1))->key - ((key_t*)(val2))->key;
}

int qsort_keys(table_t table)
{
    if (table.size == 0)
        return DATA_EMPTY_ERR;
    qsort(table.keys, table.size, sizeof(key_t), comparator_keys);
    return EXIT_SUCCESS;
}

unsigned long long tick_count(void)
{
    unsigned long high, low;
    __asm__ __volatile__ (
        "rdtsc\n"
        "movq %%rdx, %0\n"
        "movq %%rax, %1\n"
        : "=r" (high), "=r" (low)
        :: "%rax", "%rbx", "%rcx", "%rdx"
        );

    unsigned long long ticks = ((unsigned long long)high << 32) | low;

    return ticks;
}

void print_result(unsigned long long start, unsigned long long end)
{
    printf("\n %llu тактов, %.10lf секунд\n\n", end - start, (double)(end - start)/GHZ);
}

int compare_sorts(FILE *f)
{
    unsigned long long start_bubble_1, end_bubble_1, start_bubble_2, end_bubble_2, start_qsort_1, end_qsort_1, start_qsort_2, end_qsort_2; 
    system("clear");
    student_t students[MAX_SIZE];
    int size = 0;
    key_t keys[MAX_SIZE];

    int rc = 0;

    rc = read_from_file(f, students, &size, keys);
    if (rc)
        return INCORRECT_DATA;
    
    printf("Сортировка файла из %d записей\n\n", size);
    puts("-------------------------------------------------------------------------");

    start_bubble_1 = tick_count();
    bubble_sort_students(students, size);
    end_bubble_1 = tick_count();
    puts("Сортировка таблицы пузырьком: ");
    print_result(start_bubble_1, end_bubble_1);
    puts("-------------------------------------------------------------------------");
    size = 0;
    rc = read_from_file(f, students, &size, keys);
    if (rc)
        return INCORRECT_DATA;
    
    start_bubble_2 = tick_count();
    bubble_sort_keys(keys, size);
    end_bubble_2 = tick_count();
    puts("Сортировка таблицы ключей пузырьком: ");
    print_result(start_bubble_2, end_bubble_2);

    size = 0;
    puts("-------------------------------------------------------------------------");
    rc = read_from_file(f, students, &size, keys);
    if (rc)
        return INCORRECT_DATA;
    
    start_qsort_1 = tick_count();
    qsort(students, size, sizeof(student_t), comparator_table);
    end_qsort_1 = tick_count();

    puts("Сортировка таблицы qsort: ");
    print_result(start_qsort_1, end_qsort_1);
    size = 0;
    puts("-------------------------------------------------------------------------");

    rc = read_from_file(f, students, &size, keys);
    start_qsort_2 = tick_count();
    qsort(keys, size, sizeof(key_t), comparator_keys);
    end_qsort_2 = tick_count();
    puts("Сортировка таблицы ключей qsort: ");
    print_result(start_qsort_2, end_qsort_2);


    printf("\n%lu Размер массива ключей (в байтах)", sizeof(*keys) * size);
    printf("\n%lu Размер таблицы (в байтах)\n\n", sizeof(*students) * size);
    return EXIT_SUCCESS;
}
