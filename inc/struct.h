#ifndef _STRUCT_H
#define _STRUCT_H

#include "constants.h"

struct Student
{
    char name[MAX_FIELD_LEN];
    int sex; // 0 = female, 1 = male
    int age;
    int average_grade;
    int admission_year;
    int house_type; // 0 = home, 1 = obshaga

    union
    {
        struct {
            char street[MAX_FIELD_LEN];
            int house_num;
            int flat_num;
        } home_adress;

        struct {
            int obshaga_num;
            int room_num;
        } obshaga;

    } adress;
};

struct StudentTable
{
    struct Student *ptr_first;
    int size;
    int size_max;
};

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

struct Key
{
        int key;
        int id;
}Key;

struct KeyTable
{
        struct Key* ptr_first;
        int n;
};

#endif //_STRUCT_H