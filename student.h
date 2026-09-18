//
// Created by Alex on 9/11/2026.
//

#ifndef STUDENTDATA_STUDENT_H
#define STUDENTDATA_STUDENT_H

typedef struct student student_t;

student_t *addStudent(student_t *head);
void createNewStudent(student_t *student);
void printStudentsBeginningToEnd(student_t *head);
void printStudentsEndToBeginning(student_t *head);
student_t *removeStudent(char *lastName, student_t *head);
void removeAll(student_t *head);
void studentDataInterface();

#endif //STUDENTDATA_STUDENT_H