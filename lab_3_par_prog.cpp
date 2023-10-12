#include <omp.h>
#include <vector>
#include <iostream>
#include <random> 
using namespace std;

std::vector<int> generateRandomVector(int size, int min, int max) {
    std::vector<int> result;

    // Инициализация генератора рандомных чисел
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distribution(min, max);

    for (int i = 0; i < size; ++i) {
        result.push_back(distribution(gen));
    }

    return result;
}



int main()
{
    int size_matrix, sum = 0, i, j;
    double start, end;

    cout << "Enter size matrix\n";

    cin >> size_matrix;


    vector<int> array_1 = generateRandomVector(size_matrix, 1, 100);
    vector<int> array_2 = generateRandomVector(size_matrix, 1, 100);
    vector<int> array_3 = generateRandomVector(size_matrix, 1, 100);

     int total = 0;

    start = omp_get_wtime();
#pragma omp parallel
    {
#pragma omp for private(i,j, sum) reduction(+:total)
        for (int i = 0; i < size_matrix; i++)
        {
            sum = 0;
            if (array_1[i] % 2 == 0 and array_2[i] + array_3[i] != 1) {
                sum += array_2[i] + array_3[i];
            }
            else if (array_1[i] % 2 != 0 and array_2[i] - array_3[i] != 1) {
                sum += array_2[i] - array_3[i];
            }
            total += sum;
           
        }
    }
    end = omp_get_wtime();
    cout << "total :" << total << endl << "parallel_time : " << end - start << endl;

    sum = 0;
    start = omp_get_wtime();
    for (int i = 0; i < size_matrix; i++)
    {
        if (array_1[i] % 2 == 0 and array_2[i] + array_3[i] != 1) {
            sum += array_2[i] + array_3[i];
        }
        else if (array_1[i] % 2 != 0 and array_2[i] - array_3[i] != 1) {
            sum += array_2[i] - array_3[i];
        }
    }
    end = omp_get_wtime();
    cout << "not_parallel_total : " << sum << endl;
    cout << "not_parallel_time : " << end - start;
}
