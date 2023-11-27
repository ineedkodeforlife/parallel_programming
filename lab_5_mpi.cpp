#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <mpi.h>

using namespace std;

void merge(vector<int>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<int> left_half(n1);
    vector<int> right_half(n2);

    for (int i = 0; i < n1; i++)
        left_half[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        right_half[j] = arr[mid + 1 + j];

    int i = 0;
    int j = 0;
    int k = left;

    while (i < n1 && j < n2) {
        if (left_half[i] <= right_half[j]) {
            arr[k] = left_half[i];
            i++;
        }
        else {
            arr[k] = right_half[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = left_half[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = right_half[j];
        j++;
        k++;
    }
}

void mergeSort(vector<int>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

void parallelMergeSort(vector<int>& arr, int rank, int size, MPI_Comm comm) {
    int local_size = arr.size() / size;
    vector<int> local_data(local_size);

    MPI_Scatter(arr.data(), local_size, MPI_INT, local_data.data(), local_size, MPI_INT, 0, comm);

    mergeSort(local_data, 0, local_size - 1);

    vector<int> sorted_data(arr.size());

    MPI_Gather(local_data.data(), local_size, MPI_INT, sorted_data.data(), local_size, MPI_INT, 0, comm);

    if (rank == 0) {
        mergeSort(sorted_data, 0, arr.size() - 1);
        arr = sorted_data;
    }
}

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank, size;

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    MPI_Comm new_comm;
    MPI_Comm_split(MPI_COMM_WORLD, rank % 2, rank, &new_comm);

    const int N = 100000;  

    vector<int> data;

    if (rank == 0) {
        srand(time(0));
        data.resize(N);
        for (int i = 0; i < N; i++) {
            data[i] = rand() % 1000000;
        }
    }

    double start_time = MPI_Wtime();

    parallelMergeSort(data, rank, size, new_comm);

    double end_time = MPI_Wtime();

    if (rank == 0) {
        cout << "Time taken for sorting: " << end_time - start_time << " seconds" << endl;
    }

    MPI_Finalize();

    return 0;
}
