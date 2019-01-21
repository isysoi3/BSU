#include <iostream>
#include <omp.h>
#include <random>

#define matrix_size 10000
#define threads_number 4

int** matrix;

typedef long long (*function)();

long long count_with_reduction() {
    int i, j;
    long long sum, total = 0;
#pragma omp parallel for shared(matrix) private(i, j, sum) reduction (+:total) num_threads(threads_number)
    for (i = 0; i < matrix_size; i++) {
        sum = 0;
        for (j = 0; j < matrix_size; j++)
            sum += matrix[i][j];
        total = total + sum;
    }
    return total;
}

long long count_with_atomic() {
    int i, j;
    long long sum, total = 0;
#pragma omp parallel for shared(matrix) private(i, j, sum) num_threads(threads_number)
    for (i = 0; i < matrix_size; i++) {
        sum = 0;
        for (j = 0; j < matrix_size; j++)
            sum += matrix[i][j];
#pragma omp atomic
        total = total + sum;
    }
    return total;
}

long long count_with_critical() {
    int i, j;
    long long sum, total = 0;
#pragma omp parallel for shared(matrix) private(i, j, sum) num_threads(threads_number)
    for (i = 0; i < matrix_size; i++) {
        sum = 0;
        for (j = 0; j < matrix_size; j++)
            sum += matrix[i][j];
#pragma omp critical
        total = total + sum;
    }
    return total;
}

long long count_with_lock() {
    omp_lock_t lock;
    omp_init_lock(&lock);
    int i, j;
    long long sum, total = 0;
#pragma omp parallel for shared(matrix) private(i, j, sum) num_threads(threads_number)
    for (i = 0; i < matrix_size; i++) {
        sum = 0;
        for (j = 0; j < matrix_size; j++)
            sum += matrix[i][j];
        omp_set_lock(&lock);
        total = total + sum;
        omp_unset_lock(&lock);
    }
    omp_destroy_lock(&lock);
    return total;
}

long long linear_count() {
    int i, j;
    long long sum, total = 0;

    for (i = 0; i < matrix_size; i++) {
        for (j = 0; j < matrix_size; j++)
            total += matrix[i][j];
    }
    return total;
}

void count_time(const std::string &name, function func) {
    std::cout << "-------" << name << "-------" << std::endl;
    double t1, t2;
    t1 = omp_get_wtime();
    long long result = func();
    t2 = omp_get_wtime();
    std::cout << "Time is " << (t2 - t1) * 1000 << " ms" << std::endl;
    std::cout << "Result is " << result << std::endl;
}

void random_matrix() {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(0, 10);

    matrix = new int*[matrix_size];

    for (int i = 0; i < matrix_size; ++i) {
        matrix[i] = new int[matrix_size];
        for (int j = 0; j < matrix_size; ++j) {
            matrix[i][j] = dist(mt);;
        }
    }
}


int main() {

    random_matrix();

    count_time("linear", linear_count);
    count_time("reduction", count_with_reduction);
    count_time("atomic", count_with_atomic);
    count_time("critical", count_with_critical);
    count_time("lock", count_with_lock);

    for (int i = 0; i < matrix_size; ++i) {
        delete matrix[i];
    }

    return 0;
}