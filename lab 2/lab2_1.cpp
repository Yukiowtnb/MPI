#include <iostream>
#include <mpi.h>

#define DATA 10

int main(int argc, char** argv) {
    // Инициализация MPI
    MPI_Init(&argc, &argv);

    // Получение ранга и размера
    int world_rank, world_size;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    // Определение данных для передачи
    int data = world_rank;

    // Определение следующего и предыдущего процессов в кольце
    int next_rank = (world_rank + 1) % world_size;
    int prev_rank = (world_rank - 1 + world_size) % world_size;

    // Отправка данных следующему процессу
    MPI_Send(&data, 1, MPI_INT, next_rank, 0, MPI_COMM_WORLD);

    // Прием данных от предыдущего процесса
    MPI_Recv(&data, 1, MPI_INT, prev_rank, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

    // Вывод номера процесса и принятых данных
    std::cout << "Процесс " << world_rank << " принял данные: " << data << std::endl;

    // Завершение работы с MPI
    MPI_Finalize();

    return 0;
}
