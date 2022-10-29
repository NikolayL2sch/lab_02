#ifndef _STRUCT_H
#define _STRUCT_H

#include "constants.h"

typedef struct
{
    int obshaga_num;
    int room_num;
} obshaga_t;

typedef struct
{
    char street[MAX_FIELD_LEN];
    int house_num;
    int flat_num;
} home_adress_t;

typedef union
{
    home_adress_t home_adress;
    obshaga_t obshaga_adress;
} adress_t;

typedef struct
{
    char name[MAX_FIELD_LEN];
    int sex; // 0 = female, 1 = male
    int age;
    int average_grade;
    int admission_year;
    int house_type; // 0 = home, 1 = obshaga
    adress_t home_adress;
} student_t;

typedef struct key
{
    int key;
    int id;
} key_t;

typedef struct table
{
    student_t *ptr_first;
    key_t *keys;
    int size;
    int size_max;
} table_t;

#endif //_STRUCT_H