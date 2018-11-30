#include <iostream>
#include <vector>
#include <queue>
#include <thread>
#include <numeric>

#define thread_number 1
#define n 1000000

struct task {
    bool isFinish;
    int start;
};

std::vector<double> results;
std::queue<task> tasks;
std::mutex mutex;

void thread_function() {
    while (true) {
        mutex.lock();
        if (tasks.empty()) {
            mutex.unlock();
            continue;
        }
        auto current_task = tasks.front();
        tasks.pop();
        if (!current_task.isFinish) {
            mutex.unlock();
            int start = current_task.start;
            double h = 1. / n, sum = 0., x;
            for (int i = start; i < n; i += thread_number) {
                x = h * i;
                sum += 4. / (1. + x * x);
            }
            results.push_back(h * sum);
        } else {
            mutex.unlock();
            break;
        }
    }
}

int main() {
    std::chrono::time_point<std::chrono::steady_clock> start, end;
    start = std::chrono::steady_clock::now();
    std::thread threads[thread_number];


    for (auto &i : threads) {
        i = std::thread(thread_function);
    }

    mutex.lock();
    tasks.push({false, 0});
    mutex.unlock();

    mutex.lock();
    tasks.push({false, 1});
    mutex.unlock();

    mutex.lock();
    tasks.push({false, 2});
    mutex.unlock();

    for (int i = 0; i < thread_number; i++) {
        mutex.lock();
        tasks.push({true, 0});
        mutex.unlock();
    }

    for (int j = 0; j < thread_number; ++j) {
        threads[j].join();
    }

    double sum = std::accumulate(results.begin(), results.end(), 0);
    end = std::chrono::steady_clock::now();

    double elapsed_time_seconds =
            (1.0 * std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()) / 1000;
    printf("Result: %f\nElapsed time: %f\n", sum, elapsed_time_seconds);

    return 0;
}
