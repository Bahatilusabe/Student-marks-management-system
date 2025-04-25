#include <stdio.h>
#include <stdlib.h>  // Include for `mkdir`
#include <sys/stat.h> // Include for `mkdir`
#include "../include/student.h"
#include "../include/csv_export.h"

void exportToCSV() {
    // Ensure the output directory exists
    struct stat st = {0};
    if (stat("output", &st) == -1) {
        mkdir("output", 0755);
    }

    FILE *f = fopen("output/student_records.csv", "w");
    if (!f) {
        perror("❌ Failed to create CSV file");
        return;
    }

    // Header row
    fprintf(f, "ID,Name");
    for (int i = 0; i < MAX_SUBJECTS; i++) {
        fprintf(f, ",Subject%d Name,Subject%d Mark,Subject%d Grade", i + 1, i + 1, i + 1);
    }
    fprintf(f, ",Average\n");

    // Data rows
    for (int i = 0; i < studentCount; i++) {
        fprintf(f, "%d,%s", students[i].id, students[i].name);
        for (int j = 0; j < MAX_SUBJECTS; j++) {
            fprintf(f, ",%s,%d,%c",
                students[i].subjects[j].name,
                students[i].subjects[j].mark,
                students[i].subjects[j].grade
            );
        }
        fprintf(f, ",%.2f\n", students[i].average);
    }

    // Close file and confirm success
    if (fclose(f) != 0) {
        perror("❌ Error closing CSV file");
    } else {
        printf("✅ Data exported to output/student_records.csv\n");
    }
}