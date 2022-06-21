#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "StackandChess.h"

int isOnboard(int x, int y) {
    if (x >= 0 && x <= BOARDSIZE - 1 && y >= 0 && y <= BOARDSIZE - 1)
        return 1;
    else
        return 0;
}

void swap(int* x, int* y) {
    int temp = *x;
    *x = *y;
    *y = temp;
}

//看看每个点的八方向中有几个方向走一步后还在棋盘上，并以此作为权值
void weight() {
    for (int i = 0; i < BOARDSIZE; i++) {
        for (int j = 0; j < BOARDSIZE; j++) {
            Weight[i][j] = 0;
            for (int k = 0; k < BOARDSIZE; k++) {
                if (isOnboard(i + HTry[k].x, j + HTry[k].y))
                    Weight[i][j]++;
            }
        }
    }
}

//本质是一个排序函数
//棋盘的每一个点都对应一个长度为8的一维数组
//这个一维数组按照weight()函数中的权值排序
//这使得对于点(i,j)，SqWeight[i][j][0]~[7]所代表的方向，权值依次降低
//也即，SqWeight[i][j][0]代表的方向权值最高！

void weight_sort() {
    int x1, x2, y1, y2, d1, d2;
    int p, q;
    for (int i = 0; i < BOARDSIZE; i++) {
        for (int j = 0; j < BOARDSIZE; j++) {
            for (p = 0; p < BOARDSIZE; p++) {
                SqWeight[i][j][p] = p;
            }
            for (p = 0; p < BOARDSIZE; p++) {
                for (q = p + 1; q < BOARDSIZE; q++) {
                    d1 = SqWeight[i][j][p];
                    d2 = SqWeight[i][j][q];
                    x1 = i + HTry[d1].x;
                    y1 = j + HTry[d1].y;
                    x2 = i + HTry[d2].x;
                    y2 = j + HTry[d2].y;

                    if ((!isOnboard(x1, y1) && isOnboard(x2, y2)) || (isOnboard(x1, y1) && isOnboard(x2, y2) && Weight[x1][y1] > Weight[x2][y2])) {
                        swap(&SqWeight[i][j][p], &SqWeight[i][j][q]);
                    }
                }
            }
        }
    }
}