#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "StackandChess.h"

void getPath(int x, int y) {
    clock_t timeStart, timeEnd;
    timeStart = clock();  // timing
    unsigned int timesTraceback = 0;

    Sqstack* s = (Sqstack*)malloc(sizeof(Sqstack));
    initStack(s);

    chess loc,     //当前位置
        next_loc,  //下个位置
        pop_loc,   //回溯过程中的上个位置
        top_loc,   //当前栈的top储存位置
        temp;      //中间储存位置

    int step = 0;  //统计步数
    int x1, y1, d, m;

    //放上第一个位置，入栈并把步数加一
    ChessBoard[x][y] = 1;
    loc.x = x;
    loc.y = y;
    loc.z = 0;
    push(s, loc);
    step++;

    while (1) {
        if (step == 64)  //到64步走完就打印
        {
#ifdef DEMONSTRATE_
            printBoard(s);
#endif

#ifdef GETDATA_
#ifndef DEMONSTRATE_
            timeEnd = clock();
            FILE* outputtxt = fopen("outputTimeuse.txt", "a+");
            fprintf(outputtxt, "%d\t%d\t%u\t", x, y, timesTraceback);
            fprintf(outputtxt, "%lf\n", (((double)(timeEnd - timeStart)) / CLOCKS_PER_SEC));
            fclose(outputtxt);
            break;
#endif
#endif
        }
        if (stackEmpty(*s))  //栈空结束算法
            break;

        // ** main algorithm ** //

        getTop(*s, &loc);  //每次初都把当前栈顶的chess赋给loc
        x1 = loc.x;
        y1 = loc.y;
        d = loc.z;

        if (d >= 8) {  //当前棋子走完所有八个方向时，要进行回溯，即退栈（把当前步返回），并给上一步方向加一继续循环
            ChessBoard[x1][y1] = 0;
            --step;
            pop(s, &pop_loc);
            getTop(*s, &top_loc);
            temp.x = top_loc.x;
            temp.y = top_loc.y;
            temp.z = top_loc.z + 1;

            changeTop(s, temp);
            timesTraceback++;
        } else if (d < 8) {  //当前棋子没走完八个方向
            m = SqWeight[x1][y1][d];
            next_loc.x = x1 + HTry[m].x;
            next_loc.y = y1 + HTry[m].y;
            //按照排好序的权重数组算出最优的下个棋子放入next_loc

            //如果下个棋子在棋盘内且没走过，就走这一步并入栈
            if (isOnboard(next_loc.x, next_loc.y) && ChessBoard[next_loc.x][next_loc.y] == 0) {
                ChessBoard[x1][y1] = 1;
                step++;
                next_loc.z = 0;
                push(s, next_loc);
            } else {  //否则，给当前棋子换个方向（+1）继续循环
                temp.x = loc.x;
                temp.y = loc.y;
                temp.z = d + 1;
                changeTop(s, temp);
            }
        }
    }
    destroyStack(&s);
#ifdef DEMONSTRATE_
    timeEnd = clock();

    printf("Time used: %lf seconds.\n", (((double)(timeEnd - timeStart)) / CLOCKS_PER_SEC));  // print time use
    printf("Traced back %u times.\n\n", timesTraceback);                                      // print traceback times
#endif
}