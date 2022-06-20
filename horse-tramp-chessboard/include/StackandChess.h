
// ************* 模式选择，必须注释掉恰好一行 ************* //
// 如果注释两行，那么自动进入命令行演示
#define DEMONSTRATE_  //命令行演示
//#define GETDATA_      //获取所有回溯&时间信息，写入evaluation.txt

// ************* 基本参数 ************* //
#define BOARDSIZE 8
#define STACKINITSIZE 100
#define STACKINCREMENT 2

// ************* 定义数据结构 ************* //
typedef struct chess {
    int x;  //表示行 i
    int y;  //表示列 j
    int z;  //表示方向数
} chess;

typedef struct Sqstack {
    chess* base;
    chess* top;
    int stacksize;
} Sqstack;

// ************* Declare external variables ************* //
#ifndef ISMAIN
#define ISMAIN
extern int ChessBoard[BOARDSIZE][BOARDSIZE];  //用8*8的全局数组表示棋盘
extern chess HTry[8];                         //有可能会走的八个方向

extern int Weight[BOARDSIZE][BOARDSIZE];               //对棋盘上的每一个点都赋贪心算法的权值
extern int SqWeight[BOARDSIZE][BOARDSIZE][BOARDSIZE];  //给棋盘上每个点可能走的方向按权值排序
#endif

// ************* 基本函数 ************* //
int isOnboard(int x, int y);  //判断是否在棋盘上
void weight();                //赋权值函数
void weight_sort();           //给8方向排序权值函数

void getPath(int x, int y);   //非递归马踏飞燕函数
void printBoard(Sqstack* s);  //打印出带数据的棋盘

// ************* 栈操作函数 ************* //
int initStack(Sqstack* S);
void destroyStack(Sqstack** sptr);
int push(Sqstack* S, chess e);
int pop(Sqstack* S, chess* e);
int changeTop(Sqstack* S, chess e);
int getTop(Sqstack S, chess* e);
int stackEmpty(Sqstack S);
