#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/student.h"

Student students[MAX_STUDENTS];
int studentCount = 0;

void loadStudentsFromFile() {
    FILE *f = fopen("data/students.txt", "r");
    if (!f) return;

    fread(&studentCount, sizeof(int), 1, f);
    fread(students, sizeof(Student), studentCount, f);
    fclose(f);
}

void saveStudentsToFile() {
    FILE *f = fopen("data/students.txt", "w");
    if (!f) {
        perror("Could not save students");
        return;
    }

    fwrite(&studentCount, sizeof(int), 1, f);
    fwrite(students, sizeof(Student), studentCount, f);
    fclose(f);
}

void addStudent() {
    if (studentCount >= MAX_STUDENTS) {
        printf("Maximum student limit reached!\n");
        return;
    }

    Student s;
    printf("Enter Student ID: ");
    scanf("%d", &s.id); getchar();

    for (int i = 0; i < studentCount; i++) {
        if (students[i].id == s.id) {
            printf("Student ID already exists.\n");
            return;
        }
    }

    printf("Enter Student Name: ");
    fgets(s.name, MAX_NAME_LEN, stdin);
    s.name[strcspn(s.name, "\n")] = 0;

    float total = 0;
    for (int i = 0; i < MAX_SUBJECTS; i++) {
        printf("Subject %d Name: ", i + 1);
        fgets(s.subjects[i].name, MAX_SUBJECT_NAME, stdin);
        s.subjects[i].name[strcspn(s.subjects[i].name, "\n")] = 0;

        printf("Subject %d Teacher: ", i + 1);
        fgets(s.subjects[i].teacher, MAX_NAME_LEN, stdin);
        s.subjects[i].teacher[strcspn(s.subjects[i].teacher, "\n")] = 0;

        printf("Enter Mark for %s: ", s.subjects[i].name);
        scanf("%d", &s.subjects[i].mark); getchar();
        total += s.subjects[i].mark;
    }

    s.average = total / MAX_SUBJECTS;
    students[studentCount++] = s;
    saveStudentsToFile();

    printf("Student added successfully!\n");
}

void displayStudents() {
    if (studentCount == 0) {
        printf("No student records found.\n");
        return;
    }

    for (int i = 0; i < studentCount; i++) {
        printf("\n--- Student %d ---\n", i + 1);
        printf("ID: %d | Name: %s | Avg: %.2f\n", students[i].id, students[i].name, students[i].average);
        for (int j = 0; j < MAX_SUBJECTS; j++) {
            printf("  %s (%s): %d\n", students[i].subjects[j].name, students[i].subjects[j].teacher, students[i].subjects[j].mark);
        }
    }
}

void searchStudent() {
    int id;
    printf("Enter student ID to search: ");
    scanf("%d", &id);

    for (int i = 0; i < studentCount; i++) {
        if (students[i].id == id) {
            printf("Found: %s | Avg: %.2f\n", students[i].name, students[i].average);
            return;
        }
    }
    printf("Student not found.\n");
}

void updateMarks() {
    int id;
    printf("Enter Student ID to update: ");
    scanf("%d", &id); getchar();

    for (int i = 0; i < studentCount; i++) {
        if (students[i].id == id) {
            float total = 0;
            for (int j = 0; j < MAX_SUBJECTS; j++) {
                printf("Update mark for %s: ", students[i].subjects[j].name);
                scanf("%d", &students[i].subjects[j].mark); getchar();
                total += students[i].subjects[j].mark;
            }
            students[i].average = total / MAX_SUBJECTS;
            saveStudentsToFile();
            printf("Marks updated.\n");
            return;
        }
    }
    printf("Student not found.\n");
}

void deleteStudent() {
    int id;
    printf("Enter ID to delete: ");
    scanf("%d", &id);

    int found = 0;
    for (int i = 0; i < studentCount; i++) {
        if (students[i].id == id) {
            found = 1;
            for (int j = i; j < studentCount - 1; j++) {
                students[j] = students[j + 1];
            }
            studentCount--;
            saveStudentsToFile();
            printf("Student deleted.\n");
            break;
        }
    }

    if (!found) {
        printf("Student ID not found.\n");
    }
}

