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

int main() {
    printf("=== Quadratic Equation Solver ===\n\n");

    // Example 1: Two real roots
    printf("Example 1: x^2 - 5x + 6 = 0\n");
    printf("(a=1, b=-5, c=6)\n");
    solveQuadratic(1, -5, 6);

    printf("\n");

    // Example 2: One real root
    printf("Example 2: x^2 - 2x + 1 = 0\n");
    printf("(a=1, b=-2, c=1)\n");
    solveQuadratic(1, -2, 1);

    printf("\n");

    // Example 3: No real roots
    printf("Example 3: x^2 + 1 = 0\n");
    printf("(a=1, b=0, c=1)\n");
    solveQuadratic(1, 0, 1);

    return 0;
}