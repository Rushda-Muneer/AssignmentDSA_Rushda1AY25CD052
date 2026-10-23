#include <stdio.h>

#define MAX_TERMS 101
#define MAX_SIZE 20

typedef struct {
    int row;
    int col;
    int value;
} term;

void printTriples(term a[]) {
    int i;

    printf("Index\tRow\tCol\tValue\n");

    for (i = 0; i <= a[0].value; i++) {
        printf("%d\t%d\t%d\t%d\n",
               i, a[i].row, a[i].col, a[i].value);
    }
}

void fast_transpose(term a[], term b[]) {
    int row_terms[MAX_SIZE] = {0};
    int starting_pos[MAX_SIZE];
    int i, j, num_cols, num_terms;

    num_cols = a[0].col;
    num_terms = a[0].value;

    b[0].row = num_cols;
    b[0].col = a[0].row;
    b[0].value = num_terms;

    if (num_terms > 0) {
        /* Step 1: Count entries in each column */
        for (i = 1; i <= num_terms; i++)
            row_terms[a[i].col]++;

        printf("\nrow_terms[]: ");
        for (i = 0; i < num_cols; i++)
            printf("%d ", row_terms[i]);

        /* Step 2: Calculate starting positions */
        starting_pos[0] = 1;

        for (i = 1; i < num_cols; i++) {
            starting_pos[i] =
                starting_pos[i - 1] + row_terms[i - 1];
        }

        printf("\nstarting_pos[]: ");
        for (i = 0; i < num_cols; i++)
            printf("%d ", starting_pos[i]);

        printf("\n");

        /* Step 3: Place transposed triples */
        for (i = 1; i <= num_terms; i++) {
            j = starting_pos[a[i].col]++;

            b[j].row = a[i].col;
            b[j].col = a[i].row;
            b[j].value = a[i].value;
        }
    }
}

int main() {
    term a[MAX_TERMS], b[MAX_TERMS];
    int matrix[MAX_SIZE][MAX_SIZE];
    int rows, cols, i, j, count = 0;

    printf("Enter rows and columns: ");
    scanf("%d %d", &rows, &cols);

    if (rows <= 0 || cols <= 0 ||
        rows >= MAX_SIZE || cols >= MAX_SIZE) {
        printf("Invalid matrix dimensions.\n");
        return 1;
    }

    printf("Enter matrix elements row by row:\n");

    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++)
            scanf("%d", &matrix[i][j]);
    }

    /* Header information */
    a[0].row = rows;
    a[0].col = cols;

    /* Store only non-zero elements */
    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            if (matrix[i][j] != 0) {
                if (count >= MAX_TERMS - 1) {
                    printf("Too many non-zero elements.\n");
                    return 1;
                }

                count++;
                a[count].row = i;
                a[count].col = j;
                a[count].value = matrix[i][j];
            }
        }
    }

    a[0].value = count;

    printf("\nOriginal matrix triples:\n");
    printTriples(a);

    fast_transpose(a, b);

    printf("\nTransposed matrix triples:\n");
    printTriples(b);

    printf("\nTransposed triples are in row-major order.\n");

    return 0;
}
