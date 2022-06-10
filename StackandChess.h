#define BOARDSIZE 8
#define STACKINITSIZE 100 
#define STACKINCREMENT 2

typedef struct chess
{
	int x;   //表示行 i
	int y;   //表示列 j
	int z;   //表示方向数
} chess;


typedef struct Sqstack{
    chess *base;
    chess *top;
    int stacksize;
}Sqstack;


int ChessBoard[BOARDSIZE][BOARDSIZE];  //用8*8的全局数组表示棋盘
chess HTry[8];       //有可能会走的八个方向


int Weight[BOARDSIZE][BOARDSIZE];  //对棋盘上的每一个点都赋贪心算法的权值
int SqWeight[BOARDSIZE][BOARDSIZE][8];  //给棋盘上每个点可能走的方向按权值排序



int isOnboard(int x, int y); //判断是否在棋盘上
void weight();  //赋权值函数
void weight_sort();  //给8方向排序权值函数


void getPath(int x, int y);  //非递归马踏飞燕函数
void printBoard(Sqstack *s);  //打印出带数据的棋盘


//栈的操作
int initStack(Sqstack *S);
int push(Sqstack *S, chess e);
int pop(Sqstack *S, chess *e);
int changeTop(Sqstack *S, chess e);
int getTop(Sqstack S, chess *e);
int stackEmpty(Sqstack S);
