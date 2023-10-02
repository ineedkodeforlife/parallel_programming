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
    int size_matrix, sum;
    double start, end;
    
    cout << "Введите размер матриц\n";

    cin >> size_matrix;


    vector<int> array_1 = generateRandomVector(size_matrix, 1, 100);
    vector<int> array_2 = generateRandomVector(size_matrix, 1, 100);
    vector<int> array_3 = generateRandomVector(size_matrix, 1, 100);

    float total = 0;

    start = omp_get_wtime();
#pragma omp parallel shared(a)
    {
#pragma omp for private(i,j,sum) reduction(+:total)
        sum = 0;
        for (int i = 0; i < size_matrix; i++)
        {
            if (array_1[i] % 2 == 0 and array_2[i] + array_3[i] != 1) {
                sum += array_2[i] + array_3[i];
            }
            else if (array_1[i] % 2 != 0 and array_2[i] - array_3[i] != 1) {
                sum += array_2[i] - array_3[i];
            }
        }
     total = total + sum;
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
    cout << "not_parallel_total" << sum << endl;
    cout << "not_parallel_time : " << end - start;
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
