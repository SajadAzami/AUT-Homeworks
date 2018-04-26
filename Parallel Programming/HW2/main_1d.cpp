/*
*				In His Exalted Name
*	Title:	Matrix Multiplication Sequential Code
*	Author: Ahmad Siavashi, Email: siavashi@aut.ac.ir
*	Date:	15/11/2015
* 	Edited By: Sajjad Azami on April 2018
*/

// Let it be.
#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <omp.h>

typedef struct {
    int *A, *B, *C;
    int n, m, p;
} DataSet;

void fillDataSet(DataSet *dataSet);

void printDataSet(DataSet dataSet);

void closeDataSet(DataSet dataSet);

void multiply(DataSet dataSet);

long multiply_validator(DataSet set);

int main(int argc, char *argv[]) {

    int t = 0;
    int num_of_threads[4] = {1, 2, 4, 8};
    DataSet dataSet;
    if (argc < 4) {
        printf("[-] Invalid No. of arguments.\n");
        printf("[-] Try -> <n> <m> <p>\n");
        printf(">>> ");
        scanf("%d %d %d", &dataSet.n, &dataSet.m, &dataSet.p);
    } else {
        dataSet.n = atoi(argv[1]);
        dataSet.m = atoi(argv[2]);
        dataSet.p = atoi(argv[3]);
    }

    fillDataSet(&dataSet);

//    // Computer without parallelization to validate the results
//     long sum_of_elements = 0;
//     sum_of_elements = multiply_validator(dataSet);
//     printf("Sum of Elements: %li\n", sum_of_elements);

    for (t = 0; t < 4; t++) {
        omp_set_num_threads(num_of_threads[t]);

//        // Uncomment to get averaged results
//        double times[5];
//        int i;
//        for (i = 0; i < 5; i++) {
//            double start_time = omp_get_wtime();
//            multiply(dataSet);
//            double time = omp_get_wtime() - start_time;
//            times[i] = time;
//        }
//
//        double times_sum = 0;
//        for (i = 0; i < 5; i++) {
//            times_sum += times[i];
//        }

//        printDataSet(dataSet);

        double start_time = omp_get_wtime();
        multiply(dataSet);
        double time = omp_get_wtime() - start_time;

        printf("wtime%d: %f\n", num_of_threads[t], time);
    }

    closeDataSet(dataSet);

    system("read -p 'Press Enter to continue...' var");
    return EXIT_SUCCESS;
}

long multiply_validator(DataSet set, DataSet set2) {
    int i, j, k, sum;

    for (i = 0; i < set.n; i++) {
        for (j = 0; j < set.p; j++) {
            sum = 0;
            for (k = 0; k < set.m; k++) {
                sum += set.A[i * set.m + k] * set.B[k * set.p + j];
            }
            set.C[i * set.p + j] = sum;
        }
    }

    multiply(set2);

    long element_sum = 0;
    for (i = 0; i < set.n; i++) {
        for (j = 0; j < set.m; j++) {
            element_sum += set.A[i * set.m + j];
        }
    }

    for (i = 0; i < set.m; i++) {
        for (j = 0; j < set.p; j++) {
            element_sum += set.B[i * set.p + j];
        }
    }

    for (i = 0; i < set.n; i++) {
        for (j = 0; j < set.p; j++) {
            element_sum += set.C[i * set.p + j];
        }
    }
    return element_sum;
}

void fillDataSet(DataSet *dataSet) {
    int i, j;

    dataSet->A = (int *) malloc(sizeof(int) * dataSet->n * dataSet->m);
    dataSet->B = (int *) malloc(sizeof(int) * dataSet->m * dataSet->p);
    dataSet->C = (int *) malloc(sizeof(int) * dataSet->n * dataSet->p);

    srand(2);

    for (i = 0; i < dataSet->n; i++) {
        for (j = 0; j < dataSet->m; j++) {
            dataSet->A[i * dataSet->m + j] = rand() % 100;
        }
    }

    for (i = 0; i < dataSet->m; i++) {
        for (j = 0; j < dataSet->p; j++) {
            dataSet->B[i * dataSet->p + j] = rand() % 100;
        }
    }
}

void printDataSet(DataSet dataSet) {
    int i, j;

    printf("[-] Matrix A\n");
    for (i = 0; i < dataSet.n; i++) {
        for (j = 0; j < dataSet.m; j++) {
            printf("%-4d", dataSet.A[i * dataSet.m + j]);
        }
        putchar('\n');
    }

    printf("[-] Matrix B\n");
    for (i = 0; i < dataSet.m; i++) {
        for (j = 0; j < dataSet.p; j++) {
            printf("%-4d", dataSet.B[i * dataSet.p + j]);
        }
        putchar('\n');
    }

    printf("[-] Matrix C\n");
    for (i = 0; i < dataSet.n; i++) {
        for (j = 0; j < dataSet.p; j++) {
            printf("%-8d", dataSet.C[i * dataSet.p + j]);
        }
        putchar('\n');
    }
}

void closeDataSet(DataSet dataSet) {
    free(dataSet.A);
    free(dataSet.B);
    free(dataSet.C);
}

void multiply(DataSet dataSet) {
    int i, j, k, sum;

    for (i = 0; i < dataSet.n; i++) {
#pragma omp parallel for schedule(static, 100) reduction(+:sum) firstprivate(dataSet)
        for (j = 0; j < dataSet.p; j++) {
            sum = 0;
#pragma omp parallel for schedule(static, 100) reduction(+:sum) firstprivate(dataSet)
            for (k = 0; k < dataSet.m; k++) {
                sum += dataSet.A[i * dataSet.m + k] * dataSet.B[k * dataSet.p + j];
            }
            dataSet.C[i * dataSet.p + j] = sum;
        }
    }
}
