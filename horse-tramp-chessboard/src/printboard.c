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
    }  
    //先把栈中储存的按顺序的64步赋给一个8*8数组，以便打印棋盘
    //这个栈通过这个循环被清空。清空之后结束getPath()中的循环。

    const char s1[100] = "          ┌──┬──┬──┬──┬──┬──┬──┬──┐\n";
    const char s2[100] = "          ├──┼──┼──┼──┼──┼──┼──┼──┤\n";
    char* sPrint = s1;
    //按行序依次打印出棋盘，结合上述数组打印出相应位置中的步数
    printf("棋盘表示:  0  1  2  3  4  5  6  7\n");
    for (int j = 0; j < BOARDSIZE; j++) {
        printf("%s", sPrint);
        sPrint = s2;
        printf("         %d", j);
        for (i = 0; i < BOARDSIZE; i++) {
            printf("│");
            if (c[j][i] < 10)
                printf(" ");
            printf("%d", c[j][i]);
        }
        printf("│\n");
    }
    printf("          └──┴──┴──┴──┴──┴──┴──┴──┘\n\n");
}