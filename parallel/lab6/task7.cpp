//
// Created by isysoi on 13.12.18.
//

#include <iostream>
#include <omp.h>
#include <numeric>
#include <fstream>
#include <queue>

#define num_vectors 10000
#define vector_lenght 25
#define threads_number 4
#define input_file "vectors"

typedef long long (*function)();

long long parallel() {

    std::queue<int*> vectors_queue;
    long long result = 0;
    bool isFinished = false;
    omp_lock_t lock;
    omp_init_lock(&lock);

#pragma omp parallel
    {
#pragma omp sections
        {
#pragma omp section
            {
                std::ifstream fin(input_file);

                int num = 0;
                for (int i = 0; i < num_vectors; i++) {
                    int* tmp_vector = new int[vector_lenght];
                    for (int j = 0; j < vector_lenght; j++) {
                        fin >> num;
                        tmp_vector[j] = num;
                    }
                    omp_set_lock(&lock);
                    vectors_queue.push(tmp_vector);
                    omp_unset_lock(&lock);
                }
                omp_set_lock(&lock);
                isFinished = true;
                omp_unset_lock(&lock);

                fin.close();
            }
#pragma omp section
            {
                int* a;
                int* b;

                while (true) {
                    omp_set_lock(&lock);
                    if (vectors_queue.empty() && isFinished) {
                        omp_unset_lock(&lock);
                        break;
                    }
                    omp_unset_lock(&lock);

                    while (vectors_queue.size() < 2) {}

                    omp_set_lock(&lock);
                    a = vectors_queue.front();
                    vectors_queue.pop();
                    b = vectors_queue.front();
                    vectors_queue.pop();
                    omp_unset_lock(&lock);

                    long long tmp = 0;
                    for (int j = 0; j < vector_lenght; j++) {
                        tmp += a[j] * b[j];
                    }
                    result += tmp;
                    delete[] a;
                    delete[] b;
                }
            }
        }
    }
    omp_destroy_lock(&lock);

    return result;
}


long long linear() {
    std::ifstream fin(input_file);

    std::queue<int*> vectors_queue;
    int num = 0;

    for (int i = 0; i < num_vectors; i++) {
        int *tmp_vector = new int[vector_lenght];
        for (int j = 0; j < vector_lenght; j++) {
            fin >> num;
            tmp_vector[j] = num;
        }
        vectors_queue.push(tmp_vector);
    }
    fin.close();

    int* a;
    int* b;
    long long result = 0;
    while (!vectors_queue.empty()) {
        a = vectors_queue.front();
        vectors_queue.pop();
        b = vectors_queue.front();
        vectors_queue.pop();

        long long tmp = 0;
        for (int j = 0; j < vector_lenght; j++) {
            tmp += a[j] * b[j];
        }
        result += tmp;
        delete[] a;
        delete[] b;
    }
    return result;
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

int main() {

    count_time("linear", linear);
    count_time("parallel", parallel);

    return 0;
}
