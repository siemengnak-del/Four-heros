#include <stdio.h>
#include <math.h>

void clearInputBuffer() {
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF);
}

void solveQuadratic(double a, double b, double c) {
    double discriminant;
    double root1, root2;

    discriminant = b * b - 4 * a * c;

    printf("\nDiscriminant = %.2lf\n", discriminant);

    if (discriminant > 0) {
        root1 = (-b + sqrt(discriminant)) / (2 * a);
        root2 = (-b - sqrt(discriminant)) / (2 * a);

        printf("Two distinct real roots found:\n");
        printf("x1 = %.2lf\n", root1);
        printf("x2 = %.2lf\n", root2);
    }
    else if (discriminant == 0) {
        root1 = -b / (2 * a);

        printf("One repeated real root found:\n");
        printf("x = %.2lf\n", root1);
    }
    else {
        printf("No real roots exist.\n");
        printf("The equation has complex roots.\n");
    }
}

int main() {
    double a, b, c;
    int validInput = 0;

    printf("====================================\n");
    printf("   QUADRATIC EQUATION SOLVER\n");
    printf("====================================\n");
    printf("Equation form: ax^2 + bx + c = 0\n\n");

    while (!validInput) {
        printf("Enter coefficients a, b, and c: ");

        if (scanf("%lf %lf %lf", &a, &b, &c) == 3) {

            if (a == 0) {
                printf("Error: 'a' cannot be 0.\n");
                printf("This would not be a quadratic equation.\n\n");
            }
            else {
                validInput = 1;
            }
        }
        else {
            printf("Error: Invalid input.\n");
            printf("Please enter numeric values only.\n\n");

            clearInputBuffer();
        }
    }

    solveQuadratic(a, b, c);

    printf("\nProgram finished.\n");

    return 0;
}