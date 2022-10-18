#ifndef _INPUT_H
#define _INPUT_H
#include "struct.h"

void file_input(char *filename);
int string_field_input(char *str);
int input_student(struct Student *stud);
struct Student *input_student_file(FILE *f);

#endif //INPUT_H