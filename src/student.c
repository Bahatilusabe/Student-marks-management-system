#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/student.h"

Student students[MAX_STUDENTS];
int studentCount = 0;

bool loadStudentsFromFile() {
    FILE *f = fopen("data/students.txt", "rb");
    if (!f) {
        perror("Error opening file");
        return false;
    }
    if (fread(&studentCount, sizeof(int), 1, f) != 1 || studentCount > MAX_STUDENTS) {
        fclose(f);
        printf("Error reading student count.\n");
        return false;
    }
    if (fread(students, sizeof(Student), studentCount, f) != (size_t)studentCount) {
        fclose(f);
        printf("Error reading student data.\n");
        return false;
    }
    fclose(f);
    return true;
}

bool saveStudentsToFile() {
    FILE *f = fopen("data/students.txt", "wb");
    if (!f) {
        perror("Error saving students");
        return false;
    }
    if (fwrite(&studentCount, sizeof(int), 1, f) != 1) {
        fclose(f);
        printf("Error writing student count.\n");
        return false;
    }
    if (fwrite(students, sizeof(Student), studentCount, f) != (size_t)studentCount) {
        fclose(f);
        printf("Error writing student data.\n");
        return false;
    }
    fclose(f);
    return true;
}

void addStudent() {
    if (studentCount >= MAX_STUDENTS) {
        printf("Maximum student limit reached!\n");
        return;
    }

    Student s;
    printf("Enter Student ID: ");
    scanf("%d", &s.id);
    getchar(); // consume newline

    // Verify that ID does not already exist
    for (int i = 0; i < studentCount; i++) {
        if (students[i].id == s.id) {
            printf("Student ID already exists.\n");
            return;
        }
    }

    printf("Enter Student Name: ");
    fgets(s.name, MAX_NAME_LEN, stdin);
    s.name[strcspn(s.name, "\n")] = '\0';

    float total = 0;
    for (int i = 0; i < MAX_SUBJECTS; i++) {
        printf("Subject %d Name: ", i + 1);
        fgets(s.subjects[i].name, MAX_SUBJECT_NAME, stdin);
        s.subjects[i].name[strcspn(s.subjects[i].name, "\n")] = '\0';

        printf("Enter Mark for %s (0-100): ", s.subjects[i].name);
        while (scanf("%d", &s.subjects[i].mark) != 1 || s.subjects[i].mark < 0 || s.subjects[i].mark > 100) {
            printf("Invalid input. Enter a mark between 0 and 100: ");
            while (getchar() != '\n'); // clear input buffer
        }
        getchar(); // consume newline
        total += s.subjects[i].mark;
    }
    s.average = total / MAX_SUBJECTS;
    students[studentCount++] = s;

    if (saveStudentsToFile())
        printf("Student added successfully!\n");
    else
        printf("Failed to save student data.\n");
}

void displayStudents() {
    if (studentCount == 0) {
        printf("No students available.\n");
        return;
    }
    for (int i = 0; i < studentCount; i++) {
        printf("\n--- Student %d ---\n", i + 1);
        printf("ID: %d\nName: %s\nAverage: %.2f\n", students[i].id, students[i].name, students[i].average);
        for (int j = 0; j < MAX_SUBJECTS; j++) {
            printf("Subject: %s  Mark: %d  Teacher: %s\n",
                   students[i].subjects[j].name,
                   students[i].subjects[j].mark,
                   students[i].subjects[j].teacher);
        }
    }
}

void searchStudent() {
    int id;
    printf("Enter student ID to search: ");
    scanf("%d", &id);
    int found = 0;
    for (int i = 0; i < studentCount; i++) {
        if (students[i].id == id) {
            printf("Student Found:\n");
            printf("ID: %d\nName: %s\nAverage: %.2f\n", students[i].id, students[i].name, students[i].average);
            found = 1;
            break;
        }
    }
    if (!found)
        printf("Student with ID %d not found.\n", id);
}

void updateMarks() {
    int id;
    printf("Enter student ID to update marks: ");
    scanf("%d", &id);
    int found = 0;
    for (int i = 0; i < studentCount; i++) {
        if (students[i].id == id) {
            found = 1;
            float total = 0;
            for (int j = 0; j < MAX_SUBJECTS; j++) {
                printf("Enter new mark for %s (0-100): ", students[i].subjects[j].name);
                while (scanf("%d", &students[i].subjects[j].mark) != 1 ||
                       students[i].subjects[j].mark < 0 ||
                       students[i].subjects[j].mark > 100) {
                    printf("Invalid mark. Enter a number between 0 and 100: ");
                    while (getchar() != '\n');
                }
                getchar(); // consume newline
                total += students[i].subjects[j].mark;
            }
            students[i].average = total / MAX_SUBJECTS;
            if (saveStudentsToFile())
                printf("Marks updated successfully.\n");
            else
                printf("Failed to update marks.\n");
            break;
        }
    }
    if (!found)
        printf("Student with ID %d not found.\n", id);
}

void deleteStudent() {
    int id;
    printf("Enter student ID to delete: ");
    scanf("%d", &id);
    int index = -1;
    for (int i = 0; i < studentCount; i++) {
        if (students[i].id == id) {
            index = i;
            break;
        }
    }
    if (index == -1) {
        printf("Student with ID %d not found.\n", id);
        return;
    }
    for (int i = index; i < studentCount - 1; i++) {
        students[i] = students[i + 1];
    }
    studentCount--;
    if (saveStudentsToFile())
        printf("Student deleted successfully.\n");
    else
        printf("Failed to delete student data.\n");
}