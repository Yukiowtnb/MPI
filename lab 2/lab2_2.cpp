#include <iostream>
#include <mpi.h>

#define DATA 10

int main(int argc, char** argv) {
    // ������������� MPI
    MPI_Init(&argc, &argv);

    // ��������� ����� � �������
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // ����������� ������ ��� ��������
    int my_data = rank * DATA;

    // ����������� ���������� � ����������� ��������� � ������
    int next_rank = (rank + 1) % size;
    int prev_rank = (rank - 1 + size) % size;

    // �������� ������ ���������� ��������
    MPI_Send(&my_data, 1, MPI_INT, next_rank, 0, MPI_COMM_WORLD);

    // ����� ������ �� ����������� ��������
    int received_data;
    MPI_Recv(&received_data, 1, MPI_INT, prev_rank, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

    // ����� �����������
    std::cout << "������� " << rank << ": �������� " << my_data << ", ������� " << received_data << std::endl;

    // ���������� ������ � MPI
    MPI_Finalize();

    return 0;
}
