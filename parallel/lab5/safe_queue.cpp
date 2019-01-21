#include <queue>
#include <iostream>
#include <mutex>
#include <thread>
#include <fstream>
#include "SafeQueue.h"

#include <queue>
#include <mutex>
#include <memory>
#include <condition_variable>
#include <iostream>

template<typename T>
class SafeQueue {
private:
    std::queue<T> queue;
    std::mutex mutex;
    std::condition_variable condition;
public:

    bool empty() {
        std::lock_guard<std::mutex> lock_guard(mutex);
        return queue.empty();
    }

    std::shared_ptr<T> wait_and_pop() {
        std::unique_lock<std::mutex> unique_lock(mutex);
        queue.wait(unique_lock, !queue.empty());
        std::shared_ptr<T> result(std::make_shared<T>(move(queue.front())));
        queue.pop();
        return result;
    }

    std::shared_ptr<T> try_pop() {
        std::lock_guard<std::mutex> lock_guard(mutex);
        if (queue.empty())
            return std::shared_ptr<T>();
        std::shared_ptr<T> result(std::make_shared<T>(move(queue.front())));
        queue.pop();
        return result;
    }

    SafeQueue() {

    }

    void push(T element) {
        std::lock_guard<std::mutex> lock_guard(mutex);
        queue.push(element);
        condition.notify_one();
    }

};


#define SMALL_FILE_EXTENSION ".tmp"
#define threads_number 2

void bubble_sort(int *arr, int n) {
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (arr[j] > arr[j + 1])
                std::swap(arr[j], arr[j + 1]);
}

void do_work_with_file(const std::string &file_name) {
    std::fstream fin(file_name + SMALL_FILE_EXTENSION);
    std::ofstream fout(file_name + "-sorted" + SMALL_FILE_EXTENSION);
    int size = 0, number = 0;
    fin >> size;

    int *arr = new int[size];
    for (int j = 0; j < size; ++j) {
        fin >> number;
        arr[j] = number;
    }
    fin.close();

    fout << size << "\n";
    bubble_sort(arr, size);
    for (int j = 0; j < size; j++)
        fout << arr[j] << " ";

    fout.close();
}

void sort_numbers_in_file(SafeQueue<std::string> &q) {
    int i = 0;
    while (true) {
        std::shared_ptr<std::string> ptr(q.try_pop());
        if (ptr != nullptr) {
            do_work_with_file(*ptr);
            i++;
            continue;
        }
        std::cout << "Total files by thread " << std::this_thread::get_id() << ": " << i << std::endl;
        return;
    }
}

template<typename T>
void add_files_to_queue(SafeQueue<T> &queue, int start, int amount) {
    for (int i = start; i <= amount; i++)
        queue.push(std::to_string(i));
}

int main(int argc, char *argv[]) {
    int number_of_files = std::stoi(argv[1]);
    SafeQueue<std::string> file_names;
    std::vector<std::thread> threads;
    threads.reserve(threads_number);
    std::chrono::time_point<std::chrono::steady_clock> start, end;

    std::cout << "Total files: " << number_of_files << std::endl;

    start = std::chrono::steady_clock::now();
    add_files_to_queue(file_names, 1, number_of_files / 2);
    for (int i = 0; i < threads_number; i++)
        threads.emplace_back(std::thread(sort_numbers_in_file, std::ref(file_names)));
    add_files_to_queue(file_names, number_of_files / 2 + 1, number_of_files);

    for (auto &thread : threads)
        thread.join();

    end = std::chrono::steady_clock::now();

    double elapsed_time = (1. * std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()) / 1000;
    printf("Elapsed time: %.3lf s.\n", elapsed_time);

}