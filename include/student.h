#ifndef STUDENT_H
#define STUDENT_H

#include <stdbool.h> // For 'bool' type

#define MAX_SUBJECTS 13
#define MAX_NAME_LEN 50
#define MAX_SUBJECT_NAME 30
#define MAX_STUDENTS 100

// Subject structure
typedef struct {
    char name[MAX_SUBJECT_NAME];
    int mark;
    char teacher[MAX_NAME_LEN];
    char grade;
    char feedback[100];
} Subject;

// Student structure
typedef struct {
    int id;
    char name[MAX_NAME_LEN];
    Subject subjects[MAX_SUBJECTS];
    float average;
} Student;

// Function declarations
void addStudent();
void displayStudents();
void searchStudent();
void updateMarks();
void deleteStudent();
bool loadStudentsFromFile();
bool saveStudentsToFile(); // Updated return type for consistency

// Global variables
extern Student students[MAX_STUDENTS];
extern int studentCount;

#endif // STUDENT_H