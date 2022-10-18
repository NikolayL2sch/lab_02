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