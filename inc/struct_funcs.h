#ifndef _STRUCT_FUNCS_H
#define _STRUCT_FUNCS_H

#include "struct.h"

int load_table(FILE *f, struct StudentTable *tbl);
void clear_table(struct StudentTable *tbl);
int save_table_into_file(FILE *f, struct StudentTable *tbl);
void print_students_into_file(FILE *f, struct Student stud);
int add_to_table(struct StudentTable *tbl, const struct Student *stud);
int remove_from_table(struct StudentTable *tbl, int i);
int cmp_stud(const void *a, const void *b);
void sort_stud_table(struct StudentTable *tbl);
void output_stTable_console(struct StudentTable *tbl);
int create_key_table(struct StudentTable* arr_stud, struct KeyTable* arr_keys);
int cmp_key(const void *key1, const void  *key2);
void sort_key_table(struct KeyTable *arr_keys);
void print_key_table(const struct KeyTable* arr_keys);
int print_stud_table_by_key(const struct StudentTable* arr_stud, const struct KeyTable* arr_keys);
void search(struct StudentTable *tbl);
void clear_key_table(struct KeyTable* arr_keys);
void output_student_console(struct Student stud);

#endif