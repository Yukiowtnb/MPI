#include <iostream>
#include <mpi.h>

#define DATA 10

int main(int argc, char** argv) {
    // Инициализация MPI
    MPI_Init(&argc, &argv);

    // Получение ранга и размера
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Определение данных для передачи
    int my_data = rank * DATA;

    // Определение следующего и предыдущего процессов в кольце
    int next_rank = (rank + 1) % size;
    int prev_rank = (rank - 1 + size) % size;

    // Отправка данных следующему процессу
    MPI_Send(&my_data, 1, MPI_INT, next_rank, 0, MPI_COMM_WORLD);

    // Прием данных от предыдущего процесса
    int received_data;
    MPI_Recv(&received_data, 1, MPI_INT, prev_rank, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

    // Вывод результатов
    std::cout << "Процесс " << rank << ": отправил " << my_data << ", получил " << received_data << std::endl;

    // Завершение работы с MPI
    MPI_Finalize();

    return 0;
}
