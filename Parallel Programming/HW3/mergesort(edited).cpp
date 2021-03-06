/*
*				In His Exalted Name
*	Title:	MergeSort Sequential Code
*	Author: Ahmad Siavashi, Email: siavashi@aut.ac.ir
*	Date:	24/11/2015
*/

// Let it be.
#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <omp.h>

#define MAX(A, B) ((A)>(B))?(A):(B)
#define MIN(A, B) ((A)<(B))?(A):(B)

void printArray(int *array, int size);
void fillArray(int *array, int size);
void merge(int *a, int n, int m);
void mergeSort(int *a, int n);
void omp_check();
void merge_section(int *a, int n);
void merge_task(int *a, int n);

int main(int argc, char *argv[]) {
	int *array = NULL;
	int size = 0;
	int t = 0;
	int num_of_threads[4] = { 1, 2, 4, 8 };


	omp_check();
	//size = 100000000;
	//size = 60000000;
	//size = 20000000;
	//size = 4000000;
	size = 10;

	array = (int *)malloc(sizeof(int) * size);
	fillArray(array, size);

	for (t = 0; t < 4; t++) {
		omp_set_num_threads(num_of_threads[t]);
		double start_time = omp_get_wtime();
		//merge_section(array, size);
		merge_task(array, size);
		double time = omp_get_wtime() - start_time;
		printf("time for %d threads: %f\n", t, time);
	}
	printArray(array, size);
	free(array);
	system("PAUSE");
	return EXIT_SUCCESS;
}

void fillArray(int *array, int size) {
	srand(time(NULL));
	while (size-->0) {
		*array++ = rand() % 100;
	}
}

void printArray(int *array, int size) {
	while (size-->0) {
		printf("%d, ", *array++);
	}
	printf("\n");
}

void merge(int *a, int n, int m) {
	int i, j, k;
	int *temp = (int *)malloc(n * sizeof(int));
	for (i = 0, j = m, k = 0; k < n; k++) {
        temp[k] = j == n ? a[i++]
                         : i == m ? a[j++]
                                  : a[j] < a[i] ? a[j++]
                                                : a[i++];
    }
	for (i = 0; i < n; i++) {
		a[i] = temp[i];
	}
	free(temp);
}

void mergeSort(int *a, int n) {
	int m;
	if (n < 2)
		return;
	m = n / 2;
	mergeSort(a, m);
	mergeSort(a + m, n - m);
	merge(a, n, m);
}

void merge_section(int *a, int n) {
	int m;
	if (n < 2)
		return;
	m = n / 2;
#pragma omp parallel
	{
#pragma omp sections
	{
#pragma omp section
		merge_section(a, m);
#pragma omp section
		merge_section(a + m, n - m);
	}
#pragma omp single
	merge(a, n, m);
	}
}

void merge_task(int *a, int n) {
	int m;
	if (n < 2)
		return;
	m = n / 2;
#pragma omp parallel
	{
#pragma omp single nowait
		{
#pragma omp task
			merge_task(a, m);
#pragma omp task
			merge_task(a + m, n - m);
		};
	};

	merge(a, n, m);
}


void omp_check() {
	printf("------------ Info -------------\n");
#ifdef _DEBUG
	printf("[!] Configuration: Debug.\n");
#pragma message ("Change configuration to Release for a fast execution.")
#else
	printf("[-] Configuration: Release.\n");
#endif // _DEBUG
#ifdef _M_X64
	printf("[-] Platform: x64\n");
#elif _M_IX86
	printf("[-] Platform: x86\n");
#pragma message ("Change platform to x64 for more memory.")
#endif // _M_IX86
#ifdef _OPENMP
	printf("[-] OpenMP is on.\n");
	printf("[-] OpenMP version: %d\n", _OPENMP);
#else
	printf("[!] OpenMP is off.\n");
	printf("[#] Enable OpenMP.\n");
#endif // _OPENMP
	printf("[-] Maximum threads: %d\n", omp_get_max_threads());
	printf("[-] Nested Parallelism: %s\n", omp_get_nested() ? "On" : "Off");
#pragma message("Enable nested parallelism if you wish to have parallel region within parallel region.")
	printf("===============================\n");
}