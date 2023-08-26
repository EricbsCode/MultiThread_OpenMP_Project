#include <iostream>
#include <vector>
#include <cmath>
#include <chrono>
#include <omp.h>

using namespace std::chrono;

int main()
{

    auto start = high_resolution_clock::now();

    int search_max = 1000000000;
    int sqrt_search_max = (int)sqrt(search_max);

    omp_set_num_threads(1);

    std::vector<int> numbers(search_max, 0);
#pragma omp parallel for
    for (int i = 0; i < search_max; i++)
    {
        numbers[i] = (i + 1);
    }

    numbers[0] = 0;

    for (int i = 0; i < sqrt_search_max; i++)
    {
        int current_prime = numbers[i];

        if (current_prime != 0)
        {
#pragma omp parallel for
            for (int j = i; j < search_max; j += current_prime)
            {
                int current_number = numbers[j];
                if (current_number != current_prime)
                {
                    numbers[j] = 0;
                }
            }
        }
    }

    auto stop = high_resolution_clock::now();
    auto exec_time = duration_cast<microseconds>(stop - start);

    std::cout << "Found prime numbers up to " << search_max << " in " << exec_time.count() << " microseconds.\n";

    for (int i = 0; i < 100; i++) 
    {
        if (numbers[i] != 0)
        {
            std::cout << numbers[i] << " ";
        }
    }
    std::cout << std::endl;

    return 0;
}