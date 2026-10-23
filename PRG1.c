#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int roll_no;
    char name[20];
    float marks;
} Student;

int main() {
    Student *ptr, *temp;
    int n, i, total = 0;
    float sum = 0, average;
    int topper = 0;
    char choice;

    printf("Enter number of students: ");
    scanf("%d", &n);

    if (n <= 0) {
        printf("Invalid number of students.\n");
        return 1;
    }

    ptr = (Student *)malloc(n * sizeof(Student));

    if (ptr == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    for (i = 0; i < n; i++) {
        printf("Enter roll, name, marks: ");
        scanf("%d %19s %f",
              &(ptr + i)->roll_no,
              (ptr + i)->name,
              &(ptr + i)->marks);
    }

    do {
        sum = 0;
        topper = 0;

        for (i = 0; i < n; i++) {
            sum += (ptr + i)->marks;

            if ((ptr + i)->marks >
                (ptr + topper)->marks) {
                topper = i;
            }
        }

        average = sum / n;

        printf("\nAverage marks: %.2f\n", average);
        printf("Topper: %s (Roll %d, Marks %.2f)\n",
               (ptr + topper)->name,
               (ptr + topper)->roll_no,
               (ptr + topper)->marks);

        printf("\nAdd 2 more students? (y/n): ");
        scanf(" %c", &choice);

        if (choice == 'y' || choice == 'Y') {
            temp = (Student *)realloc(
                ptr, (n + 2) * sizeof(Student));

            if (temp == NULL) {
                printf("Memory reallocation failed.\n");
                free(ptr);
                return 1;
            }

            ptr = temp;

            for (i = n; i < n + 2; i++) {
                printf("Enter roll, name, marks: ");
                scanf("%d %19s %f",
                      &(ptr + i)->roll_no,
                      (ptr + i)->name,
                      &(ptr + i)->marks);
            }

            n = n + 2;
        } else {
            break;
        }

    } while (1);

    free(ptr);
    ptr = NULL;

    return 0;
}
