
#include <fstream>
#include <chrono>

#pragma warning(disable: 4996)

#define SMALL_SPLITED_FILE_NAME ".tmp"
#define INPUT_FILE "input.txt"
#define OUTPUT_FILE "output.txt"
#define SMALL_FILE_SIZE 500
int splited_files_count = 0;

void bubble_sort(int *arr, int n) {
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (arr[j] > arr[j + 1])
                std::swap(arr[j], arr[j + 1]);
}

void split_input_file(const char *input) {
    std::ifstream fin(input);

    char *name = new char[20];
    int number;
    int big_file_size = 0;
    fin >> big_file_size;

    int small_file_count = big_file_size / SMALL_FILE_SIZE;
    int residue = big_file_size - small_file_count * SMALL_FILE_SIZE;
    if (residue)
        small_file_count += 1;

    for (int i = 0; i < small_file_count; ++i) {
        sprintf(name, "%d%s", i, SMALL_SPLITED_FILE_NAME);
        int size = ((i == small_file_count - 1 && residue != 0) ? residue : SMALL_FILE_SIZE);
        int *arr = new int[size];
        for (int j = 0; j < size; ++j) {
            fin >> number;
            arr[j] = number;
        }
        std::ofstream out(name);
        out << size << "\n";
        bubble_sort(arr, size);
        for (int j = 0; j < size; j++)
            out << arr[j] << " ";

        out.close();
    }
    splited_files_count = small_file_count;

    fin.close();
    delete[] name;
}

void merge_two_files_in_one(char *name1, char *name2, char *nameout) {
    std::fstream in1(name1);
    std::fstream in2(name2);
    std::ofstream out(nameout);
    int small_file_size1, small_file_size2;
    int number1, number2;

    in1 >> small_file_size1;
    in2 >> small_file_size2;
    in1 >> number1;
    in2 >> number2;


    int count = small_file_size1 + small_file_size2;
    out << count << "\n";

    int peek1 = small_file_size1 - 1;
    int peek2 = small_file_size2 - 1;
    for (int i = 0; i < count; ++i) {
        if (!peek1) {
            out << number2 << " ";
            in2 >> number2;
            continue;
        }
        if (!peek2) {
            out << number1 << " ";
            in1 >> number1;
            continue;
        }
        if (number1 > number2) {
            out << number2 << " ";
            in2 >> number2;
            peek2--;
        } else {
            out << number1 << " ";
            in1 >> number1;
            peek1--;
        }
    }

    in1.close();
    in2.close();
    out.close();
}

void merge_to_output_file(const char *output) {
    int files_to_merge = splited_files_count;
    char *name1 = new char[20];
    char *name2 = new char[20];
    char *rez_name = new char[20];

    for (int i = 1; i < files_to_merge; ++i) {
        sprintf(name1, "%d%s", i - 1, SMALL_SPLITED_FILE_NAME);
        sprintf(name2, "%d%s", i, SMALL_SPLITED_FILE_NAME);
        sprintf(rez_name, "m%d%s", i, SMALL_SPLITED_FILE_NAME);
        merge_two_files_in_one(name1, name2, rez_name);
        remove(name1);
        remove(name2);
        rename(rez_name, name2);
    }

    if (files_to_merge == 1)
        sprintf(name2, "%d%s", 0, SMALL_SPLITED_FILE_NAME);

    remove(output);
    rename(name2, output);

    delete[] name1;
    delete[] name2;
    delete[] rez_name;
}

int main() {
    std::chrono::time_point<std::chrono::steady_clock> start, end;

    start = std::chrono::steady_clock::now();
    split_input_file(INPUT_FILE);
    merge_to_output_file(OUTPUT_FILE);
    end = std::chrono::steady_clock::now();

    double elapsed_time = (1. * std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()) / 1000;
    printf("Elapsed time: %.3lf s.\n", elapsed_time);

}