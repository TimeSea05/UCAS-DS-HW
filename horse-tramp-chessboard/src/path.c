#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "StackandChess.h"

void getPath(int x,int y)
{
    Sqstack *s = (Sqstack*)malloc(sizeof(Sqstack));
    initStack(s);

    chess loc,next_loc,pop_loc,top_loc,temp;//依次表示棋盘上的当前位置，下个位置，回溯过程中的上个位置，当前栈的top储存位置，中间储存位置
    
    int step = 0;//统计步数
    int x1,y1,d,m;

    //放上第一个位置，入栈并把步数加一
    ChessBoard[x][y] = 1;
    loc.x = x;
    loc.y = y;
    loc.z = 0;
    push(s,loc);
    step++;

    while(1){
        if(step == 64)  //到64步走完就打印
            printBoard(s);
        if(stackEmpty(*s))  //栈空结束算法
            break;
        getTop(*s,&loc);  //每次初都把当前栈顶的chess赋给loc
        x1 = loc.x;
        y1 = loc.y;
        d = loc.z;

        if(d>=8){  //当前棋子走完所有八个方向时，要进行回溯，即退栈（把当前步返回），并给上一步方向加一继续循环
            ChessBoard[x1][y1] = 0;
            --step;
            pop(s,&pop_loc);
            getTop(*s,&top_loc);
            temp.x = top_loc.x;
            temp.y = top_loc.y;
            temp.z = top_loc.z + 1;

            changeTop(s,temp);
        }
        else if(d<8){  //当前棋子没走完八个方向
            m = SqWeight[x1][y1][d];
            next_loc.x = x1 + HTry[m].x;
            next_loc.y = y1 + HTry[m].y;
            //按照排好序的权重数组算出最优的下个棋子放入next_loc

            //如果下个棋子在棋盘内且没走过，就走这一步并入栈
            if(isOnboard(next_loc.x,next_loc.y) && ChessBoard[next_loc.x][next_loc.y]==0){
                ChessBoard[x1][y1] = 1;
                step++;
                next_loc.z = 0;
                push(s,next_loc);
            }
            else{     //否则，给当前棋子换个方向（+1）继续循环
                temp.x = loc.x;
                temp.y = loc.y;
                temp.z = d + 1;
                changeTop(s,temp);
            }
        }
    }

}