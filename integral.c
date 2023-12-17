#include <math.h>

#define F(a) (f(a) - g(a))
#define P ((double) 1 / (double) 3)

typedef double (*functype) (double x);
int iter;

double root(functype f, functype g, double a, double b, double eps1);
double integral(functype f, double a, double b, double eps2);

// calculates root of the equation f(x) - g(x) = 0
// on the segment [a, b] with precision eps1
double root(functype f, functype g, double a, double b, double eps1) {
    iter += 1; // counting number of iterations
    double fa = F(a);
    double fb = F(b);
    double fab = F((a + b) / 2);
    double c = (a * fb - b * fa) / (fb - fa);
    // deciding from which side to approach the root
    if ((fa < 0 && fab < (fa + fb) / 2) || (fa > 0 && fab > (fa + fb) / 2)) {
        if (F(c) * F(c + eps1) <= 0) {
            return (2 * c + eps1) / 2;
        }
        return root(f, g, c, b, eps1);
    }
    if (F(c) * F(c - eps1) <= 0) { // if the root lies on a sufficiently small segment
        return c - eps1 / 2;
    }
    return root(f, g, a, c, eps1);
}

// calculates definite integral of the function f
// on the segment [a, b] with precision eps2
double integral(functype f, double a, double b, double eps2) {
    int n = 10; // number of points in the segment split
    // in integral has n points in the segment split, i2n has 2*n points
    double in, i2n = 0;
    do {
        n *= 2;
        in = i2n;
        i2n = 0;
        double h = (b - a) / (double) n;
        double cur = a + h / 2;
        for (int i = 0; i < n; ++i) {
            i2n += f(cur);
            cur += h;
        }
        i2n *= h; // area of rectangles
    } while (P * fabs(in - i2n) >= eps2); // Runge rule
    return i2n;  // returning more precise integral
}
