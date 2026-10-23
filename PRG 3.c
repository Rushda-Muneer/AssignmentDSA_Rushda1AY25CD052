#include <stdio.h>

typedef struct {
    int degree;
    float coef[101];
} polynomial;

polynomial add(polynomial a, polynomial b) {
    polynomial result;
    int i, exp;
    float ca, cb;

    result.degree = (a.degree > b.degree)
                    ? a.degree : b.degree;

    for (i = 0; i <= result.degree; i++) {
        exp = result.degree - i;

        if (exp <= a.degree)
            ca = a.coef[a.degree - exp];
        else
            ca = 0;

        if (exp <= b.degree)
            cb = b.coef[b.degree - exp];
        else
            cb = 0;

        result.coef[i] = ca + cb;
    }

    return result;
}

void display(polynomial p) {
    int i, exp, printed = 0;
    float c;

    for (i = 0; i <= p.degree; i++) {
        c = p.coef[i];
        exp = p.degree - i;

        if (c == 0)
            continue;

        if (printed)
            printf(c > 0 ? " + " : " - ");
        else if (c < 0)
            printf("-");

        if (c < 0)
            c = -c;

        if (exp == 0) {
            printf("%g", c);
        } else if (exp == 1) {
            if (c == 1)
                printf("x");
            else
                printf("%gx", c);
        } else {
            if (c == 1)
                printf("x^%d", exp);
            else
                printf("%gx^%d", c, exp);
        }

        printed = 1;
    }

    if (!printed)
        printf("0");

    printf("\n");
}

void readPolynomial(polynomial *p) {
    int i;

    printf("Enter degree of polynomial: ");
    scanf("%d", &p->degree);

    if (p->degree < 0 || p->degree > 100) {
        printf("Invalid degree.\n");
        p->degree = -1;
        return;
    }

    printf("Enter coefficients from highest power to constant:\n");

    for (i = 0; i <= p->degree; i++)
        scanf("%f", &p->coef[i]);
}

int main() {
    polynomial a, b, result;

    printf("First polynomial\n");
    readPolynomial(&a);

    if (a.degree < 0)
        return 1;

    printf("Second polynomial\n");
    readPolynomial(&b);

    if (b.degree < 0)
        return 1;

    result = add(a, b);

    printf("Polynomial A: ");
    display(a);

    printf("Polynomial B: ");
    display(b);

    printf("Sum: ");
    display(result);

    return 0;
}
