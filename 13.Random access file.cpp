#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_EMPLOYEES 100

struct Employee {
    int empId;
    char name[50];
    float salary;
};

void addEmployee(FILE *file) {
    struct Employee emp;
    printf("Enter employee ID: ");
    scanf("%d", &emp.empId);
    printf("Enter employee name: ");
    scanf("%s", emp.name);
    printf("Enter employee salary: ");
    scanf("%f", &emp.salary);

    fseek(file, (emp.empId - 1) * sizeof(struct Employee), SEEK_SET);
    fwrite(&emp, sizeof(struct Employee), 1, file);
}

void displayEmployee(FILE *file, int empId) {
    struct Employee emp;
    fseek(file, (empId - 1) * sizeof(struct Employee), SEEK_SET);
    fread(&emp, sizeof(struct Employee), 1, file);
    printf("Employee ID: %d\n", emp.empId);
    printf("Name: %s\n", emp.name);
    printf("Salary: %.2f\n", emp.salary);
}

void modifyEmployee(FILE *file, int empId) {
    struct Employee emp;
    fseek(file, (empId - 1) * sizeof(struct Employee), SEEK_SET);
    fread(&emp, sizeof(struct Employee), 1, file);

    printf("Enter new name: ");
    scanf("%s", emp.name);
    printf("Enter new salary: ");
    scanf("%f", &emp.salary);

    fseek(file, (empId - 1) * sizeof(struct Employee), SEEK_SET);
    fwrite(&emp, sizeof(struct Employee), 1, file);
}

int main() {
    FILE *file;
    file = fopen("employees.dat", "rb+");

    if (file == NULL) {
        printf("File not found. Creating a new one.\n");
        file = fopen("employees.dat", "wb+");
    }

    if (file == NULL) {
        printf("Unable to open or create file.\n");
        return 1;
    }

    int choice, empId;
    do {
        printf("\n1. Add Employee\n2. Display Employee\n3. Modify Employee\n4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addEmployee(file);
                break;
            case 2:
                printf("Enter employee ID: ");
                scanf("%d", &empId);
                displayEmployee(file, empId);
                break;
            case 3:
                printf("Enter employee ID to modify: ");
                scanf("%d", &empId);
                modifyEmployee(file, empId);
                break;
            case 4:
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid choice!\n");
        }
    } while (choice != 4);

    fclose(file);
    return 0;
}
