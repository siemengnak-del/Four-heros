#include <stdio.h>
#include <math.h>

void solveQuadratic(double a, double b, double c) {
    double discriminant, root1, root2;

    // Check if a is zero
    if (a == 0) {
        printf("This is not a quadratic equation.\n");
        return;
    }

    discriminant = b * b - 4 * a * c;

    if (discriminant > 0) {
        root1 = (-b + sqrt(discriminant)) / (2 * a);
        root2 = (-b - sqrt(discriminant)) / (2 * a);

        printf("Two real roots:\n");
        printf("x1 = %.2lf\n", root1);
        printf("x2 = %.2lf\n", root2);
    }
    else if (discriminant == 0) {
        root1 = -b / (2 * a);

        printf("One real root:\n");
        printf("x = %.2lf\n", root1);
    }
    else {
        printf("No real roots (complex roots).\n");
    }
}