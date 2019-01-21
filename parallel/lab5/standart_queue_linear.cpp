#include <queue>
#include <iostream>
#include <mutex>
#include <thread>
#include <fstream>


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

template<typename T>
void add_files_to_queue(std::queue<T> &queue, int start, int amount) {
    for (int i = start; i <= amount; i++) {
        queue.push(std::to_string(i));
    }
}

int main(int argc, char *argv[]) {
    int number_of_files = std::stoi(argv[1]);
    std::queue<std::string> file_names;
    std::chrono::time_point<std::chrono::steady_clock> start, end;

    std::cout << "Total files: " << number_of_files << std::endl;

    start = std::chrono::steady_clock::now();
    add_files_to_queue(file_names, 1, number_of_files);

    while (!file_names.empty())
    {
        auto file_name = file_names.front();
        file_names.pop();
        do_work_with_file(file_name);
    }


    end = std::chrono::steady_clock::now();

    double elapsed_time = (1. * std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()) / 1000;
    printf("Elapsed time: %.3lf s.\n", elapsed_time);

}