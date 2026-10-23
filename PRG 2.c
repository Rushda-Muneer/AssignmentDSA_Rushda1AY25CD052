#include <stdio.h>
#include <stdlib.h>

enum EmpType {
    FULL_TIME,
    CONTRACT
};

typedef struct {
    char name[20];
    int emp_id;
    enum EmpType type;

    union {
        float salary;

        struct {
            float hourly_rate;
            int hours_worked;
        } contract_info;

    } pay;

} Employee;

int main() {
    Employee *emp;
    int n, i;
    float amount, total_bill = 0;

    printf("Enter number of employees: ");

    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid number of employees.\n");
        return 1;
    }

    emp = (Employee *)malloc(n * sizeof(Employee));

    if (emp == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    for (i = 0; i < n; i++) {
        printf("\nEnter employee name and ID: ");

        if (scanf("%19s %d",
                  emp[i].name,
                  &emp[i].emp_id) != 2) {
            printf("Invalid input.\n");
            free(emp);
            return 1;
        }

        printf("Enter type (0-Full-time, 1-Contract): ");

        if (scanf("%d", (int *)&emp[i].type) != 1) {
            printf("Invalid input.\n");
            free(emp);
            return 1;
        }

        if (emp[i].type == FULL_TIME) {
            printf("Enter monthly salary: ");

            if (scanf("%f", &emp[i].pay.salary) != 1) {
                printf("Invalid salary.\n");
                free(emp);
                return 1;
            }
        }
        else if (emp[i].type == CONTRACT) {
            printf("Enter hourly rate and hours worked: ");

            if (scanf("%f %d",
                      &emp[i].pay.contract_info.hourly_rate,
                      &emp[i].pay.contract_info.hours_worked) != 2) {
                printf("Invalid input.\n");
                free(emp);
                return 1;
            }
        }
        else {
            printf("Invalid employee type.\n");
            free(emp);
            return 1;
        }
    }

    printf("\n--- Employee Payslips ---\n");

    for (i = 0; i < n; i++) {
        if (emp[i].type == FULL_TIME) {
            amount = emp[i].pay.salary;
        }
        else {
            amount = emp[i].pay.contract_info.hourly_rate *
                     emp[i].pay.contract_info.hours_worked;
        }

        printf("\nEmployee Name: %s\n", emp[i].name);
        printf("Employee ID: %d\n", emp[i].emp_id);
        printf("Total Pay: Rs. %.2f\n", amount);

        total_bill += amount;
    }

    printf("\nTotal Salary Bill: Rs. %.2f\n", total_bill);

    free(emp);
    emp = NULL;

    return 0;
}
