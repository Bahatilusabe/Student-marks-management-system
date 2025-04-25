# Student Marks Management System

A fully featured **Student Marks Management System** designed for schools to manage student records, generate performance reports, analyze subject-level data, and export results in multiple formats. Built using **C programming**, the system offers rich features, including PDF generation, automated remarks, grading customization, and analytics.

---

## Features

Core Functionality

- Add, view, update, and delete student records
- Input and manage marks for 13 different subjects
- Grading system with customizable thresholds
- Support for 100 students across Form 1 to Form 4
- Unique student ID generation

 Advanced Reporting

- Generate detailed **PDF performance reports** with:
  - Subject marks
  - Grades
  - Teacher names
  - Automated student remarks
  - Best & worst performing subjects
  - Subject averages by form
  - Color-coded performance charts
- Export data to **CSV (Excel-compatible)** format

Smart Analytics

- Identify top-performing and struggling subjects by form
- Visual representation of academic performance
- Performance summary with insights for academic planning

Configuration & Customization

- Modify the grading scale easily
- Subject-wise student distribution
- Assign teachers to subjects

 Planned Features

- Email performance reports to guardians
- Graphical dashboard
- Integration with school portals

---

## Subjects Supported

1. Mathematics  
2. English  
3. Kiswahili  
4. Biology  
5. Chemistry  
6. Geography  
7. History  
8. CRE  
9. Physics  
10. Computer Studies  
11. Business Studies  
12. Art Studies  
13. Music Studies  
14. Aviation Studies

---

System Requirements

- GCC Compiler (for building the system)
- Cairo Graphics Library (for PDF generation)
- Linux/MacOS or Windows with terminal emulator (e.g., Git Bash, WSL)

---

## Project Structure

```bash
Student-marks-management-system/
│
├── main.c                      # Entry point of the program
├── include/                   # Header files
├── src/                       # Source code 
├── student.c / student.h      # Student record management
├── grading.c / grading.h      # Grading logic
├── report.c / report.h        # Report and PDF generation
├── README.md                  # You're reading it!

Setup Instructions

Follow these steps to set up the project on your local machine:
- Clone the Repository
Clone the repository and navigate to the project directory:
git clone <repository_url>
cd Student-marks-management-system

- Directory and File Setup
Ensure the following directories and files exist:mkdir -p output/ReportCards
mkdir -p data
touch data/students.txt

- Compile the Program
Use the following gcc command to compile the program:gcc src/main.c src/student.c src/grading.c src/reports.c src/csv_export.c -Iinclude $(pkg-config --cflags --libs cairo) -o student_management.exe

- To run the program
./student_management.exe
