#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "StackandChess.h"

int initStack(Sqstack* S) {
    S->base = (chess*)malloc(STACKINITSIZE * sizeof(chess));
    if (!S->base)
        return -1;
    S->top = S->base;
    S->stacksize = STACKINITSIZE;
    return 1;
}

int push(Sqstack* S, chess e) {
    *(S->top)++ = e;
    return 1;
}

int pop(Sqstack* S, chess* e) {
    if (S->top == S->base)
        return 0;
    *e = *(--S->top);
    return 1;
}

int changeTop(Sqstack* S, chess e) {
    if (S->top == S->base)
        return 0;
    else {
        *(S->top - 1) = e;
        return 1;
    }
}

int getTop(Sqstack S, chess* e) {
    if (S.top == S.base)
        return 0;
    else {
        *e = *(S.top - 1);
        return 1;
    }
}

int stackEmpty(Sqstack S) {
    if (S.base == S.top)
        return 1;
    else
        return 0;
}