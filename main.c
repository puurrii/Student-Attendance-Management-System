#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

struct Student {
    int id;
    char name[50];
    int attendance;
};


void displayMenu();
void addStudent();
void viewRecords();
void takeAttendance();
void deleteRecord();

int main() {
    while (1) {
        displayMenu();

        int choice;
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addStudent();
                break;

            case 2:
                viewRecords();
                break;

            case 3:
                takeAttendance();
                break;

            case 4:
                deleteRecord();
                break;

            case 5:
                printf("Exiting the program.\n");
                exit(0);

            default:
                printf("Invalid choice. Please enter a valid option.\n");
        }
    }

    return 0;
}

void displayMenu() {
    printf("\nAttendance Management System\n");
    printf("1. Add Student\n");
    printf("2. View Records\n");
    printf("3. Take Attendance\n");
    printf("4. Delete Record\n");
    printf("5. Exit\n");
    printf("Enter your choice: ");
}

void addStudent() {
    FILE *file = fopen("students.dat", "ab");
    if (file == NULL) {
        printf("Error opening file for writing.\n");
        return 1;
    }

    struct Student newStudent;
    printf("Enter Student ID: ");
    scanf("%d", &newStudent.id);

    printf("Enter Student Name: ");
    scanf("%s", newStudent.name);

    newStudent.attendance = 0;

    fwrite(&newStudent, sizeof(struct Student), 1, file);

    fclose(file);

    printf("Student added successfully.\n");
}

void viewRecords() {
    FILE *file = fopen("students.dat", "rb");
    if (file == NULL) {
        printf("Error opening file for reading.\n");
        return 1;
    }

    struct Student currentStudent;

    printf("\nStudent Records\n");
    printf("ID\tName\tAttendance\n");

    while (fread(&currentStudent, sizeof(struct Student), 1, file) == 1) {
        printf("%d\t%s\t%d\n", currentStudent.id, currentStudent.name, currentStudent.attendance);
    }

    fclose(file);
}

void takeAttendance() {
    FILE *file = fopen("students.dat", "r+b");
    if (file == NULL) {
        printf("Error opening file for reading and writing.\n");
        return;
    }

    int attendanceId;
    printf("Enter Student ID for Attendance: ");
    scanf("%d", &attendanceId);

    struct Student currentStudent;

    while (fread(&currentStudent, sizeof(struct Student), 1, file) == 1) {
        if (currentStudent.id == attendanceId) {
            currentStudent.attendance++;
            fseek(file, -sizeof(struct Student), SEEK_CUR);
            fwrite(&currentStudent, sizeof(struct Student), 1, file);
            printf("Attendance recorded for %s.\n", currentStudent.name);
            break;
        }
    }

    fclose(file);
}

void deleteRecord() {
    FILE *file = fopen("students.dat", "r+b");
    if (file == NULL) {
        printf("Error opening file for reading and writing.\n");
        return;
    }

    int deleteId;
    printf("Enter Student Name to delete: ");
    scanf("%d", &deleteId);

    struct Student currentStudent;
    int found = 0;

    while (fread(&currentStudent, sizeof(struct Student), 1, file) == 1) {
        if (currentStudent.name == deleteId) {
            found = 1;
            break;
        }
    }

    if (found) {
        fseek(file, -sizeof(struct Student), SEEK_CUR);
        struct Student emptyStudent = {0};
        fwrite(&emptyStudent, sizeof(struct Student), 1, file);
        printf("Record with ID %d deleted.\n", deleteId);
    } else {
        printf("Record with ID %d not found.\n", deleteId);
    }

    fclose(file);
}

