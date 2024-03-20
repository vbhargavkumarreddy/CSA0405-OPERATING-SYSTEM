#include <stdio.h>
#include <stdlib.h>
struct Employee {
    int empID;
    char empName[50];
    float empSalary;
};
void addEmployee(FILE *file) {
    struct Employee emp;

    printf("Enter Employee ID: ");
    scanf("%d", &emp.empID);
    printf("Enter Employee Name: ");
    scanf(" %[^\n]s", emp.empName);
    printf("Enter Employee Salary: ");
    scanf("%f", &emp.empSalary);
    fseek(file, 0, SEEK_END);
    fwrite(&emp, sizeof(struct Employee), 1, file);

    printf("Employee record added successfully.\n");
}
void displayAllEmployees(FILE *file) {
    struct Employee emp;
    fseek(file, 0, SEEK_SET);

    printf("Employee Records:\n");
    printf("ID\tName\t\tSalary\n");
    while (fread(&emp, sizeof(struct Employee), 1, file) == 1) {
        printf("%d\t%-20s\t%.2f\n", emp.empID, emp.empName, emp.empSalary);
    }
    printf("\n");
}
void updateEmployee(FILE *file, int empID) {
    struct Employee emp;
    int found = 0;
    fseek(file, 0, SEEK_SET);
    while (fread(&emp, sizeof(struct Employee), 1, file) == 1) {
        if (emp.empID == empID) {
            found = 1;
            printf("Enter new details for Employee %d:\n", empID);
            printf("Enter Employee Name: ");
            scanf(" %[^\n]s", emp.empName);
            printf("Enter Employee Salary: ");
            scanf("%f", &emp.empSalary);
            fseek(file, -sizeof(struct Employee), SEEK_CUR);
            fwrite(&emp, sizeof(struct Employee), 1, file);
            printf("Employee record updated successfully.\n");
            break;
        }
    }
    if (!found) {
        printf("Employee with ID %d not found.\n", empID);
    }
}
void searchEmployee(FILE *file, int empID) {
    struct Employee emp;
    int found = 0;
    fseek(file, 0, SEEK_SET);
    while (fread(&emp, sizeof(struct Employee), 1, file) == 1) {
        if (emp.empID == empID) {
            found = 1;
            printf("Employee Found:\n");
            printf("ID\tName\t\tSalary\n");
            printf("%d\t%-20s\t%.2f\n", emp.empID, emp.empName, emp.empSalary);
            break;
        }
    }
    if (!found) {
        printf("Employee with ID %d not found.\n", empID);
    }
}
int main() {
    FILE *employeeFile;
    int choice, empID;
    employeeFile = fopen("employee_records.dat", "rb+");

    if (employeeFile == NULL) {
        employeeFile = fopen("employee_records.dat", "wb+");
        if (employeeFile == NULL) {
            perror("Error opening file");
            return 1;
        }
    }
    do {
        printf("1. Add Employee Record\n");
        printf("2. Display All Employees\n");
        printf("3. Update Employee Record\n");
        printf("4. Search Employee Record\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addEmployee(employeeFile);
                break;
            case 2:
                displayAllEmployees(employeeFile);
                break;
            case 3:
                printf("Enter Employee ID to update: ");
                scanf("%d", &empID);
                updateEmployee(employeeFile, empID);
                break;
            case 4:
                printf("Enter Employee ID to search: ");
                scanf("%d", &empID);
                searchEmployee(employeeFile, empID);
                break;
            case 5:
                printf("Exiting the program.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }

    } while (choice != 5);

    fclose(employeeFile);

    return 0;
}

