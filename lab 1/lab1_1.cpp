#include <omp.h>
#include <vector>
#include <iostream>

#define M 10

int mainone() {
    std::vector<std::vector<float>> A(M, std::vector<float>(M));
    std::vector<float> b(M), c(M, 0.0);

    // Инициализация данных
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < M; j++) {
            A[i][j] = static_cast<float>(j + 1);
        }
        b[i] = static_cast<float>(i + 1);
    }
    std::cout << "Matrix" << std::endl;
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < M; j++) {
            std::cout << A[i][j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << "Vector" << std::endl;
    for (int i = 0; i < M; i++) {
        std::cout << b[i] << " ";
    }
    std::cout << std::endl;

    // Создание множества параллельных процессов
#pragma omp parallel
    {
        int rank = omp_get_thread_num();
        int thread_count = omp_get_num_threads();
        int chunk_size = M / thread_count;
        int start = rank * chunk_size;
        int end = (rank == thread_count - 1) ? M : start + chunk_size;

        // Распределение работ между потоками
        for (int i = start; i < end; i++) {
            for (int j = 0; j < M; j++) {
                c[i] += A[i][j] * b[j];
            }
        }
    }

    // Вывод результата
    for (int i = 0; i < M; i++) {
        std::cout << "c[" << i << "] = " << c[i] << std::endl;
    }

    return 0;
}
