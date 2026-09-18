// You should have a .h file that declares function prototypes, structs, etc.
// Your .c file(s) should #include only .h files and contain all the actual C code.
// You need to make a C struct to hold information of a student. In this struct you should have:at a minimum
//
//Once you have your struct, write a program to use it that will prompt the user to
//(1) add an student to the list,
//(2) delete student(s) from the list,
//(3) print the list from beginning to end,
//(4) print the list from end to beginning, and
//(5) exit the program.
//When adding a student, your program prompts for each piece of information,
//and adds the student to the end/tail of the list.
//When deleting, your program prompts for the last name of the student and deletes all the entries with that last name.
//When printing, start at one end of the list,
//traverse and print each student until reaching the other end. When exiting the program,
//free all dynamically allocated memory to leave no memory leak.
//You may use fgets() to input character strings (for names and year).  Read the man page of fgets() for details.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "student.h"

#define BUFFERSIZE 128

typedef struct student {
    char *lastName;
    char *firstName;
    long id;
    char *year;
    int gradYear;
    struct student *next;
    struct student *prev;
} student_t;
int main(void) {
    studentDataInterface();
    return 0;
}
//the add student function takes in the head of a doubly linked list and adds a new student to the end of the list.
//Uses helper function createNewStudent to create a new student struct.
//Allocates memory for new student before calling CreateNewStudent.
//returns the newly added student as the new tail.
student_t *addStudent(student_t *head) {
    student_t *student = malloc(sizeof(student_t));
    createNewStudent(student);
    printf("\nNew Student Added\nStudent name: %s %s\nStudent ID: %lu\nStudent's current year: %s\nStudent's expected graduation year: %d\n", student->firstName, student->lastName, student->id,student->year, student->gradYear);

    student_t *current = head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = student;
    student->prev = current;
    return student;
}
//Helper function to addStudent.
//Takes in an empty student struct that has already been allocated memory
//Takes in user input using fgets() for student information
void createNewStudent(student_t *student) {
    if (student == NULL) {
        return;
    }
    char buffer[BUFFERSIZE];
    int len;
    printf("Please type in the students last name:");
    if (fgets(buffer, BUFFERSIZE, stdin) != NULL) {
        len = (int) strlen(buffer);
        buffer[len-1]='\0';

        student->lastName = (char*) malloc(len);
        strcpy(student->lastName,buffer);
    }
    printf("Please type in the students first name:");
    if (fgets(buffer, BUFFERSIZE, stdin) != NULL) {
        len = (int) strlen(buffer);
        buffer[len-1]='\0';
        student->firstName = (char*) malloc(len);
        strcpy(student->firstName,buffer);
    }
    printf("Please type in the students id number:");
    if (fgets(buffer, BUFFERSIZE, stdin) != NULL) {
        student->id=atol(buffer);
    }
    printf("Please type in the students current year (freshman, sophomore, junior, or senior): ");
    if (fgets(buffer, BUFFERSIZE, stdin)) {
        len = (int)strlen(buffer);
        buffer[len-1]='\0';
        student->year = (char*) malloc(len);
        strcpy(student->year,buffer);
    }
    printf("Please type in the students expected graduation year: ");
    if (fgets(buffer, BUFFERSIZE, stdin)) {
        student->gradYear = atoi(buffer);
    }
    student->next=NULL;
    student->prev=NULL;
}
//Takes in the head of a list and loops through and prints all student info (name, id, year and grad year)
//starts at head of list
void printStudentsBeginningToEnd(student_t *head) {
    student_t *current = head;
    while (current != NULL) {
        printf("\nStudent name: %s %s\nStudent ID: %lu\nStudent's current year: %s\nStudent's expected graduation year: %d\n", current->firstName, current->lastName, current->id,current->year, current->gradYear);
        current = current->next;
    }
}
//Takes in the tail of a list and loops through and prints all student info (name, id, year and grad year)
//starts at tail of list
void printStudentsEndToBeginning(student_t *tail) {
    student_t *current = tail;
    while (current != NULL) {
        printf("\nStudent name: %s %s\nStudent ID: %lu\nStudent's current year: %s\nStudent's expected graduation year: %d\n", current->firstName, current->lastName, current->id,current->year, current->gradYear);
        current = current->prev;
    }
}
//Takes in the head of a list and a lastName of the student(s) to be deleted
//uses free() to deallocate memory for the target student(s)
//returns new head of list
student_t *removeStudent(char *lastName, student_t *head) {
    int isHead = strcmp(head->lastName, lastName) == 0;
    student_t  *current = head;
    while (current != NULL) {
        if (strcmp(current->lastName, lastName) == 0) {
            student_t *next = current->next;

            if (current->prev != NULL) {
                current->prev->next = current->next;
            }
            if (current->next != NULL) {
                current->next->prev = current->prev;
            }
            printf("\nDeleting %s %s\n", current->firstName, current->lastName);
            head = isHead ? head->next : head;
            free(current->lastName);
            free(current->firstName);
            free(current->year);
            free(current);

            current = next;
        }
        else {
            current = current->next;
        }
    }
    return head;
}
//uses removeStudent on all students in list to deallocate memory at end of program
void removeAll(student_t *head) {
    while (head != NULL) {
        head = removeStudent(head->lastName, head);
    }
}
//Provides an interface for users to maintain a list of students by calling different functions on user input
void studentDataInterface() {
    int len,exit = 0;
    char buffer[BUFFERSIZE];
    student_t *head = malloc(sizeof(student_t)), *tail = 0;
    createNewStudent(head);
    while (!exit) {
        printf("\nStudent Data Options:\n"
               "(1) Add Student\n"
               "(2) Delete Student\n"
               "(3) Print Student List beginning to end\n"
               "(4) Print Student List end to beginning\n"
               "(5) Exit\n");
        if (fgets(buffer, BUFFERSIZE, stdin) != NULL) {
            switch (buffer[0]) {
                case '1' :
                    tail = addStudent(head);
                    break;
                case '2' :
                    printf("Enter the last name of the student(s) you want to remove:\n");
                    if (fgets(buffer, BUFFERSIZE, stdin)) {
                        len = (int) strlen(buffer);
                        buffer[len-1]='\0';
                        head = removeStudent(buffer, head);
                    }
                    break;
                case '3' :
                    printStudentsBeginningToEnd(head);
                    break;
                case '4' :
                    if (tail==0) {
                        tail = head;
                    }
                    printStudentsEndToBeginning(tail);
                    break;
                case '5' :
                    exit = 1;
                    removeAll(head);
                    printf("\nGoodbye user!\n");
                    break;
                default :
                    printf("\nUh oh! Something went wrong, please try again\n");
            }
        }
    }
}