#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <iostream>
#include <bitset>
#include <vector>

using namespace std;


int main() {
    int rows, cols;

    cout << "Введите количество строк: ";
    cin >> rows;

    cout << "Введите количество столбцов: ";
    cin >> cols;

    vector<std::vector<int>> array(rows, std::vector<int>(cols));


    int i, j;
    int sum, mult;
    int n, k;
    string bin_val;
    int m, t;
    double start, end;
    sum = 0;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            array[i][j] = i * j;
        }
    }

#pragma omp parallel shared(sum) private(mult) 
    {
#pragma omp for private(j,sum) 
        start = omp_get_wtime();
        sum = 0;
        for (i = 0; i < rows; i++)
        {
            mult = 0;
            for (j = 1; j < cols; j++) {
                mult = array[i][j] * array[i][j - 1];
                while (mult)
                {
                    mult = mult / 2;
                    t = mult % 2;
                    if (t == 1) {
                        sum += 1;
                    }
                }
            }

        }
    }
    cout << sum << endl;
    int omp_get_num_threads(void);
    //cout << omp_get_num_threads;
    end = omp_get_wtime();
    cout << "Work took %f seconds = " << end - start;
    /* Р—Р°РІРµСЂС€РµРЅРёРµ РїР°СЂР°Р»Р»РµР»СЊРЅРѕРіРѕ С„СЂР°РіРјРµРЅС‚Р° */

    //dwStart = GetTickCount();
    int num_threads;
    num_threads = 1;

    void omp_set_num_threads(int num_threads);
    start = omp_get_wtime();
    sum = 0;
    for (i = 0; i < rows; i++)
    {
        mult = 0;
        for (j = 1; j < cols; j++) {
            mult = array[i][j] * array[i][j - 1];
            while (mult)
            {
                mult = mult / 2;
                t = mult % 2;
                if (t == 1) {
                    sum += 1;
                }
            }
        }

    }
    cout << sum << endl;
    int omp_get_num_threads(void);
    //cout << omp_get_num_threads;
    end = omp_get_wtime();
    cout << "Work took %f seconds = " << end - start;
}
