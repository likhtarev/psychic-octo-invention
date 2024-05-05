#include <stdio.h>
#include <thread>
#define ROW 2
#define COL 2
#define n = 2
int res = 0;

void multiplyMatrix(int matrixA[ROW][COL], int matrixB[COL][COL], int result[ROW][COL]) {
    for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < COL; j++) {
            result[i][j] = 0;
            for (int k = 0; k < COL; k++) {
                result[i][j] += matrixA[i][k] * matrixB[k][j];
            }
        }
    }
}





int matrixelemmult(int index[], int matrixA[ROW][COL], int matrixB[COL][COL], int& res ) {
    int i = index[0];
    int j = index[1];
    for (int k = 0; k < ROW; k++) {
        res += matrixA[i][k] * matrixB[k][j];
    }
    return res;
}

int main() {
    int matrixA[ROW][COL] = { {1, 2}, {3, 4} };
    int matrixB[COL][COL] = { {5, 6}, {7, 8} };
    int result[ROW][COL];
    int resultWithoutThreads[ROW][COL];
    int index00[] = { 0,0 };
    int index01[] = { 0,1 };
    int index10[] = { 1,0 };
    int index11[] = { 1,1 };
    int result00 = 0;
    int result01 = 0;
    int result10 = 0;
    int result11 = 0;
    
    
    clock_t start1 = clock();
    std::thread th1(matrixelemmult, index00, matrixA, matrixB, std::ref(result00));
    th1.join();
    result[0][0] = result00;
    std::thread th2(matrixelemmult, index01, matrixA, matrixB, std::ref(result01));
    th2.join();
    result[0][1] = result01;
    std::thread th3(matrixelemmult, index10, matrixA, matrixB, std::ref(result10));
    th3.join();
    result[1][0] = result10;
    std::thread th4(matrixelemmult, index11, matrixA, matrixB, std::ref(result11));
    th4.join();
    result[1][1] = result11;
    clock_t end1 = clock();
    double seconds1 = (double)(end1 - start1) / CLOCKS_PER_SEC;
    printf("RunTime with threads : %f sec\n", seconds1);

    clock_t start2 = clock();
    multiplyMatrix(matrixA, matrixB, resultWithoutThreads);
    clock_t end2 = clock();
    double seconds2 = (double)(end2 - start2) / CLOCKS_PER_SEC;
    printf("RunTime without threads : %f sec\n", seconds2);
    
    for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < COL; j++) {
            printf("%d ", result[i][j]);
        }
        printf("\n");
    }

    return 0;
}
