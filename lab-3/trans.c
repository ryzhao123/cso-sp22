/* 
    Name: Rena Zhao
    NetID: ryz215
    GitHub Name: ryzhao123
*/

/* 
 * trans.c - Matrix transpose B = A^T
 *
 * Each transpose function must have a prototype of the form:
 * void trans(int M, int N, int A[N][M], int B[M][N]);
 *
 * A transpose function is evaluated by counting the number of misses
 * on a 1KB direct mapped cache with a block size of 32 bytes.
 */ 
#include <stdio.h>
#include "lab3.h"

int is_transpose(int M, int N, int A[N][M], int B[M][N]);

/* 
 * transpose_submit - This is the solution transpose function that you
 *     will be graded on for Part B of the assignment. Do not change
 *     the description string "Transpose submission", as the driver
 *     searches for that string to identify the transpose function to
 *     be graded. 
 */
char transpose_submit_desc[] = "Transpose submission";
void transpose_submit(int M, int N, int A[N][M], int B[M][N]) {
    int r, c;
    int diagonalElement, diagonalIndex; 
    int x0, x1, x2, x3, x4, x5, x6, x7;

    if (N == 32) {
        for (diagonalIndex = 0; diagonalIndex < M; diagonalIndex += 8) {
            for (diagonalElement = 0; diagonalElement < N; diagonalElement += 8) {
                for (r = diagonalElement; r < diagonalElement + 8; r++) {
                    for (c = diagonalIndex; c < diagonalIndex + 8; c++) {
                        if (r != c) {
                            B[c][r] = A[r][c];
                        } else {
                            x0 = A[r][c];
                            x1 = r;
                        }
                    }
                    if (diagonalElement == diagonalIndex) {
                        B[x1][x1] = x0;
                    }
                }
            }
        }
    } else if (N == 64) {
        for (diagonalIndex = 0; diagonalIndex < M; diagonalIndex += 8) {
            for (diagonalElement = 0; diagonalElement < N; diagonalElement += 8) {
                for (r = diagonalElement; r < diagonalElement + 4; r++) {
                    x0 = A[r][diagonalIndex];
                    x1 = A[r][diagonalIndex + 1];
                    x2 = A[r][diagonalIndex + 2];
                    x3 = A[r][diagonalIndex + 3];
                    x4 = A[r][diagonalIndex + 4];
                    x5 = A[r][diagonalIndex + 5];
                    x6 = A[r][diagonalIndex + 6];
                    x7 = A[r][diagonalIndex + 7];
                    
                    B[diagonalIndex][r] = x0;
                    B[diagonalIndex + 1][r] = x1;
                    B[diagonalIndex + 2][r] = x2;
                    B[diagonalIndex + 3][r] = x3;
                    B[diagonalIndex][r + 4] = x4;
                    B[diagonalIndex + 1][r + 4] = x5;
                    B[diagonalIndex + 2][r + 4] = x6;
                    B[diagonalIndex + 3][r + 4] = x7;
                }
                for (c = diagonalIndex; c < diagonalIndex + 4; c++) {
                    x4 = A[diagonalElement + 4][c];
                    x5 = A[diagonalElement + 5][c];
                    x6 = A[diagonalElement + 6][c];
                    x7 = A[diagonalElement + 7][c];

                    x0 = B[c][diagonalElement + 4];
                    x1 = B[c][diagonalElement + 5];
                    x2 = B[c][diagonalElement + 6];
                    x3 = B[c][diagonalElement + 7];

                    B[c][diagonalElement + 4] = x4;
                    B[c][diagonalElement + 5] = x5;
                    B[c][diagonalElement + 6] = x6;
                    B[c][diagonalElement + 7] = x7;

                    B[c + 4][diagonalElement] = x0;
                    B[c + 4][diagonalElement + 1] = x1;
                    B[c + 4][diagonalElement + 2] = x2;
                    B[c + 4][diagonalElement + 3] = x3;

                    B[c + 4][diagonalElement + 4] = A[diagonalElement + 4][c + 4];
                    B[c + 4][diagonalElement + 5] = A[diagonalElement + 5][c + 4];
                    B[c + 4][diagonalElement + 6] = A[diagonalElement + 6][c + 4];
                    B[c + 4][diagonalElement + 7] = A[diagonalElement + 7][c + 4];
                }
            }
        }
    } else {
        for (diagonalIndex = 0; diagonalIndex < M; diagonalIndex += 16) {
            for (diagonalElement = 0; diagonalElement < N; diagonalElement += 16) {
                for (r = diagonalElement; (r < N) && (r < diagonalElement + 16); r++) {
                    for (c = diagonalIndex; (c < M) && (c < diagonalIndex + 16); c++) {
                        if (r != c) {
                            B[c][r] = A[r][c];
                        } else {
                            x0 = A[r][c];
                            x1 = r;
                        }
                    }
                    if (diagonalElement == diagonalIndex) {
                        B[x1][x1] = x0;
                    }
                }
            }
        }
    }
}

/* 
 * trans - A simple baseline transpose function, not optimized for the cache.
 */
char trans_desc[] = "Simple row-wise scan transpose";
void trans(int M, int N, int A[N][M], int B[M][N]) {
    int i, j, tmp;
    for (i = 0; i < N; i++) {
        for (j = 0; j < M; j++) {
            tmp = A[i][j];
            B[j][i] = tmp;
        }
    }    
}

/*
 * registerFunctions - This function registers your transpose
 *     functions with the driver.  At runtime, the driver will
 *     evaluate each of the registered functions and summarize their
 *     performance. This is a handy way to experiment with different
 *     transpose strategies.
 */
void registerFunctions() {
    /* Register your solution function */
    registerTransFunction(transpose_submit, transpose_submit_desc); 

    /* Register any additional transpose functions */
    registerTransFunction(trans, trans_desc); 
}

/* 
 * is_transpose - This helper function checks if B is the transpose of
 *     A. You can check the correctness of your transpose by calling
 *     it before returning from the transpose function.
 */
int is_transpose(int M, int N, int A[N][M], int B[M][N]) {
    int i, j;
    for (i = 0; i < N; i++) {
        for (j = 0; j < M; ++j) {
            if (A[i][j] != B[j][i]) {
                return 0;
            }
        }
    }
    return 1;
}
