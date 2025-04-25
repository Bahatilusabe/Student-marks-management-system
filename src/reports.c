#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <cairo.h>
#include <cairo-pdf.h>
#include "../include/student.h"
#include "../include/reports.h"
#include "../include/grading.h"

void generateReportCard(int studentID) {
    Student *student = NULL;
    for (int i = 0; i < studentCount; i++) {
        if (students[i].id == studentID) {
            student = &students[i];
            break;
        }
    }

    if (!student) {
        printf("Student not found (ID: %d).\n", studentID);
        return;
    }

    char filename[150];
    snprintf(filename, sizeof(filename), "output/ReportCards/%d_ReportCard.pdf", student->id);

    struct stat st;
    if (stat("output/ReportCards", &st) == -1) {
        mkdir("output", 0755);
        mkdir("output/ReportCards", 0755);
    }

    cairo_surface_t *surface = cairo_pdf_surface_create(filename, 595, 842);
    cairo_t *cr = cairo_create(surface);

    cairo_select_font_face(cr, "Arial", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);
    cairo_set_font_size(cr, 18);
    cairo_move_to(cr, 50, 50);
    cairo_show_text(cr, "Student Report Card");

    cairo_set_font_size(cr, 12);
    cairo_move_to(cr, 50, 100);
    cairo_show_text(cr, "Student Name: ");
    cairo_show_text(cr, student->name);

    cairo_move_to(cr, 50, 120);
    cairo_show_text(cr, "Student ID: ");
    char temp[20];
    sprintf(temp, "%d", student->id);
    cairo_show_text(cr, temp);

    cairo_move_to(cr, 50, 140);
    cairo_show_text(cr, "Average Mark: ");
    sprintf(temp, "%.2f", student->average);
    cairo_show_text(cr, temp);

    for (int i = 0; i < MAX_SUBJECTS; i++) {
        cairo_move_to(cr, 50, 200 + i * 20);
        cairo_show_text(cr, student->subjects[i].name);

        cairo_move_to(cr, 250, 200 + i * 20);
        sprintf(temp, "%d", student->subjects[i].mark);
        cairo_show_text(cr, temp);

        cairo_move_to(cr, 350, 200 + i * 20);
        char gradeStr[2] = { student->subjects[i].grade, '\0' };
        cairo_show_text(cr, gradeStr);
    }

    cairo_show_page(cr);
    cairo_destroy(cr);
    cairo_surface_destroy(surface);

    printf("Report Card generated for Student ID %d: %s\n", student->id, filename);
}

void generateReportCards() {
    if (studentCount == 0) {
        printf("No student records available.\n");
        return;
    }
    for (int i = 0; i < studentCount; i++) {
        generateReportCard(students[i].id);
    }
}

void viewPerformanceAnalytics() {
    if (studentCount == 0) {
        printf("No student data available for analytics.\n");
        return;
    }

    float total = 0, highest = 0, lowest = 100;
    for (int i = 0; i < studentCount; i++) {
        total += students[i].average;
        if (students[i].average > highest) highest = students[i].average;
        if (students[i].average < lowest) lowest = students[i].average;
    }

    float overall = total / studentCount;
    printf("Performance Analytics:\n");
    printf("Overall Average: %.2f\n", overall);
    printf("Highest Average: %.2f\n", highest);
    printf("Lowest Average: %.2f\n", lowest);
}