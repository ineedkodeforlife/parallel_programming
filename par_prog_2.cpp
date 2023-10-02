#include <omp.h>
#include <iostream>
#include<vector>
using namespace std;


const int NMAX = 500;
const int LIMIT = 500;
void main()
{
    double start, end;
    int i, j;
    float sum;
   //vector<std::vector<int>> a(NMAX, std::vector<int>(NMAX));
    float a[NMAX][NMAX];

    for (i = 0; i < NMAX; i++)
        for (j = 0; j < NMAX; j++)
            a[i][j] = i+j;


start = omp_get_wtime();
#pragma omp parallel shared(a) if (NMAX>LIMIT)
    {
#pragma omp for private(i,j,sum) 
        for (i = 0; i < NMAX; i++)
        {
            sum = 0;
            for (j = 0; j < NMAX; j++)
                sum += a[i][j];
            //cout << "sum elements string: " << i << "  " << sum << endl;
        }
    } /* Завершение параллельного фрагмента */

end = omp_get_wtime();
cout << "Time work = " << end - start;
}
