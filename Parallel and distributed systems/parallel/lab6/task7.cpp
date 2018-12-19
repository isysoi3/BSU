//
// Created by isysoi on 13.12.18.
//

#include <iostream>
#include <omp.h>
#include <numeric>
#include <fstream>
#include <queue>

#define num_vectors 2000
#define vector_lenght 25
#define threads_number 4
#define input_file "vectors"

typedef long long (*function)();

long long parallel() {

    std::queue<std::vector<int>> vectors_queue;
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
                std::vector<int> tmp_vector;

                int num = 0;
                for (int i = 0; i < num_vectors; i++) {
                    for (int j = 0; j < vector_lenght; j++) {
                        fin >> num;
                        tmp_vector.push_back(num);
                    }
                    omp_set_lock(&lock);
                    vectors_queue.push(tmp_vector);
                    omp_unset_lock(&lock);
                    tmp_vector.clear();
                }
                omp_set_lock(&lock);
                isFinished = true;
                omp_unset_lock(&lock);

                fin.close();
            }
#pragma omp section
            {
                std::vector<int> a;
                std::vector<int> b;

                while (true) {
                    omp_set_lock(&lock);
                    if (vectors_queue.empty() && isFinished)
                        break;
                    omp_unset_lock(&lock);

                    while (vectors_queue.size() < 2) {}

                    omp_set_lock(&lock);
                    a = vectors_queue.front();
                    vectors_queue.pop();
                    b = vectors_queue.front();
                    vectors_queue.pop();
                    omp_unset_lock(&lock);

                    result += std::inner_product(std::begin(a), std::end(a), std::begin(b), 0);
                }
                omp_unset_lock(&lock);
            }
        }
    }
    omp_destroy_lock(&lock);

    return result;
}


long long linear() {
    std::ifstream fin(input_file);

    std::queue<std::vector<int>> vectors_queue;
    std::vector<int> tmp_vector;
    tmp_vector.reserve(vector_lenght);
    int num = 0;

    for (int i = 0; i < num_vectors; i++) {
        for (int j = 0; j < vector_lenght; j++) {
            fin >> num;
            tmp_vector.push_back(num);
        }
        vectors_queue.push(tmp_vector);
        tmp_vector.clear();
    }
    fin.close();

    std::vector<int> a(vector_lenght);
    std::vector<int> b(vector_lenght);
    long long result = 0;
    while (!vectors_queue.empty()) {
        a = vectors_queue.front();
        vectors_queue.pop();
        b = vectors_queue.front();
        vectors_queue.pop();

        result += std::inner_product(std::begin(a), std::end(a), std::begin(b), 0);
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

   // count_time("linear", linear);
    count_time("parallel", parallel);

    return 0;
}
