#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "StackandChess.h"

void printBoard(Sqstack* s)  //打印函数
{
    int c[BOARDSIZE][BOARDSIZE] = {0};
    int k = BOARDSIZE * BOARDSIZE;
    int i = 0;
    chess e;
    while (!stackEmpty(*s)) {
        pop(s, &e);
        c[e.x][e.y] = k;
        k--;
    }  //先把栈中储存的按顺序的64步赋给一个8*8数组，以便打印棋盘

    //一下按行顺序依次打印出棋盘，结合上述数组打印出相应位置中的步数
    printf("棋盘表示: 0   1   2   3   4   5   6   7\n");
    printf("        ┌─┬─┬─┬─┬─┬─┬─┬─┐\n");
    printf("       0");
    for (i = 0; i < BOARDSIZE; i++) {
        if (c[0][i] < 10)
            printf("│ %d", c[0][i]);
        else
            printf("│%d", c[0][i]);
    }
    printf("│\n");

    printf("        ├─┼─┼─┼─┼─┼─┼─┼─┤\n");
    printf("       1");
    for (i = 0; i < BOARDSIZE; i++) {
        if (c[1][i] < 10)
            printf("│ %d", c[1][i]);
        else
            printf("│%d", c[1][i]);
    }
    printf("│\n");

    printf("        ├─┼─┼─┼─┼─┼─┼─┼─┤\n");
    printf("       2");
    for (i = 0; i < BOARDSIZE; i++) {
        if (c[2][i] < 10)
            printf("│ %d", c[2][i]);
        else
            printf("│%d", c[2][i]);
    }
    printf("│\n");

    printf("        ├─┼─┼─┼─┼─┼─┼─┼─┤\n");
    printf("       3");
    for (i = 0; i < BOARDSIZE; i++) {
        if (c[3][i] < 10)
            printf("│ %d", c[3][i]);
        else
            printf("│%d", c[3][i]);
    }
    printf("│\n");

    printf("        ├─┼─┼─┼─┼─┼─┼─┼─┤\n");
    printf("       4");
    for (i = 0; i < BOARDSIZE; i++) {
        if (c[4][i] < 10)
            printf("│ %d", c[4][i]);
        else
            printf("│%d", c[4][i]);
    }
    printf("│\n");

    printf("        ├─┼─┼─┼─┼─┼─┼─┼─┤\n");
    printf("       5");
    for (i = 0; i < BOARDSIZE; i++) {
        if (c[5][i] < 10)
            printf("│ %d", c[5][i]);
        else
            printf("│%d", c[5][i]);
    }
    printf("│\n");

    printf("        ├─┼─┼─┼─┼─┼─┼─┼─┤\n");
    printf("       6");
    for (i = 0; i < BOARDSIZE; i++) {
        if (c[6][i] < 10)
            printf("│ %d", c[6][i]);
        else
            printf("│%d", c[6][i]);
    }
    printf("│\n");

    printf("        ├─┼─┼─┼─┼─┼─┼─┼─┤\n");
    printf("       7");
    for (i = 0; i < BOARDSIZE; i++) {
        if (c[7][i] < 10)
            printf("│ %d", c[7][i]);
        else
            printf("│%d", c[7][i]);
    }
    printf("│\n");

    printf("        └─┴─┴─┴─┴─┴─┴─┴─┘\n");
}