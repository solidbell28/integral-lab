#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <getopt.h>

typedef double (*functype) (double x);
typedef struct option option;
extern int iter;

extern double func1(double x);
extern double func2(double x);
extern double func3(double x);
extern double func1_test(double x);
extern double func2_test(double x);
extern double func3_test(double x);
extern double root(functype f, functype g, double a, double b, double eps1);
extern double integral(functype f, double a, double b, double eps2);

int main(int argc, char *argv[]) {
    // flags for command line options + variables used for testing 'root' and 'integral' functions
    int c, f1, f2, option_index = 0, r_flag = 0, i_flag = 0, testr_flag = 0, testi_flag = 0;
    double a, b, e, r, ans;

    // long options of command line
    option long_options[5] = {
            {"help", 0, 0, 'h'},
            {"root", 0, 0, 'r'},
            {"iterations", 0, 0, 'i'},
            {"test-root", 1, 0, 'R'},
            {"test-integral", 1, 0, 'I'}
    };

    // Array of pointers to assembler functions
    // Used for testing 'root' and 'integral' functions
    functype functions[6], fn1, fn2;
    functions[0] = func1;
    functions[1] = func2;
    functions[2] = func3;
    functions[3] = func1_test;
    functions[4] = func2_test;
    functions[5] = func3_test;

    c = getopt_long(argc, argv, "hriR:I:", long_options, &option_index);

    while (c != -1) {
        switch (c) {
            // -h or --help option
            // prints all available command line options
            case 'h': {
                FILE *file = fopen("help.txt", "r");
                char *s = malloc(1000 * sizeof(char));
                while (fgets(s, 1000, file) != NULL) {
                    fputs(s, stdout);
                }
                free(s);
                fclose(file);
                exit(0);
            }

            // -i or --iterations option
            // sets corresponding flag
            case 'i': {
                i_flag = 1;
                break;
            }

            // -r or --root option
            // sets corresponding flag
            case 'r': {
                r_flag = 1;
                break;
            }

            // -I or --test-integral option
            // tests 'integral' function with the specified parameters + sets corresponding flag
            case 'I': {
                testi_flag = 1;
                // scanning parameters
                if (sscanf(optarg, "%d:%lf:%lf:%lf:%lf", &f1, &a, &b, &e, &r) != 5) {
                    printf("Error: bad arguments for option '-I' or '--test-integral'\n");
                    exit(1);
                }
                fn1 = functions[f1 - 1];
                ans = integral(fn1, a, b, e);
                // printing result, absolute and relative error
                printf("'Integral' test\n");
                printf("Calculated value: %lf\n", ans);
                printf("Absolute error: %lf\n", fabs(ans - r));
                printf("Relative error: %lf\n\n", fabs((ans - r) / r));
                break;
            }

            // -R or --test-root option
            // tests 'root' function with the specified parameters + sets corresponding flag
            case 'R': {
                testr_flag = 1;
                // scanning parameters
                sscanf(optarg, "%d:%d:%lf:%lf:%lf:%lf", &f1, &f2, &a, &b, &e, &r);
                fn1 = functions[f1 - 1];
                fn2 = functions[f2 - 1];
                ans = root(fn1, fn2, a, b, e);
                // printing result, absolute and relative error
                printf("'Root' test\n");
                printf("Calculated value: %lf\n", ans);
                printf("Absolute error: %lf\n", fabs(ans - r));
                printf("Relative error: %lf\n\n", fabs((ans - r) / r));
                break;
            }

            // unknown option
            // terminates the program with error
            default: {
                printf("Error: unknown option\n");
                exit(1);
            }
        }
        // getting next command line option
        c = getopt_long(argc, argv, "hriR:I:", long_options, &option_index);
    }

    // terminates the program if it was run in testing mode
    if (testr_flag || testi_flag) {
        exit(0);
    }

    // calculating points of intersection of curves
    // printing number of iterations needed to calculate the value if i_flag was set
    iter = 0;
    double x1 = root(func1, func3, 0.1, 3, 0.000001);
    if (i_flag) {
        printf("Number of iterations needed to find the 1st root: %d\n", iter);
    }
    iter = 0;
    double x2 = root(func2, func3, 0.1, 3, 0.000001);
    if (i_flag) {
        printf("Number of iterations needed to find the 2nd root: %d\n", iter);
    }
    iter = 0;
    double x3 = root(func1, func2, 0.1, 3, 0.000001);
    if (i_flag) {
        printf("Number of iterations needed to find the 3rd root: %d\n\n", iter);
    }

    // printing points of intersection of curves if r_flag was set
    if (r_flag) {
        printf("Points of intersection of curves: %lf, %lf, %lf\n\n", x1, x2, x3);
    }

    // calculating needed area and printing it
    double s1 = integral(func1, x1, x3, 0.000001);
    double s2 = integral(func2, x2, x3, 0.000001);
    double s3 = integral(func3, x1, x2, 0.000001);

    printf("Area between the curves: %lf\n", s1 - s2 - s3);

    return 0;
}
