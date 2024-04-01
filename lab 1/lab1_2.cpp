#include <omp.h>
#include <vector>
#include <iostream>

#define N 10

int main() {
    std::vector<std::vector<float>> A(N, std::vector<float>(N));
    std::vector<std::vector<float>> B(N, std::vector<float>(N));
    std::vector<std::vector<float>> C(N, std::vector<float>(N, 0.0));

    // Инициализация данных
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            A[i][j] = static_cast<float>(j + 1);
            B[i][j] = static_cast<float>(i + 1);
        }
    }
    std::cout << "Matrix A" << std::endl;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            std::cout << A[i][j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << "Matrix B" << std::endl;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            std::cout << B[i][j] << " ";
        }
        std::cout << std::endl;
    }

    // Создание множества параллельных процессов
#pragma omp parallel
    {
        int rank = omp_get_thread_num();
        int thread_count = omp_get_num_threads();
        int chunk_size = N / thread_count;
        int start = rank * chunk_size;
        int end = (rank == thread_count - 1) ? N : start + chunk_size;

        // Распределение работ между потоками
        for (int i = start; i < end; i++) {
            for (int j = 0; j < N; j++) {
                for (int k = 0; k < N; k++) {
                    C[i][j] += A[i][k] * B[k][j];
                }
            }
        }
    }

    std::cout << "Matrix C" << std::endl;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            std::cout << C[i][j] << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}
