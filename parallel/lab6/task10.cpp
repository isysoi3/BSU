//
// Created by isysoi on 13.12.18.
//

#include <iostream>
#include <omp.h>
#include <random>
#include <climits>

#define matrix_size 15000
#define threads_number 4

int **matrix;

typedef int (function)();

int parallel_nested() {
    int i, j;
    int max = INT_MIN;
    int min_in_row = INT_MAX;

    omp_set_nested(true);

#pragma omp parallel for private(i) num_threads(2)
    for (i = 0; i < matrix_size; i++) {
#pragma omp parallel for shared(min_in_row) private(j) num_threads(2)
        for (j = 0; j < matrix_size; j++) {
            if (matrix[i][j] < min_in_row)
#pragma omp critical
            {
                if (matrix[i][j] < min_in_row) {
                    min_in_row = matrix[i][j];
                }
            }
        }
        if (min_in_row > max)
#pragma omp critical
        {
            if (min_in_row > max)
                max = min_in_row;
        }
    }
    return max;
}

int parallel() {
    int i, j;
    int max = INT_MIN;

#pragma omp parallel for shared(max) private(i, j) num_threads(threads_number)
    for (i = 0; i < matrix_size; i++) {
        int min_in_row = INT_MAX;
        for (j = 0; j < matrix_size; j++)
            if (matrix[i][j] < min_in_row)
                min_in_row = matrix[i][j];

        if (min_in_row > max)
#pragma omp critical
        {
            if (min_in_row > max)
                max = min_in_row;
        }
    }


    return max;
}

int linear() {
    int i, j;
    int max = INT_MIN;
    for (i = 0; i < matrix_size; i++) {
        int min_in_row = INT_MAX;
        for (int j = 0; j < matrix_size; j++)
            if (matrix[i][j] < min_in_row)
                min_in_row = matrix[i][j];

        if (min_in_row > max)
            max = min_in_row;

    }
    return max;
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

    matrix = new int *[matrix_size];

    for (int i = 0; i < matrix_size; ++i) {
        matrix[i] = new int[matrix_size];
        for (int j = 0; j < matrix_size; ++j) {
            matrix[i][j] = dist(mt);;
        }
    }
}

int main() {

    random_matrix();

    count_time("linear", linear);
    count_time("parallel", parallel);
    count_time("parallel_nested", parallel_nested);


    for (int i = 0; i < matrix_size; ++i) {
        delete matrix[i];
    }


    return 0;
}
