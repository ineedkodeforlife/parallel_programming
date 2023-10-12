#include <omp.h>
#include <vector>
#include <iostream>
#include <random> 
using namespace std;

std::vector<int> generateRandomVector(int size, int min, int max) {
    std::vector<int> result;

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
    int size_matrix, i, j, sum, max_sum = 0;
    double start, end;

    cout << "Enter size of matrix\n";

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
    cout << "total_reduction :" << total << endl << "parallel_time : " << end - start << endl;

    total = 0;


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
#pragma omp barrier

    }
    end = omp_get_wtime();
    cout << "total_reduction_barrier :" << total << endl << "parallel_time_reduction_barrier : " << end - start << endl;

    total = 0;

    start = omp_get_wtime();
#pragma omp parallel 
    {
#pragma omp for private(i,j,sum)
        for (int i = 0; i < size_matrix; i++)
        {
            sum = 0;
            if (array_1[i] % 2 == 0 and array_2[i] + array_3[i] != 1) {
                sum += array_2[i] + array_3[i];
            }
            else if (array_1[i] % 2 != 0 and array_2[i] - array_3[i] != 1) {
                sum += array_2[i] - array_3[i];
            }

            if (sum > max_sum) {
#pragma omp critical
                if (sum > max_sum) {
                    max_sum = sum;
                }
            }

#pragma omp atomic
            total += sum;
        }
    }
    end = omp_get_wtime();
    cout << "total_atomic : " << total << endl << "parallel_time_atomic : " << end - start << endl;


    total = 0;

    start = omp_get_wtime();
#pragma omp parallel 
    {
#pragma omp for private(i,j,sum)
        for (int i = 0; i < size_matrix; i++)
        {
            sum = 0;
            if (array_1[i] % 2 == 0 and array_2[i] + array_3[i] != 1) {
                sum += array_2[i] + array_3[i];
            }
            else if (array_1[i] % 2 != 0 and array_2[i] - array_3[i] != 1) {
                sum += array_2[i] - array_3[i];
            }

            if (sum > max_sum) {
#pragma omp critical
                if (sum > max_sum) {
                    max_sum = sum;
                }
            }
#pragma omp atomic
            total += sum;
        }
#pragma omp barrier

    }
    end = omp_get_wtime();
    cout << "total_barier : " << total << endl << "parallel_time_atomic_barrier : " << end - start << endl;

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