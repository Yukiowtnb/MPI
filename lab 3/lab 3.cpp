#include <stdio.h>
#include <stdlib.h>
#include <cuda.h>

#define SIZE 216 // Размер матрицы
#define BLOCK_SIZE 16 // Размер блока потоков

// Ядро CUDA для транспонирования матрицы
__global__ void transpose(float* A, float* C) {
    int i = blockIdx.x * blockDim.x + threadIdx.x;
    int j = blockIdx.y * blockDim.y + threadIdx.y;

    if (i < SIZE && j < SIZE) {
        C[j * SIZE + i] = A[i * SIZE + j];
    }
}

void printMatrix(float* matrix) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf("%d ", (int)matrix[i * SIZE + j]);
        }
        printf("\n");
    }
}

int main() {
    float* A, * C;
    float* d_A, * d_C;

    // Выделение памяти на хосте
    A = (float*)malloc(SIZE * SIZE * sizeof(float));
    C = (float*)malloc(SIZE * SIZE * sizeof(float));

    // Заполнение матрицы A случайными числами от 0 до 9
    for (int i = 0; i < SIZE * SIZE; i++) {
        A[i] = rand() % 10;
    }

    printf("Исходная матрица:\n");
    printMatrix(A);

    // Выделение памяти на устройстве
    cudaMalloc((void**)&d_A, SIZE * SIZE * sizeof(float));
    cudaMalloc((void**)&d_C, SIZE * SIZE * sizeof(float));

    // Копирование данных с хоста на устройство
    cudaMemcpy(d_A, A, SIZE * SIZE * sizeof(float), cudaMemcpyHostToDevice);

    // Запуск ядра CUDA
    dim3 threadsPerBlock(BLOCK_SIZE, BLOCK_SIZE);
    dim3 numBlocks((SIZE + BLOCK_SIZE - 1) / BLOCK_SIZE, (SIZE + BLOCK_SIZE - 1) / BLOCK_SIZE);
    transpose << <numBlocks, threadsPerBlock >> > (d_A, d_C);

    // Копирование данных с устройства на хост
    cudaMemcpy(C, d_C, SIZE * SIZE * sizeof(float), cudaMemcpyDeviceToHost);

    printf("\nТранспонированная матрица:\n");
    printMatrix(C);

    // Освобождение памяти
    free(A);
    free(C);
    cudaFree(d_A);
    cudaFree(d_C);

    return 0;
}
