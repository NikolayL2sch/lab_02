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

void swap_students(struct Student *a, struct Student *b);
void mysort_stud(struct Student *base, int nitems);
void swap_keys(struct Key *a, struct Key *b);
void mysort_keys(struct Key *base, size_t nitems);

#endif // SORT_H