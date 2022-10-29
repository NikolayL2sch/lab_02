#ifndef SORT_H
#define SORT_H

#include "struct.h"

unsigned long long tick(void);
void measure_sorting_time(void);

int bubble_table(table_t table);
void bubble_sort_students(student_t *students, int size);
void bubble_sort_keys(key_t *keys, int size);
int bubble_table_keys(table_t table);
int comparator_table(const void *val1, const void *val2);
int qsort_table(table_t table);
int comparator_keys(const void *val1, const void *val2);
int qsort_keys(table_t table);
unsigned long long tick_count(void);
void print_result(unsigned long long start, unsigned long long end);
int compare_sorts(FILE *f);

#endif // SORT_H
