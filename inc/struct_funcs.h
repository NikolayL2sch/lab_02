#ifndef _STRUCT_FUNCS_H
#define _STRUCT_FUNCS_H

#include "struct.h"

int read_from_file(FILE *f, student_t *students, int *size, key_t *keys);
int add_student(student_t *students, int *size, key_t *keys);
void swap_students(student_t *students, int i, int j);
void swap_keys(key_t *keys, int i, int j);
void del_by_id(student_t *students, key_t *keys, int size, int id);
int delete_by_grade(student_t *students, int *size, key_t *keys);
void print_student(student_t student);
int search(table_t table);
int print_table(table_t table);
int print_keys(table_t table);
int print_table_by_keys(table_t table);

#endif
