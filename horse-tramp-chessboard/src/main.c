/*本算法采取贪心算法对马踏棋盘算法进行优化，以减少回溯次数*/
#define ISMAIN  //兼容.h文件
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "StackandChess.h"

int ChessBoard[BOARDSIZE][BOARDSIZE];  //用8*8的全局数组表示棋盘

int Weight[BOARDSIZE][BOARDSIZE];               //对棋盘上的每一个点都赋贪心算法的权值
int SqWeight[BOARDSIZE][BOARDSIZE][BOARDSIZE];  //给棋盘上每个点可能走的方向按权值排序

// HTry数组以此存储有可能会走的八个方向，其中每个方向中第三个元素‘0’只用于凑出chess结构且不增加getPath函数中的方向数
chess HTry[8] = {
    {-2, 1, 0},
    {-1, 2, 0},
    {1, 2, 0},
    {2, 1, 0},
    {2, -1, 0},
    {1, -2, 0},
    {-1, -2, 0},
    {-2, -1, 0}};

int main() {
    int x, y, z;

    weight();
    weight_sort();

    printf("\n***********************************************************************\n");
    printf("*                                                                     *\n");
    printf("*                                                                     *\n");
    printf("*  [NOTE] PLEASE CHECK TERMINAL ENCODING IF ANY DISPLAY ERROR OCCURS  *\n");
    printf("*                  THE RECOMMENDED ENCODING IS UTF-8                  *\n");
    printf("*                                                                     *\n");
    printf("*                                                                     *\n");
    printf("*---------------------------------------------------------------------*\n");
    printf("*                                                                     *\n");
    printf("*                                                                     *\n");
    printf("*         中国科学院大学《数据结构》课程大作业之《马踏棋盘》          *\n");
    printf("*                  小组成员：安文韬、史文轩、张梓堃                   *\n");
    printf("*                                                                     *\n");
    printf("*                                                                     *\n");
    printf("***********************************************************************\n\n\n");

#ifdef DEMONSTRATE_

    printf("Start Demonstration...\n\n");
    while (1) {
        printf("依次输入起始点所在的行、列, 用空格分开(范围: 0-7):\n示例: \"2 3\" (不含引号)");
        scanf("%d %d", &x, &y);
        if (x >= 0 && x <= 7 && y >= 0 && y <= 7) {
            //初始化棋盘
            for (int i = 0; i < BOARDSIZE; i++) {
                for (int j = 0; j < BOARDSIZE; j++) {
                    ChessBoard[i][j] = 0;
                }
            }
            getPath(x, y);  //迷宫寻路核心算法
            printf("是否继续? 如果是请输入1, 否则输入0\n");
            scanf("%d", &z);
            if (z)
                continue;
            else
                break;
        } else
            printf("坐标不合要求, 请重新输入\n");
    }

#endif

#ifdef GETDATA_
#ifndef DEMONSTRATE_
    printf("Start Getting Data...\n\n");
    FILE* outputtxt = fopen("outputTimeuse.txt", "a+");
    fprintf(outputtxt, "x\ty\tTraceback\tTime/sec\n");
    fclose(outputtxt);

    for (int x = 0; x < BOARDSIZE; x++) {
        for (int y = 0; y < BOARDSIZE; y++) {
            //初始化棋盘
            for (int i = 0; i < BOARDSIZE; i++) {
                for (int j = 0; j < BOARDSIZE; j++) {
                    ChessBoard[i][j] = 0;
                }
            }
            getPath(x, y);  //迷宫寻路核心算法
            printf("Finished (%d,%d)\n", x, y);
        }
    }
    printf("\nDone!\n");
#endif
#endif

    return 0;
}
