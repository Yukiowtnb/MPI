#include <iostream>
#include <mpi.h>

#define DATA 10

int main(int argc, char** argv) {
    // ������������� MPI
    MPI_Init(&argc, &argv);

    // ��������� ����� � �������
    int world_rank, world_size;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    // ����������� ������ ��� ��������
    int data = world_rank;

    // ����������� ���������� � ����������� ��������� � ������
    int next_rank = (world_rank + 1) % world_size;
    int prev_rank = (world_rank - 1 + world_size) % world_size;

    // �������� ������ ���������� ��������
    MPI_Send(&data, 1, MPI_INT, next_rank, 0, MPI_COMM_WORLD);

    // ����� ������ �� ����������� ��������
    MPI_Recv(&data, 1, MPI_INT, prev_rank, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

    // ����� ������ �������� � �������� ������
    std::cout << "������� " << world_rank << " ������ ������: " << data << std::endl;

    // ���������� ������ � MPI
    MPI_Finalize();

    return 0;
}
