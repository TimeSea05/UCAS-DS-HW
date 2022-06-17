/*本算法采取贪心算法对马踏棋盘算法进行优化，以减少回溯次数*/
#define ISMAIN
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "StackandChess.h"

int ChessBoard[BOARDSIZE][BOARDSIZE];  //用8*8的全局数组表示棋盘
chess HTry[8];                         //有可能会走的八个方向

int Weight[BOARDSIZE][BOARDSIZE];       //对棋盘上的每一个点都赋贪心算法的权值
int SqWeight[BOARDSIZE][BOARDSIZE][8];  //给棋盘上每个点可能走的方向按权值排序

// HTry数组以此存储了八个方向，其中每个方向中第三个元素‘0’只用于凑出chess结构且不增加getPath函数中的方向数
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

    while (1) {
        printf("输入起始点坐标：\n");
        scanf("%d %d", &x, &y);
        if (x >= 0 && x <= 7 && y >= 0 && y <= 7) {
            //初始化棋盘
            for (int i = 0; i < BOARDSIZE; i++) {
                for (int j = 0; j < BOARDSIZE; j++) {
                    ChessBoard[i][j] = 0;
                }
            }
            getPath(x, y);  //迷宫寻路核心算法
            printf("是否继续？如果是请输入1，否则输入0\n");
            scanf("%d", &z);
            if (z)
                continue;
            else
                break;
        } else
            printf("坐标不合要求，请重新输入\n");
    }

    return 0;
}
