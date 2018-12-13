#include <iostream>
#include <omp.h>
#include <random>

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
    }
    return total;
}

int count_with_atomic() {
    int i, j, sum;
    int total = 0;
#pragma omp parallel for shared(a) private(i, j, sum)
    for (i = 0; i < NMAX; i++) {
        sum = 0;
        for (j = 0; j < NMAX; j++)
            sum += a[i][j];
        printf("Сумма элементов строки %d равна %i\n", i, sum);
#pragma omp atomic
        total = total + sum;
    }
    return total;
}

int count_with_critical() {
    int i, j, sum;
    int total = 0;
#pragma omp parallel for shared(a) private(i, j, sum)
    for (i = 0; i < NMAX; i++) {
        sum = 0;
        for (j = 0; j < NMAX; j++)
            sum += a[i][j];
        printf("Сумма элементов строки %d равна %i\n", i, sum);
#pragma omp critical
        total = total + sum;
    }
    return total;
}

int count_with_lock() {
    omp_lock_t lock;
    omp_init_lock(&lock);
    int i, j, sum;
    int total = 0;
#pragma omp parallel for shared(a) private(i, j, sum)
    for (i = 0; i < NMAX; i++) {
        sum = 0;
        for (j = 0; j < NMAX; j++)
            sum += a[i][j];
        printf("Сумма элементов строки %d равна %i\n", i, sum);
        omp_set_lock (&lock);
        total = total + sum;
        omp_unset_lock (&lock);
    }
    omp_destroy_lock (&lock);
    return total;
}

void count_time(const std::string &name, function func) {
    std::cout << "-------" << name << "-------" << std::endl;
    double t1, t2;
    t1 = omp_get_wtime();
    int result = func();
    t2 = omp_get_wtime();
    std::cout << "Time is " << t2 - t1 << std::endl;
    std::cout << "Result is " << result << std::endl;
}

void random_matrix() {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(0, 25);

    for (int i = 0; i < NMAX; ++i) {
        for (int j = 0; j < NMAX; ++j) {
            a[i][j] = dist(mt);;
        }
    }
}


int main() {

    random_matrix();

    count_time("reduction", count_with_reduction);
    count_time("atomic", count_with_atomic);
    count_time("critical", count_with_critical);
    count_time("lock", count_with_lock);

    return 0;
}