#include <iostream>
#include <omp.h>

#define NMAX 10
int a[NMAX][NMAX];

typedef int (*function)();

int count_with_reduction() {
    int i, j, sum;
    int total = 0;
#pragma omp parallel for shared(a) private(i, j, sum) reduction (+:total)
    for (i = 0; i < NMAX; i++) {
        sum = 0;
        for (j = 0; j < NMAX; j++)
            sum += a[i][j];
        printf("Сумма элементов строки %d равна %i\n", i, sum);
        total = total + sum;
    } /* Завершение параллельного фрагмента */
    printf("Общая сумма элементов матрицы равна %i\n", total);
    return total;
}

void count_time(std::string name, function func) {
    double t1, t2;
    t1 = omp_get_wtime();
    int result = func();
    t2 = omp_get_wtime();
    std::cout << "Time for " << name << " is " << t2 - t1 << std::endl;
    std::cout << "Result " << result;
}

void random_matrix() {
    for (int i = 0; i < NMAX; ++i) {
        for (int j = 0; j < NMAX; ++j) {
            a[i][j] = rand() % 25 + 0;
        }
    }
}


int main() {

    random_matrix();

    count_time("reduction",count_with_reduction);


    return 0;
}