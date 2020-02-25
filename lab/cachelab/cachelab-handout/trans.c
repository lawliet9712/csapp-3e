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
#include "cachelab.h"

int is_transpose(int M, int N, int A[N][M], int B[M][N]);

/* 
 * You can define additional transpose functions below. We've defined
 * a simple one below to help you get started. 
 */ 

/* 
 * trans - A simple baseline transpose function, not optimized for the cache.
 */
char trans_desc[] = "Simple row-wise scan transpose";
void trans(int M, int N, int A[N][M], int B[M][N])
{
    int i, j, tmp;

    for (i = 0; i < N; i++) {
        for (j = 0; j < M; j++) {
            tmp = A[i][j];
            B[j][i] = tmp;
        }
    }    
}

char trans_desc_m32_n32[] = "Simple row-wise scan transpose";
void trans_m32_n32(int M, int N, int A[N][M], int B[M][N])
{
    int i, j, k;
    for (i = 0; i < N ; i+=8) {
        for (j = 7; j < M; j+=8) {
            for (k = i; k < i+ 8 && k < N; k++){
                int tmp_1 = A[k][j-7];
                int tmp_2 = A[k][j-6];
                int tmp_3 = A[k][j-5];
                int tmp_4 = A[k][j-4];
                int tmp_5 = A[k][j-3];
                int tmp_6 = A[k][j-2];
                int tmp_7 = A[k][j-1];
                int tmp_8 = A[k][j];

                B[j-7][k] = tmp_1;
                B[j-6][k] = tmp_2;
                B[j-5][k] = tmp_3;
                B[j-4][k] = tmp_4;
                B[j-3][k] = tmp_5;
                B[j-2][k] = tmp_6;
                B[j-1][k] = tmp_7;
                B[j][k] = tmp_8;
            }
        }    
    }
}

char trans_desc_m64_n64[] = "Simple row-wise scan transpose";
void trans_m64_n64(int M, int N, int A[N][M], int B[M][N])
{
    // 每个 block 可以存 8 个 int ，每次将前 4 个 int 进行转置后，后 4 个再进行转置会造成冲突不命中，故每次转置前 4 个 int ，将后 4 个临时放在矩阵 B 中已经 hit 的 block 中
    int i, j, k, y, tmp_1, tmp_2, tmp_3, tmp_4, tmp_5, tmp_6, tmp_7, tmp_8;
    for (i = 0; i < N ; i+=8) {
        for (j = 0; j < M; j+=8) {
            // 由于是 64*64 得矩阵,最多只能cache 4 行,每超过 4 行出现冲突不命中
            for (k = i; k < i+4 && k < N; k++){
                tmp_1 = A[k][j];
                tmp_2 = A[k][j+1];
                tmp_3 = A[k][j+2];
                tmp_4 = A[k][j+3];
                tmp_5 = A[k][j+4];
                tmp_6 = A[k][j+5];
                tmp_7 = A[k][j+6];
                tmp_8 = A[k][j+7];

                // 将 A[k] 得 block cache 全取出来，避免后续冲突不命中
                B[j][k] = tmp_1;
                B[j+1][k] = tmp_2;
                B[j+2][k] = tmp_3;
                B[j+3][k] = tmp_4;

                B[j][k+4] = tmp_5;
                B[j+1][k+4] = tmp_6;
                B[j+2][k+4] = tmp_7;
                B[j+3][k+4] = tmp_8;
            }

            // 将临时缓存的 A[k] 后 4 个 int 转置到正确位置
            // 并且将缓存的位置更新为正确的值
            for (y = j; y < j+4 && y < M; y++)
            {
                tmp_1 = A[i+4][y];
                tmp_2 = A[i+5][y];
                tmp_3 = A[i+6][y];
                tmp_4 = A[i+7][y];
                tmp_5 = B[y][i+4];
                tmp_6 = B[y][i+5];
                tmp_7 = B[y][i+6];
                tmp_8 = B[y][i+7];

                B[y][i+4] = tmp_1;
                B[y][i+5] = tmp_2; 
                B[y][i+6] = tmp_3;           
                B[y][i+7] = tmp_4;
                B[y+4][i] = tmp_5;
                B[y+4][i+1] = tmp_6;
                B[y+4][i+2] = tmp_7;
                B[y+4][i+3] = tmp_8;
            }

            for (y = i+4; y < i+8 && y < N; y++)
            {
                tmp_1 = A[y][j+4];
                tmp_2 = A[y][j+5];
                tmp_3 = A[y][j+6];
                tmp_4 = A[y][j+7];

                B[j+4][y] = tmp_1;
                B[j+5][y] = tmp_2;
                B[j+6][y] = tmp_3;
                B[j+7][y] = tmp_4;
            }

        }
    }
}

char trans_desc_m61_n67[] = "Simple row-wise scan transpose";
void trans_m61_n67(int M, int N, int A[N][M], int B[M][N])
{
    int i, j, k, y;
    for (i = 0; i < N; i+=16)
    {
        for (j = 0; j < M; j+=16)
        {
            for (k = i; k < i+16 && k < N; k++)
            {
                for (y = j; y < j+16 && y < M; y++)
                {
                    B[y][k] = A[k][y];
                }
            }

        }

    }
}

/* 
 * transpose_submit - This is the solution transpose function that you
 *     will be graded on for Part B of the assignment. Do not change
 *     the description string "Transpose submission", as the driver
 *     searches for that string to identify the transpose function to
 *     be graded. 
 */
char transpose_submit_desc[] = "Transpose submission";
void transpose_submit(int M, int N, int A[N][M], int B[M][N])
{
    if (M == 32 && N == 32)
    {
        trans_m32_n32(M, N, A, B);
    }
    else if (M == 64 && N == 64)
    {
        trans_m64_n64(M, N, A, B);
    }
    else if (M == 61 && N == 67)
    {
        trans_m61_n67(M, N, A, B);
    }

}



/*
 * registerFunctions - This function registers your transpose
 *     functions with the driver.  At runtime, the driver will
 *     evaluate each of the registered functions and summarize their
 *     performance. This is a handy way to experiment with different
 *     transpose strategies.
 */
void registerFunctions()
{
    /* Register your solution function */
    registerTransFunction(transpose_submit, transpose_submit_desc); 

    /* Register any additional transpose functions */
    //registerTransFunction(trans, trans_desc); 

}

/* 
 * is_transpose - This helper function checks if B is the transpose of
 *     A. You can check the correctness of your transpose by calling
 *     it before returning from the transpose function.
 */
int is_transpose(int M, int N, int A[N][M], int B[M][N])
{
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

